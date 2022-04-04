CC = gcc
CFLAGS = -c -Wall
LIBS = -lm

all: main.o stack_operations.o virtual_machine_structure.o algorithms.o
	$(CC) $(LIBS) main.o stack_operations.o virtual_machine_structure.o algorithms.o -o main.out

main.o:
	$(CC) $(CFLAGS) main.c

stack_operations.o:
	$(CC) $(CFLAGS) stack_operations.c

virtual_machine_structure.o:
	$(CC) $(CFLAGS) virtual_machine_structure.c

algorithms.o:
	$(CC) $(CFLAGS) algorithms.c
