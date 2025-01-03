CC = cc
CFLAGS := -std=c11 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments -Wunreachable-code
DBGFLAGS := -g
COBJFLAGS := $(CFLAGS) -c
INCFLAGS :=
LDFLAGS :=

BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug

TARGET_NAME := app
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DBG := $(DBG_PATH)/$(TARGET_NAME)

SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

.PHONY: prepare build run debug clean

default: prepare build run

prepare:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

build: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(COBJFLAGS) $(INCFLAGS) -o $@ $<

run:
	$(TARGET)

debug: $(TARGET_DBG)
$(TARGET_DBG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DBGFLAGS) -o $@ $^
$(DBG_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(COBJFLAGS) $(INCFLAGS) $(DBGFLAGS) -o $@ $<

clean:
	rm -rf $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)
