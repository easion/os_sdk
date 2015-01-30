MY_TARGET_IN := $(MY_TARGET)
MY_TARGETDIR_IN := $(MY_TARGETDIR)
MY_SRCDIR_IN := $(MY_SRCDIR)
MY_OBJS_IN := $(MY_OBJS)
MY_CFLAGS_IN := $(MY_CFLAGS)
MY_CPPFLAGS_IN := $(MY_CPPFLAGS)
MY_INCLUDES_IN := $(MY_INCLUDES)

# create a new version in the target directory
_TEMP_OBJS := $(addprefix $(MY_TARGETDIR_IN)/,$(MY_OBJS_IN))

ALL_OBJS := $(ALL_OBJS) $(_TEMP_OBJS)

# add to the global deps
ALL_DEPS := $(ALL_DEPS) $(_TEMP_OBJS:.o=.d)

$(MY_TARGET_IN): $(_TEMP_OBJS)
	@$(MKDIR)
	@echo linking2 $@
	@$(LD) $(GLOBAL_LDFLAGS) -r -o $@ $^

include  $(SDKDIR)/bin/templates/compile.mk

MY_TARGET :=
MY_TARGETDIR :=
MY_SRCDIR :=
MY_OBJS :=
MY_CFLAGS :=
MY_CPPFLAGS :=
MY_INCLUDES :=

