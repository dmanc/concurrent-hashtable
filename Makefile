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

compile-time: $(BIN_DIR)/time
$(BIN_DIR)/time: timing.cpp sequential.h
	mkdir -p $(BIN_DIR)
	$(CC) $(CCFLAGS) timing.cpp -o $(BIN_DIR)/time

test: $(BIN_DIR)/unit
	$(BIN_DIR)/unit

time: $(BIN_DIR)/time
	$(BIN_DIR)/time

clean:
	rm -rf bin

