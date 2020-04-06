#include "common.h"


 //extern initilization
char html_buffer[5*MAX_RESPONSE+1];
char *p_html_buffer = html_buffer;
char *web_addr[MAX_URL_NUM+1];
int addr_index = 0;
int addr_fetching_index = 0;
char url_buffer[MAX_URL_LEN+1];
char parent_addr_buffer[MAX_URL_LEN+1];
char input[MAX_DOMAIN_LEN+1];
char request[200];

int main(int argc, char *argv[]){
	
  
	if(argc < 2){
		fprintf(stderr, "Usage: %s <hostname> \n", argv[0]);
		exit(1); 
	}
  
  strcpy(input, url_ok(argv[1]));
  web_addr[addr_index] = url_ok(argv[1]);
  sequential_visit();


	return 0;
}
