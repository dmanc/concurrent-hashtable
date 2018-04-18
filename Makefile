CC=g++
CCFLAGS=-O3 -std=c++14
BIN_DIR=bin

BASEHEADER=hashtable.h

all: compile-test

compile-test: $(BIN_DIR)/unit
$(BIN_DIR)/unit: unit.cpp
	mkdir -p $(BIN_DIR)
	$(CC) unit.cpp -o $(BIN_DIR)/unit

test: $(BIN_DIR)/unit
	$(BIN_DIR)/unit

clean:
	rm -rf bin

