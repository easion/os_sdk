#include	<unistd.h>
#include	<stdio.h>

struct vm_region
{
	int id;
	int lock;
	int wiring;

	unsigned long vm_base;
	unsigned long vm_addr;
	int vm_size;
	char vm_name[32];
};

void* mmap ( void * addr , size_t len , int prot , int flags , int fd , off_t offset )
{
	int ret;
	char *paddr;

	if(!addr)
		paddr=malloc(len);
	else if(addr>0x800000)
		return NULL;
	else{
		paddr=addr;
	}

	ret=do_system_call(90,paddr,len,flags,fd, offset);
	return paddr;
}


int munmap( void * addr, size_t len )
{
	//free
	//ret=netbas_system_call(NR_UNMAP,paddr,len,flags, offset);
}

int msync ( void * addr , size_t len, int flags)
{
}

int delete_vm_region ( char*name )
{
	int ret=0;

	ret=netbas_system_call(103,name,0,0,0, 0);
	return ret;
}

//long get_vm_region (int id, struct vm_region *vm)
long get_vm_region (char *id, struct vm_region *vm)
{
	long ret;
	struct vm_region myvm;
	
	ret=netbas_system_call(104,id,&myvm,0,0, 0);	
	if (vm)
	{
		memcpy(vm, &myvm,sizeof(struct vm_region));
	}
	return myvm.vm_base;
}

//int mapto (unsigned long dest , unsigned long src  )
int create_vm_region ( unsigned long *user_space, unsigned long dest ,char*name, int size, long flags  )
{
	int ret;

	ret=netbas_system_call(105,user_space,dest,name,size, flags);
	return ret;
}



int map_file_vm_region ( char*path, void **addr, int len )
{
	int ret=0;

	//ret=netbas_system_call(105,src,dest,name,size, flags);
	return ret;
}



