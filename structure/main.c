#include "common.h"











 
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	int fd;
	char buffer[BUFFER_SIZE];

	if(argc < 3){
		fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
		exit(1); 
	}
  
  char* request = generateGET("", argv[1], "luoyuc");
     
     
  
	fd = socket_connect(argv[1], atoi(argv[2])); 
	write(fd, request, strlen(request)); 
	bzero(buffer, BUFFER_SIZE);
	printf("\n\n%s\n\n", request);
 
	while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
		fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFFER_SIZE);
	}
 
	shutdown(fd, SHUT_RDWR); 
	close(fd); 

	return 0;
}
