CC       := cc
CPPFLAGS :=
CFLAGS   := -std=c99 -Wall -Werror -Wextra
LDFLAGS  :=
LDLIBS   :=

BIN  := main
SRCS := $(wildcard *.c)
DEPS := $(SRCS:.c=.d)
OBJS := $(SRCS:.c=.o)

DEV := 0

ifeq ($(DEV), 1)
	CFLAGS += -O0 -g -MMD
else
	CFLAGS += -O3
endif

$(BIN): $(OBJS)

-include $(DEPS)

.PHONY: run
run: $(BIN)
	./$(BIN)

.PHONY: clean
clean:
	rm -rf $(OBJS) $(DEPS) $(BIN)
