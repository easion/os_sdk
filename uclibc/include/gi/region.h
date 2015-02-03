/* $XConsortium: region.h,v 11.14 94/04/17 20:22:20 rws Exp $ */
/************************************************************************

Copyright (c) 1987  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

************************************************************************/

#ifndef _XREGION_H
#define _XREGION_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NULL
#define NULL 0
#endif
/*
#define Xfree(ptr) FREE((ptr))

# define Xmalloc(size) MALLOC((size))
# define Xrealloc(ptr, size) realloc((ptr), (size))
# define Xcalloc(nelem, elsize) calloc((nelem), (elsize))



typedef struct {
    short x, y, width, height;
}  *RectanglePtr;

typedef struct {
    short x, y;
    unsigned short width, height;
} XRectangle;
*/

/* Return values from XRectInRegion() */

#define RectangleOut 0
#define RectangleIn  1
#define RectanglePart 2


#define MAXSHORT 32767
#define MINSHORT -MAXSHORT
#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif



/* Xutil.h contains the declaration: 
 * typedef struct _g_region *gi_region_ptr_t; 
 */   

/*  1 if two BOXs overlap.
 *  0 if two BOXs do not overlap.
 *  Remember, x2 and y2 are not in the region 
 */
#define EXTENTCHECK(r1, r2) \
	((r1)->x2 > (r2)->x1 && \
	 (r1)->x1 < (r2)->x2 && \
	 (r1)->y2 > (r2)->y1 && \
	 (r1)->y1 < (r2)->y2)

/*
 *  update region extents
 */
#define EXTENTS(r,idRect){\
            if((r)->x1 < (idRect)->extents.x1)\
              (idRect)->extents.x1 = (r)->x1;\
            if((r)->y1 < (idRect)->extents.y1)\
              (idRect)->extents.y1 = (r)->y1;\
            if((r)->x2 > (idRect)->extents.x2)\
              (idRect)->extents.x2 = (r)->x2;\
            if((r)->y2 > (idRect)->extents.y2)\
              (idRect)->extents.y2 = (r)->y2;\
        }




/*
 *   Check to see if there is enough memory in the present region.
 */
#define MEMCHECK(reg, rect, firstrect){\
        if ((reg)->numRects >= ((reg)->size - 1)){\
          (firstrect) = (gi_boxrec_t *) Xrealloc \
          ((char *)(firstrect), (unsigned) (2 * (sizeof(gi_boxrec_t)) * ((reg)->size)));\
          if ((firstrect) == 0)\
            return(0);\
          (reg)->size *= 2;\
          (rect) = &(firstrect)[(reg)->numRects];\
         }\
       }

/*  this routine checks to see if the previous rectangle is the same
 *  or subsumes the new rectangle to add.
 */

#define CHECK_PREVIOUS(Reg, R, Rx1, Ry1, Rx2, Ry2)\
               (!(((Reg)->numRects > 0)&&\
                  ((R-1)->y1 == (Ry1)) &&\
                  ((R-1)->y2 == (Ry2)) &&\
                  ((R-1)->x1 <= (Rx1)) &&\
                  ((R-1)->x2 >= (Rx2))))

/*  add a rectangle to the given Region */
#define ADDRECT(reg, r, rx1, ry1, rx2, ry2){\
    if (((rx1) < (rx2)) && ((ry1) < (ry2)) &&\
        CHECK_PREVIOUS((reg), (r), (rx1), (ry1), (rx2), (ry2))){\
              (r)->x1 = (rx1);\
              (r)->y1 = (ry1);\
              (r)->x2 = (rx2);\
              (r)->y2 = (ry2);\
              EXTENTS((r), (reg));\
              (reg)->numRects++;\
              (r)++;\
            }\
        }



/*  add a rectangle to the given Region */
#define ADDRECTNOX(reg, r, rx1, ry1, rx2, ry2){\
            if ((rx1 < rx2) && (ry1 < ry2) &&\
                CHECK_PREVIOUS((reg), (r), (rx1), (ry1), (rx2), (ry2))){\
              (r)->x1 = (rx1);\
              (r)->y1 = (ry1);\
              (r)->x2 = (rx2);\
              (r)->y2 = (ry2);\
              (reg)->numRects++;\
              (r)++;\
            }\
        }

#define EMPTY_REGION(pReg) pReg->numRects = 0

#define REGION_NOT_EMPTY(pReg) pReg->numRects

#define INBOX(r, x, y) \
      ( ( ((r).x2 >  x)) && \
        ( ((r).x1 <= x)) && \
        ( ((r).y2 >  y)) && \
        ( ((r).y1 <= y)) )

/*
 * number of points to buffer before sending them off
 * to scanlines() :  Must be an even number
 */
#define NUMPTSTOBUFFER 200

#if 0
/*
 * used to allocate buffers for points and link
 * the buffers together
 */
typedef struct _POINTBLOCK {
    gi_point_t pts[NUMPTSTOBUFFER];
    struct _POINTBLOCK *next;
} POINTBLOCK;
#endif

#ifndef XLIB_ILLEGAL_ACCESS
//int XSetRegion( gi_gc_ptr_t gcid, gi_region_ptr_t r );
int XSetGCRegion(gi_gc_ptr_t gc,gi_region_ptr_t r );
int XSetClipMask(   gi_gc_ptr_t	,    gi_window_id_t		/* pixmap */);
//int gi_set_gc_clip_rectangles(  gi_gc_ptr_t gcid,register gi_cliprect_t * r , int num);

gi_region_ptr_t XCreateRegion(void);
int XClipBox( gi_region_ptr_t r, gi_cliprect_t *rect );
int XUnionRectWithRegion(gi_cliprect_t *rect, gi_region_ptr_t source, gi_region_ptr_t dest);
int XUnionBoxWithRegion(gi_boxrec_t *rect, gi_region_ptr_t source, gi_region_ptr_t dest);
int XDestroyRegion( gi_region_ptr_t r );
int XOffsetRegion(gi_region_ptr_t pRegion, int x, int y);
int XShrinkRegion(gi_region_ptr_t r, int dx, int dy);
int XIntersectRegion(gi_region_ptr_t reg1, gi_region_ptr_t reg2, gi_region_ptr_t newReg);
int XUnionRegion(gi_region_ptr_t reg1, gi_region_ptr_t reg2, gi_region_ptr_t newReg);
int XSubtractRegion(gi_region_ptr_t regM, gi_region_ptr_t regS, gi_region_ptr_t regD);
int XXorRegion( gi_region_ptr_t sra, gi_region_ptr_t srb, gi_region_ptr_t dr );
int XEmptyRegion( gi_region_ptr_t r );
int XEqualRegion( gi_region_ptr_t r1, gi_region_ptr_t r2 );
int XPointInRegion( gi_region_ptr_t pRegion, int x, int y );
int XRectInRegion(gi_region_ptr_t region, int rx, int ry, unsigned int rwidth, unsigned int rheight);
int XSetWindowRegion(gi_window_id_t window,gi_region_ptr_t r );
int gi_set_window_paint_region(gi_window_id_t window,gi_region_ptr_t r );

gi_region_ptr_t XCreateRoundRectRegion( int left, int top, int right, int bottom,
	int ellipse_width, int ellipse_height );
#endif


void XSetRectRegion(gi_region_ptr_t rgn, int left, int top, int right,
	int bottom);
void XSetRectRegionIndirect(gi_region_ptr_t rgn, gi_cliprect_t *pcr);
gi_region_t* gi_create_region_from_bitmap(const char*buffer, int width,	int height);
gi_region_t*gi_create_region_from_pixmap(gi_window_id_t src, int x, int y, int width,	int height);
gi_region_t* gi_create_region_from_bitmap_pitch(const char*buffer, int width,  int height, int pitch);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
