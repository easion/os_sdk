#include <netbas/netbas.h>
#include	<stdio.h>
#include	<sys/types.h>


int netbas_ptrace(int req, char * buf, void* size, void *args)
{
	return netbas_system_call(NR_PTRACE,(int)req,(int)buf,(int)size,(int)args,0);
}

int delete_vm_region ( int id )
{
	int ret=0;

	ret=netbas_system_call(103,id,0,0,0, 0);
	return ret;
}


int get_vm_region_info (int id, struct shm_info *dest )
{
	int ret;

	ret=netbas_system_call(100,id,dest, 0,0,0);
	return ret;
}


int clone_vm_region (int id, char* name, void**paddr )
{
	long ret;
	struct shm_info info;

	ret=netbas_system_call(102,id,paddr,name,0, 0);
	
	if (ret<0)
	{
		return -1;
	}
	return ret;
}


int remap_vm_region (int id, void* myspace)
{
	long ret;

	ret=netbas_system_call(101,id,myspace,0,0, 0);
	
	if (ret<0)
	{
		return NULL;
	}

	return 0;
}


//int mapto (unsigned long dest , unsigned long src  )
int new_vm_region (char *name, int size, long flags, void**addr  )
{
	int ret;	

	ret=netbas_system_call(105,addr,name,flags,size, 0);
	if (ret<0)
	{
		return -1;
	}
	return ret;
}

int create_vm_region (unsigned long dest , int size, long flags, unsigned *addr  )
{
	int err;
	int id = new_vm_region("create_vm_region", size,flags, addr);
	if (id<0)
	{
		return -1;
	}

	err=remap_vm_region(id,dest);
	if (err)
	{
		printf("create_vm_region: remap_vm_region error\n");
		delete_vm_region(id);
		return -1;
	}
	return id;
}

void* attach_vm_region (int id, int size, int *newid)
{
	void *addr=NULL;
	int _id;

	_id = clone_vm_region(id,"attach_vm_region",&addr);
	if (_id<0)
	{
		return NULL;
	}

	printf("addr = %x\n", addr);

	if(newid)
	*newid = _id;
	return addr;
}

int get_vm_region_param (unsigned long *dest , int *size)
{
	int ret;

	ret=netbas_system_call(100,dest,size, 0,0,0);
	return ret;
}



