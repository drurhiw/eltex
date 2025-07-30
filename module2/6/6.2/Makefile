CC = gcc
LDFLAGS = -L. -lbook

all: libbook.so phonebook run

libbook.so: phone_numbers.c book.h
	$(CC) -shared phone_numbers.c -o libbook.so

phonebook: main.c
	$(CC) main.c $(LDFLAGS) -o phonebook

run:
	LD_LIBRARY_PATH=. ./phonebook

clean:
	rm -f libbook.so phonebook