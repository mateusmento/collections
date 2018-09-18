CC = gcc

INC_PATH = -Iinclude
LIB_PATH = -Llib

CFLAGS_COMMON = -Wall -std=c99
CFLAGS_DEBUG =  $(CFLAGS_COMMON) -g -O0
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2
CFLAGS = $(CFLAGS_DEBUG) $(INC_PATH) $(LIB_PATH)


FOLDERS = obj lib bin

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
LIB = -lcoll

TEST_SRC = $(wildcard test/*.c)
TEST_OUT = $(patsubst test/%.c, bin/%.out, $(TEST_SRC))

OUT_LIB = lib/libcoll.a

bin/%.out: test/%.c 	
	$(CC) $(CFLAGS) $< -o $@ $(LIB)

$(TEST_OUT): $(OUT_LIB)

$(OUT_LIB): $(OBJ)
	$(AR) cr $(OUT_LIB) $(OBJ)

obj/%.o: src/%.c $(FOLDERS)
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir obj
lib:
	mkdir lib
bin:
	mkdir bin


.PHONY: init clean install all

init: $(FOLDERS)

install: $(OUT_LIB)

test: $(TEST_OUT)

clean:
	rm -rf obj
	rm -rf obj/test
	rm -rf lib
	rm -rf bin
	rm -rf bin/test

