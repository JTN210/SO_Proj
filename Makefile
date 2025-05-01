CC = gcc
CFLAGS = -Wall -g -Iinclude

CLIENT_SRC = client.c
SERVER_SRC = server.c
CLIENT_BIN = dclient
SERVER_BIN = dserver

all: dclient dserver

dclient: $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_SRC)

dserver: $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_SRC)

clean:
	rm -f *.o

fclean: clean
	rm -f $(CLIENT_BIN) $(SERVER_BIN)

re: fclean all