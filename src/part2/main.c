#include "linked_list2.h"
#include "stdio.h"
#include "unistd.h"

int main(int argc, char ** argv)
{
  int b = -1;
  int M = -1;
  int t = -1;
  int errflag = 0;
  int c;
  while ((c = getopt(argc, argv, ":b:s:t:")) != -1) {
  	switch (c) {
  	case 'b':
  	  b = atoi(optarg);
	  break;
	case 's':
	  M = atoi(optarg);
	  break;
	case 't':
	  t = atoi(optarg);
	  break;
	case ':':
	  fprintf(stderr, "Option -%c, requires an operand\n", optopt);
	  ++errflag;
	  break;
	case '?':
	  fprintf(stderr, "Unrecognised option: -%c\n", optopt);
	  ++errflag;
	  break;
  	}
  }

  if (errflag || b == -1 || M == -1 || t == -1) {
  	fprintf(stderr, "usage: testlist2 [-b <blocksize>] [-s <memsize>] [-t <tiers>]");
  	return 1;
  }

  if (b <= 0 || M <= 0 || t <= 0) {
  	fprintf(stderr, "Arguments must be postive\n");
  	return 1;
  }

  if (b < 12) {
    fprintf(stderr, "Blocksize must be at least 12\n");
    return 1;
  }

  if (M % b != 0) {
    fprintf(stderr, "Memory size must be divisible by blocksize\n");
    return 1;
  }

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
