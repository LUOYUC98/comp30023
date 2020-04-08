#include "common.h"







void sequential_visit(){
 for(int i = 0;addr_fetching_index<= MIN(addr_index, MAX_URL_NUM-1); i++){
      int auth = authes[addr_fetching_index];
      char* curr_url = web_addr[addr_fetching_index++];
      //printf("\n\n--------turn %d-------------\n\n", i);
      
      generateGET(get_path(curr_url), get_domain(curr_url), "luoyuc", auth);
      
      int status_code = get_response(get_domain(curr_url));
      printf("正在访问第%d个网站: %s : %d\n",i,curr_url, status_code);

      
      if(status_code == 200 && content_type_is_text()){
       // printf(" curr_fetching_index = %d, addr_index = %d, start to scan: curr_url = %s\n",addr_fetching_index-1, addr_index, curr_url);
        strcpy(parent_addr_buffer,curr_url);
        //print_parent_addr();
        extract_matches();
       // print_cached_web_addr();
      }

      else if((status_code == 404 || status_code == 410 ||status_code == 414) && content_type_is_text()){
        strcpy(parent_addr_buffer,curr_url);
        extract_matches();
      }

      else if((status_code == 503 ||status_code == 504) && content_type_is_text() && check_duplicate(curr_url)<=2){
        web_addr[++addr_index] = (char*)malloc(strlen(curr_url)+1);
        strcpy(web_addr[addr_index], curr_url);
        strcpy(parent_addr_buffer,curr_url);
        extract_matches();
      }

      else if(status_code == 301){ 
        //print_cached_web_addr();
        char* redirect_raw = get_location_301();
        //printf("redirect raw = %s\n", redirect_raw);

        char* redirect = url_ok(redirect_raw);
        printf("redirect to = %s\n", redirect);
        web_addr[++addr_index] = (char*)malloc(strlen(redirect)+1);
         
        strcpy(web_addr[addr_index], redirect);
        strcpy(parent_addr_buffer,curr_url);
        
        extract_matches();
       // free(redirect_raw);
       // free(redirect);
      }

      else if(status_code == 401){
        authes[addr_index+1] = get_auth_type();
        web_addr[++addr_index] = (char*)malloc(strlen(curr_url)+1);
        strcpy(web_addr[addr_index], curr_url);
        
        strcpy(parent_addr_buffer,curr_url);
        extract_matches();
      }
      
     // print_cached_web_addr();
      //printf("addr_index = %d\n", addr_index);
     //printf("\n\n--------turn %d ended-------------\n\n", i);
  }
}


  
