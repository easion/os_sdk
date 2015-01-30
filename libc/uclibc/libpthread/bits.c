/* POSIX threads for Syllable - A simple PThreads implementation             */
/*                                                                           */
/* Copyright (C) 2002 Kristian Van Der Vliet (vanders@users.sourceforge.net) */
/*                                                                           */
/* This program is free software; you can redistribute it and/or             */
/* modify it under the terms of the GNU Library General Public License       */
/* as published by the Free Software Foundation; either version 2            */
/* of the License, or (at your option) any later version.                    */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Library General Public License for more details.                      */

#ifndef __F_SYLLABLE_PTHREAD_BITS_
#define __F_SYLLABLE_PTHREAD_BITS_

#ifdef __cplusplus
extern "C"{
#endif
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "inc/bits.h"

inline int __pt_lock_mutex( sem_id mutex )
{
	return( thread_lock_semaphore_x( mutex,  MSG_ALWAYS_WAIT ) );
}

inline int __pt_unlock_mutex( sem_id mutex )
{
	return( thread_unlock_semaphore_x( mutex) );
}


#ifdef __cplusplus
}
#endif

#endif	/* __F_SYLLABLE_PTHREAD_BITS_ */



