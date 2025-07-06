# Main module sources
CORE_SRCS := \
	core/src/callbacks.c \
	core/src/opencomm_main.c

CORE_LIB  := $(BUILD_DIR)/libopencomm_core.a
CORE_OBJS := $(CORE_SRCS:%.c=$(OBJ_DIR)/%.o)

include core/version.mk
OPENCOMM_CORE_VER = $(OPENCOMM_CORE_VER_MAJ).$(OPENCOMM_CORE_VER_MIN).$(OPENCOMM_CORE_VER_PATCH)
ifdef OPENCOMM_CORE_VER_PRERELEASE
OPENCOMM_CORE_VER := $(OPENCOMM_CORE_VERSION)-$(OPENCOMM_CORE_VER_PRERELEASE)
endif
$(eval $(call build_semver,OPENCOMM_CORE))

$(CORE_LIB)-$(OPENCOMM_CORE_VER): $(CORE_OBJS)
	mkdir -p $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

CPPFLAGS += \
	-DOPENCOMM_CORE_VER=\"$(OPENCOMM_CORE_VER)\"

LIB_TARGETS += $(CORE_LIB)-$(OPENCOMM_CORE_VER)
