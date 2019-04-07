CC = gcc
CFLAGS = -Wall -std=c99

all: build clean

build: main.o list.o
	$(CC) $(CFLAGS) main.o list.o -o tp0

main.o:
	$(CC) $(CFLAGS) -c main.c -o main.o

list.o:
	$(CC) $(CFLAGS) -c list.c -o list.o

clean:
	rm *.o
