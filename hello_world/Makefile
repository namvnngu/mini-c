CC        := cc
CPPFLAGS  :=
CFLAGS    := -std=c99 -Wall -Werror -Wextra
LDFLAGS   :=
LOADLIBES :=
LDLIBS    :=

BIN  := main
SRC  := $(wildcard *.c)
OBJ  := $(SRC:.c=.o)

DEV := 0

ifeq ($(DEV), 1)
	CFLAGS += -O0 -g
else
	CFLAGS += -O3
endif

$(BIN): $(OBJ)

.PHONY: run
run: $(BIN)
	./$(BIN)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN)
