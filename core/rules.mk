# Main module sources
CORE_SRCS := \
	core/src/callbacks.c \
	core/src/opencomm_main.c

CORE_OBJS := $(CORE_SRCS:%.c=$(OBJ_DIR)/%.o)

SRCS += $(CORE_SRCS)
OBJS += $(CORE_OBJS)

