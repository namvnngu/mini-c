CC = cc
CFLAGS := -std=c99 -Wall -Werror -Wextra
DBGFLAGS := -g -fsanitize=address
COBJFLAGS := $(CFLAGS) -c
INCFLAGS :=
LDFLAGS := -lncurses

SRC_PATH := src
DBG_PATH := debug
RELEASE_PATH := release

TARGET_NAME := tetris
TARGET_RELEASE := $(RELEASE_PATH)/$(TARGET_NAME)
TARGET_DBG := $(DBG_PATH)/$(TARGET_NAME)

SRC := $(SRC_PATH)/main.c $(SRC_PATH)/ecs.c
OBJ_RELEASE := $(RELEASE_PATH)/main.o
OBJ_DEBUG := $(DBG_PATH)/main.o

.PHONY: debug
debug: prepare build-debug run-debug

.PHONY: release
release: prepare build-release run-release

.PHONY: prepare
prepare:
	@mkdir -p $(RELEASE_PATH) $(RELEASE_PATH) $(DBG_PATH)

.PHONY: build-release
build-release: $(TARGET_RELEASE)
$(TARGET_RELEASE): $(OBJ_RELEASE)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
$(OBJ_RELEASE): $(SRC)
	$(CC) $(COBJFLAGS) $(INCFLAGS) -o $@ $<

.PHONY: run-release
run-release:
	$(TARGET_RELEASE)

.PHONY: build-debug
build-debug: $(TARGET_DBG)
$(TARGET_DBG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DBGFLAGS) -o $@ $^
$(OBJ_DEBUG): $(SRC)
	$(CC) $(COBJFLAGS) $(INCFLAGS) $(DBGFLAGS) -o $@ $<

.PHONY: run-debug
run-debug:
	$(TARGET_DBG)

.PHONY: clean
clean:
	rm -rf $(RELEASE_PATH) $(DBG_PATH)
