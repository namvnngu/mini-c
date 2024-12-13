.POSIX:
.SUFFIXES:

CC = cc

INCFLAGS =
CFLAGS = -std=c11 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments -Wunreachable-code
LDFLAGS =

BIN = bin
DIST = dist
SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)

.PHONY: all clean

all: prebuild build run
prebuild:
	mkdir -p ./$(DIST)
run:
	$(DIST)/$(BIN)
build: $(OBJ)
	$(CC) -o $(DIST)/$(BIN) $^ $(LDFLAGS)
%.o: %.c
	$(CC) -o $@ -c $< $(INCFLAGS) $(CFLAGS)
clean:
	rm -rf $(DIST) $(OBJ)
