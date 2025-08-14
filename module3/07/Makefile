CC = gcc

all: comp1 comp2 run

comp1:
	$(CC) -o server server.c -lrt

comp2:
	$(CC) -o client client.c -lrt

run:
	./server


clean:
	rm -f server client