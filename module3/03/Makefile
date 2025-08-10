CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect run

collect:
	$(CC) -o book phone_numbers.c main.c

run:
	./book

clean:
	rm -f *.o book *.dat
