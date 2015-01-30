# Makefile for uClibc
#
# Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
#
# Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
#



TOPDIR=../
include $(TOPDIR)Rules.mak

CFLAGS+=-include libm.h -D__USE_ISOC99=1

CSRC =  float_wrappers.c ldouble_wrappers.c e_acos.c e_acosh.c e_asin.c e_atan2.c e_atanh.c e_cosh.c \
	e_exp.c e_fmod.c e_gamma.c e_gamma_r.c e_hypot.c e_j0.c \
	e_j1.c e_jn.c e_lgamma.c e_lgamma_r.c e_log.c e_log2.c e_log10.c \
	e_pow.c e_remainder.c e_rem_pio2.c e_scalb.c e_sinh.c \
	e_sqrt.c k_cos.c k_rem_pio2.c k_sin.c k_standard.c k_tan.c \
	s_asinh.c s_atan.c s_cbrt.c s_ceil.c s_copysign.c s_cos.c \
	s_erf.c s_expm1.c s_fabs.c s_finite.c s_floor.c s_frexp.c \
	s_ilogb.c s_ldexp.c s_lib_version.c s_lrint.c s_lround.c s_llround.c \
	s_log1p.c s_logb.c s_matherr.c s_modf.c s_nextafter.c s_round.c \
	s_rint.c s_scalbn.c s_signgam.c s_significand.c s_sin.c s_tan.c \
	s_tanh.c s_trunc.c w_acos.c w_acosh.c w_asin.c w_atan2.c w_atanh.c \
	w_cabs.c w_cosh.c w_drem.c w_exp.c w_fmod.c w_gamma.c \
	w_hypot.c w_j0.c w_j1.c w_jn.c w_lgamma.c w_lgamma_r.c \
	w_log.c w_log2.c w_log10.c w_pow.c w_remainder.c w_scalb.c w_sinh.c \
	w_sqrt.c nan.c carg.c s_llrint.c \
	s_fpclassify.c s_fpclassifyf.c s_signbit.c s_signbitf.c \
	s_isnan.c s_isnanf.c s_isinf.c s_isinff.c s_finitef.c \
	s_fdim.c s_fma.c s_fmax.c s_fmin.c s_nearbyint.c \
	s_remquo.c s_scalbln.c w_exp2.c w_tgamma.c

CSRC += w_acos.c w_asin.c s_atan.c w_atan2.c s_ceil.c s_cos.c \
	w_cosh.c w_exp.c s_fabs.c s_floor.c w_fmod.c s_frexp.c \
	s_ldexp.c w_log.c w_log10.c s_modf.c w_pow.c s_sin.c \
	w_sinh.c w_sqrt.c s_tan.c s_tanh.c \
	s_expm1.c s_scalbn.c s_copysign.c e_acos.c e_asin.c e_atan2.c \
	k_cos.c e_cosh.c e_exp.c e_fmod.c e_log.c e_log10.c e_pow.c \
	k_sin.c e_sinh.c e_sqrt.c k_tan.c e_rem_pio2.c k_rem_pio2.c \
	s_finite.c\
	 fedisblxcpt.c  fegetenv.c     fegetround.c   fesetenv.c    feupdateenv.c   fraiseexcpt.c   ftestexcept.c\
	fclrexcpt.c    feenablxcpt.c  fegetexcept.c  feholdexcpt.c  fesetround.c  fgetexcptflg.c  fsetexcptflg.c




COBJS=$(patsubst %.c,%.o, $(CSRC))

OBJS=$(MOBJ) $(MOBJ2) $(MOBJ3) $(COBJS)

LIBM=libm.a
all: $(OBJS) $(LIBM)

$(LIBM): ar-target subdirs

ar-target: $(OBJS)
	$(AR) rcs $(LIBM) $(OBJS)
#	$(RANDLIB) $(LIBM)
	cp -fr $(LIBM) $(SDKDIR)/uclibc/lib

$(MOBJ): $(MSRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(STRIPTOOL) -x -R .note -R .comment $*.o


$(COBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: subdirs_clean
	$(RM) *.[oa] *~ core

subdirs: $(patsubst %, _dir_%, $(DIRS))
subdirs_clean: $(patsubst %, _dirclean_%, $(ALL_SUBDIRS))

$(patsubst %, _dir_%, $(DIRS)) : dummy
	$(MAKE) -C $(patsubst _dir_%, %, $@)

$(patsubst %, _dirclean_%, $(ALL_SUBDIRS)) : dummy
	$(MAKE) -C $(patsubst _dirclean_%, %, $@) clean

.PHONY: dummy


