CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect 

collect:
	$(CC) -o chmod chmod.c main.c

run:
	./chmod

check:
	ls -l text.txt

clean:
	rm -f *.o chmod test_program
