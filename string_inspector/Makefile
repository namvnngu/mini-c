CC        := cc
COBJFLAGS := -std=c99 -Wall -Werror -Wextra -c
INCFLAGS  :=
LDFLAGS   :=

SRC_PATH := src
SRC      := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c)))

TARGET_NAME := strinspect

DBG_PATH   := debug
DBG_TARGET := $(DBG_PATH)/$(TARGET_NAME)
DBG_OBJ    := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
DBG_FLAGS  := -O0 -g

RELEASE_PATH   := release
RELEASE_TARGET := $(RELEASE_PATH)/$(TARGET_NAME)
RELEASE_OBJ    := $(addprefix $(RELEASE_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
RELEASE_FLAGS  := -O3

.PHONY: debug
debug: prepare build-debug

.PHONY: release
release: prepare build-release

.PHONY: prepare
prepare:
	@mkdir -p $(RELEASE_PATH) $(DBG_PATH)

.PHONY: build-debug
build-debug: $(DBG_TARGET)
$(DBG_TARGET): $(DBG_OBJ)
	$(CC) $(LDFLAGS) $(DBG_FLAGS) -o $@ $^
$(DBG_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(COBJFLAGS) $(DBG_FLAGS) $(INCFLAGS) -o $@ $<

.PHONY: build-release
build-release: $(RELEASE_TARGET)
$(RELEASE_TARGET): $(RELEASE_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
$(RELEASE_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(COBJFLAGS) $(RELEASE_FLAGS) $(INCFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(RELEASE_PATH) $(DBG_PATH)
