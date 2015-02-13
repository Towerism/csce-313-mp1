#include "linked_list2.h"
#include "stdio.h"

int main(int argc, char ** argv)
{
  int b = 128;
  int M = b * 4;  // so we have space for 4 items in each of the lists
  int t = 4;    // 4 tiers

  char buf [1024];
  memset (buf, 1, 1024);    // set each byte to 1

  char* msg = "a sample message";

  Init (M, b, t); // initialize
  // test operations
  int testnums [] = {0, 1<<29 , (1<<29) + 5 , 50, (1<<30) + 5, (1<<30) - 500};
  int i = 0;
  // some sample insertions
  for (i=0; i< 6; i ++)
  {
    /* printf("%d \n", testnums[i]); */
    Insert (testnums [i], buf, 50);   // insert 50 bytes from the buffer as value for each of the insertions
  }
  PrintList();
  
  Delete(50);

  printf("\nAttempting to find key 50\n");
  char* ptr = Lookup(50);
  if (ptr) {
    printf("Key: %d , ValueLength: %d \n", GetNodeKey(ptr), GetNodeValueLength(ptr));
  } else {
    printf("Key not found\n");
  }
  
  printf("Attempting to find key %d\n", 1<<29);
  ptr = Lookup(1<<29);
  if (ptr) {
  	printf("Key: %d , ValueLength: %d \n", GetNodeKey(ptr), GetNodeValueLength(ptr));
  } else {
  	printf("Key not found\n");
  }

  printf("\nPrinting list:\n");
  PrintList();

  // end test operations
  Destroy ();

}
