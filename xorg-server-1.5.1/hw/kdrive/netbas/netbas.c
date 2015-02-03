/*
 * Copyright ?1999 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include <kdrive-config.h>
#endif
#include "kdrive.h"

#include <errno.h>
#include <signal.h>
#include <linux/vt.h>
#include <linux/kd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <X11/keysym.h>
#include <linux/apm_bios.h>

static int  vtno;
int  NetbasConsoleFd;
int  NetbasApmFd = -1;
static int  activeVT;
static Bool enabled;

static void
NetbasVTRequest (int sig)
{
    kdSwitchPending = TRUE;
}

/* Check before chowning -- this avoids touching the file system */
static void
NetbasCheckChown (char *file)
{
    struct stat	    st;
    __uid_t	    u;
    __gid_t	    g;

    if (stat (file, &st) < 0)
	return;
    u = getuid ();
    g = getgid ();
    if (st.st_uid != u || st.st_gid != g)
	chown (file, u, g);
}

static int
NetbasInit (void)
{
    int fd = -1;
    char vtname[11];
    struct vt_stat vts;

	thread_set_priority(getpid(),35); //提升优先级

    NetbasConsoleFd = open("/dev/kbd",O_RDONLY);
    /* check if we're run with euid==0 */
    if (geteuid() != 0)
    {
	FatalError("NetbasInit: Server must be suid root\n");
    }

    if (kdVirtualTerminal >= 0)
	vtno = kdVirtualTerminal;
    else
    {
	
    }

	fprintf(stderr,"%s() NetbasConsoleFd = %d\n",__FUNCTION__, NetbasConsoleFd);

    //close(fd);

    sprintf(vtname,"/dev/tty%d",vtno); /* /dev/tty1-64 */

    if ((NetbasConsoleFd = 0) < 0)
    {
	FatalError("NetbasInit: Cannot open %s (%s)\n",
		   vtname, strerror(errno));
    }

    /* change ownership of the vt */
    //NetbasCheckChown (vtname);

    /*
     * the current VT device we're running on is not "console", we want
     * to grab all consoles too
     *
     * Why is this needed?
     */
    //NetbasCheckChown ("/dev/tty0");
    /*
     * Netbas doesn't switch to an active vt after the last close of a vt,
     * so we do this ourselves by remembering which is active now.
     */
    //memset (&vts, '\0', sizeof (vts));	/* valgrind */
   

    return 1;
}

Bool
NetbasFindPci (CARD16 vendor, CARD16 device, CARD32 count, KdCardAttr *attr)
{
    FILE    *f;
    char    line[2048], *l, *end;
    CARD32  bus, id, addr;
    int	    n;
    CARD32  ven_dev;
    Bool    ret = FALSE;
    int	    i;

    attr->vendorID = vendor;
    attr->deviceID = device;
    ven_dev = (((CARD32) vendor) << 16) | ((CARD32) device);
    f = fopen ("/proc/bus/pci/devices", "r");
    if (!f)
	return FALSE;
    attr->io = 0;
    while (fgets (line, sizeof (line)-1, f))
    {
	line[sizeof(line)-1] = '\0';
	l = line;
	bus = strtoul (l, &end, 16);
	if (end == l)
	    continue;
	l = end;
	id = strtoul (l, &end, 16);
	if (end == l)
	    continue;
	l = end;
	if (id != ven_dev)
	    continue;
	if (count--)
	    continue;
	(void) strtoul (l, &end, 16);	/* IRQ */
	if (end == l)
	    continue;
	l = end;
	n = 0;
	for (i = 0; i < 6; i++)
	{
	    addr = strtoul (l, &end, 16);
	    if (end == l)
		break;
	    if (addr & 1)
		attr->io = addr & ~0xf;
	    else
	    {
		if (n == KD_MAX_CARD_ADDRESS)
		    break;
		attr->address[n++] = addr & ~0xf;
	    }
	    l = end;
	}
	while (n > 0)
	{
	    if (attr->address[n-1] != 0)
		break;
	    n--;
	}
	attr->naddr = n;
	attr->domain = 0; /* XXX */
	attr->bus = (bus >> 8) & 0xff;
	attr->slot = (bus >> 3) & 0x1f;
	attr->func = bus & 0x07;
	ret = TRUE;
	break;
    }
    fclose (f);
    return ret;
}

unsigned char *
NetbasGetPciCfg(KdCardAttr *attr) 
{
    char filename[256];
    FILE *f;
    unsigned char *cfg;
    int r;

    snprintf(filename, 255, "/proc/bus/pci/%02x/%02x.%x",
             attr->bus >> 8, (attr->bus & 0xff) >> 3, attr->bus & 7);
/*     fprintf(stderr,"Find card on path %s\n",filename); */

    if (!(f=fopen(filename,"r"))) 
        return NULL;

    if (!(cfg=xalloc(256))) 
    {
        fclose(f);
        return NULL;
    }

    if (256 != (r=fread(cfg, 1, 256, f)))
    {
        fprintf(stderr,"NetbasGetPciCfg: read %d, expected 256\n",r);
        free(cfg);
        cfg=NULL;
    }
    fclose(f);
/*     fprintf(stderr,"NetbasGetPciCfg: success, returning %p\n",cfg); */
    return cfg;
}

static void
NetbasSetSwitchMode (int mode)
{
    
}

static void
NetbasApmBlock (pointer blockData, OSTimePtr pTimeout, pointer pReadmask)
{
}

static Bool NetbasApmRunning;

static void
NetbasApmWakeup (pointer blockData, int result, pointer pReadmask)
{
    fd_set  *readmask = (fd_set *) pReadmask;

    if (result > 0 && NetbasApmFd >= 0 && FD_ISSET (NetbasApmFd, readmask))
    {
	
    }
}

#ifdef FNONBLOCK
#define NOBLOCK FNONBLOCK
#else
#define NOBLOCK FNDELAY
#endif

static void
NetbasEnable (void)
{
    if (enabled)
	return;
   
    enabled = TRUE;
}

static void
NetbasDisable (void)
{
    
    enabled = FALSE;
    if (NetbasApmFd >= 0)
    {
	RemoveBlockAndWakeupHandlers (NetbasApmBlock, NetbasApmWakeup, 0);
	RemoveEnabledDevice (NetbasApmFd);
	close (NetbasApmFd);
	NetbasApmFd = -1;
    }
}

static void
NetbasFini (void)
{
    struct vt_mode   VT;
    struct vt_stat  vts;
    int		    fd;

    if (NetbasConsoleFd < 0)
	return;

    return;
}

void
KdOsAddInputDrivers ()
{
    //KdAddPointerDriver(&NetbasMouseDriver);
   // KdAddPointerDriver(&MsMouseDriver);
    KdAddPointerDriver(&Ps2MouseDriver);
#ifdef TSLIB
    KdAddPointerDriver(&TsDriver);
#endif
    //KdAddPointerDriver(&NetbasEvdevMouseDriver);
    KdAddKeyboardDriver(&NetbasKeyboardDriver);
    //KdAddKeyboardDriver(&NetbasEvdevKeyboardDriver);

	
}

static void
NetbasBell(int volume, int pitch, int duration)
{
    //if (volume && pitch)
    //    ioctl(NetbasConsoleFd, KDMKTONE, ((1193190 / pitch) & 0xffff) |
     //         (((unsigned long)duration * volume / 50) << 16));
}

KdOsFuncs   NetbasFuncs = {
    .Init = NetbasInit,
    .Enable = NetbasEnable,
    .Disable = NetbasDisable,
    .Fini = NetbasFini,
    .Bell = NetbasBell,
};

void
OsVendorInit (void)
{
    KdOsInit (&NetbasFuncs);
}

