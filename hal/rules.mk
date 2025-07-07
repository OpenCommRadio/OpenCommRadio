HAL_SRCS := \
	hal/src/hal.c

HAL_INCLUDES := \
	-Ihal/include

HAL_LIB  := $(BUILD_DIR)/libopencomm_hal.a
HAL_OBJS := $(HAL_SRCS:%.c=$(OBJ_DIR)/%.o)

include hal/version.mk
include mk/semver.mk
$(eval $(call build_semver,OPENCOMM_HAL))

$(HAL_LIB)-$(OPENCOMM_HAL_VER): $(HAL_OBJS)
	mkdir -p $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

INCLUDES += $(HAL_INCLUDES)


LIB_TARGETS += $(HAL_LIB)-$(OPENCOMM_HAL_VER)
