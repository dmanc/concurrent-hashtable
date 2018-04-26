CC=g++
CCFLAGS=-O3 -pthread -Wall -std=c++14 -g
BIN_DIR=bin

BASEHEADER=hashtable.h
TARGET=hashtable

all: compile-test

$(TARGET): $(TARGET).cpp
	mkdir -p $(BIN_DIR)
	$(CC) $(CCFLAGS) -o $(BIN_DIR)/$(TARGET) $(TARGET).cpp

compile-test: $(BIN_DIR)/unit
$(BIN_DIR)/unit: unit.cpp sequential.h
	mkdir -p $(BIN_DIR)
	$(CC) $(CCFLAGS) unit.cpp -o $(BIN_DIR)/unit

test: $(BIN_DIR)/unit
	$(BIN_DIR)/unit

clean:
	rm -rf bin

