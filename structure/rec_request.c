#include "common.h"

void sequential_visit(){
  while(addr_fetching_index < MAX_URL_NUM){
    char* curr_url = web_addr[addr_fetching_index];
    int socket_fd = socket_connect(curr_url, 80);
    get_response(socket_fd, get_path(curr_url), get_domain(curr_url), "80", "luoyuc");
    if(get_status_code() == 200 && not_truncated() && content_type_is_text()){
      strcpy(parent_addr_buffer, curr_url);
      extract_matches();
    }
  }
}
