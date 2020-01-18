CC=g++
CFLAGS=-g -std=c++11
EXEC=accelerometer run

all: $(EXEC)

%.o: %.c
		$(CC) -c $(CFLAGS) -o $@ $<


.PHONY: clean
	clean:
		-rm -rf $(EXEC) 
