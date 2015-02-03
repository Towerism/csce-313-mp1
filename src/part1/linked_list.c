#include <stdio.h>
#include <string.h>
#include "linked_list.h"
/* #define _1_INT_OFFSET_ sizeof(int) */
/* #define _2_INT_OFFSET_ sizeof(int)*2 */
static char* head_ptr;
static void* free_ptr;
static int memory_pool;
static int block_size;

void  Init (int M, int b){
  head_ptr = (char*)malloc(M);
  free_ptr = head_ptr;
  memory_pool = M;
  block_size = b;
}
void  Destroy (){
  free(head_ptr);
}
int   Insert (int key,char* value_ptr, int value_len){
  if(block_size - ptr_offset == value_len)
  {
      //throw
  }
  *(int*)(free_ptr + key_offset) = key;
  *(int*)(free_ptr + len_offset) = value_len;
  memcpy(free_ptr + ptr_offset, value_ptr, value_len);
  free_ptr += block_size;
  //TODO:find out spec meaning
  return key;
}
int   Delete (int key){
  void* delete_ptr = head_ptr;
  int i;

  for(i = 0; i < memory_pool/b; ++i) {
    if(*(int*)delete_ptr != key) {
      delete_ptr += block_size;
    }
    else {
      (free_ptr + key_offset) = NULL;
      (free_ptr + len_offset) = NULL;
      (delete_ptr + ptr_offset) = NULL;
      break;
    }
  }

}

char*   Lookup (int key){return NULL;}
void  PrintList (){}
