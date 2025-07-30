CC = gcc
AR = ar
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect 

book.o: phone_numbers.c book.h
	$(CC) -c phone_numbers.c  -o book.o

libbook.a:
	$(AR) rcs libbook.a book.o

collect: main.c libbook.a
	$(CC) main.c -L. -lbook -o phonebook

run:
	./phonebook

test: test_program
	./test_program

test_program: phone_numbers.o test.o
	$(CC) phone_numbers.o test.o -o test_program $(LDFLAGS)

clean:
	rm -f *.o book test_program
