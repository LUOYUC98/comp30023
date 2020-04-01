#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>


//connect.c
int socket_connect(char *host, in_port_t port);

//fetch.c
char* generateGET(char* path, char* addr, char*user_agent);

//
