CC = clang
CFLAGS = -std=c11 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin
EXE = app

.PHONY: all clean

all: dirs app run

dirs:
	mkdir -p ./$(BIN)

run:
	$(BIN)/$(EXE)

app: $(OBJ)
	$(CC) -o $(BIN)/$(EXE) $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
