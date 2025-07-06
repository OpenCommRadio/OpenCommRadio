# Define reusable function to build SemVer string
define build_semver
$(1)_VER := $($(1)_VER_MAJ).$($(1)_VER_MIN).$($(1)_VER_PATCH)
ifdef $(1)_VER_PRERELEASE
$(1)_VER := $$($(1)_VERSION)-$($(1)_VER_PRERELEASE)
endif
CPPFLAGS += -D$(1)_VER=\"$(1)_VER\"
endef

