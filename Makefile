CC = gcc
CFLAGS = -Wall -Iinclude 
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
OUT_LIB = lib/libcoll.a
OUT_EXE = main.out
TEST_OUT_EXE = list.out


obj/%.o: src/%.c
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OUT_LIB): $(OBJ)
	ar cr $(OUT_LIB) $(OBJ)

install: $(OUT_LIB)
	
test: $(OUT_LIB)
	$(CC) $(CFLAGS) -Llib -g test/main.c -lcoll -o $(OUT_EXE)
	$(CC) $(CFLAGS) -Llib -g test/list.test.c -lcoll -o $(TEST_OUT_EXE)



.PHONY: clean
clean:
	rm $(TEST_OUT_EXE)
	rm $(OUT_EXE)
	rm $(OUT_LIB)
	rm obj/*.o
