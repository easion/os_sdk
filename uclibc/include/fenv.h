#ifndef _FENV_H

#define _FENV_H
#include <bits/fenv.h>


/* Arrange to hide uClibc internals */
#if (defined __GNUC__ && \
  (defined __GNUC_MINOR__ && ( __GNUC__ >= 3 && __GNUC_MINOR__ >= 3 ) \
   || __GNUC__ >= 4)) || defined __ICC
# define attribute_hidden __attribute__ ((visibility ("hidden")))
# define __hidden_proto_hiddenattr(attrs...) __attribute__ ((visibility ("hidden"), ##attrs))
#else
# define attribute_hidden
# define __hidden_proto_hiddenattr(attrs...)
#endif

# define libm_hidden_proto(name, attrs...)
# define libm_hidden_def(name)
# define libm_hidden_weak(name)
# define libm_hidden_ver(local, name)
# define libm_hidden_data_def(name)
# define libm_hidden_data_weak(name)
# define libm_hidden_data_ver(local, name)

#endif

