CC = gcc -Wall

all: divoc

inout.o: inout.c inout.h
	$(CC) -c inout.c

database.o: database.c database.h
	$(CC) -c database.c

divoc: divoc.c inout.o database.o
	$(CC) inout.o database.o divoc.c -o divoc

clean:
	rm -f divoc *.o *~ *.bak
