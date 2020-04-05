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
#include <ctype.h>
#include <regex.h>
#define MAX_URL_NUM 100
#define MAX_RESPONSE 10000
#define MAX_URL_LEN 10000
#define BUFF_SIZE 100
#define MAX_DOMAIN_LEN 253
#define MAX(a,b) (((a)>(b))?(a):(b))


//global variable
extern char html_buffer[MAX_RESPONSE+1];
extern char* p_html_buffer;
extern char*web_addr[MAX_URL_NUM+1];
extern int addr_index;
extern int addr_fetching_index;

extern char parent_addr_buffer[MAX_URL_LEN+1];
extern char input[MAX_DOMAIN_LEN+1];


//connect.c
int socket_connect(char *host, in_port_t port);

//fetch.c
char* generateGET(char* path, char* addr, char*user_agent);
void get_response(char* path, char* domain, char* port_number, char* user_agent);
char* get_html_start();
int get_status_code();
int contain_punc(char* path);
char* get_path(char* url);
char* get_domain(char * url);
char* url_ok(char* url);
int check_duplicate(char* url);
int need_crawl(char* url);
int not_truncated();
int content_type_is_text();
char* get_parent_url(char* url);
//html_phase.c
void extract_matches();


//rec_request.c

void sequential_visit();
//debug.c
void print_cached_web_addr();
void print_parent_addr();
void print_html_buffer();
