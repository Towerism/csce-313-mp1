#include "linked_list2.h"
#include <limits.h>
#include <stdio.h>
static void* head_ptrs;
static void* free_ptrs;
static void* tail_ptrs;

static int number_of_tiers;
static int memory_pool;
static int block_size;

static int key_offset = sizeof(char*);
static int len_offset = sizeof(char*) + sizeof(int);
static int ptr_offset = sizeof(char*) + sizeof(int)*2;

void  Init (int M, int b, int t) {
  int i;
  int amount = t * sizeof(void*);
  head_ptrs = malloc( amount );
  free_ptrs = malloc(sizeof(void*) * t);
  tail_ptrs = malloc(sizeof(void*) * t);
  for(i = 0; i < t; ++i)
  {
    //ALLCOATING Linked_List tiers
    void* head_ptr_temp = malloc(M + sizeof(void*));
    *GetPtr(i, head_ptrs) = head_ptr_temp;
    *GetPtr(i, free_ptrs) = head_ptr_temp;
    *GetPtr(i, tail_ptrs) = (head_ptr_temp + M);
  }
  number_of_tiers = t;
  memory_pool = M;
  block_size = b;
}
void** GetPtr(int index, void* ptr_array) {
  return (void**)(ptr_array + (index * block_size));
}
void  DestroyTier (int index) {
  void * ptr = *GetPtr(index, head_ptrs);
  free(ptr);
}
void Destroy() {
  int i;
  for(i = 0; i < number_of_tiers; ++i) {
    DestroyTier(i);
  }
  free(head_ptrs);
  free(tail_ptrs);
  free(free_ptrs);
}
int   Insert (int key,char * value_ptr, int value_len){
  /* double intervals =  number_of_tiers / INT_MAX; */
  int tier = key % number_of_tiers;
  void* free_ptr = *GetPtr(tier, free_ptrs);
  void* head_ptr = *GetPtr(tier, head_ptrs);
  void* tail_ptr = *GetPtr(tier, tail_ptrs);

  if(block_size - ptr_offset <= value_len) {
    //throw exception?
    printf("Size too big\n");
    return 0;
  }
  else if(free_ptr == tail_ptr) {
    printf("STOP, DROP, Hammertime \n");
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
/* int   Delete (int key){ */
/*   void* ptr = head_ptr; */
/*   int i; */
/*   for(i = 0; i < memory_pool/block_size; ++i) { */
/*     if(GetNodeKey(ptr) != key) { */
/*       ptr += block_size; */
/*     } */
/*     else { */
/*       if(ptr!=head_ptr) { */
/*         *(char**)(ptr - block_size) = (ptr + block_size); */
/*       } */
/*       *(int**)(ptr + key_offset) = NULL; */
/*       *(int**)(ptr + len_offset) = NULL; */
/*       *(char**)(ptr + ptr_offset) = NULL; */
/*       *(char**)(ptr) = NULL; */
/*       return 1; */
/*     } */
/*   } */
/*   return 0; */

/* } */
int   Delete (int key){ }
char*   Lookup (int key) { }
void  PrintList () {
  int i;
  for(i = 0; i < number_of_tiers; ++i) {
    PrintTier(i);
  }
}
void  PrintTier(int index) {
  void * ptr = *GetPtr(index, head_ptrs);
  int i;
  for(i = 0; i < memory_pool/block_size; ++i) {
    if(GetNodeKey(ptr) != 0 && GetNodeValueLength(ptr) != 0) {
      printf("Key: %d , ValueLength: %d \n", GetNodeKey(ptr), GetNodeValueLength(ptr));
    }
    //Martin?
    ptr+= block_size;
    /* ptr = *(void**)ptr; */

  }
}

char* GetNodeValue(void* ptr) {
  return (char*)(ptr + ptr_offset);
}
int GetNodeKey(void* ptr){
  return *(int*)(ptr + key_offset);
}
int GetNodeValueLength(void* ptr) {
  return *(int*)(ptr + len_offset);
}
