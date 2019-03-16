.PHONY: all clean

ROOT_DIR := ../../

CC := gcc
CCFLAGS := -std=c11 -I $(ROOT_DIR)

all: main

clean:
	rm -f main *.o

main: main.c custom_type.o
	$(CC) $(CCFLAGS) -o main $^

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $^

custom_type.o: custom_type.c custom_type.h $(ROOT_DIR)/util.h
	$(CC) $(CCFLAGS) -c -o $@ $<

