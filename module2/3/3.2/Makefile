CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

all:  collect 

collect:
	$(CC) -o task task.c main.c

run1:
	./task 192.168.0.1 255.255.255.0 10

clean:
	rm -f *.o task 
