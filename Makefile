CC=g++
CCFLAGS=-O3

BASEHEADER=hashtable.h

all: compile-test

compile-test:
unit.bin: unit.cpp
	$(CC) unit.cpp -o unit.bin

test: unit.bin
	./unit.bin
