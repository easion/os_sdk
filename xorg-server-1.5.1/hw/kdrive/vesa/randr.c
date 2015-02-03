#ifdef RANDR
#include <randrstr.h>
#endif


#ifdef RANDR
Bool
vesaRandRGetInfo (ScreenPtr pScreen, Rotation *rotations)
{
    KdScreenPriv(pScreen);
    VesaModePtr		    modes, mode;
    KdScreenInfo	    *screen = pScreenPriv->screen;
    VesaCardPrivPtr	    priv = pScreenPriv->card->driver;
    VesaScreenPrivPtr	    pscr = pScreenPriv->screen->driver;
    int			    nmode;
    int			    n;
    RRVisualGroupPtr	    pVisualGroup;
    RRGroupOfVisualGroupPtr pGroupOfVisualGroup;
    RRScreenSizePtr	    pSize;
    
    *rotations = RR_Rotate_0|RR_Rotate_90|RR_Rotate_180|RR_Rotate_270;
    /*
     * Get mode information from BIOS -- every time in case
     * something changes, like an external monitor is plugged in
     */
    modes = vesaGetModes (priv->vi, &nmode);
    if (!modes)
	return FALSE;
    if (priv->modes)
	xfree (priv->modes);
    priv->modes = modes;
    priv->nmode = nmode;
    /*
     * XXX Create a single set of visual sets that has all of the visuals
     * for the root depth
     */
    for (n = 0; n < pScreen->numDepths; n++)
	if (pScreen->allowedDepths[n].numVids)

	    break;
    if (n == pScreen->numDepths)
	return FALSE;
    
    pVisualGroup = RRCreateVisualGroup (pScreen);
    if (!pVisualGroup)
	return FALSE;
    
    if (!RRAddDepthToVisualGroup (pScreen,
				pVisualGroup,
				&pScreen->allowedDepths[n]))
    {
	RRDestroyVisualGroup (pScreen, pVisualGroup);
	return FALSE;
    }
    pVisualGroup = RRRegisterVisualGroup (pScreen, pVisualGroup);
    if (!pVisualGroup)
	return FALSE;
    
    pGroupOfVisualGroup = RRCreateGroupOfVisualGroup (pScreen);

    if (!RRAddVisualGroupToGroupOfVisualGroup (pScreen,
					 pGroupOfVisualGroup,
					 pVisualGroup))
    {
	RRDestroyGroupOfVisualGroup (pScreen, pGroupOfVisualGroup);
	/* pVisualGroup left until screen closed */
	return FALSE;
    }

    pGroupOfVisualGroup = RRRegisterGroupOfVisualGroup (pScreen, pGroupOfVisualGroup);
    if (!pGroupOfVisualGroup)

	return FALSE;

    for (n = 0; n < nmode; n++)
    {
	mode = &priv->modes[n];
	if (vesaModeSupported (priv, mode, FALSE))
	{
	    /*
	     * XXX limit reported modes to those matching the current
	     * format
	     */
	    if (mode->NumberOfPlanes == pscr->mode.NumberOfPlanes &&
		mode->BitsPerPixel == pscr->mode.BitsPerPixel &&
		mode->MemoryModel == pscr->mode.MemoryModel &&
		mode->RedMaskSize == pscr->mode.RedMaskSize &&
		mode->RedFieldPosition == pscr->mode.RedFieldPosition &&
		mode->GreenMaskSize == pscr->mode.GreenMaskSize &&
		mode->GreenFieldPosition == pscr->mode.GreenFieldPosition &&
		mode->BlueMaskSize == pscr->mode.BlueMaskSize &&
		mode->BlueFieldPosition == pscr->mode.BlueFieldPosition)
	    {
		int width, height, width_mm, height_mm;
		if (screen->rotation == 0 || screen->rotation == 180)
		{
		    width = mode->XResolution;
		    height = mode->YResolution;
		    width_mm = screen->width_mm;
		    height_mm = screen->height_mm;
		}
		else
		{
		    width = mode->YResolution;

		    height = mode->XResolution;
		    width_mm = screen->height_mm;
		    height_mm = screen->width_mm;
		}
		pSize = RRRegisterSize (pScreen,
					width, height,
					width_mm, height_mm,
					pGroupOfVisualGroup);
		if (mode->XResolution == screen->width &&
		    mode->YResolution == screen->height)
		{
		    int	rotate = pscr->rotate - screen->rotation;
		    int	rot;
		    if (rotate < 0)
			rotate += 360;
		    switch (rotate) {
		    case   0: rot = RR_Rotate_0; break;
		    case  90: rot = RR_Rotate_90; break;
		    case 180: rot = RR_Rotate_180; break;
		    case 270: rot = RR_Rotate_270; break;
		    }
		    RRSetCurrentConfig (pScreen, rot, pSize,
					pVisualGroup);
		}
	    }
	}
    }
    return TRUE;
}


int
vesaLayerAdd (WindowPtr pWin, pointer value)
{
    ScreenPtr	    pScreen = pWin->drawable.pScreen;
    LayerPtr	    pLayer = (LayerPtr) value;

    if (!LayerWindowAdd (pScreen, pLayer, pWin))
	return WT_STOPWALKING;

    return WT_WALKCHILDREN;
}

int
vesaLayerRemove (WindowPtr pWin, pointer value)
{
    ScreenPtr	    pScreen = pWin->drawable.pScreen;
    LayerPtr	    pLayer = (LayerPtr) value;

    LayerWindowRemove (pScreen, pLayer, pWin);

    return WT_WALKCHILDREN;
}


#ifdef RANDR
Bool
vesaRandRSetConfig (ScreenPtr		pScreen,
		    Rotation		rotation,
		    RRScreenSizePtr	pSize,
		    RRVisualGroupPtr	pVisualGroup)
{
    KdScreenPriv(pScreen);
    VesaModePtr		mode;
    KdScreenInfo	*screen = pScreenPriv->screen;
    VesaCardPrivPtr	priv = pScreenPriv->card->driver;
    VesaScreenPrivPtr	pscr = pScreenPriv->screen->driver;
    int			n;
    Bool		wasEnabled = pScreenPriv->enabled;
    Bool		ret = FALSE;
    VesaScreenPrivRec	oldscr;
    int			oldwidth;
    int			oldheight;
    int			oldmmwidth;
    int			oldmmheight;
    LayerPtr		pNewLayer;
    int			newwidth, newheight;

    if (screen->rotation == 0 || screen->rotation == 180)
    {
	newwidth = pSize->width;
	newheight = pSize->height;
    }
    else
    {
	newwidth = pSize->height;
	newheight = pSize->width;
    }

    for (n = 0; n < priv->nmode; n++)
    {
	mode = &priv->modes[n];
	if (vesaModeSupported (priv, mode, FALSE))
	{
	    /* 
	     * XXX all we have to match is the size
	     */
	    if (mode->XResolution == newwidth &&
		mode->YResolution == newheight &&
		mode->NumberOfPlanes == pscr->mode.NumberOfPlanes &&
		mode->BitsPerPixel == pscr->mode.BitsPerPixel &&
		mode->RedMaskSize == pscr->mode.RedMaskSize &&
		mode->RedFieldPosition == pscr->mode.RedFieldPosition &&
		mode->GreenMaskSize == pscr->mode.GreenMaskSize &&
		mode->GreenFieldPosition == pscr->mode.GreenFieldPosition &&
		mode->BlueMaskSize == pscr->mode.BlueMaskSize &&
		mode->BlueFieldPosition == pscr->mode.BlueFieldPosition)
		break;
	}
    }
    if (n == priv->nmode)
	goto bail0;
    
    if (wasEnabled)
	KdDisableScreen (pScreen);

    if (mode->mode != pscr->mode.mode)
    {
	ret = vesaSetMode (pScreen, mode);
	if (!ret)
	    goto bail1;

    }

    oldscr = *pscr;
    
    oldwidth = screen->width;
    oldheight = screen->height;
    oldmmwidth = pScreen->mmWidth;
    oldmmheight = pScreen->mmHeight;
    
    /*
     * Set new configuration
     */
    
    pscr->mode = *mode;
    switch (rotation) {
    case RR_Rotate_0:	pscr->rotate = 0; break;
    case RR_Rotate_90:	pscr->rotate = 90; break;
    case RR_Rotate_180:	pscr->rotate = 180; break;
    case RR_Rotate_270:	pscr->rotate = 270; break;
    }

    pscr->rotate += screen->rotation;
    if (pscr->rotate >= 360)
	pscr->rotate -= 360;

    /*
     * Can't rotate some formats
     */
    switch (screen->fb[0].bitsPerPixel) {
    case 8:
    case 16:


    case 32:
	break;
    default:
	if (pscr->rotate)
	    goto bail2;
	break;
    }

    vesaUnmapFramebuffer (screen);
    if (!vesaMapFramebuffer (screen))
	goto bail3;
    
#if 0
    /*
     * XXX can't switch depths yet
     */
    screen->fb[0].depth = depth;
    screen->fb[0].bitsPerPixel = bpp;
#endif
    screen->fb[0].byteStride = mode->BytesPerScanLine;
    screen->fb[0].pixelStride = ((mode->BytesPerScanLine * 8) / screen->fb[0].bitsPerPixel);
    
    /*
     * Compute screen geometry 
     */
    vesaConfigureScreen (pScreen);

    /*
     * Set frame buffer mapping
     */
    if (!pscr->shadow)

    {
	(*pScreen->ModifyPixmapHeader) (fbGetScreenPixmap (pScreen),
					pScreen->width,
					pScreen->height,
					screen->fb[0].depth,
					screen->fb[0].bitsPerPixel,
					screen->fb[0].byteStride,
					screen->fb[0].frameBuffer);
    }
	
    /*
     * Create the layer
     */
    pNewLayer = vesaLayerCreate (pScreen);
    if (!pNewLayer)
	goto bail4;
    
    if (WalkTree (pScreen, vesaLayerAdd, (pointer) pNewLayer) == WT_STOPWALKING)
	goto bail5;
    
    WalkTree (pScreen, vesaLayerRemove, (pointer) pscr->pLayer);
    LayerDestroy (pScreen, pscr->pLayer);

    pscr->pLayer = pNewLayer;


    if (wasEnabled)
	KdEnableScreen (pScreen);

    return TRUE;

bail5:

    WalkTree (pScreen, vesaLayerRemove, (pointer) pNewLayer);
    LayerDestroy (pScreen, pNewLayer);
bail4:
    vesaUnmapFramebuffer (screen);
    *pscr = oldscr;
    (void) vesaMapFramebuffer (screen);
    
bail3:
    pScreen->width = oldwidth;
    pScreen->height = oldheight;
    pScreen->mmWidth = oldmmwidth;
    pScreen->mmHeight = oldmmheight;
    
bail2:
    *pscr = oldscr;
    
    /*
     * Set frame buffer mapping
     */
    if (!pscr->shadow)
    {
	(*pScreen->ModifyPixmapHeader) (fbGetScreenPixmap (pScreen),
					pScreen->width,
					pScreen->height,
					screen->fb[0].depth,
					screen->fb[0].bitsPerPixel,
					screen->fb[0].byteStride,
					screen->fb[0].frameBuffer);
    }

    (void) vesaSetMode (pScreen, &pscr->mode);


bail1:
    if (wasEnabled)
	KdEnableScreen (pScreen);
bail0:
    
    return FALSE;
}

Bool
vesaRandRInit (ScreenPtr pScreen)
{
    rrScrPrivPtr    pScrPriv;
    
    if (!RRScreenInit (pScreen))
	return FALSE;

    pScrPriv = rrGetScrPriv(pScreen);
    pScrPriv->rrGetInfo = vesaRandRGetInfo;
    pScrPriv->rrSetConfig = vesaRandRSetConfig;
    return TRUE;
}
#endif
#endif



#ifndef TOSHIBA_SMM

# ifndef __netbas__
#  define TOSHIBA_SMM 1
# endif

# ifndef TOSHIBA_SMM
#  define TOSHIBA_SMM 0
# endif

#endif

#if TOSHIBA_SMM
/*
 * Toshiba laptops use a special interface to operate the backlight
 */
#include <sys/ioctl.h>
#define TOSH_PROC "/proc/toshiba"
#define TOSH_DEVICE "/dev/toshiba"
#define TOSH_SMM _IOWR('t', 0x90, 24)

typedef struct {
	unsigned int eax;
	unsigned int ebx __attribute__ ((packed));
	unsigned int ecx __attribute__ ((packed));
	unsigned int edx __attribute__ ((packed));
	unsigned int esi __attribute__ ((packed));
	unsigned int edi __attribute__ ((packed));
} SMMRegisters;

#define HCI_BACKLIGHT	0x0002
#define HCI_DISABLE	0x0000
#define HCI_ENABLE	0x0001
#define HCI_GET		0xfe00,
#define HCI_SET		0xff00

Bool
toshibaDPMS (ScreenPtr pScreen, int mode)
{
    SMMRegisters    regs;
    static int	    fd;

    if (!fd)
	fd = open (TOSH_DEVICE, 2);
    if (fd < 0)
	return FALSE;
    regs.eax = HCI_SET;
    regs.ebx = HCI_BACKLIGHT;
    regs.ecx = mode ? HCI_DISABLE : HCI_ENABLE;
    if (ioctl (fd, TOSH_SMM, &regs) < 0)


	return FALSE;
    return TRUE;
}
#endif /* TOSHIBA_SMM */




