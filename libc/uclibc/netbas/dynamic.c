#define JICAMA
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <netbas/netbas.h>
#include <netbas/dirent.h>
#include <sys/stat.h>
#include <stdarg.h>

typedef void constructor_t( void );
typedef int image_init( int nImageID );

int load_library(char const *path,long flags)
{
	int ret;	
  int n,i;
  void *fn_init[255];
  image_init* dynamic_module_init ;

	ret=netbas_system_call(60,path,flags,0,0, 0);
	if (ret<0)
	{
	printf("load_library error = %d\n",ret);
		return -1;
	}
	printf("load_library = %d\n",ret);

#if 0
  n = get_dynamic_dependencies(ret,fn_init,0);

  for (i=0; i<n; i++)
  {
	  dynamic_module_init = fn_init[i];
	    if ( dynamic_module_init != NULL ) {
		printf( "Calling dependencies %p\n" ,dynamic_module_init);
		dynamic_module_init( ret );
	  }
  }
#endif
	return ret;
}

int unload_library(int id)
{
	int ret;	

	ret=netbas_system_call(61,id,0,0,0,0);
	
	return ret;
}

void*dynamic_symbol(int id, char *name)
{
	int ret;	
	void *fn_addr=NULL;

	ret=netbas_system_call(62,id,name,&fn_addr,0,0);

	if (ret<0)
	{
		return NULL;
	}
	
	return fn_addr;
}

int get_dynamic_module_info(int id, dyinfo_t *info)
{
	int ret;	

	ret=netbas_system_call(63,id,info,0,0,0);
	
	return ret;
}

int get_dynamic_dependencies(int id, void**info, int init_head)
{
	int ret;	

	ret=netbas_system_call(64,id,info,init_head,0,0);
	
	return ret;
}



static void __do_init_library( dyinfo_t* infoptr, int main_app ) {
  int i;
  int nImageId = infoptr->dy_image_id;
  int subcount = infoptr->dy_num_count;
  image_init* dynamic_module_init = infoptr->dy_init;
  void **ctor_addr;

 if ( ( main_app ) && ( infoptr->dy_ctor_count > 0 ) ) {
    constructor_t* fn_ctor = *( ( constructor_t** )infoptr->dy_ctor_addr );

	ctor_addr = infoptr->dy_ctor_addr;

    for ( i = 0; i < infoptr->dy_ctor_count; i++ ) {
		fn_ctor = ctor_addr[i];
	//printf( "Calling fn_ctor %p, count %d\n" ,fn_ctor,i);
      fn_ctor();
      //fn_ctor+=4;
	  //break;
    }
  }

  /* Initialise each sub-image */
  for ( i = nImageId+1; i < subcount; i++ ) {
    if ( get_dynamic_module_info( i,  infoptr ) == 0 ) {
      __do_init_library( infoptr, 0 );
    }
  }

  /* Call any init functions */
  //if( opened_counts[ image_id ] == open_count && NULL != img_init )
  //img_init( image_id );

  if ( dynamic_module_init != NULL ) {
	 // printf( "Calling module init %p\n" ,dynamic_module_init);
   //printf( "Calling img_init %p\n" ,dynamic_module_init);
   // dynamic_module_init( nImageId );
  }
}


extern void (*__ctor_list)(void);
extern void (*__ctor_end)(void);

extern void (*__dtor_list)(void);
extern void (*__dtor_end)(void);

//typedef unsigned long vintp; //- integer type to store a pointer.
//extern unsigned long __ctor_list, __ctor_end, __dtor_list, __dtor_end;
static int __bss_count = 1;

void __ctor_call()
{ 
	void (**f)(void);

	for(f = &__ctor_list; f < &__ctor_end; f++) {
		(**f)();
		//printf("ctor  %p -- %p \n",*f,f);
	}
}

void __dtor_call()
{ 
	void (**f)(void);

	for (f = &__dtor_list; f < &__dtor_end; f++) {
		(**f)();
	}
}



int __init_library(  ) {
  dyinfo_t sInfo;
  int n,i;
  image_init* dynamic_module_init ;
  void *fn_init[255];

  return 0;


  memset(fn_init,0,sizeof(fn_init));

  n = get_dynamic_dependencies(0,fn_init,0);

  for (i=0; i<n; i++)
  {
	  dynamic_module_init = fn_init[i];
	    if ( dynamic_module_init != NULL ) {
		printf( "Calling dependencies app %d/%d %p\n" ,i,n,dynamic_module_init);
		//dynamic_module_init( 0 );
	  }
  }

	//printf("__init_library called 222\n");
  if ( get_dynamic_module_info( 0, &sInfo ) == 0 ) {
    __do_init_library( &sInfo, 1 );
	//printf("__init_library called 333\n");
    return 0;
  } else {
	  //¾²Ì¬Á´½Ó³ÌÐò
   // printf( "%s(): Unable to get image information for library: %d\n", __FUNCTION__, 0 );
  }
    return -1;
}

#include <errno.h>
#define RTLD_LAZY	0x01
#define RTLD_NOW	0x02
#define RTLD_GLOBAL	0x04
#define RTLD_LOCAL	0x08

#define RTLD_NEXT	0x00

enum __dl_errors {
	_DL_ENONE,
	_DL_ENOGLOBAL,
	_DL_EBADHANDLE,
	_DL_EBADSYMBOL,
	_DL_ENOSYM,
	_DL_EBADLIBRARY
};

void *dlopen(const char *file, int mode);
void *dlsym(void *handle, const char *name);
int   dlclose(void *handle);
char *dlerror(void);

/* Type for namespace indeces. Required by Glibc link.h */
typedef long int Lmid_t;


static int __dl_errno = 0;

static inline void __dl_set_errno( int errno )
{
	__dl_errno = errno;
}

static inline int __dl_get_errno( void )
{
	return( __dl_errno );
}

void *dlopen(const char *file, int mode)
{
	int dl, kernmode = 0;
	void *ret = NULL;

	if( file == 0 )
	{
		__dl_set_errno( _DL_ENOGLOBAL );
		return( ret );
	}

	/* We can ignore the RTLD_LAZY and RTLD_NOW flags.  Syllable always does the
	   equivilent of RTLD_NOW and the spec allows RTLD_LAZY to be implementation
	   dependent; so we let it be RTLD_NOW too */

	/* Note that RTLD_GLOBAL and RTLD_LOCAL arn't exactly correct either.  They're
	   probably close enough for now though. */

	//if( mode & RTLD_GLOBAL )
	//	kernmode |= IM_APP_SPACE;

	//if( mode & RTLD_LOCAL )
	//	kernmode |= IM_LIBRARY_SPACE;

	dl = load_library( file, kernmode );
	if( dl >= 0 )
		ret = (void*)dl;
	else
		__dl_set_errno( _DL_EBADLIBRARY );

	return( ret );
}

void *dlsym(void *handle, const char *name)
{
	int error = 0;
	int dl = (int)handle;
	void* symbol;

	if( dl == 0 )
	{
		__dl_set_errno( _DL_EBADHANDLE );
		return( NULL );
	}

	if( name == NULL )
	{
		__dl_set_errno( _DL_EBADSYMBOL );
		return( NULL );
	}

	if( dl == RTLD_NEXT )
	{
		__dl_set_errno( _DL_EBADHANDLE );
		return( NULL );
	}

	symbol = dynamic_symbol( dl, name );
	if( !symbol )
	{
		__dl_set_errno( _DL_ENOSYM );
		return( NULL );
	}

	return( symbol );
}

int dlclose(void *handle)
{
	int dl = (int)handle;

	if( dl == 0 )
	{
		__dl_set_errno( _DL_EBADHANDLE );
		return( EINVAL );
	}

	unload_library( dl );

	return( 0 );
}

char *dlerror(void)
{
	char *estr;
	int errno = __dl_get_errno();

	__dl_set_errno( _DL_ENONE );

	switch( errno )
	{
		case _DL_ENOGLOBAL:
		{
			estr = "Global symbol lookups not supported";
			break;
		}

		case _DL_EBADHANDLE:
		{
			estr = "Invalid handle";
			break;
		}

		case _DL_EBADSYMBOL:
		{
			estr = "Bad symbol name";
			break;
		}

		case _DL_ENOSYM:
		{
			estr = "Symbol not found";
			break;
		}

		case _DL_EBADLIBRARY:
		{
			estr = "Failed to load library";
			break;
		}

		case _DL_ENONE:
		{
			estr = NULL;
			break;
		}

		default:
		{
			estr = "Unknown error";
			break;
		}
	}

	return( estr );
}

