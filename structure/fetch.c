#include "common.h"

#define MAX_URL_NUM 100
#define MAX_RESPONSE 10000
#define MAX_URL_LEN 10000
#define BUFF_SIZE 100

char*web_addr[MAX_URL_NUM+1];
char html_buffer[MAX_RESPONSE+1];


char* generateGET(char* path, char* addr, char*user_agent){
    char* request = (char*)malloc(sizeof(char)*200);
    sprintf(request, "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nContent-Type: text/plain\r\n\r\n", path, addr, user_agent);
    return request;


}


char* get_html(int fd, char* path, char* url, char* port_number, char* user_agent){
  char buffer[BUFF_SIZE+1];
  char* request = generateGET(path, url, user_agent);
	fd = socket_connect(url, atoi(port_number)); 
	write(fd, request, strlen(request)); 
	bzero(buffer, BUFF_SIZE);
	printf("\n\n%s\n\n", request);

  
	while(read(fd, buffer, BUFF_SIZE) != 0){
    strcpy(html_buffer, buffer);
    html_buffer += strlen(buffer);
    fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFF_SIZE);
	}
 
	shutdown(fd, SHUT_RDWR); 
	close(fd); 
  }
  
  
  
