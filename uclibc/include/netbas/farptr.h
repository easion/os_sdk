
#ifndef __dj_include_sys_farptr_h_
#define __dj_include_sys_farptr_h_

#ifdef __cplusplus
extern "C" {
#endif



void _farpokeb(unsigned short, unsigned long, unsigned char);
void _farpokew(unsigned short, unsigned long, unsigned short);
void _farpokel(unsigned short, unsigned long, unsigned long);
unsigned char _farpeekb(unsigned short, unsigned long);
unsigned short _farpeekw(unsigned short, unsigned long);
unsigned long _farpeekl(unsigned short, unsigned long);
void _farsetsel(unsigned short);
unsigned short _fargetsel(void);
void _farnspokeb(unsigned long, unsigned char);
void _farnspokew(unsigned long, unsigned short);
void _farnspokel(unsigned long, unsigned long);
unsigned char _farnspeekb(unsigned long);
unsigned short _farnspeekw(unsigned long);
unsigned long _farnspeekl(unsigned long);

#define USER_GLOBAL_CODE 0X1b
#define USER_GLOBAL_DATA 0X23
#define DOS_DATA 0X30
#define VIDEO_DATA_SEG 0X3B


#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_sys_farptr_h_ */
