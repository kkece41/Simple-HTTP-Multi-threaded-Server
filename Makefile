# To compile, type "make" or make "all"
# To remove files, type "make clean"

CC = gcc
CFLAGS = -Wall -g 
OBJS = server.o request.o io_helper.o 

.SUFFIXES: .c .o 

kkserver: server client

server: server.o request.o io_helper.o MyQueue.o
	$(CC) $(CFLAGS) -o server server.o request.o io_helper.o MyQueue.o -lpthread

client: client.o io_helper.o
	$(CC) $(CFLAGS) -o client client.o io_helper.o

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lpthread

clean:
	-rm -f $(OBJS) server
