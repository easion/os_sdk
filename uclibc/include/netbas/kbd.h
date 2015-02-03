
#ifndef __KBD_H__
#define __KBD_H__

#define	NCE_KEY_F1		0x80
#define	NCE_KEY_ESCAPE		0x1b
#define	NCE_KEY_F2		0x81   //(NCE_KEY_F1 + 1)
#define	NCE_KEY_F3		0x82   //(NCE_KEY_F2 + 1)
#define	NCE_KEY_F4		0x83   //(NCE_KEY_F3 + 1)
#define	NCE_KEY_F5		0x84   //(NCE_KEY_F4 + 1)
#define	NCE_KEY_F6		0x85   //(NCE_KEY_F5 + 1)
#define	NCE_KEY_F7		0x86   //(NCE_KEY_F6 + 1)
#define	NCE_KEY_F8		0x87   //(NCE_KEY_F7 + 1)
#define	NCE_KEY_F9		0x88   //(NCE_KEY_F8 + 1)
#define	NCE_KEY_F10	0x89	//(NCE_KEY_F9 + 1)
#define	NCE_KEY_F11	0x8a	//(NCE_KEY_F10 + 1)
#define	NCE_KEY_F12	0x8b   //	(NCE_KEY_F11 + 1)
/* cursor keys */
#define	NCE_KEY_INS		0x90
#define	NCE_KEY_INSERT NCE_KEY_INS
#define	NCE_KEY_DELETE		0x91 //(NCE_KEY_INS + 1)
#define	NCE_KEY_HOME	0x92 //(NCE_KEY_DEL + 1)
#define	NCE_KEY_END		0x93 //(NCE_KEY_HOME + 1)
#define	NCE_KEY_PAGEUP	0x94 //(NCE_KEY_END + 1)
#define	NCE_KEY_PAGEDOWN	0x95 //(NCE_KEY_PGUP + 1)
#define	NCE_KEY_LEFT		0x96 //(NCE_KEY_PGDN + 1)
#define	NCE_KEY_UP		     0x97 //(NCE_KEY_LFT + 1)
#define	NCE_KEY_DOWN		0x98 //(NCE_KEY_UP + 1)
#define	NCE_KEY_RIGHT		     0x99 //(NCE_KEY_DN + 1)
/* print screen/sys rq and pause/break */
#define	NCE_KEY_PRNT	  0x9a //(NCE_KEY_RT + 1)
#define	NCE_KEY_PAUSE	0x9b //(NCE_KEY_PRNT + 1)
/* these return a value but they could also act as additional bucky keys */
#define	NCE_KEY_LWIN	   0x9c //(NCE_KEY_PAUSE + 1)
#define	NCE_KEY_RWIN	    0x9d //(NCE_KEY_LWIN + 1)
#define	NCE_KEY_MENU	    0x9f //(NCE_KEY_RWIN + 1)
#define	NCE_KEY_TAB	    '\t' //(NCE_KEY_RWIN + 1)
#define	NCE_KEY_ENTER	    '\n' //(NCE_KEY_RWIN + 1)
#define	NCE_KEY_BACKSPACE	    '\b' //(NCE_KEY_RWIN + 1)

#endif /* !__KBD_H__ */
