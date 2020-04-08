#include "common.h"

char* url_ok(char* url){
  //printf("url = %s\n", url);
   if(contain_punc(url) != 0 || strstr(url, "mailto:")!=NULL || strstr(url, "ftp")!=NULL){return NULL;}
  char* new_url = NULL;

  /*
  char* split = url+strlen(url)-1;
  while(*(split) == '/'){
   *(split--) = '\0';
  }
  */
  
    //complete url

   //complete url
   /*
   if(strstr(url, "http://www.")!=NULL){
    return strstr(url, "http://www.")+strlen("http://www.");
  }
   */
  if(strstr(url, "https://")!=NULL){
    return strstr(url, "https://")+strlen("https://");
  }
  
  
  else if(strstr(url, "http://")!=NULL){
    //printf("complete!!!!\n");
    return strstr(url, "http://")+strlen("http://");
  }

   //complete url
   /*
   else if(strstr(url, "www.")!=NULL){
    return strstr(url, "www.")+strlen("www.");
  }
*/




  //if // appears, simply get the followings
  else if (url[0]=='/' && url[1]=='/'){
    return url+2;
    
  }
  
  //just give full path
  else if (url[0]=='/'){
    
    char* parent_domain = get_domain(parent_addr_buffer);
    new_url = (char*)malloc(strlen(parent_domain)+strlen(url)+1);
    strcpy(new_url, parent_domain);
    strcat(new_url+strlen(parent_domain), url);
    //free(parent_domain);
    return new_url;
  }
  
  else if (isalpha(url[0])){
    new_url = (char*)malloc(strlen(parent_addr_buffer)+strlen(url)+1+1);
    char* parent_url = get_parent_url(parent_addr_buffer);
    strcpy(new_url, parent_url);
    strcpy(new_url+strlen(parent_url), url);
    return new_url;
  }

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
  return new_url;
}


char* get_path(char* url){
  char*p;
  if((p = get_domain(url))!= NULL){
      return strstr(url, p)+strlen(p);
  }
  return url;
}

int contain_punc(char* url){
 
  return strstr(url, "..") != NULL||strstr(url, "./") != NULL || strstr(url, "#") != NULL ||
         strstr(url, "?") != NULL || strstr(url, "%") != NULL;
}


int check_duplicate(char* url){
  int count = 0;
  for(int i = 0; i<= addr_index; i++){
    if(strcmp(url, web_addr[i]) == 0){
      count++;
      }
  }
  return count;
}

//assume url is complete url
int need_crawl(char* url){
  char* url_domain = get_domain(url);
  char* input_domain = get_domain(input);
  return !strcmp(strstr(url_domain, "."),strstr(input_domain, "."));
}






char* get_parent_url(char* curr_fetching_url){ 

  if(strstr(curr_fetching_url, "/") == NULL
  || curr_fetching_url[strlen(curr_fetching_url)-1] == '/'){
    //printf("NO need chunking: parent url = %s\n", curr_fetching_url);
    return curr_fetching_url;
    }
    char* split = curr_fetching_url+strlen(curr_fetching_url)-1;
    while(*(split)!='/'){
      split--;
    }
    while(*(split)=='/'){
     // printf("split: %s\n", split);
      split--;
    }
    char* curr_url_chunk = malloc(strlen(curr_fetching_url));
    strncpy(curr_url_chunk, curr_fetching_url, split - curr_fetching_url+1);
    curr_url_chunk[strlen(curr_url_chunk)] = '/';

    //bzero(split+1, sizeof(split));
   // printf("need parent url = %s\n", url);
    return curr_url_chunk;
}

