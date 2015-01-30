
#include <errno.h>

static struct errdef {
	int	num;
	char 	*str;
} errlist[] = {


{ OSKIT_E_UNEXPECTED	,	"Unexpected error" },
{ OSKIT_E_NOTIMPL	,	"Not implemented" },
{ OSKIT_E_NOINTERFACE	,	"Interface not supported" },
{ OSKIT_E_POINTER	,	"Bad pointer" },
{ OSKIT_E_ABORT		,	"Operation aborted" },
{ OSKIT_E_FAIL		,	"Operation failed" },
{ OSKIT_E_ACCESSDENIED	,	"Access denied" },
{ OSKIT_E_OUTOFMEMORY	,	"Out of memory" },
{ OSKIT_E_INVALIDARG	,	"Invalid argument" },
{ OSKIT_EDOM		,	"Argument out of domain" },
{ OSKIT_ERANGE		,	"Result too large" },
{ OSKIT_E2BIG		,	"Argument list too long" },
{ OSKIT_EACCES		,	"Permission denied" },
{ OSKIT_EAGAIN		,	"Rsrc temporarily unavail" },
{ OSKIT_EBADF		,	"Bad file descriptor" },
{ OSKIT_EBUSY		,	"Device busy" },
{ OSKIT_ECHILD		,	"No child processes" },
{ OSKIT_EDEADLK		,	"Resource deadlock avoided" },
{ OSKIT_EEXIST		,	"File exists" },
{ OSKIT_EFAULT		,	"Bad address" },
{ OSKIT_EFBIG		,	"File too large" },
{ OSKIT_EINTR		,	"Interrupted system call" },
{ OSKIT_EINVAL		, 	"Invalid argument" },
{ OSKIT_EIO		,	"Input/output error" },
{ OSKIT_EISDIR		,	"Is a directory" },
{ OSKIT_EMFILE		,	"Too many open files" },
{ OSKIT_EMLINK		,	"Too many links" },
{ OSKIT_ENAMETOOLONG	,	"File name too long" },
{ OSKIT_ENFILE		,	"Max files open in system" },
{ OSKIT_ENODEV		,	"Op not supported by device" },
{ OSKIT_ENOENT		,	"No such file or directory" },
{ OSKIT_ENOEXEC		,	"Exec format error" },
{ OSKIT_ENOLCK		,	"No locks available" },
{ OSKIT_ENOMEM		, 	"Cannot allocate memory" },
{ OSKIT_ENOSPC		,	"No space left on device" },
{ OSKIT_ENOSYS		,	"Function not implemented" },
{ OSKIT_ENOTDIR		,	"Not a directory" },
{ OSKIT_ENOTEMPTY	,	"Directory not empty" },
{ OSKIT_ENOTTY		,	"Inappropriate ioctl" },
{ OSKIT_ENXIO		,	"Device not configured" },
{ OSKIT_EPERM		, 	"Op not permitted" },
{ OSKIT_EPIPE		,	"Broken pipe" },
{ OSKIT_EROFS		,	"Read-only file system" },
{ OSKIT_ESPIPE		,	"Illegal seek" },
{ OSKIT_ESRCH		,	"No such process" },
{ OSKIT_EXDEV		,	"Cross-device link" },
{ OSKIT_EBADMSG		,	"Bad message" },
{ OSKIT_ECANCELED	,	"Operation canceled" },
{ OSKIT_EINPROGRESS	,	"Operation in progress" },
{ OSKIT_EMSGSIZE		,	"Bad message buffer length" },
{ OSKIT_ENOTSUP		,	"Not supported" },
{ OSKIT_ETIMEDOUT	,	"Operation timed out" },
{ OSKIT_EADDRINUSE	,	"Address in use" },
{ OSKIT_EADDRNOTAVAIL	,	"Address not available" },
{ OSKIT_EAFNOSUPPORT	,	"Address family unsupported" },
{ OSKIT_EALREADY		,	"Already connected" },
{ OSKIT_ECONNABORTED	,	"Connection aborted" },
{ OSKIT_ECONNREFUSED	,	"Connection refused" },
{ OSKIT_ECONNRESET	,	"Connection reset" },
{ OSKIT_EDESTADDRREQ	,	"Dest address required" },
{ OSKIT_EDQUOT		,	"Reserved" },
{ OSKIT_EHOSTUNREACH	,	"Host is unreachable" },
{ OSKIT_EIDRM		,	"Identifier removed" },
{ OSKIT_EILSEQ		,	"Illegal byte sequence" },
{ OSKIT_EISCONN		,	"Connection in progress" },
{ OSKIT_ELOOP		,	"Too many symbolic links" },
{ OSKIT_EMULTIHOP	,	"Reserved" },
{ OSKIT_ENETDOWN		,	"Network is down" },
{ OSKIT_ENETUNREACH	,	"Network unreachable" },
{ OSKIT_ENOBUFS		,	"No buffer space available" },
{ OSKIT_ENODATA		,	"No message is available" },
{ OSKIT_ENOLINK		,	"Reserved" },
{ OSKIT_ENOMSG		,	"No message of desired type" },
{ OSKIT_ENOPROTOOPT	,	"Protocol not available" },
{ OSKIT_ENOSR		,	"No STREAM resources" },
{ OSKIT_ENOSTR		,	"Not a STREAM" },
{ OSKIT_ENOTCONN		,	"Socket not connected" },
{ OSKIT_ENOTSOCK		,	"Not a socket" },
{ OSKIT_EOPNOTSUPP	,	"Op not supported on socket" },
{ OSKIT_EOVERFLOW	,	"Value too large" },
{ OSKIT_EPROTO		,	"Protocol error" },
{ OSKIT_EPROTONOSUPPORT	,	"Protocol not supported" },
{ OSKIT_EPROTOTYPE	,	"Socket type not supported" },
{ OSKIT_ESTALE		,	"Reserved" },
{ OSKIT_ETIME		,	"Stream ioctl timeout" },
{ OSKIT_ETXTBSY		,	"Text file busy" },
{ OSKIT_EWOULDBLOCK	,	"Operation would block" },
};

#define NERROR	(sizeof(errlist)/sizeof(errlist[0]))

char *
strerror(int num)
{
	static char tmp[sizeof PREFIX + 20];
	int	i = 0;

	for (i = 0; i < NERROR; i++)
		if (errlist[i].num == num)
			return errlist[i].str;

	/* 
	 * Note: we shouldn't be doing this, as this creates a 
	 * rather unnecessary link-time dependency
	 */
	sprintf(tmp, "Unknown error: 0x%x", num);
	return tmp;
}
