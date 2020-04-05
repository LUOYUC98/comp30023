#include "common.h"


 //extern initilization
char html_buffer[MAX_RESPONSE+1];
char *p_html_buffer = html_buffer;
char *web_addr[MAX_URL_NUM+1];
int addr_index = 0;
int addr_fetching_index = 0;
int html_cursor = 0;
char parent_addr_buffer[MAX_URL_LEN+1];
char input[MAX_DOMAIN_LEN+1] = "web1.comp30023";


int main(int argc, char *argv[]){

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
printf("len = %lu\n", strlen(html_buffer));
 

	return 0;
}
