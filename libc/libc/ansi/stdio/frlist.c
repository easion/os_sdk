/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <stdio.h>
#include <libc/local.h>

static __file_rec __initial_file_rec = {
  0,
  3,
{ &__dj_stdin, &__dj_stdout, &__dj_stderr }
};

__file_rec *__file_rec_list = &__initial_file_rec;
