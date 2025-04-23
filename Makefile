CC = gcc
CFLAGS = -Wall -g

dclient: dclient.o client.o

client: client.o dclient.h

dclient.o: dclient.c dclient.h

dclient.o: dclient.c dclient.h

clean:
	rm -f *.o dclient docs.txt

	
