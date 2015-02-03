
include Makefile.cfg
include Makefile.parse

.PHONY := all clean dist install optimize doxy-doc xynth.pc test strip update pspdev

all:
	echo done
#	@$(MAKE) -C src

clean1:
	@$(MAKE) --no-print-directory clean -C src
	@$(MAKE) --no-print-directory clean -C tools/theme
	@$(MAKE) --no-print-directory clean -C tools/optimize
	rm -f xynth.pc
	rm -rf dist
	rm -rf doc

dist: all xynth.pc
	rm -rf dist
	mkdir -p $(DISTTOPDIR)
	mkdir -p $(DISTINCDIR)
	mkdir -p $(DISTLIBDIR)
	mkdir -p $(DISTBINDIR)
	mkdir -p $(DISTCONFDIR)
	mkdir -p $(DISTFONTDIR)
	mkdir -p $(DISTTHEMEDIR)
	@$(MAKE) --no-print-directory dist -C src
	mkdir -p $(DISTPKGCONFIG)
	cp xynth.pc $(DISTPKGCONFIG)/xynth.pc

XYINSTALLDIR=$(SDKDIR)/livecd/iso/bin/

installinit:
	mkdir -p $(XYINSTALLDIR)Xynth
	mkdir -p $(XYINSTALLDIR)Xynth/Data
	mkdir -p $(XYINSTALLDIR)Xynth/Data/Themes
	mkdir -p $(XYINSTALLDIR)Xynth/Data/Conf
	mkdir -p $(XYINSTALLDIR)Xynth/Data/Fonts
	cp src/configs/xynth.conf $(XYINSTALLDIR)Xynth/Data/Conf
	cp src/fonts/* $(XYINSTALLDIR)Xynth/Data/Fonts	
	cp demo/desktop/cfg $(XYINSTALLDIR)Xynth/Data/desktop -Rf
	cp demo/desktop/img $(XYINSTALLDIR)Xynth/Data/desktop -Rf

installme:
	cp src/server/xynth $(XYINSTALLDIR)xyserver -fr
#	cp src/widget/libwidget.so ../../CdRoot/System/Runtime
#	cp src/lib/libxynth.so ../../CdRoot/System/Runtime
	mkdir -p $(XYINSTALLDIR)Xynth/Data/desktop/cfg
	mkdir -p $(XYINSTALLDIR)Xynth/Data/desktop/img
	cp demo/desktop/desktop $(SDKDIR)/livecd/iso/bin/ -fr
	cp demo/term/xyterm $(SDKDIR)/livecd/iso/bin/ -fr
	cp demo/simple/simple $(SDKDIR)/livecd/iso/bin/ -fr
	cp demo/child/child $(SDKDIR)/livecd/iso/bin/ -fr
	cp src/lib/libxynth.a $(SDKDIR)/uclibc/lib -fr
	mkdir -p $(SDKDIR)/uclibc/include/xynth
	cp src/lib/xynth.h $(SDKDIR)/uclibc/include/xynth/ -fr
	cp src/lib/xynth_.h $(SDKDIR)/uclibc/include/xynth/ -fr
#	cp src/themes/silverado/silverado.so $(XYINSTALLDIR)Xynth/Data/Themes -fr

cleanme:
	@echo build ...
	make -C ./src/server/ clean
	make -C ./demo/term/ clean
	make -C ./demo/desktop/ clean
	make -C ./demo/simple/ clean
	make -C ./demo/child/ clean

me:
	@echo build ...
	make -C ./src/lib/
	make -C ./src/server/
	make -C ./demo/child/
	make -C ./demo/term/
	make -C ./demo/desktop/
	make -C ./demo/simple/
	make -C ./ports/links-2.1pre30/

optimize:
	$(MAKE) -C tools/optimize

doxy-doc:
	rm -rf doc
	EXCLUDE_PATTERNS='*/dist/* \
	                  */demo/* \
			  */tools/* \
			  */ports/* \
			  */themes/* \
			  */libz/* \
			  */libpng/* \
			  */freetype2/* \
			  */expat/* \
			  */pixman/* \
			  */lrmi-*/* \
			  */pthread_w32/*' \
	SRCDIR='.' \
	PROJECT='xynth' \
	DOCDIR='doc' \
	VERSION='0.8.40' \
	PERL_PATH='perl' \
	HAVE_DOT='NO' \
	GENERATE_MAN='NO' \
	GENERATE_RTF='NO' \
	GENERATE_XML='NO' \
	GENERATE_HTMLHELP='NO' \
	GENERATE_CHI='NO' \
	GENERATE_HTML='YES' \
	GENERATE_LATEX='NO' \
	doxygen ./doxygen.cfg

xynth.pc: Makefile.parse Makefile.cfg
	@rm -rf xynth.pc
	@echo > subs.sed
	@echo "s,@prefix@,${INSTALLDIR},g"     >> subs.sed
	@echo "s,@version@,${XYNTH_VERSION},g" >> subs.sed
ifeq ($(WIDGET_LIB), Y)
	@echo "s,@widget_libs@,-lwidget,g"     >> subs.sed
endif
	@sed -f subs.sed $@.in > $@
	@rm -rf subs.sed

test: clean all dist install

update: clean
	svn update

strip: dist
	@$(foreach F, $(wildcard $(DISTBINDIR)/*), $(STRIP) $(F) > /dev/null 2>&1;)
	@$(foreach F, $(wildcard $(DISTLIBDIR)/lib*), $(STRIP) $(F) > /dev/null 2>&1;)
	@$(foreach F, $(wildcard $(DISTTHEMEDIR)/*), $(STRIP) $(F) > /dev/null 2>&1;)

pspdev:
	mount /mnt/sdb1
	cp -Rf dist/psp/game/*xynth* /mnt/sdb1/psp/game/
	umount /mnt/sdb1
