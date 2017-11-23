CC=gcc
CFLAGS= -Wall -pedantic

all:
	$(CC) $(CFLAGS) client.c -o client
	$(CC) $(CFLAGS) server.c -o server

client :
	$(CC) $(CFLAGS) client.c -o client

server : 
	$(CC) $(CFLAGS) server.c -o server

del_server:
	rm server

del_client:
	rm client

clean:
	rm client
	rm server