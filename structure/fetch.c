#include "common.h"



char* generateGET(char* path, char* addr, char*user_agent){
    char* request = (char*)malloc(sizeof(char)*200);
    sprintf(request, "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nContent-Type: text/plain\r\n\r\n", path, addr, user_agent);
    return request;


}


void get_response(int fd, char* path, char* domain, char* port_number, char* user_agent){
  
  char buffer[BUFF_SIZE+1];
  char* request = generateGET(path, domain, user_agent);
	fd = socket_connect(domain, atoi(port_number)); 
	write(fd, request, strlen(request)); 
	bzero(buffer, BUFF_SIZE);
	printf("\n\n%s\n\n", request);
  
  
	while(read(fd, buffer, BUFF_SIZE) != 0){
    strcpy(p_html_buffer, buffer);
    p_html_buffer += strlen(buffer);
    fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFF_SIZE);
	}
  printf("\n\n%s", html_buffer);

  if(get_status_code() == 200){
    strcpy(parent_domain_buffer, domain);
  }
	shutdown(fd, SHUT_RDWR); 
	close(fd); 
  free(request);
  }
  

  
char* get_html_start(){
    char* start = strstr(html_buffer, "\r\n\r\n");
    if(start == NULL){printf("\n\nNOT FOUND\n\n");}
    printf("\n\nHTML:\n%s\n\n", start);
   return start;
}
 


int get_status_code(){
  char* start = strstr(html_buffer, "HTTP/1.0 ");
  if(start == NULL){
    start = strstr(html_buffer, "HTTP/1.1 ");
  }
  start += strlen("HTTP/1.1 ");
  char code_str[3] = {start[0], start[1], start[2]};
  int code = atoi(code_str);
  printf("\nstatus code: %d\n", code);
  return code;
}
  


int content_type_is_text(){
 return strstr(html_buffer, "Content-Type: text/html") != NULL;
}


char* url_ok(char* domain, char* url_str){
// check #?. in path
  if(contain_punc(get_path(url_str)) != 0){return NULL;}
  char* new_url = NULL;
  //complete url
  if(get_domain(url_str)!=NULL){
    new_url = (char*)malloc(MAX_DOMAIN_LEN+1);
    domain = NULL;
    strcpy(new_url, url_str);
  }
  char* p;
  //if // appears, simply get the followings
  if((p = strstr(url_str, "//")) != NULL){
    new_url = (char*)malloc(MAX_DOMAIN_LEN+1);
    strcpy(new_url, p+2);
    
  }
  
  //just give path
  else if (url_str[0]=='/'){
    
    new_url = (char*)malloc(MAX_DOMAIN_LEN+1);
    strcpy(new_url, domain);
    strcat(new_url, url_str);
    
  }
  
  if(strstr(new_url,"http://")!=NULL){
    new_url+=strlen("http://");
  }

  printf("url_ok = %s\n", new_url);
  return new_url;
  
}


char* get_domain(char * url){
  char* new_url = NULL;
  regex_t regex;  
  regmatch_t match[1];
  regcomp(&regex, "[a-zA-Z0-9.-]+\\.[a-zA-Z]+", REG_EXTENDED);
  int result = regexec(&regex, url, 1, match, 0);
  if(result == 0){
    new_url = (char*)malloc(MAX_DOMAIN_LEN+1);
    strncpy(new_url, url+match[0].rm_so, match[0].rm_eo - match[0].rm_so);
  }

  return new_url;
}


char* get_path(char* url){
  char*p;
  if((p = get_domain(url))!= NULL){
    return strstr(url, p)+strlen(p);
  }
  return url;
}


int contain_punc(char* path){
  return strstr(path, "./") != NULL || strstr(path, "#") != NULL ||
         strstr(path, "?") != NULL;
}


int check_duplicate(char* url){
  for(int i = 0; i<= addr_index; i++){
    printf("checking: %s\n\n", web_addr[i]);
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


