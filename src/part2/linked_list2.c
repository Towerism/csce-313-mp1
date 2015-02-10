#include "linked_list2.h"
#include <limits.h>
#include <stdio.h>
static void* head_ptr;
static void* tail_ptr;

static int number_of_tiers;
static int memory_pool;
static int block_size;

static int key_offset = sizeof(void*);
static int len_offset = sizeof(void*) + sizeof(int);
static int ptr_offset = sizeof(void*) + sizeof(int)*2;
static int tier_size;

void  Init (int M, int b, int t) {
  int i;
  int amount = t * M;
  head_ptr = malloc(amount);
  tail_ptr = head_ptr + amount;
  number_of_tiers = t;
  memory_pool = M;
  tier_size = M;
  block_size = b;
  void * ptr = head_ptr;
  for(i = 0; i < memory_pool/block_size * number_of_tiers; ++i) {
    *(int*)(ptr + key_offset) = -1;
    ptr+= block_size;
  }
}

void* GetTierPtr(int tier) {
  return (void*)(head_ptr + (tier * tier_size));
}

void Destroy() {
  free(head_ptr);
}

int getTier(int key) {
  int interval = INT_MAX / number_of_tiers;
  //out of bounds when key is INT_MAX, put in last tier
  int tier = (key == INT_MAX) ? number_of_tiers - 1 : key / interval;
  return tier;
}

int  Insert(int key, char * value_ptr, int value_len){
  int tier = getTier(key);
  void* temp_free_ptr = GetTierPtr(tier);
  void* temp_head_ptr = GetTierPtr(tier);
  void* temp_tail_ptr = GetTierPtr(tier) + tier_size;

  if(block_size - ptr_offset <= value_len) {
    //throw exception?
    printf("Size too big\n");
    return 0;
  }
  else if(temp_free_ptr == temp_tail_ptr) {
    return 1;
  }
  else {
	while (GetNodeKey(temp_free_ptr) >= 0) {
      temp_free_ptr += block_size;
      if (temp_free_ptr == temp_tail_ptr) {
        return 0;
      }
    }
    //set previous nodes "next" ptr
    if(temp_free_ptr != temp_head_ptr) {
      *(char**)(temp_free_ptr - block_size) = temp_free_ptr;
    }
    *(int*)(temp_free_ptr + key_offset) = key;
    *(int*)(temp_free_ptr + len_offset) = value_len;
    memcpy(temp_free_ptr + ptr_offset, value_ptr, value_len);

    temp_free_ptr += block_size;
  }
}

int   Delete (int key){
  char* ptr = Lookup(key);
  *(int*)(ptr + key_offset) = -1;
}

char*   Lookup (int key) {
  int tier = getTier(key);
  void* temp_free_ptr = GetTierPtr(tier);
  int i;
  for (i = 0; i < memory_pool/block_size; ++i) { 
    int current_key = GetNodeKey(temp_free_ptr);
    if (current_key == key) {
      return temp_free_ptr; 
    }
    temp_free_ptr += block_size;
  }
  return NULL;
}

void  PrintList () {
  int i;
  void * ptr = head_ptr;
  for(i = 0; i < memory_pool/block_size * number_of_tiers; ++i) {
    if (GetNodeKey(ptr) >= 0) {
      printf("Key: %d , ValueLength: %d \n", GetNodeKey(ptr), GetNodeValueLength(ptr));
    }
    ptr+= block_size;
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
