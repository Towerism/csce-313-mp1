#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
/* #define _1_INT_OFFSET_ sizeof(int) */
/* #define _2_INT_OFFSET_ sizeof(int)*2 */
static void* head_ptr;
static void* free_ptr;
static int memory_pool;
static int block_size;

void  Init (int M, int b){
  //calloc gets rid of free() problem, but introduces other one.
  //The real problem is insert 13 where they use a null byte
  head_ptr = malloc(M);

  free_ptr = head_ptr;
  memory_pool = M;
  block_size = b;
}

void  Destroy (){
  free(head_ptr);
}

int   Insert (int key,char* value_ptr, int value_len){
  if(block_size - ptr_offset <= value_len)
  {
    //throw exception?
    printf("Size too big\n");
    return 0;
  }
  else {
    //set previous nodes "next" ptr
    if(free_ptr != head_ptr) {
      *(char*)(free_ptr - block_size) = free_ptr;
    }
    *(int*)(free_ptr + key_offset) = key;
    *(int*)(free_ptr + len_offset) = value_len;
    memcpy(free_ptr + ptr_offset, value_ptr, value_len);
    
    free_ptr += block_size;
  }
  //TODO:find out spec meaning(what do we return
  return 1;
}
int   Delete (int key){
  void* ptr = head_ptr;
  int i;
  for(i = 0; i <= memory_pool/block_size; ++i) {
    if(getNodeKey(ptr) != key) {
      ptr += block_size;
    }
    else {
      if(ptr!=head_ptr) {
        *(char*)(ptr - block_size) = (ptr + block_size);
      }
      *(int*)(ptr + key_offset) = NULL;
      *(int*)(ptr + len_offset) = NULL;
      *(char*)(ptr + ptr_offset) = '\0';
      *(char*)(ptr) = '\0';
      return 1;
    }
  }
  return 0;
}

char* Lookup (int key) {

  char* ptr = head_ptr;
  int i;
  for(i = 0; i <= memory_pool/block_size; ++i) {
    if(getNodeKey(ptr) == key && key != NULL) {
      return (ptr + key_offset);
    }
    else {
      ptr += block_size;
    }
  }
  return '\0';
}

void PrintString( int num_of_chars, char* to_print ) {
  int i;
  for(i = 0; i < num_of_chars; ++i) {
    printf("%c",*(++to_print));
  }
}

void  PrintList () {
  void * ptr = head_ptr;
  int i;
//getNodeKey(ptr) == key && key != NULL
  for(i = 0; i <= memory_pool/block_size; ++i) {
    if(getNodeKey(ptr) != NULL && getNodeValueLength(ptr) != NULL) {
      printf("Key: %d , ValueLength: %d \n", getNodeKey(ptr), getNodeValueLength(ptr));
    }
      ptr += block_size;

  }
  printf("\n");
}


//Wrapper Functions for Offset
char* getNodeValue(void* ptr) {
  return (char*)(ptr + ptr_offset);
}
int getNodeKey(void* ptr){
  return *(int*)(ptr + key_offset);
}
int getNodeValueLength(void* ptr) {
  return *(int*)(ptr + len_offset);
}
