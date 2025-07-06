HAL_SRCS := \
	hal/src/hal.c

HAL_INCLUDES := \
	-Ihal/include

HAL_LIB  := $(BUILD_DIR)/libhal.a
HAL_OBJS := $(HAL_SRCS:%.c=$(OBJ_DIR)/%.o)

$(HAL_LIB): $(HAL_OBJS)
	mkdir -p $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

INCLUDES += $(HAL_INCLUDES)
TARGETS  += $(HAL_LIB)
