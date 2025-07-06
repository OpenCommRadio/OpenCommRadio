# Root build settings
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
INCLUDES  :=

PLATFORM ?= linux

SRCS :=
OBJS :=
TARGETS :=
include platforms/$(PLATFORM)/rules.mk

include hal/rules.mk
include core/rules.mk

CPPFLAGS += $(INCLUDES)


# Top-level build target: build everything
all: $(TARGETS)

# Compilation rule
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

