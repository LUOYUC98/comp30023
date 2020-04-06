#include "common.h"

void sequential_visit(){
 for(int i = 0; addr_fetching_index<= MIN(addr_index, MAX_URL_NUM-1); i++){
      char* curr_url = web_addr[addr_fetching_index++];
      //printf("\n\n--------turn %d-------------\n\n", i);
      
      int status_code = get_response(get_path(curr_url), get_domain(curr_url), "80", "luoyuc");
      printf("正在访问第%d个网站: %s : %d\n",i,curr_url, status_code);
       // printf(" curr_fetching_index = %d, addr_index = %d, start to look: curr_url = %s\n",addr_fetching_index-1, addr_index, curr_url);
      //printf("code  = %d\n, content_type_is_text:%d\n", status_code,  content_type_is_text());
      
      if(status_code == 200 && content_type_is_text()){
        printf(" curr_fetching_index = %d, addr_index = %d, start to scan: curr_url = %s\n",addr_fetching_index-1, addr_index, curr_url);
        strcpy(parent_addr_buffer,curr_url);
        //print_parent_addr();
        extract_matches();
      //  print_cached_web_addr();
      }
    // printf("\n\n--------turn %d ended-------------\n\n", i);
  }
}


  
