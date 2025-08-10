CC = gcc

all: compproc compsum compcat compmax run

compproc:
	$(CC) -o proc processes.c 

compsum:
	$(CC) -o sum sum.c 

compcat:
	$(CC) -o cat cat.c 

compmax:
	$(CC) -o max max.c 

run:
	./proc 

clean:
	rm -f proc sum cat max