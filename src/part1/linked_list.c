#include "linked_list.h"
static void* head_ptr;
static void* free_ptr;
static void* tail_ptr;
static int memory_pool;
static int block_size;
static int key_offset = sizeof(char*);
static int len_offset = sizeof(char*) + sizeof(int);
static int ptr_offset = sizeof(char*) + sizeof(int)*2;

void  Init (int M, int b){
  head_ptr = malloc(M + sizeof(void*));
  tail_ptr = (head_ptr + M);

  free_ptr = head_ptr;
  memory_pool = M;
  block_size = b;
  
  void * ptr = head_ptr;
  int i;
  for(i = 0; i < memory_pool/block_size; ++i) {
    *(int*)(ptr + key_offset) = -1;
    *(void**)ptr = NULL;
    ptr+= block_size;
  }
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
  else if(free_ptr == tail_ptr)
  {
      printf("List is full\n"); 
  }
  else {
    //set previous nodes "next" ptr
    if(free_ptr != head_ptr) {
      *(char**)(free_ptr - block_size) = free_ptr;
    }
    *(int*)(free_ptr + key_offset) = key;
    *(int*)(free_ptr + len_offset) = value_len;
    memcpy(free_ptr + ptr_offset, value_ptr, value_len);

    free_ptr += block_size;
  }
  return 1;
}
int   Delete (int key){
  void* ptr = head_ptr;
  int i;
  for(i = 0; i < memory_pool/block_size; ++i) {
    if(getNodeKey(ptr) != key) {
      ptr += block_size;
    }
    else {
      if(ptr!=head_ptr) {
        *(char**)(ptr - block_size) = (ptr + block_size);
      }
      *(int**)(ptr + key_offset) = NULL;
      *(int**)(ptr + len_offset) = NULL;
      *(char**)(ptr + ptr_offset) = NULL;
      *(char**)(ptr) = NULL;
      return 1;
    }
  }
  return 0;
}
void LookupAndPrint(int x)
{
  char* kv = Lookup(x);
  if (kv)
    printf ("Key = %d, ValueLength = %d, Value = %s \n", *(int *) kv, *(int *) (kv+4), kv + 8);
}


char* Lookup (int key) {
char* ptr = head_ptr;

  int i;
  for(i = 0; i < memory_pool/block_size; ++i) {
    if(getNodeKey(ptr) == key && (ptr + key_offset) != NULL) {
      return (ptr + key_offset);
    }
    ptr += block_size;
  }
  return NULL;
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
  for(i = 0; i < memory_pool/block_size; ++i) {
    if(getNodeKey(ptr) != -1) {
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
