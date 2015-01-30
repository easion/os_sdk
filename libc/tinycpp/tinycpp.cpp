extern "C" {
#include<assert.h>
}
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
//http://wiki.osdev.org/C%2B%2B

static bool pure_virtual_call=false;

#ifndef _ICXXABI_H
	#define _ICXXABI_H
 
	#define ATEXIT_MAX_FUNCS	128
 
	#ifdef __cplusplus
	extern "C" {
	#endif
 
typedef unsigned uarch_t;
 
struct atexit_func_entry_t
{
	/*
	* Each member is at least 4 bytes large. Such that each entry is 12bytes.
	* 128 * 12 = 1.5KB exact.
	**/
	void (*destructor_func)(void *);
	void *obj_ptr;
	void *dso_handle;
};
 
int __cxa_atexit(void (*f)(void *), void *objptr, void *dso);
void __cxa_finalize(void *f);
 
	#ifdef __cplusplus
	};
	#endif
 
#endif

	#ifdef __cplusplus
	extern "C" {
	#endif
 
atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
uarch_t __atexit_func_count = 0;
 
void *__dso_handle = 0; //Attention! Optimally, you should remove the '= 0' part and define this in your asm script.
 
int __cxa_atexit(void (*f)(void *), void *objptr, void *dso)
{
	if (__atexit_func_count >= ATEXIT_MAX_FUNCS) {return -1;};
	__atexit_funcs[__atexit_func_count].destructor_func = f;
	__atexit_funcs[__atexit_func_count].obj_ptr = objptr;
	__atexit_funcs[__atexit_func_count].dso_handle = dso;
	__atexit_func_count++;
	return 0; /*I would prefer if functions returned 1 on success, but the ABI says...*/
};
 
void __cxa_finalize(void *f)
{
	uarch_t i = __atexit_func_count;
	if (!f)
	{
		/*
		* According to the Itanium C++ ABI, if __cxa_finalize is called without a
		* function ptr, then it means that we should destroy EVERYTHING MUAHAHAHA!!
		*
		* TODO:
		* Note well, however, that deleting a function from here that contains a __dso_handle
		* means that one link to a shared object file has been terminated. In other words,
		* We should monitor this list (optional, of course), since it tells us how many links to 
		* an object file exist at runtime in a particular application. This can be used to tell 
		* when a shared object is no longer in use. It is one of many methods, however.
		**/
		//You may insert a prinf() here to tell you whether or not the function gets called. Testing
		//is CRITICAL!
		while (--i)
		{
			if (__atexit_funcs[i].destructor_func)
			{
				/* ^^^ That if statement is a safeguard...
				* To make sure we don't call any entries that have already been called and unset at runtime.
				* Those will contain a value of 0, and calling a function with value 0
				* will cause undefined behaviour. Remember that linear address 0, 
				* in a non-virtual address space (physical) contains the IVT and BDA.
				*
				* In a virtual environment, the kernel will receive a page fault, and then probably
				* map in some trash, or a blank page, or something stupid like that.
				* This will result in the processor executing trash, and...we don't want that.
				**/
				(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
			};
		};
		return;
	};
 
	for ( ; i >= 0; )
	{
		/*
		* The ABI states that multiple calls to the __cxa_finalize(destructor_func_ptr) function
		* should not destroy objects multiple times. Only one call is needed to eliminate multiple
		* entries with the same address.
		*
		* FIXME:
		* This presents the obvious problem: all destructors must be stored in the order they
		* were placed in the list. I.e: the last initialized object's destructor must be first
		* in the list of destructors to be called. But removing a destructor from the list at runtime
		* creates holes in the table with unfilled entries.
		* Remember that the insertion algorithm in __cxa_atexit simply inserts the next destructor
		* at the end of the table. So, we have holes with our current algorithm
		* This function should be modified to move all the destructors above the one currently
		* being called and removed one place down in the list, so as to cover up the hole.
		* Otherwise, whenever a destructor is called and removed, an entire space in the table is wasted.
		**/
		if (__atexit_funcs[i].destructor_func == f)
		{
			/* 
			* Note that in the next line, not every destructor function is a class destructor.
			* It is perfectly legal to register a non class destructor function as a simple cleanup
			* function to be called on program termination, in which case, it would not NEED an
			* object This pointer. A smart programmer may even take advantage of this and register
			* a C function in the table with the address of some structure containing data about
			* what to clean up on exit.
			* In the case of a function that takes no arguments, it will simply be ignore within the
			* function itself. No worries.
			**/
			(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
			__atexit_funcs[i].destructor_func = 0;
 
			/*
			* Notice that we didn't decrement __atexit_func_count: this is because this algorithm
			* requires patching to deal with the FIXME outlined above.
			**/
		};
	};
};

#ifdef __cplusplus
	};
	#endif


extern "C"  void __exit_netbas(void){
	exit(1);
}

extern "C" {

int __gxx_personality_v0;

void __cxa_pure_virtual(void)
{
	// Do nothing or print an error message.
 assert(!pure_virtual_call);
 ::__exit_netbas();
}

void _pure_virtual(void)
{
	// Do nothing or print an error message.
 assert(!pure_virtual_call);
 ::__exit_netbas();
}

void __pure_virtual(void)
{
	// Do nothing or print an error message.
 assert(!pure_virtual_call);
 ::__exit_netbas();
}

}

void * operator new(size_t n)
{
 return malloc(n);
}

void * operator new[](size_t n)
{
 return malloc(n);
}


void operator delete(void * ptr)
{
 free(ptr);
}

void operator delete[](void * ptr)
{
 free(ptr);
}

#include "typeinfo"


__cxxabiv1::__fundamental_type_info::~__fundamental_type_info() {}

__cxxabiv1::__class_type_info::~__class_type_info() {}

bool __cxxabiv1::__class_type_info::__do_upcast(const __cxxabiv1::__class_type_info *info, void **) const {
        return *this == *info;
}

__cxxabiv1::__si_class_type_info::~__si_class_type_info() {}

bool __cxxabiv1::__si_class_type_info::__do_upcast(const __cxxabiv1::__class_type_info *info, void **) const {
        if (__class_type_info::__do_upcast(info, 0))
                return true;

        return __base_type->__do_upcast(info, 0);
 }

__cxxabiv1::__pbase_type_info::~__pbase_type_info() {}

bool __cxxabiv1::__pbase_type_info::__do_upcast(const __cxxabiv1::__class_type_info *dst, void **) const {
        /* ??? */
        return false; //__pointee->__do_upcast(dst, 0);
}

bool __cxxabiv1::__pbase_type_info::__is_pointer_p() const {
        return true;
}


__cxxabiv1::__pointer_type_info::~__pointer_type_info() {}

__cxxabiv1::__vmi_class_type_info::~__vmi_class_type_info() {}

std::type_info::~type_info() {}

bool std::type_info::__is_pointer_p() const {
	printf("%s got line%d\n",__FUNCTION__,__LINE__);
        return false;
}

bool std::type_info::__is_function_p() const {
	printf("%s got line%d\n",__FUNCTION__,__LINE__);
        return false;
}

bool std::type_info::__do_catch(const type_info *, void **, unsigned int) const {
        return false;
}

bool std::type_info::__do_upcast(const __cxxabiv1::__class_type_info *, void **) const {
        return false;
}

extern "C" std::type_info const &__cxa_bad_typeid () {
        return typeid (void);
}

struct vtable_prefix {
        unsigned int whole_object;
        const __cxxabiv1::__class_type_info *whole_type;
        const void *origin;
};

