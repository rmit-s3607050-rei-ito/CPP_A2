# OBJS = obj/main_noncurses.o obj/model.o obj/bst.o

BIN = draughts

CC = g++

SRC_EXT = cpp

SRC_DIR = src
OBJ_DIR = obj

CFLAGS = -Wall -pedantic -std=c++14 -g -I$(SRC_DIR) -I inc
# LFLAGS = -lboost_program_options

UNAME_S = $(shell uname -s)

SOURCES := $(shell find $(SRC_DIR)/ -name '*.$(SRC_EXT)')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=%.o)
OBJECTS := $(OBJECTS:%.o=$(OBJ_DIR)/%.o)
DEPS := $(OBJECTS:.o=.d)

test_datastructures : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

obj/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -f obj/*.o test_datastructures
