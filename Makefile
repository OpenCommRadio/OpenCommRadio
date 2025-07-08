.DEFAULT_GOAL := all

BUILD_DIR     := build
OBJ_DIR       := $(BUILD_DIR)/obj
LIB_TARGETS   :=
EXEC_TARGETS  :=
TOOLS_TARGETS :=
PLATFORM ?= linux

define make_native
	unset CC CFLAGS CPPFLAGS LD LDFLAGS AR OBJCOPY; \
	$(MAKE) -C $(1) $(2)
endef

include platforms/$(PLATFORM)/rules.mk
include hal/rules.mk
include core/rules.mk

CPPFLAGS += $(INCLUDES)

all: $(LIB_TARGETS) $(EXEC_TARGETS)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

CPPFLAGS += $(INCLUDES)

# TODO - this should really be in platforms/linux/rules.mk - with some method for handling building the executables for other platforms eventually
$(BUILD_DIR)/opencommradio: $(OBJS) $(LIB_TARGETS)
	@mkdir -p $(dir $@)
	$(CC) -lpthread -lreadline $(LIB_TARGETS) $(OBJS)  -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:	$(CLEAN_TARGETS)
	rm -rf $(BUILD_DIR)

.PHONY: all clean
default: all
