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

#ifndef __F_SYLLABLE_PTHREAD_BITS_H_
#define __F_SYLLABLE_PTHREAD_BITS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <time.h>
#if 0  // CONFIG_SMP
#define LOCK_ "lock ; "
#else
#define LOCK_ ""
#endif
struct __atomic_fool_gcc_struct { unsigned long a[100]; };
#define __atomic_fool_gcc(x) (*(struct __atomic_fool_gcc_struct *)(x))

/**
 * atomic_read - read atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically reads the value of @v.
 */ 
#define atomic_read(v)		((v)->counter)

/**
 * atomic_set - set atomic variable
 * @v: pointer of type atomic_t
 * @i: required value
 * 
 * Atomically sets the value of @v to @i.
 */ 
#define atomic_set(v,i)		(((v)->counter) = (i))


/**
 * atomic_add - add integer to atomic variable
 * @i: integer value to add
 * @v: pointer of type atomic_t
 * 
 * Atomically adds @i to @v.
 */
static inline void atomic_add( atomic_t* v, int i )
{
	__asm__ __volatile__(
		LOCK_ "addl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

/**
 * atomic_sub - subtract the atomic variable
 * @i: integer value to subtract
 * @v: pointer of type atomic_t
 * 
 * Atomically subtracts @i from @v.
 */
static inline void atomic_sub( atomic_t *v, int i )
{
	__asm__ __volatile__(
		LOCK_ "subl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

	/**
 * atomic_inc - increment atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically increments @v by 1.
 */ 
static inline void atomic_inc(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_ "incl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

/**
 * atomic_dec - decrement atomic variable
 * @v: pointer of type atomic_t
 * 
 * Atomically decrements @v by 1.
 */ 
static inline void atomic_dec(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_ "decl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}
/**
 * atomic_swap - swap two values
 * @v: pointer to int or atomic_t value to swap
 * @i: integer value to swap
 *
 * Atomically swaps @i into @v and returns the old value at @v.
 * Note: no "lock" prefix even on SMP: xchg always implies lock.
 */
static inline int atomic_swap( volatile void *v, int i )
{
	__asm__ __volatile__("xchgl %0,%1"
		:"=r" (i)
		:"m" (__atomic_fool_gcc(v)), "0" (i)
		:"memory");
	return i;
}

//#include <atheos/semaphore.h>

enum
{
    IDLE_PRIORITY	    = -100,
    LOW_PRIORITY	    = -50,
    NORMAL_PRIORITY	    =  0,
    DISPLAY_PRIORITY	    =  50,
    URGENT_DISPLAY_PRIORITY =  100,
    REALTIME_PRIORITY	    =  150
};



inline int __pt_lock_mutex( sem_id mutex );
inline int __pt_unlock_mutex( sem_id mutex );

typedef struct __pt_timer_args_s
{
	struct timespec *abstime;
	pthread_t thread;
	pthread_cond_t* cond;
	int error;
} __pt_timer_args;

typedef struct __pt_cleanup_s
{
	void (*routine)(void*);
	void *arg;
	struct __pt_cleanup_s *prev;
} __pt_cleanup;


#define	__DEFAULT_STACK_SIZE	1024 * 128

#ifdef __cplusplus
}
#endif

#endif	/* __F_SYLLABLE_PTHREAD_BITS_H_ */









