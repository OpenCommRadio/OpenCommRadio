.DEFAULT_GOAL := all
BUILD_DIR   := build
OBJ_DIR    := $(BUILD_DIR)/obj
LIB_TARGETS :=
EXEC_TARGET :=
PLATFORM ?= linux

include platforms/$(PLATFORM)/rules.mk
include hal/rules.mk
include core/rules.mk

all: $(LIB_TARGETS) $(EXEC_TARGETS) 
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

CPPFLAGS += $(INCLUDES)

# Only link the executable if it was requested
$(BUILD_DIR)/opencommradio: $(OBJS) $(LIB_TARGETS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) $(LIB_TARGETS) -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
default: all
