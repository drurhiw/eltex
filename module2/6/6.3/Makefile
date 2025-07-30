CC = gcc
LDFLAGS = -ldl

FUNC_DIR = funcs
LIB_DIR = libs

LIBS = libsum.so libsub.so libmul.so libdivide.so

all: libs calculator

libs: $(LIBS)

libsum.so: $(FUNC_DIR)/sum.c calculator2.h
	$(CC) -shared -o $(LIB_DIR)/$@ $(FUNC_DIR)/sum.c

libsub.so: $(FUNC_DIR)/sub.c calculator2.h
	$(CC) -shared -o $(LIB_DIR)/$@ $(FUNC_DIR)/sub.c

libmul.so: $(FUNC_DIR)/mul.c calculator2.h
	$(CC) -shared -o $(LIB_DIR)/$@ $(FUNC_DIR)/mul.c

libdivide.so: $(FUNC_DIR)/divide.c calculator2.h
	$(CC) -shared -o $(LIB_DIR)/$@ $(FUNC_DIR)/divide.c

calculator: main.c calculator2.h
	$(CC) -o $@ main.c $(LDFLAGS)

run:
	./calculator

clean:
	rm -f $(LIB_DIR)/*.so calculator
