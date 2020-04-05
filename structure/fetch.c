#include "common.h"




char* generateGET(char* path, char* addr, char*user_agent){
    char* request = (char*)malloc(sizeof(char)*MAX_URL_LEN*2);
    sprintf(request, "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nContent-Type: text/plain\r\n\r\n", path, addr, user_agent);
   // printf("\nrequest:%s\n", request);
    return request;


}


void get_response(char* path, char* domain, char* port_number, char* user_agent){
  
  char buffer[BUFF_SIZE+1];
  char* request = generateGET(path, domain, user_agent);
 // printf("domain = %s\n", domain);
	int fd = socket_connect(domain, atoi(port_number)); 
 
	write(fd, request, strlen(request)); 
 
	bzero(buffer, BUFF_SIZE);
//	printf("\n\n%s\n\n", request);
  

	while(read(fd, buffer, BUFF_SIZE) != 0){
    strcpy(p_html_buffer, buffer);
    p_html_buffer += strlen(buffer);
    fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFF_SIZE);
	}
   
  printf("\n\n%s\n", html_buffer);

  if(get_status_code() == 200){
  printf("you stuck here?\n");
    strcpy(parent_addr_buffer, domain);
  }
  
	shutdown(fd, SHUT_RDWR); 
	close(fd); 
  free(request);
  
  }
  

  
char* get_html_start(){
    char* start = strstr(html_buffer, "\n\n")+strlen("\n\n");
    if(start == NULL){printf("\n\nNOT FOUND\n\n");}

   return start;
}
 


int get_status_code(){
 //
  char* start = strstr(html_buffer, "HTTP/1.0 ");
  
  if(start == NULL){
    start = strstr(html_buffer, "HTTP/1.1 ");
  }
  printf("start = %s\n", start);
  start += strlen("HTTP/1.1 ");
   
  
  char code_str[3] = {start[0], start[1], start[2]};
  
  int code = atoi(code_str);
  printf("\nstatus code: %d\n", code);
  return code;
}



  int not_truncated(){
  //printf("addawda\n");
    char* content_length = strstr(html_buffer, "Content-Length: ")+strlen("Content-Length: ");
    char length_char[5];
    int i;
    while(isdigit(content_length[i++]) != 0);
    for(int j = 0; j<i; j++){
      length_char[j] = content_length[j];
    }
    int length = atoi(length_char);
    char* html_start = get_html_start();
   // printf("cmp: strlen(html_start):%zu length:%d\n", strlen(html_start), length);
    return strlen(html_start) == length;

}





int content_type_is_text(){

 return strstr(html_buffer, "Content-Type: text/html") != NULL;
}




char* url_ok(char* url){
// check #?. in path
  if(contain_punc(url) != 0){return NULL;}
  char* new_url = NULL;
  //complete url
  if(strstr(url, "http://")!=NULL){
   // printf("find http: \n");
    //printf("url_ok = %s\n", strstr(url, "http://")+strlen("http://"));
    return strstr(url, "http://")+strlen("http://");
  }
 
  //if // appears, simply get the followings
  else if (strstr(url, "//") != NULL){
   // printf("url_ok = %s\n", strstr(url, "//")+strlen("//"));
    return strstr(url, "//")+strlen("//");
    
  }
  
  //just give full path
  else if (url[0]=='/'){
    char* parent_domain = get_domain(parent_addr_buffer);
    new_url = (char*)malloc(strlen(parent_domain)+strlen(url)+1);
    strcpy(new_url, parent_domain);
    strcat(new_url, url);
    //printf("url_ok = %s\n", new_url);
  }
  
  else if (isalpha(url[0])){
    new_url = (char*)malloc(strlen(parent_addr_buffer)+strlen(url)+1+1);
    strcpy(new_url, parent_addr_buffer);
    if(parent_addr_buffer[strlen(parent_addr_buffer)-1] != '/'){
      new_url[strlen(parent_addr_buffer)] = '/';
    }
    strcpy(new_url, url);
    //printf("url_ok = %s\n", new_url);
    return new_url;
  }
  
    printf("unexpected url: %s\n", url);

  return NULL;
}


char* get_domain(char * url){
  char* new_url = NULL;
  regex_t regex;  
  regmatch_t match[1];
  regcomp(&regex, "[a-zA-Z0-9.-]+\\.[a-zA-Z0-9]+", REG_EXTENDED);
  int result = regexec(&regex, url, 1, match, 0);
  if(result == 0){
    new_url = (char*)malloc(MAX_DOMAIN_LEN+1);
    strncpy(new_url, url+match[0].rm_so, match[0].rm_eo - match[0].rm_so);
  }
  printf("domain: %s\n", new_url);
  
  return new_url;
}


char* get_path(char* url){
  printf("url = %s\n", url);
  char*p;
  if((p = get_domain(url))!= NULL){
    printf("with domain path = %s\n", strstr(url, p)+strlen(p));
    return strstr(url, p)+strlen(p);
  }
  printf("no domain path = %s\n", url);
  return url;
}


int contain_punc(char* url){
  return strstr(url, "./") != NULL || strstr(url, "#") != NULL ||
         strstr(url, "?") != NULL;
}


int check_duplicate(char* url){
  for(int i = 0; i<= addr_index; i++){
    //printf("checking: %s\n\n", web_addr[i]);
    if(strcmp(url, web_addr[i]) == 0){return 0;}
  }
  return 1;
}

//assume url is complete url
int need_crawl(char* url){
  char* url_domain = get_domain(url);
  char* input_domain = get_domain(input);
  return !strcmp(strstr(url_domain, "."),strstr(input_domain, "."));
}

char* get_parent_url(char* url){  
  if(strstr(url, "/") == NULL){return url;}
  char* split = url+strlen(url)-1;
  
    while(*(--split)!='/');
    while(*(--split)=='/');
    char* pure_path = (char*)malloc(split - url + 1);
    //printf("reach: %s\n", split);
    return strncpy(pure_path, url, split - url+1);


}
