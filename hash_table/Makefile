.POSIX:
.SUFFIXES:

CC = cc

INCFLAGS =
CFLAGS = -std=c11 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments -Wunreachable-code
LDFLAGS =

EXE = app
BUILD_DIR = build
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean

all: dirs app run
dirs:
	mkdir -p ./$(BUILD_DIR)
	rsync -a --include='*/' --exclude='*' "$(SRC_DIR)" "$(BUILD_DIR)"
run:
	$(BUILD_DIR)/$(EXE)
app: $(OBJ_FILES)
	$(CC) -o $(BUILD_DIR)/$(EXE) $^ $(LDFLAGS)
$(OBJ_FILES): $(SRC_FILES)
	$(CC) -o $@ -c $< $(INCFLAGS) $(CFLAGS)
clean:
	rm -rf $(BUILD_DIR)
