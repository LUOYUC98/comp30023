#include "common.h"




void generateGET(char* path, char* addr, char*user_agent, int auth){
  //printf("auth  = %d\n", auth);
  if(auth == 0){
    sprintf(request, "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nContent-Type: text/plain\r\n\r\n", path, addr, user_agent);
    return;
  }
  if(auth == 1){
  sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nContent-Type: text/plain\r\nAuthorization: Basic Z3Vlc3Q6Z3Vlc3Q=\r\n\r\n", path, addr, user_agent);
  return;
  }
}

  
  int get_response( char* domain){
 
  char buffer[BUFF_SIZE+1];
  //printf("\n\n%s\n\n", request);
	int fd = socket_connect(domain, 80); 
	write(fd, request, strlen(request)); 
	bzero(buffer, BUFF_SIZE);
  bzero(request, strlen(request));
	int status_Code;
  
  
	while(read(fd, buffer, BUFF_SIZE) != 0){
    strcpy(p_html_buffer, buffer);
    p_html_buffer += strlen(buffer);
   // fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFF_SIZE);
    
    if(strlen(html_buffer) >49000){
      //printf("overload!!!!\n");
      break;
      status_Code = 0;
    }
  // read(fd, html_buffer, strlen(html_buffer)) 

//printf("length:%zu\n",strlen(html_buffer));
	
  //char headerResponse[300];
  //int len = get_html_start(html_buffer) - html_buffer;
  //strncpy(headerResponse, html_buffer, len);
  //printf("\n\n%s\n", get_html_start(html_buffer));
  }
//  printf("length:%zu\n",strlen(html_buffer));

	shutdown(fd, SHUT_RDWR); 
	close(fd); 
  status_Code = get_status_code();
 
  
  p_html_buffer = html_buffer;
  return status_Code;
  }
  
  

  
char* get_html_start(){
    char* start = strstr(html_buffer, "\r\n\r\n")+strlen("\r\n\r\n");
    if(start == NULL){printf("\n\nNOT FOUND\n\n");}
    
   return start;
}
 

