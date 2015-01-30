
#define JICAMA
#include <stdio.h> /* va_list, va_start(), va_end() */
#include <netbas/netbas.h>
#include <netbas/farptr.h>
#include <netbas/int86.h>



static unsigned ScreenAddress = 0xb8000UL; /* initialize just in case */
static unsigned short ScreenVirtualSegment = 0; /* 0: non DOS/V */
static unsigned short ScreenVirtualOffset = 0;  /* !0: DOS/V virtual VRAM address */
static int intense_bg_mode=0;         /* non-zero if high bit is for bright bg */

/* drawing state variables */
int _text_color = 0;
int _wscroll = 1;


int screen_h;

static int _text_x=0;
static int _text_y=0;
static int winleft=0;
static int winright=25;

static int wintop=0;
unsigned char ScreenAttrib = 0x07;

static void
getwincursor(int *row, int *col)
{
*row=_text_x;
*col=_text_y;
}
void
textattr(int attr)
{
   ScreenAttrib = (unsigned char)attr;
}


void
textcolor(int color)
{
  /* strip blinking (highest) bit and textcolor */
  int bg = ScreenAttrib & (intense_bg_mode ? 0xf0 : 0x70);
  ScreenAttrib = (bg | (color & (intense_bg_mode ? 0x0f : 0x8f)));
	if(color >= 8)
		printf("\x1B[%u;1m", 30 + (color & 7));
	else
		printf("\x1B[%u;0m", 30 + (color & 7));
}

void
textbackground(int color)
{
  /* strip background color from ScreenAttrib, keep blinking bit */
  int fg = ScreenAttrib & (intense_bg_mode ? 0x0f : 0x8f);

  /* high intensity background colors (>7) are not allowed, unless
     intense_bg_mode is on, so we strip 0x08 bit (and higher bits) of color */
  color &= (intense_bg_mode ? 0x0f : 0x07);
   ScreenAttrib = (fg | (color << 4));

	//printf("\x1B[%um", 40 + (color & 7));
} 

void	
ScreenSetCursor(int _row, int _col)
{
  __dpmi_regs r;
  r.h.ah = 2;
  r.h.bh = 0;
  r.h.dh = _row;
  r.h.dl = _col;
  __dpmi_int(0x10, &r);
}

void	
ScreenGetCursor(int *_row, int *_col)
{
  __dpmi_regs r;
  r.h.ah = 3;
  r.h.bh = 0;
  __dpmi_int(0x10, &r);
  *_row = r.h.dh;
  *_col = r.h.dl;
}


void	
ScreenPutChar(int _ch, int _attr, int _x, int _y)
{
  if ((_x < 0) || (_y < 0))
    return;
  if ((_x >= 80) || (_y >= 25))
    return;
  _ch &= 0xff;
  _attr = (_attr & 0xff) << 8;
  _farpokew(_dos_ds, 0xb8000 + (_x+_y*80)*2, _ch|_attr);
}

int
highvideo(void)
{
  return (ScreenAttrib |= 0x08);
}




 void
bell(void)
{
  __dpmi_regs regs;
  regs.h.ah = 0x0e;		/* write */
  regs.h.al = 0x07;		/* bell */
  __dpmi_int(0x10, &regs);
}

int 
get_screenattrib(void)
{
  __dpmi_regs regs;
  regs.h.ah = 0x08;		/* read character and attribute */
  regs.h.bh = 0;		/* video page 0 */
  __dpmi_int(0x10, &regs);
  return(regs.h.ah & 0x7f);	/* strip highest (BLINK) bit */
}

int
wherex(void)
{
 // int row, col;
  
 // ScreenGetCursor(&row, &col);
  
  return _text_x-winleft + 2;
}

int
wherey(void)
{
  //int row, col;
  
  //ScreenGetCursor(&row, &col);
  
  return _text_y - wintop + 2;
}

void sgotoxy(unsigned x, unsigned y)
{
	printf("\x1B[%u;%uH", y, x);
}



 void clear_screen(void)
{
	printf("\x1B[2J");
}

 void clrscr(void)
{
	printf("\x1B[2J");
}
void
blinkvideo(void)
{

  /* Set intensity/blinking bit to BLINKING.  */
  __dpmi_regs regs;
  regs.h.bl = 1;
  regs.x.ax = 0x1003;
  __dpmi_int(0x10, &regs);
  intense_bg_mode = (_farpeekb(_dos_ds, 0x465) & 0x20) == 0;
}

void
intensevideo(void)
{

  /* Set intensity/blinking bit to INTENSE (bright background).  */
  __dpmi_regs regs;
  regs.h.bl = 0;
  regs.x.ax = 0x1003;
  __dpmi_int(0x10, &regs);
  intense_bg_mode = (_farpeekb(_dos_ds, 0x465) & 0x20) == 0;
}
#define VIDADDR(r,c) (ScreenAddress + 2*(((r) * 80) + (c)))
#define VOFFSET(r,c) (ScreenVirtualOffset + 2*(((r) * 80) + (c)))
static void
refreshvirtualscreen(int c, int r, int count)
{
  __dpmi_regs regs;

  regs.x.es = ScreenVirtualSegment;
  regs.x.di = VOFFSET(r, c);
  regs.h.ah = 0xff;	/* Refresh Screen */
  regs.x.cx = count;	/* number of characters */
  __dpmi_int(0x10, &regs);
}
int
puttext(int c, int r, int c2, int r2, void *buf)
{
  short *cbuf = (short *)buf;
  /* we should check for valid parameters, and maybe return 0 */
  r--, r2--, c--, c2--;
  for (; r <= r2; r++)
  {
    dosmemput(cbuf, (c2-c+1)*2, VIDADDR(r, c));
    cbuf += c2-c+1;
    if (ScreenVirtualSegment != 0)    refreshvirtualscreen(c, r, c2-c+1);
  }
  return 1;
}
void
clreol(void)
{
  short   image[ 256 ];
  short   val = ' ' | (ScreenAttrib << 8);
  int     c, row, col, ncols;
  
  getwincursor(&row, &col);
  ncols = winright - col;
  
  for (c = 0; c < ncols; c++)
    image[ c ] = val;
  
  puttext(col + 1, row + 1, winright, row + 1, image);
}


int gotoxy(int _x, int _y)
{
	_text_x=(_x>25?25:_x);
	_text_y=(_y>80?80:_y);
	sgotoxy(_text_x,_text_y);
}


#define LINEAR(seg, off)	( (unsigned long)(((unsigned short)(seg) << 4) + (unsigned short)(off)) )
void dosmemput(const void *_buffer, size_t _length, unsigned long _offset);
void dosmemget(unsigned long _offset, size_t _length, void *_buffer);

void movedata (unsigned long src_sel, unsigned long src_offs, unsigned long dest_sel, unsigned long dest_offs,
                                                            unsigned long len) 
	{
		unsigned long ln;
		if (dest_sel==_dos_ds)
		{
			ln=LINEAR(src_sel, src_offs);
			dosmemput((void *)ln, len, dest_offs);
		}else{
			ln=LINEAR(dest_sel, dest_offs);
			dosmemget(src_offs, len, (void *) ln);
		}
	}
static int adapter_type = -1;       /* 1: EGA, 2: VGA/PGA/MCGA, else 0 */

static int
isEGA(void)
{
  if (adapter_type == -1)
    {
      __dpmi_regs regs;

      /* Get display combination code.  */
      regs.x.ax = 0x1a00;
      __dpmi_int(0x10, &regs);
      if (regs.h.al == 0x1a)    /* if Int 10h/AX=1A00h supported */
        switch (regs.h.bl)
          {
            case 4:
            case 5:
                adapter_type = 1; /* EGA */
                break;
            case 6:             /* PGA */
            case 7:             /* VGA */
            case 8:             /* VGA */
            case 10:            /* MCGA */
            case 11:            /* MCGA */
            case 12:            /* MCGA */
                adapter_type = 2;
                break;
            default:
                adapter_type = 0;
          }

      else
        {
          /* Int 10h/AX=1A00h not supported.  Try getting EGA info.  */
          regs.h.ah = 0x12;
          regs.h.bl = 0x10;
          regs.h.bh = 0xff;
          __dpmi_int(0x10, &regs);
          adapter_type = (regs.h.bh != 0xff);
        }
    }

  return adapter_type;
}


void
textmode(int mode)
{
  __dpmi_regs regs;
  int mode_to_set = mode;

  //if (mode == LASTMODE) mode = mode_to_set = last_mode;

  /* Should we support 2 LAST_MODEs in a row?  Right now we do; if not,
     put an ``else'' clause before next line.  */
  //last_mode = currmode;
  if (mode == C4350)
    /* 
     * just set mode 3 and load 8x8 font, idea taken 
     * (and code translated from Assembler to C)
     * from Csaba Biegels stdvga.asm
     */
    mode_to_set = 0x03;  
  regs.h.ah = 0x00;		/* set mode */
  regs.h.al = mode_to_set;
  __dpmi_int(0x10, &regs);
  if (mode == C80 || mode == BW80 || mode == C4350)
  {
    if (isEGA())
    {
      /* 
       * enable cursor size emulation, see Ralf Browns
       * interrupt list
       */
      regs.h.ah = 0x12;
      regs.h.bl = 0x34;
      regs.h.al = 0x00;		/* 0: enable (1: disable) */
      __dpmi_int(0x10, &regs);
    }
  }
  if (mode == C4350)
  {
    if (!isEGA())
      return;
    /* load 8x8 font */
    regs.x.ax = 0x1112;         
    regs.x.bx = 0;
    __dpmi_int(0x10, &regs);
  }
  regs.x.es = regs.x.di = 0;	/* Dummy for checking */
  regs.h.ah = 0xfe;		/* Get Video Buffer */
  __dpmi_int(0x10, &regs);
  ScreenVirtualSegment = regs.x.es;
  ScreenVirtualOffset = regs.x.di;
    ScreenVirtualSegment = regs.x.es;
  ScreenVirtualOffset = regs.x.di;
  if (ScreenVirtualSegment != 0)
    ScreenAddress = (ScreenVirtualSegment << 4UL) + ScreenVirtualOffset;
}    

tputs(const char *str, char c)
{
	int i, limit=strlen(str)*2;
	int pos=(_text_x*80+_text_y)*2;

	 _farsetsel(USER_GLOBAL_DATA);
	for ( i = 0; i < limit; i+=2 ) { 
		_farnspokeb(0xB8000+pos+i, *str++ );
		_farnspokeb( 0xB8000+pos+i+1, c);
		}
}

text_puts(int x, int y, const char *str, char c)
{
	int i, limit=strlen(str)*2;
	int pos=(x*80+y)*2;

	 _farsetsel(USER_GLOBAL_DATA);
	for ( i = 0; i < limit; i+=2 ) { 
		_farnspokeb(0xB8000+pos+i, *str++ );
		_farnspokeb( 0xB8000+pos+i+1, c);
		}
}




/* sets the drawing color */
void text_color(int c)
{
   _text_color = c;
}



/* sets the drawing position */
void text_pos(int x, int y)
{
   _text_x = x-1; 
   _text_y = y-1; 
}



/* prints a character */
void text_c(int c)
{
   if (_text_x < 80)
      _farpokew(USER_GLOBAL_DATA, 0xB8000+_text_x*2+_text_y*160, c|(_text_color<<8));

   _text_x++; 
}



/* prints a string */
void text_str(char *s) 
{ 
   while (*s) { 
      text_c((unsigned char)*s); 
      s++; 
   } 
}



/* prints the first part of a string */
void text_clamp(char *s, int max) 
{ 
   int i;

   if ((int)strlen(s) <= max) {
      text_str(s);
   }
   else {
      for (i=0; i<max; i++)
	 text_c((unsigned char)s[i]);

      text_str("..."); 
   }
}

/* clears to the end of the current line */
void text_clear_eol() 
{ 
   while (_text_x < 80)
      text_c(' ');
}

static void
fillrow(int row, int left, int right, int fill)
{
  int col;
  short filler[right-left+1];
  
  for (col = left; col <= right; col++)
    filler[col-left] = fill;
  dosmemput(filler, (right-left+1)*2, VIDADDR(row, left));
  if (ScreenVirtualSegment != 0)
    refreshvirtualscreen(left, row, right-left+1);
}
void
delline(void)
{
  int row, col, left, right, nbytes, bot, fill;
  ScreenGetCursor(&row, &col);
  left = winleft - 1;
  right = winright - 1;
  nbytes = (right-left+1)*2;
  bot = 25-1;
  fill = ' ' | (ScreenAttrib << 8);
  while(row < bot)
  {
    movedata(_dos_ds, VIDADDR(row+1, left),
	     _dos_ds, VIDADDR(row, left),
	     nbytes);
    if (ScreenVirtualSegment != 0)
      refreshvirtualscreen(left, row, nbytes/2);
    row++;
  }
  fillrow(bot,left,right,fill);
}

int
putch(int c)
{
  int     row, col;
  
  ScreenGetCursor(&row, &col);
  
  /*  first, handle the character */
  if (c == '\n')
  {
    row++;
  }
  else if (c == '\r')
  {
    col = winleft - 1;
  }
  else if (c == '\b')
  {
    if (col > winleft - 1)
      col--;  
    else if (row > wintop -1)
    {
      /* 
       * Turbo-C ignores this case; we are smarter.
       */
      row--;
      col = winright-1;
    }  
  }      
  else if (c == 0x07)
    bell();
  else {
    ScreenPutChar(c, ScreenAttrib, col, row);
    if (ScreenVirtualSegment != 0)
      refreshvirtualscreen(col, row, 1);
    col++;
  }
  
  /* now, readjust the window     */
  
  if (col >= winright)
  {
    col = winleft - 1;
    row++;
  }
  
  if (row >=25)//???winbottom)
  {
    /* scrollwin(0, winbottom - wintop, 1); */
    if (_wscroll)
    {
      ScreenSetCursor(wintop-1,0);
      delline();
    }
    row--;
  }
  
  ScreenSetCursor(row, col);
  _text_y = row - wintop + 2;
  _text_x = col - winleft + 2;
  return c;
}
