#include "common.h"


void print_cached_web_addr(){
  printf("---------web_addr-------\n");
  for(int i = 0; i <= addr_index; i++){
    printf("%dth addr: %s\n", i, web_addr[i]);
  }
    printf("----------------\n");
}


void print_parent_addr(){
    printf("---------parent_addr-------\n");
    printf("%s\n", parent_addr_buffer);
    printf("----------------\n");
}

void print_html_buffer(){
  printf("---------parent_addr-------\n");
  if(strlen(parent_addr_buffer) == 0){
    printf("html buffer cleaned\n");
  }else{    printf("html buffer not cleaned\n");}
  printf("----------------\n");
}

