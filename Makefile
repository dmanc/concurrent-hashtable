CC=g++
CCFLAGS=-O3 -std=c++14
BIN_DIR=bin

BASEHEADER=hashtable.h

all: compile-test

compile-test:
$(BIN_DIR)/unit.bin: unit.cpp
	mkdir -p $(BIN_DIR)
	$(CC) unit.cpp -o $(BIN_DIR)/unit.bin

test: $(BIN_DIR)/unit.bin
	$(BIN_DIR)/unit.bin

clean:
	rm -rf bin

