INSTALL_DIR=$(SDKDIR)/livecd/iso/
# do not use directly, is included by other templates
CROSS=i386-elf-
CPP=$(CROSS)g++
CXX=$(CROSS)g++
CC=$(CROSS)gcc
AR=$(CROSS)ar
LD=$(CROSS)ld
STRIP=$(CROSS)strip
OBJDUMP=$(CROSS)objdump
RANLIB = $(CROSS)ranlib
CP=cp

CFLAGS +=  -I.
CPPFLAGS += -I./


# make sure the MY_CFLAGS_IN, MY_CPPFLAGS_IN, and MY_INCLUDES_IN vars are resolved when the rule is made
$(MY_TARGETDIR_IN)/%.o: MY_CFLAGS_IN:=$(MY_CFLAGS_IN)
$(MY_TARGETDIR_IN)/%.o: MY_CPPFLAGS_IN:=$(MY_CPPFLAGS_IN)
$(MY_TARGETDIR_IN)/%.o: MY_INCLUDES_IN:=$(MY_INCLUDES_IN)

# build rules
CPPFLAGS += $(MY_CFLAGS_IN)
MY_CFLAGS_IN  += $(CFLAGS)
# empty rule for dependency files, they are built by the compile process
$(MY_TARGETDIR_IN)/%.d:

$(MY_TARGETDIR_IN)/%.o: $(MY_SRCDIR_IN)/%.cpp 
	@$(MKDIR)
	@echo compiling cpp $<
	$(CXX) -c $< $(GLOBAL_CPPFLAGS) $(MY_CPPFLAGS_IN) $(MY_INCLUDES_IN) -MD -MT $@ -MF $(@:%o=%d) 

$(MY_TARGETDIR_IN)/%.o: $(MY_SRCDIR_IN)/%.c
	@$(MKDIR)
	@echo compiling c files $<
	$(CC)   -I. -I$(SDKDIR)/uclibc/include -c $< $(GLOBAL_CFLAGS) $(MY_CFLAGS_IN) $(MY_INCLUDES_IN) -MD -MT $@ -MF $(@:%o=%d) -o $@

$(MY_TARGETDIR_IN)/%.o: $(MY_SRCDIR_IN)/%.S
	@$(MKDIR)
	@echo assembling $<
	$(CC) -c  -I. -I$(SDKDIR)/uclibc/include $< $(GLOBAL_ASFLAGS) $(GLOBAL_CFLAGS) $(MY_CFLAGS_IN) $(MY_INCLUDES_IN) -MD -MT $@ -MF $(@:%o=%d) -o $@


$(MY_TARGETDIR_IN)/%.o: $(MY_SRCDIR_IN)/%.asm
	yasm $*.asm -o $*.o -f elf
