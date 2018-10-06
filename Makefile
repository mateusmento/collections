CC = gcc

INC_PATH = -Iinclude
LIB_PATH = -Llib

CFLAGS_COMMON = -Wall -std=c99
CFLAGS_DEBUG =  $(CFLAGS_COMMON) -g -O0
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2

CFLAGS = $(CFLAGS_DEBUG) $(INC_PATH) $(LIB_PATH)

FOLDERS = obj lib bin

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
LIB = -lcoll

LIB_OUT = lib/libcoll.a

TEST_SRC = $(wildcard test/*.c)
TEST_OUT = $(patsubst test/%.c, bin/%, $(TEST_SRC))


all: init test

$(TEST_OUT): bin/%: test/%.c $(LIB_OUT)
	$(CC) $(CFLAGS) $< $(LIB) -o $@

$(LIB_OUT): $(OBJ)
	$(AR) cr -o $@ $^

$(OBJ): obj/%.o: src/%.c include/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(FOLDERS): %:
	mkdir $@


.PHONY: init clean install all

init: $(FOLDERS)
install: $(LIB_OUT)
test: $(TEST_OUT)
clean:
	rm -rf obj
	rm -rf lib
	rm -rf bin
