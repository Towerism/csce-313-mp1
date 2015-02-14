CC=gcc
testlist: linked_list.o main.o
	$(CC) linked_list.o main.o -o testlist
linked_list.o: linked_list.c linked_list.h
	$(CC) -c linked_list.c
main.o: main.c
	$(CC) -c main.c
clean:
	rm *.o testlist
