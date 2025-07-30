CC = gcc
LDFLAGS = -ldl

TARGET = calculator
LIB = libcalc.so

all: $(TARGET)

$(LIB): calculator2.c calculator2.h
	$(CC) -shared -o $(LIB) calculator2.c

$(TARGET): main.c $(LIB)
	$(CC) -o $(TARGET) main.c $(LDFLAGS)

run: $(TARGET)
	LD_LIBRARY_PATH=. ./$(TARGET)

clean:
	rm -f $(TARGET) $(LIB)
