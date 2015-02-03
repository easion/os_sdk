/***************************************************************************
    begin                : Mon Sep 22 2003
    copyright            : (C) 2003 - 2007 by Alper Akcan
    email                : distchx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "../lib/xynth_.h"
#include "server.h"
#include "kbd_map.h"
#include "video/helper/kbd.h"

void s_server_kbd_switch_handler (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
        int f = -1;
	s_video_input_t *keybd;
	keybd = (s_video_input_t *) handler->data;

        switch (event->keybd->button) {
		case S_KEYCODE_F1:  f = 1;  break;
		case S_KEYCODE_F2:  f = 2;  break;
		case S_KEYCODE_F3:  f = 3;  break;
		case S_KEYCODE_F4:  f = 4;  break;
		case S_KEYCODE_F5:  f = 5;  break;
		case S_KEYCODE_F6:  f = 6;  break;
		case S_KEYCODE_F7:  f = 7;  break;
		case S_KEYCODE_F8:  f = 8;  break;
		case S_KEYCODE_F9:  f = 9;  break;
		case S_KEYCODE_F10: f = 10; break;
	};

	if (f >= 0) {
#if defined(VIDEO_HELPER_CONSOLE)
		int s_video_helper_console_switch (int);
		s_video_helper_console_switch(f);
#endif
		memset(server->window->event->keybd, 0, sizeof(s_keybd_t));
		server->window->event->type &= ~KEYBD_MASK;
	}
}

void s_server_kbd_window_close_handler (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_close(window);
}

void s_server_kbd_server_quit_handler (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_quit(window);
}

#include <netbas/kbd.h>


static unsigned char scanCodes[255]={
	0,0x1b,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t', /* 0x00 - 0x0F */
	'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s', /* 0x10 - 0x1F */
	'd','f','g','h','j','k','l',';','\'',0,0,'#','z','x','c','v', /* 0x20 - 0x2F */
	'b','n','m',',','.','/',0,0,0,' ',0,0,0,0,0,0, /* 0x30 - 0x3F */
	0,0,0,0,0,0,0,'7','8','9',0,'4','5','6',0,'1', /* 0x40 - 0x4F */
	'2','3',0,0,0,0,'\\','4','5','6','7','8','9',0,0,0, /* 0x50 - 0x5F */
};

static unsigned char shiftScanCodes[255]={
	0,0,'!','"',0xA3,'$','%','^','&','*','(',')','_','+','\b', /* 0x00 - 0x0F */
	0,'Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,'A', /* 0x10 - 0x1F */
	'S','D','F','G','H','J','K','L',':','@',0,0,'~',
	'Z','X','C','V','B','N','M','<','>','?',0,
	0,0,
	' ',
	0,0,0,0,0,0,0,0,0,0, /* Function keys */
	0,0,0,0,0,0,0,0,0,0,0,'1','2','3',0,0,'4','5','|','7','8','9',
};
#include <xynth/xynth.h>
#include <netbas/kbd.h>
#include <netbas/netbas.h>
#define KEYCODES	27

#define NCE_KEY_RETURN NCE_KEY_ENTER 
static S_KEYCODE_CODE keycodes_c[KEYCODES] = {S_KEYCODE_F1, S_KEYCODE_F2, S_KEYCODE_F3, S_KEYCODE_F4, S_KEYCODE_F5,
					      S_KEYCODE_F6, S_KEYCODE_F7, S_KEYCODE_F8, S_KEYCODE_F9, S_KEYCODE_F10,
                                              S_KEYCODE_F11, S_KEYCODE_F12, S_KEYCODE_TAB, S_KEYCODE_END, S_KEYCODE_HOME,
                                              S_KEYCODE_UP, S_KEYCODE_DOWN, S_KEYCODE_LEFT, S_KEYCODE_RIGHT, S_KEYCODE_RETURN,
                                              S_KEYCODE_DELETE, S_KEYCODE_INSERT, S_KEYCODE_REMOVE, S_KEYCODE_ESCAPE,
                                              S_KEYCODE_PAGEUP, S_KEYCODE_PAGEDOWN, S_KEYCODE_KP_ENTER};
static unsigned char keycodes_netbas[KEYCODES] = {NCE_KEY_F1, NCE_KEY_F2, NCE_KEY_F3, NCE_KEY_F4, NCE_KEY_F5,
					      NCE_KEY_F6, NCE_KEY_F7, NCE_KEY_F8, NCE_KEY_F9, NCE_KEY_F10,
                                              NCE_KEY_F11, NCE_KEY_F12, NCE_KEY_TAB, NCE_KEY_END, NCE_KEY_HOME,
                                              NCE_KEY_UP, NCE_KEY_DOWN, NCE_KEY_LEFT, NCE_KEY_RIGHT, NCE_KEY_RETURN,
                                              NCE_KEY_BACKSPACE, NCE_KEY_INS,  NCE_KEY_DELETE, NCE_KEY_ESCAPE,
                                              NCE_KEY_PAGEUP, NCE_KEY_PAGEDOWN, NCE_KEY_ENTER};


static char *keycodes_s[KEYCODES] = {"\033[[A", "\033[[B", "\033[[C", "\033[[D", "\033[[E",
	"\033[17~", "\033[18~",     "\033[19~", "\033[20~", "\033[21~",
	"\033[23~", "\033[24~", "\t", "\033[4~",    "\033[1~", 
	"\033[A", "\033[B", "\033[D", "\033[C", "\n",
	"\010", "\033[2~",    "\033[3~", "\033",
	"\033[5~", "\033[6~", "\n"};

int find_kbd(unsigned char code)
{
	int i;

	for (i = 0; i < KEYCODES; i++) {
		if (keycodes_netbas[i] == code) {
			return keycodes_c[i];
		}
	}

	return -1;
}

int s_video_helper_kbd_update(s_video_input_data_t* keybd)
{
	int n;
	unsigned char scan, key;
	int key2;
	S_KEYCODE_FLAG flag = server->window->event->keybd->flag;

	read(0, &scan, 1);
#if 0	
	keybd->keybd.state = (scan & 0x80) ? KEYBD_RELEASED : KEYBD_PRESSED;
	//keybd->keybd.state =  KEYBD_PRESSED;

	key=(scan & 0x7F);
	//key=(scan );
	keybd->keybd.scancode=scan;
	
	keybd->keybd.button = s_video_helper_keybd_keycode_[key][KEYCODE_PLAIN];
	keybd->keybd.keycode = s_video_helper_keybd_keycode_[key][KEYCODE_PLAIN];

	switch (keybd->keybd.button)
	{
		case S_KEYCODE_LEFTSHIFT:
		case S_KEYCODE_RIGHTSHIFT:
		case S_KEYCODE_LEFTCONTROL:
		case S_KEYCODE_RIGHTCONTROL:
		case S_KEYCODE_ALT:
		case S_KEYCODE_ALTGR:
		case S_KEYCODE_CAPS_LOCK:
			return 0; /* CHECK */
		default:
			break;
	}
	
	if ((flag & KEYCODE_LSHIFTF) || (flag & KEYCODE_RSHIFTF))
		keybd->keybd.ascii = shiftScanCodes[key];
	else
		keybd->keybd.ascii=scanCodes[key];
#else
	keybd->keybd.state =  KEYBD_PRESSED;
	key2 = find_kbd(scan);

	if (key2>0)
	{
	keybd->keybd.button = (unsigned char)key2;
	keybd->keybd.keycode = (unsigned char)key2;	
	keybd->keybd.scancode=key2;
	}
	else{
	keybd->keybd.button = scan;
	keybd->keybd.keycode = scan;	
	keybd->keybd.scancode=scan;
	}

	keybd->keybd.ascii = scan;
#endif

	return 0;
}





int s_server_kbd_update (s_window_t *window, s_pollfd_t *pfd)
{
	int force_release = 0;
	s_video_input_data_t kdata;
	server->window->event->type = 0;
	memset(&kdata, 0, sizeof(s_video_input_data_t));
	if (s_video_helper_kbd_update(&kdata))
		return 0;

	s_server_event_parse_keyboard(&(kdata.keybd));
	s_server_event_changed();
	if (force_release) {
		server->window->event->type = 0;
		kdata.keybd.state = KEYBD_RELEASED;
		s_server_event_parse_keyboard(&(kdata.keybd));
		s_server_event_changed();
	}
	return 0;
}

#include <sys/time.h> /* struct timeval, select() */
/* ICANON, ECHO, TCSANOW, struct termios */
#include <termios.h> /* tcgetattr(), tcsetattr() */
#include <stdlib.h> /* atexit(), exit() */
#include <unistd.h> /* read() */
#include <stdio.h> /* printf() */

static struct termios g_old_kbd_mode;
/*****************************************************************************
*****************************************************************************/
static void cooked(void)
{
	tcsetattr(0, TCSANOW, &g_old_kbd_mode);
}
/*****************************************************************************
*****************************************************************************/
static void raw(void)
{
/**/
	struct termios new_kbd_mode;

/* put keyboard (stdin, actually) in raw, unbuffered mode */
	tcgetattr(0, &g_old_kbd_mode);
	memcpy(&new_kbd_mode, &g_old_kbd_mode, sizeof(struct termios));
	new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
	new_kbd_mode.c_cc[VTIME] = 0;
	new_kbd_mode.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_kbd_mode);
/* when we exit, go back to normal, "cooked" mode */
	atexit(cooked);

}
#define TRAWON		0x7400
#define TRAWOFF		0x7401
int KbdInit()
{
#ifndef SERVER_DISABLE_GRAPHICS
	//SysIoCtl(1, 1, 7);
#endif

//	SysIoCtl(1, 1, 4);

	//raw();
#if 0	

	ioctl(0,TRAWON,NULL);
#endif

	return 0;
}

void s_server_kbd_init (s_server_conf_t *cfg)
{
	int i;
	int fd = -1;
	s_pollfd_t *pfd;
	s_handler_t *hndl;

    fd=KbdInit();

	if (fd < 0)
		return;

	s_pollfd_init(&pfd);
	pfd->fd = fd;
        pfd->pf_in = s_server_kbd_update;
        pfd->pf_close = s_server_kbd_uninit;
        pfd->data = NULL;
        //s_event_add(server->window, pfd);
        s_pollfd_add(server->window, pfd);

        s_handler_init(&hndl);
        hndl->type = KEYBD_HANDLER;
	hndl->keybd.flag = KEYCODE_LALTF;
	hndl->keybd.button = S_KEYCODE_F4;
	hndl->keybd.p = s_server_kbd_window_close_handler;
	s_handler_add(server->window, hndl);

        s_handler_init(&hndl);
        hndl->type = KEYBD_HANDLER;
	hndl->keybd.flag = KEYCODE_LCTRLF | KEYCODE_LALTF;
	hndl->keybd.button = S_KEYCODE_DELETE;
	hndl->keybd.p = s_server_kbd_server_quit_handler;
	s_handler_add(server->window, hndl);

	for (i = 1; i <= 10; i++) {
	        s_handler_init(&hndl);
        	hndl->type = KEYBD_HANDLER;
		hndl->keybd.flag = KEYCODE_LSHIFTF;
	        switch (i) {
			case 1:  hndl->keybd.button = S_KEYCODE_F1;  break;
			case 2:  hndl->keybd.button = S_KEYCODE_F2;  break;
			case 3:  hndl->keybd.button = S_KEYCODE_F3;  break;
			case 4:  hndl->keybd.button = S_KEYCODE_F4;  break;
			case 5:  hndl->keybd.button = S_KEYCODE_F5;  break;
			case 6:  hndl->keybd.button = S_KEYCODE_F6;  break;
			case 7:  hndl->keybd.button = S_KEYCODE_F7;  break;
			case 8:  hndl->keybd.button = S_KEYCODE_F8;  break;
			case 9:  hndl->keybd.button = S_KEYCODE_F9;  break;
			case 10: hndl->keybd.button = S_KEYCODE_F10; break;
		};
		hndl->keybd.p = s_server_kbd_switch_handler;
		hndl->data = NULL;
		s_handler_add(server->window, hndl);
	}
}

int s_server_kbd_uninit (s_window_t *window, s_pollfd_t *pfd)
{
	printf("kbd_uninit\n");
	s_server_quit(server->window);
	ioctl(0,TRAWOFF,NULL);
    return 0;
}

S_KEYCODE_CODE s_server_keyname_to_keycode (char *name)
{
	unsigned int i;
	for (i = 0; i < S_KEYCODE_CODES; i++) {
		if (strcmp(name, s_keycodes_map[i].name) == 0) {
			return s_keycodes_map[i].code;
		}
	}
	return 0;
}
