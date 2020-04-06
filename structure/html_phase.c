#include "common.h"




void read_url(char* start){
  char* track = start;
  int count = 0;
  while(*(track)!='\"'&& *(track)!='\''){
    count++;
    track++;
  }
  
  strncpy(url_buffer, p_html_buffer, count);
  
}


void extract_matches(){
  if(addr_index == MAX_URL_NUM-1){return;}
  regex_t regex;
  regmatch_t match_buffer[1];// match result
  char buff[100];
    int compile = regcomp(&regex, "<(a|A)[^>]+(href|HREF)=(\"|')", REG_EXTENDED);

  int result;
  printf("result = %d\n", regexec(&regex, p_html_buffer, 1, match_buffer, 0));
  
  
  while((result = regexec(&regex, p_html_buffer, 1, match_buffer, 0)) == 0){
     bzero(match_buffer, 1);
     p_html_buffer += match_buffer->rm_eo;
     printf("match: %s\n", url_buffer);
     read_url(p_html_buffer);
     p_html_buffer += strlen(url_buffer);
     char* new_url = url_ok(url_buffer);
   if(addr_index < MAX_URL_NUM && new_url!= NULL && need_crawl(new_url) && check_duplicate(new_url)!=0){
      web_addr[++addr_index] = (char*)malloc(strlen(new_url)+1);
      strcpy(web_addr[addr_index], new_url);
    }
    bzero(url_buffer,  strlen(url_buffer));
  }
  bzero(parent_addr_buffer, strlen(parent_addr_buffer));
  bzero(html_buffer, strlen(html_buffer));
 
  p_html_buffer = html_buffer;
  
}





