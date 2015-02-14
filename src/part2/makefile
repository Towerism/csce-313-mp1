CC=gcc
testlist: linked_list2.o main.o
	$(CC) linked_list2.o main.o -o testlist2
linked_list2.o: linked_list2.c linked_list2.h
	$(CC) -c linked_list2.c
main.o: main.c
	$(CC) -c main.c
clean:
	rm *.o testlist2
