SHELL:=/bin/bash -O globstar

BIN_NAME=tp3
BIN_DIR=.
OBJ_DIR=./obj
SRC_DIR=./src
SRC=$(wildcard $(SRC_DIR)/**/*.c)

CFLAGS += -lm -Wall -Wextra -Werror

.PHONY: all

all: setup heuristic brute_force

heuristic: heuristic.o
	gcc $(SRC) $(OBJ_DIR)/heuristic.o -o $(BIN_DIR)/$(BIN_NAME)h $(CFLAGS)

heuristic.o:
	gcc -c $(SRC_DIR)/heuristic.c -o $(OBJ_DIR)/heuristic.o $(CFLAGS)

brute_force: brute_force.o
	gcc $(SRC) $(OBJ_DIR)/brute_force.o -o $(BIN_DIR)/$(BIN_NAME)fb $(CFLAGS)

brute_force.o:
	gcc -c $(SRC_DIR)/brute_force.c -o $(OBJ_DIR)/brute_force.o $(CFLAGS)

setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/*

run_h:
	$(BIN_DIR)/$(BIN_NAME)h

run_fb:
	$(BIN_DIR)/$(BIN_NAME)fb

valgrind_fb:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$(BIN_NAME)fb

valgrind_h:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BIN_DIR)/$(BIN_NAME)h
