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

VPATH := $(LIB_PATH)
vpath %.c src
vpath %.h include

FOLDERS := $(LIB_PATH) $(OBJ_PATH) $(DEP_PATH)

SRC := $(wildcard src/*.c src/**/*.c)
OBJ := $(patsubst src/%.c, $(OBJ_PATH)/%.o, $(SRC))
DEP := $(patsubst src/%.c, $(DEP_PATH)/%.d, $(SRC))

TEST_SRC := $(wildcard test/*.c)

LIB_OUTPUT := $(LIB_PATH)/libcoll.a


all: $(LIB_OUTPUT)

$(LIB_OUTPUT): $(OBJ) | $(LIB_PATH)
	$(AR) cr $@ $?

$(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	$(COMPILE.c) $(OUTPUT_OPTIONS) -o $@ $<

$(FOLDERS):
	@$(MKDIR) $@

-include $(DEP)

$(DEP_PATH)/%.d: %.c | $(DEP_PATH)
	$(CC) $(INCLUDES) -MM $< -MT "$(OBJ_PATH)/$*.o $(DEP_PATH)/$*.d" -MP -MF $@

.PHONY: install clean

install: $(LIB_OUTPUT) 

clean:
	rm -rf build
