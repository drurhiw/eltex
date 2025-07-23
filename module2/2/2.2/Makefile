CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect 

collect:
	$(CC) -o calc calculator.c main.c

run:
	./calc

test: test_program
	./test_program

test_program: calculator.o test.o
	$(CC) calculator.o test.o -o test_program $(LDFLAGS)

clean:
	rm -f *.o calc test_program
