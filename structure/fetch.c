#include "common.h"




void generateGET(char* path, char* addr, char*user_agent){
    sprintf(request, "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nContent-Type: text/plain\r\n\r\n", path, addr, user_agent);
}

  
  int get_response( char* path, char* domain, char* port_number, char* user_agent){
  
  char buffer[BUFF_SIZE+1];
  generateGET(path, domain, user_agent);
	int fd = socket_connect(domain, atoi(port_number)); 
	write(fd, request, strlen(request)); 
	bzero(buffer, BUFF_SIZE);
  bzero(request, 200);
	//printf("\n\n%s\n\n", request);
  
  
	while(read(fd, buffer, BUFF_SIZE) != 0){
    strcpy(p_html_buffer, buffer);
    p_html_buffer += strlen(buffer);
    fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFF_SIZE);
    if(p_html_buffer - html_buffer >49000){break;}
	}
  //char headerResponse[300];
  //int len = get_html_start(html_buffer) - html_buffer;
 // strncpy(headerResponse, html_buffer, len);
 // printf("\n\n%s\n", get_html_start(html_buffer));
  
  
	shutdown(fd, SHUT_RDWR); 
	close(fd); 
  int status_Code = get_status_code();
  if(p_html_buffer - html_buffer >49000){
    status_Code = 404;
  }
  p_html_buffer = html_buffer;
  return status_Code;
  }
  
  

  
char* get_html_start(){
    char* start = strstr(html_buffer, "\r\n\r\n")+strlen("\r\n\r\n");
    if(start == NULL){printf("\n\nNOT FOUND\n\n");}
    
   return start;
}
 

