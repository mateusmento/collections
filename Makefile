MKDIR := mkdir -p
CC := gcc


INCLUDES := -Iinclude

CFLAGS_COMMON := -std=c11 $(INCLUDES)
CFLAGS_RELEASE := -O2
CFLAGS_DEBUG := -g -O0
CFLAGS := $(CFLAGS_COMMON)
CFLAGS += $(CFLAGS_DEBUG)

RELEASE_PATH := build/release
DEBUG_PATH := build/debug
BUILD_PATH := $(DEBUG_PATH)

DEP_PATH := build/dep
OBJ_PATH := $(BUILD_PATH)/obj
LIB_PATH := $(BUILD_PATH)/lib


SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEP := $(patsubst src/%.c, $(DEP_PATH)/%.d, $(SRC))

TEST_SRC := $(wildcard test/*.c)

OUTPUT = $(LIB_PATH)/libcoll.a


all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	@$(MKDIR) $(LIB_PATH)
	$(AR) cr $@ $?

$(OBJ): $(OBJ_PATH)/%.o: src/%.c
	@$(MKDIR) $(OBJ_PATH)
	$(COMPILE.c) $(OUTPUT_OPTIONS) -o $@ $<

-include $(DEP)

$(DEP): $(DEP_PATH)/%.d: src/%.c
	@$(MKDIR) $(DEP_PATH)
	$(CC) $(INCLUDES) -MM $< -MT "$(OBJ_PATH)/$*.o $(DEP_PATH)/$*.d" > $@



.PHONY: install clean

install: $(OUTPUT) 

clean:
	rm -rf build
