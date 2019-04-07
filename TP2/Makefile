all: build clean

build: main.o
	gcc -o tp0 main.o

main.o:
	gcc -o main.o -c main.c -Wall -std=c99

clean:
	rm *.o
