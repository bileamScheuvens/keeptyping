CC = gcc
TARGET_EXEC := keeptyping

BUILD_DIR := ./build
SRC_DIR := ./src
SOURCES := $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(SOURCES:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CFLAGS := $(INC_FLAGS) -MMD -MP $(shell pkg-config --cflags ncurses)
LDFLAGS := $(shell pkg-config --libs ncurses)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -g -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
