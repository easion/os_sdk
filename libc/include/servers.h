

#ifndef _SERVER_H
#define _SERVER_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __DLL__
typedef struct message
{
	u16_t self;
	u16_t xx;
	int func;
	int message_len;
	u32_t msg_addr;
}msg_t;

#define SEND		   1	/* function code for sending messages */
#define RECEIVE		   2	/* function code for receiving messages */
#define BOTH		   3	/* function code for SEND + RECEIVE */
#define REPLY		   4	/* function code for SEND + RECEIVE */

#define FIRST_KRNL_SERVER		48 ///this is a SERVER process



#define TTY_SERVER		FIRST_KRNL_SERVER+0 ///this is a SERVER process
#define DEV_SERVER		FIRST_KRNL_SERVER+1 ///this is a SERVER process
#define FS_SERVER		    FIRST_KRNL_SERVER+2 ///this is a SERVER process
#define NET_SERVER		FIRST_KRNL_SERVER+3 ///this is a SERVER process
#define GUI_SERVER		FIRST_KRNL_SERVER+4 ///this is a SERVER process
#define GFX_SERVER		FIRST_KRNL_SERVER+5 ///this is a SERVER process
#define FAT_SERVER		FS_SERVER ///this is a SERVER process
#define TCPIP_SERVER	FIRST_KRNL_SERVER+7 ///this is a SERVER process


int send(int task, msg_t *ptr);
int receive(int task, msg_t *ptr);
int reply(int task, msg_t *ptr);

int get_boot_arg(struct bparam_s *p);
int show_system_logo(int,int);
int tell_vesalfb(u32_t base, int x, int y, int bpp);
#endif


#ifdef __cplusplus
}
#endif
#endif 
