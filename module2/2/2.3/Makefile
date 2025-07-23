CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect 

collect:
	$(CC) -o calc calculator2.c main.c

run:
	./calc

test: test_program
	./test_program

test_program: calculator2.o test.o
	$(CC) calculator2.o test.o -o test_program $(LDFLAGS)

clean:
	rm -f *.o calc2 test_program
