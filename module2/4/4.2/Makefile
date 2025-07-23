CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect 

collect:
	$(CC) -o queue queue.c main.c

run:
	./queue

test: test_program
	./test_program

test_program: queue.o test.o
	$(CC) queue.o test.o -o test_program $(LDFLAGS)

clean:
	rm -f *.o queue test_program
