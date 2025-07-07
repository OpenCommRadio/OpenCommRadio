# Main module sources
CORE_SRCS := \
	core/src/core_state.c \
	core/src/callbacks.c \
	core/src/opencomm_main.c

CORE_INCLUDES := \
	-Icore/include

CORE_LIB  := $(BUILD_DIR)/libopencomm_core.a
CORE_OBJS := $(CORE_SRCS:%.c=$(OBJ_DIR)/%.o)

include core/version.mk
include mk/semver.mk
$(eval $(call build_semver,OPENCOMM_CORE))

$(CORE_LIB)-$(OPENCOMM_CORE_VER): $(CORE_OBJS)
	mkdir -p $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

INCLUDES += $(CORE_INCLUDES)

LIB_TARGETS += $(CORE_LIB)-$(OPENCOMM_CORE_VER)
