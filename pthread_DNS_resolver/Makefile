CC = gcc
CFLAGS = -g -Wall

all: multi_lookup

clean: 
		rm queue.o multi_lookup

multi_lookup: queue.o
		$(CC) $(CFLAGS) multi_lookup.c queue.o -o multi_lookup

queue.o: queue.h
		$(CC) $(CFLAGS) -c queue.c -o queue.o
