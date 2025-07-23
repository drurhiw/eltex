CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect 

collect:
	$(CC) -o book phone_numbers.c main.c

run:
	./book

test: test_program
	./test_program

test_program: phone_numbers.o test.o
	$(CC) phone_numbers.o test.o -o test_program $(LDFLAGS)

clean:
	rm -f *.o book test_program
