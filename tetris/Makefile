CC = cc
COBJFLAGS := -std=c99 -Wall -Werror -Wextra -c
INCFLAGS :=
LDFLAGS := -lncurses
RELEASEFLAGS := -O3
DBGFLAGS = -g -fsanitize=address

SRC_PATH := src
DBG_PATH := debug
RELEASE_PATH := release

TARGET_NAME := tetris
TARGET_RELEASE := $(RELEASE_PATH)/$(TARGET_NAME)
TARGET_DBG := $(DBG_PATH)/$(TARGET_NAME)

SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c)))
OBJ_RELEASE := $(addprefix $(RELEASE_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

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
	$(CC) $(LDFLAGS) -o $@ $^
$(RELEASE_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(COBJFLAGS) $(RELEASEFLAGS) $(INCFLAGS) -o $@ $<

.PHONY: run-release
run-release:
	$(TARGET_RELEASE)

.PHONY: build-debug
build-debug: $(TARGET_DBG)
$(TARGET_DBG): $(OBJ_DEBUG)
	$(CC) $(LDFLAGS) $(DBGFLAGS) -o $@ $^
$(DBG_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(COBJFLAGS) $(DBGFLAGS) $(INCFLAGS) -o $@ $<

.PHONY: run-debug
run-debug:
	$(TARGET_DBG)

.PHONY: clean
clean:
	rm -rf $(RELEASE_PATH) $(DBG_PATH)
