#include"common.h"

int get_status_code(){
 
  char* start = strstr(html_buffer, "HTTP/1.0 ");
  
  if(start == NULL){
    start = strstr(html_buffer, "HTTP/1.1 ");
  }
  start += strlen("HTTP/1.1 ");
   
  
  char code_str[3] = {start[0], start[1], start[2]};
  
  int code = atoi(code_str);
  return code;
}


  int not_truncated(){
    char* content_length = strstr(html_buffer, "Content-Length: ")+strlen("Content-Length: ");
    char length_char[5];
    int i;
    while(isdigit(content_length[i++]) != 0);
    for(int j = 0; j<i; j++){
      length_char[j] = content_length[j];
    }
    int length = atoi(length_char);
    char* html_start = get_html_start();
    return strlen(html_start) == length;

}


int content_type_is_text(){
 return strstr(html_buffer, "Content-Type: text/html") != NULL ||  strstr(html_buffer, "content-type: text/html") != NULL;
}


char* get_location_301(){
    
    // printf("html_buffer = %s\n", html_buffer);
   

     char*  start = strstr(html_buffer, "ocation: ")+strlen("ocation: ");
    
    p_html_buffer = start;
    
    int count = 0;
    while(*(start)!='\"'&& *(start)!='\''&& *(start)!='\r'){
      
      count++;
      start++;
    }
  char* redirect = (char*)malloc(count+1);
  strncpy(redirect, p_html_buffer, count);
  return redirect;
}

int get_auth_type(){
   
    char* basic = strstr(html_buffer, ": Basic");
    if(basic!=NULL){return 1;}

    return 0;
}
