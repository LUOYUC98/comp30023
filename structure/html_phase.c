#include "common.h"




void read_url(char* start){
    //printf("reading\n");
  char* track = start;
  int count = 0;
  while(*(track)!='\"'&& *(track)!='\''&& *(track)!='\r'){

    count++;
    track++;
    //printf("track at %c\n", *(track));
  }
  //printf("stuck!\n");
  strncpy(url_buffer, p_html_buffer, count);
  //printf("url_buufer = %s\n", url_buffer);
}

void extract_matches(){
  if(addr_index == MAX_URL_NUM-1){return;}
  regex_t regex;
  regmatch_t match_buffer[1];// match result
  
    int compile = regcomp(&regex, "<(a|A)[^>]+(href|HREF)(\\s)*?=(\\s)*?(\"|')", REG_EXTENDED);

  int result;
  
  
  
  while((result = regexec(&regex, p_html_buffer, 1, match_buffer, 0)) == 0){
     
     p_html_buffer += match_buffer->rm_eo;
   //  printf("here!!!!!!\n");
     read_url(p_html_buffer);
    //printf("match = %s\n", url_buffer);
     p_html_buffer += strlen(url_buffer);
     char* new_url = url_ok(url_buffer);
   // printf("%dth new_url = %s\n",addr_index, new_url);
    
    
   if(addr_index < MAX_URL_NUM && new_url!= NULL && need_crawl(new_url) && check_duplicate(new_url)==0){
      
      web_addr[++addr_index] = (char*)malloc(strlen(new_url)+1);
      strcpy(web_addr[addr_index], new_url);
      //  printf("here!\n");
    }
    bzero(url_buffer,  strlen(url_buffer));
    bzero(match_buffer, 1);
   // printf("hereherehere\n");
  }
  bzero(parent_addr_buffer, strlen(parent_addr_buffer));
  bzero(html_buffer, strlen(html_buffer));
 // printf("html_len = %zu\n", strlen(html_buffer));
  p_html_buffer = html_buffer;
  
}





