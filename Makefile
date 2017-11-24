CC=gcc
CFLAGS= -Wall -pedantic

all: server client
	
client :
	$(CC) $(CFLAGS) client.c -o client

server : 
	$(CC) $(CFLAGS) server.c -o server

del_server:
	rm server

del_client:
	rm client

clean: del_client del_server