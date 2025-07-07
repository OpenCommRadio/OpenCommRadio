PLATFORM_LINUX_SRCS := \
	platforms/linux/src/hal_platform_linux.c \
	platforms/linux/src/linux_main.c

PLATFORM_LINUX_INCLUDES := \
	-Iplatforms/linux/include

PLATFORM_LINUX_LIB  := $(BUILD_DIR)/libplatform_linux.a
PLATFORM_LINUX_OBJS := $(PLATFORM_LINUX_SRCS:%.c=$(OBJ_DIR)/%.o)

include platforms/linux/version.mk
include mk/semver.mk
$(eval $(call build_semver,OPENCOMM_PLATFORM_LINUX))

$(PLATFORM_LINUX_LIB): $(PLATFORM_LINUX_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

INCLUDES    += $(PLATFORM_LINUX_INCLUDES)
LIB_TARGETS += $(PLATFORM_LINUX_LIB)

EXEC_TARGETS += $(BUILD_DIR)/opencommradio
