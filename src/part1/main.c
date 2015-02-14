#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "linked_list.h"

int main(int argc, char ** argv)
{

  int b = -1;
  int M = -1;
  int errflag = 0;
  int c;

  while ((c = getopt(argc, argv, ":b:s:")) != -1) {
  	switch (c) {
  	case 'b':
  	  b = atoi(optarg);
	  break;
	case 's':
	  M = atoi(optarg);
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

  if (errflag || b == -1 || M == -1) { 
  	fprintf(stderr, "usage: testlist [-b <blocksize>] [-s <memsize>]");
  	return 1;
  }

  if (b <= 0 || M <= 0) {
    fprintf(stderr, "Arguments must be positive\n");
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

  char * msg = "a sample message";

  Init(M,b); // initialize
  // test operations
  int testnums [] = {100, 5, 200, 7, 39, 25, 400, 50, 200, 300};
  int i = 0;
  // some sample insertions
  for (i=0; i< 10; i ++)
  {
    Insert (testnums [i], buf, 50);   // insert 50 bytes from the buffer as value for each of the insertions
  }
  Insert (150, buf, 200); // this Insert should fail
  PrintList ();
  Delete (7);
  Insert (13, msg, strlen(msg)+1);  // insertion of strings, copies the null byte at the end
  Delete (55);
  Insert (15, "test msg", 8);
  Delete (3);
  PrintList ();

  // a sample lookup operations that should return null, because it is looking up a non-existent number
  char* kv = Lookup(3);
  if (kv)
    printf ("Key = %d, Value Len = %d\n, Value = %s", *(int *) kv, *(int *) (kv+4), kv + 8);


 //this look up  should succeed and print the string "a sample message"
 //TODO: MARTIN, this is where the seg fault is happening
  kv = Lookup (13);
  if (kv)
    printf ("Key = %d, ValueLength = %d, Value = %s", *(int *) kv, *(int *) (kv+4), kv + 8);


// end test operations
  Destroy ();

}
