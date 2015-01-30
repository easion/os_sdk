#include<sys/uio.h>
#include<unistd.h>

ssize_t readv(int __fd,__const struct iovec *__vector,int __count)
{
 ssize_t total=0,nr;
 int i;
 for(i=0;i<__count;i++,__vector++)
 {
  nr=read(__fd,__vector->iov_base,__vector->iov_len);
  if(nr<0)
  {
   total=nr;
   break;
  }
  total+=nr;
 }
 return total;
}

ssize_t writev(int __fd,__const struct iovec *__vector,int __count)
{
 ssize_t total=0,nr;
 int i;
 for(i=0;i<__count;i++,__vector++)
 {
  nr=write(__fd,__vector->iov_base,__vector->iov_len);
  if(nr<0)
  {
   total=nr;
   break;
  }
  total+=nr;
 }
 return total;
}

int setmode(int handle, int mode)
{
	return -1;
}
