CC = gcc

all: comp1 comp2 run

comp1:
	$(CC) -o pro producer.c 

comp2:
	$(CC) -o con consumer.c 

run:
	./pro

run2:
	./con

clean:
	rm -f pro con *.txt