#include "common.h"


#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	/*int fd;
	char buffer[BUFFER_SIZE];

	if(argc < 3){
		fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
		exit(1); 
	}
  */
 // char* request = generateGET("", argv[1], "luoyuc");
     
     
 
  //get_response(fd, "", argv[1], argv[2], "luoyuc");
  //get_html_start();
 // get_status_code();

 //extern initilization
char html_buffer[MAX_RESPONSE+1];
char *p_html_buffer = html_buffer;
char *web_addr[MAX_URL_NUM+1];
int addr_index = 0;
int html_cursor = 0;
char parent_domain_buffer[MAX_DOMAIN_LEN+1];
char input[MAX_DOMAIN_LEN+1] = "web1.comp30023";
 web_addr[0] = "web1.comp30023";
 
 FILE* fp = fopen("html.txt", "r");
 
 char symbol;
 int count = 0;
if(fp != NULL)
{
    while((symbol = getc(fp)) != EOF)
    {
        html_buffer[count++] = symbol;
    }
    fclose(fp);
}

 extract_matches();


	return 0;
}