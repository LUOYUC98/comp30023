#include "common.h"




char* read_url(char* start){
  char* track = start;
  int count = 0;
  while(*(track)!='\"'&& *(track)!='\''){
    count++;
    track++;
  }
  char* url = (char*)malloc(count+1);
  strncpy(url, html_buffer+html_cursor, count);
  
  return url;
}


void extract_matches(){
  regex_t regex;
  regmatch_t match_buffer[1];// match result
  char buff[100];
  int compile = regcomp(&regex, "<(a|A)[^>]+(href|HREF)=(\"|')", REG_EXTENDED);
  int result;

  while((result = regexec(&regex, html_buffer+html_cursor, 1, match_buffer, 0)) == 0){
     bzero(match_buffer, 1);
     char* start = html_buffer + html_cursor + match_buffer->rm_eo;
     html_cursor += match_buffer->rm_eo;
     char* fetched_url = read_url(start);
     html_cursor += strlen(fetched_url);
     printf("match = %s\n",fetched_url);
     char* new_url = url_ok(fetched_url);
   if(addr_index < MAX_URL_NUM && new_url!= NULL && need_crawl(new_url) && check_duplicate(new_url)!=0){
      web_addr[++addr_index] = (char*)malloc(strlen(new_url)+1);
      strcpy(web_addr[addr_index], new_url);
    }
  }
  bzero(parent_addr_buffer, strlen(parent_addr_buffer));
  bzero(html_buffer, strlen(html_buffer));

}





