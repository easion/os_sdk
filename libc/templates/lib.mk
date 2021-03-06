MY_TARGET_IN := $(MY_TARGET)
MY_STATIC_TARGET_IN := $(MY_STATIC_TARGET)
MY_TARGETDIR_IN := $(MY_TARGETDIR)
MY_SRCDIR_IN := $(MY_SRCDIR)
MY_OBJS_IN := $(MY_OBJS)
MY_CFLAGS_IN := $(MY_CFLAGS)
MY_CPPFLAGS_IN := $(MY_CPPFLAGS)
MY_INCLUDES_IN := $(MY_INCLUDES)
MY_LINKSCRIPT_IN := $(MY_LINKSCRIPT)

# create a new version in the target directory
_TEMP_OBJS := $(addprefix $(MY_TARGETDIR_IN)/,$(MY_OBJS_IN))

ALL_OBJS := $(ALL_OBJS) $(_TEMP_OBJS)

# add to the global deps
ALL_DEPS := $(ALL_DEPS) $(_TEMP_OBJS:.o=.d)

ifneq ($(MY_TARGET_IN), ) 
$(MY_TARGET_IN): MY_TARGET_IN:=$(MY_TARGET_IN)
$(MY_TARGET_IN): MY_LINKSCRIPT_IN:=$(MY_LINKSCRIPT_IN)
$(MY_TARGET_IN): MY_TARGETDIR_IN:=$(MY_TARGETDIR_IN) 
$(MY_TARGET_IN): $(LIBGLUE) $(_TEMP_OBJS)
	@$(MKDIR)
	@mkdir -p $(MY_TARGETDIR_IN)
	@echo linking library $@
	@$(AR) rcs  $@.a $^
	$(LD) $(GLOBAL_LDFLAGS) -shared -soname $(notdir $(MY_TARGET_IN)) --script=$(MY_LINKSCRIPT_IN) -o $@ $^
	@echo creating listing file $@.lst
	$(OBJDUMP) -afx $@ > $@.lst
	$(STRIP) $@


endif
ifneq ($(MY_STATIC_TARGET_IN), ) 
$(MY_STATIC_TARGET_IN): MY_TARGETDIR_IN:=$(MY_TARGETDIR_IN) 
$(MY_STATIC_TARGET_IN): $(_TEMP_OBJS)
	@$(MKDIR)
	@echo creating static lib $@
	@$(AR) r $@ $^
endif

include  $(SDKDIR)/bin/templates/compile.mk

MY_TARGET :=
MY_STATIC_TARGET := 
MY_TARGETDIR :=
MY_SRCDIR :=
#MY_OBJS :=
MY_CFLAGS :=
MY_CPPFLAGS :=
MY_INCLUDES :=
MY_LINKSCRIPT :=

