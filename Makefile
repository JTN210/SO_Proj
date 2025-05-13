CC = gcc
CFLAGS = -Wall -g -Iinclude $(shell pkg-config --cflags glib-2.0)
LDFLAGS = $(shell pkg-config --libs glib-2.0)

CLIENT_SRC = dclient.c client.c 
SERVER_SRC = dserver.c server.c 
CLIENT_BIN = dclient
SERVER_BIN = dserver

all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRC) $(LDFLAGS)

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $(SERVER_SRC) $(LDFLAGS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(CLIENT_BIN) $(SERVER_BIN)

re: fclean all