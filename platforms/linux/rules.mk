PLATFORM_LINUX_SRCS := \
	platforms/linux/src/hal_platform_linux.c

PLATFORM_LINUX_INCLUDES := \
	-Iplatforms/linux/include

PLATFORM_LINUX_LIB  := $(BUILD_DIR)/libplatform_linux.a
PLATFORM_LINUX_OBJS := $(PLATFORM_LINUX_SRCS:%.c=$(OBJ_DIR)/%.o)

$(PLATFORM_LINUX_LIB): $(PLATFORM_LINUX_OBJS)
	mkdir -p $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

INCLUDES += $(PLATFORM_LINUX_INCLUDES)
TARGETS  += $(PLATFORM_LINUX_LIB)
