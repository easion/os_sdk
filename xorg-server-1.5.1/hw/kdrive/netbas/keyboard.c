

#ifdef HAVE_CONFIG_H
#include <kdrive-config.h>
#endif
#include "kdrive.h"
#include <linux/keyboard.h>
#include <linux/kd.h>
#define XK_PUBLISHING
#include <X11/keysym.h>
#include <termios.h>
#include <sys/ioctl.h>

extern int NetbasConsoleFd;

static int __linux_keymap[]={

/*0*/ 0x200, 0x200, 0x200, 0x27f,
/*1*/ 0x1b, 0x1b, 0x1b, 0x200,
/*2*/ 0x31, 0x21, 0x200, 0x200,
/*3*/ 0x32, 0x40, 0x40, 0x200,
/*4*/ 0x33, 0x23, 0x200, 0x200,
/*5*/ 0x34, 0x24, 0x24, 0x200,
/*6*/ 0x35, 0x25, 0x200, 0x200,
/*7*/ 0x36, 0x5e, 0x200, 0x200,
/*8*/ 0x37, 0x26, 0x7b, 0x200,
/*9*/ 0x38, 0x2a, 0x5b, 0x200,
/*10*/ 0x39, 0x28, 0x5d, 0x200,
/*11*/ 0x30, 0x29, 0x7d, 0x200,
/*12*/ 0x2d, 0x5f, 0x5c, 0x200,
/*13*/ 0x3d, 0x2b, 0x200, 0x200,
/*14*/ 0x7f, 0x7f, 0x7f, 0x200,
/*15*/ 0x9, 0x9, 0x9, 0x200,
/*16*/ 0xb71, 0xb51, 0xb71, 0x200,
/*17*/ 0xb77, 0xb57, 0xb77, 0x200,
/*18*/ 0xb65, 0xb45, 0xb65, 0x200,
/*19*/ 0xb72, 0xb52, 0xb72, 0x200,
/*20*/ 0xb74, 0xb54, 0xb74, 0x200,
/*21*/ 0xb79, 0xb59, 0xb79, 0x200,
/*22*/ 0xb75, 0xb55, 0xb75, 0x200,
/*23*/ 0xb69, 0xb49, 0xb69, 0x200,
/*24*/ 0xb6f, 0xb4f, 0xb6f, 0x200,
/*25*/ 0xb70, 0xb50, 0xb70, 0x200,
/*26*/ 0x5b, 0x7b, 0x200, 0x200,
/*27*/ 0x5d, 0x7d, 0x7e, 0x200,
/*28*/ 0x201, 0x201, 0x201, 0x200,
/*29*/ 0x702, 0x702, 0x702, 0x200,
/*30*/ 0xb61, 0xb41, 0xb61, 0x200,
/*31*/ 0xb73, 0xb53, 0xb73, 0x200,
/*32*/ 0xb64, 0xb44, 0xb64, 0x200,
/*33*/ 0xb66, 0xb46, 0xb66, 0x200,
/*34*/ 0xb67, 0xb47, 0xb67, 0x200,
/*35*/ 0xb68, 0xb48, 0xb68, 0x200,
/*36*/ 0xb6a, 0xb4a, 0xb6a, 0x200,
/*37*/ 0xb6b, 0xb4b, 0xb6b, 0x200,
/*38*/ 0xb6c, 0xb4c, 0xb6c, 0x200,
/*39*/ 0x3b, 0x3a, 0x200, 0x200,
/*40*/ 0x27, 0x22, 0x200, 0x200,
/*41*/ 0x60, 0x7e, 0x200, 0x200,
/*42*/ 0x700, 0x700, 0x700, 0x200,
/*43*/ 0x5c, 0x7c, 0x200, 0x200,
/*44*/ 0xb7a, 0xb5a, 0xb7a, 0x200,
/*45*/ 0xb78, 0xb58, 0xb78, 0x200,
/*46*/ 0xb63, 0xb43, 0x200, 0x200,
/*47*/ 0xb76, 0xb56, 0xb76, 0x200,
/*48*/ 0xb62, 0xb42, 0xb62, 0x200,
/*49*/ 0xb6e, 0xb4e, 0xb6e, 0x200,
/*50*/ 0xb6d, 0xb4d, 0xb6d, 0x200,
/*51*/ 0x2c, 0x3c, 0x200, 0x200,
/*52*/ 0x2e, 0x3e, 0x200, 0x200,
/*53*/ 0x2f, 0x3f, 0x200, 0x200,
/*54*/ 0x700, 0x700, 0x700, 0x200,
/*55*/ 0x30c, 0x30c, 0x916, 0x200,
/*56*/ 0x703, 0x703, 0x703, 0x200,
/*57*/ 0x20, 0x20, 0x20, 0x200,
/*58*/ 0x207, 0x207, 0x207, 0x200,
/*59*/ 0x100, 0x10c, 0x50c, 0x200,
/*60*/ 0x101, 0x10d, 0x50d, 0x200,
/*61*/ 0x102, 0x10e, 0x50e, 0x200,
/*62*/ 0x103, 0x10f, 0x50f, 0x200,
/*63*/ 0x104, 0x110, 0x510, 0x200,
/*64*/ 0x105, 0x111, 0x511, 0x200,
/*65*/ 0x106, 0x112, 0x512, 0x200,
/*66*/ 0x107, 0x113, 0x513, 0x200,
/*67*/ 0x108, 0x11e, 0x514, 0x200,
/*68*/ 0x109, 0x11f, 0x515, 0x200,
/*69*/ 0x208, 0x208, 0x914, 0x200,
/*70*/ 0x209, 0x203, 0x202, 0x200,
/*71*/ 0x307, 0x307, 0x911, 0x200,
/*72*/ 0x308, 0x308, 0x912, 0x200,
/*73*/ 0x309, 0x309, 0x913, 0x200,
/*74*/ 0x30b, 0x30b, 0x917, 0x200,
/*75*/ 0x304, 0x304, 0x90e, 0x200,
/*76*/ 0x305, 0x305, 0x90f, 0x200,
/*77*/ 0x306, 0x306, 0x910, 0x200,
/*78*/ 0x30a, 0x30a, 0x918, 0x200,
/*79*/ 0x301, 0x301, 0x90b, 0x200,
/*80*/ 0x302, 0x302, 0x90c, 0x200,
/*81*/ 0x303, 0x303, 0x90d, 0x200,
/*82*/ 0x300, 0x300, 0x90a, 0x200,
/*83*/ 0x310, 0x310, 0x310, 0x200,
/*84*/ 0x206, 0x206, 0x206, 0x200,
/*85*/ 0x200, 0x200, 0x200, 0x200,
/*86*/ 0x3c, 0x3e, 0x7c, 0x200,
/*87*/ 0x10a, 0x120, 0x516, 0x200,
/*88*/ 0x10b, 0x121, 0x517, 0x200,
/*89*/ 0x200, 0x200, 0x200, 0x200,
/*90*/ 0x200, 0x200, 0x200, 0x200,
/*91*/ 0x200, 0x200, 0x200, 0x200,
/*92*/ 0x200, 0x200, 0x200, 0x200,
/*93*/ 0x200, 0x200, 0x200, 0x200,
/*94*/ 0x200, 0x200, 0x200, 0x200,
/*95*/ 0x200, 0x200, 0x200, 0x200,
/*96*/ 0x30e, 0x30e, 0x919, 0x200,
/*97*/ 0x702, 0x702, 0x702, 0x200,
/*98*/ 0x30d, 0x30d, 0x915, 0x200,
/*99*/ 0x20e, 0x20e, 0x20e, 0x200,
/*100*/ 0x701, 0x701, 0x701, 0x200,
/*101*/ 0x205, 0x205, 0x205, 0x200,
/*102*/ 0x114, 0x114, 0x114, 0x200,
/*103*/ 0x603, 0x603, 0x603, 0x200,
/*104*/ 0x118, 0x20b, 0x118, 0x200,
/*105*/ 0x601, 0x601, 0x601, 0x200,
/*106*/ 0x602, 0x602, 0x602, 0x200,
/*107*/ 0x117, 0x117, 0x117, 0x200,
/*108*/ 0x600, 0x600, 0x600, 0x200,
/*109*/ 0x119, 0x20a, 0x119, 0x200,
/*110*/ 0x115, 0x115, 0x115, 0x200,
/*111*/ 0x116, 0x116, 0x116, 0x200,
/*112*/ 0x11a, 0x11a, 0x11a, 0x200,
/*113*/ 0x10c, 0x10c, 0x10c, 0x200,
/*114*/ 0x10d, 0x10d, 0x10d, 0x200,
/*115*/ 0x11b, 0x11b, 0x11b, 0x200,
/*116*/ 0x11c, 0x11c, 0x11c, 0x200,
/*117*/ 0x110, 0x110, 0x110, 0x200,
/*118*/ 0x311, 0x311, 0x311, 0x200,
/*119*/ 0x11d, 0x11d, 0x11d, 0x200,
/*120*/ 0x200, 0x200, 0x200, 0x200,
/*121*/ 0x200, 0x200, 0x200, 0x200,
/*122*/ 0x200, 0x200, 0x200, 0x200,
/*123*/ 0x200, 0x200, 0x200, 0x200,
/*124*/ 0x200, 0x200, 0x200, 0x200,
/*125*/ 0x200, 0x200, 0x200, 0x200,
/*126*/ 0x200, 0x200, 0x200, 0x200,
/*127*/ 0x200, 0x200, 0x200, 0x200,
/*128*/ 0x200, 0x200, 0x200, 0x200,
/*129*/ 0x200, 0x200, 0x200, 0x200,
/*130*/ 0x200, 0x200, 0x200, 0x200,
/*131*/ 0x200, 0x200, 0x200, 0x200,
/*132*/ 0x200, 0x200, 0x200, 0x200,
/*133*/ 0x200, 0x200, 0x200, 0x200,
/*134*/ 0x200, 0x200, 0x200, 0x200,
/*135*/ 0x200, 0x200, 0x200, 0x200,
/*136*/ 0x200, 0x200, 0x200, 0x200,
/*137*/ 0x200, 0x200, 0x200, 0x200,
/*138*/ 0x200, 0x200, 0x200, 0x200,
/*139*/ 0x200, 0x200, 0x200, 0x200,
/*140*/ 0x200, 0x200, 0x200, 0x200,
/*141*/ 0x200, 0x200, 0x200, 0x200,
/*142*/ 0x200, 0x200, 0x200, 0x200,
/*143*/ 0x200, 0x200, 0x200, 0x200,
/*144*/ 0x200, 0x200, 0x200, 0x200,
/*145*/ 0x200, 0x200, 0x200, 0x200,
/*146*/ 0x200, 0x200, 0x200, 0x200,
/*147*/ 0x200, 0x200, 0x200, 0x200,
/*148*/ 0x200, 0x200, 0x200, 0x200,
/*149*/ 0x200, 0x200, 0x200, 0x200,
/*150*/ 0x200, 0x200, 0x200, 0x200,
/*151*/ 0x200, 0x200, 0x200, 0x200,
/*152*/ 0x200, 0x200, 0x200, 0x200,
/*153*/ 0x200, 0x200, 0x200, 0x200,
/*154*/ 0x200, 0x200, 0x200, 0x200,
/*155*/ 0x200, 0x200, 0x200, 0x200,
/*156*/ 0x200, 0x200, 0x200, 0x200,
/*157*/ 0x200, 0x200, 0x200, 0x200,
/*158*/ 0x200, 0x200, 0x200, 0x200,
/*159*/ 0x200, 0x200, 0x200, 0x200,
/*160*/ 0x200, 0x200, 0x200, 0x200,
/*161*/ 0x200, 0x200, 0x200, 0x200,
/*162*/ 0x200, 0x200, 0x200, 0x200,
/*163*/ 0x200, 0x200, 0x200, 0x200,
/*164*/ 0x200, 0x200, 0x200, 0x200,
/*165*/ 0x200, 0x200, 0x200, 0x200,
/*166*/ 0x200, 0x200, 0x200, 0x200,
/*167*/ 0x200, 0x200, 0x200, 0x200,
/*168*/ 0x200, 0x200, 0x200, 0x200,
/*169*/ 0x200, 0x200, 0x200, 0x200,
/*170*/ 0x200, 0x200, 0x200, 0x200,
/*171*/ 0x200, 0x200, 0x200, 0x200,
/*172*/ 0x200, 0x200, 0x200, 0x200,
/*173*/ 0x200, 0x200, 0x200, 0x200,
/*174*/ 0x200, 0x200, 0x200, 0x200,
/*175*/ 0x200, 0x200, 0x200, 0x200,
/*176*/ 0x200, 0x200, 0x200, 0x200,
/*177*/ 0x200, 0x200, 0x200, 0x200,
/*178*/ 0x200, 0x200, 0x200, 0x200,
/*179*/ 0x200, 0x200, 0x200, 0x200,
/*180*/ 0x200, 0x200, 0x200, 0x200,
/*181*/ 0x200, 0x200, 0x200, 0x200,
/*182*/ 0x200, 0x200, 0x200, 0x200,
/*183*/ 0x200, 0x200, 0x200, 0x200,
/*184*/ 0x200, 0x200, 0x200, 0x200,
/*185*/ 0x200, 0x200, 0x200, 0x200,
/*186*/ 0x200, 0x200, 0x200, 0x200,
/*187*/ 0x200, 0x200, 0x200, 0x200,
/*188*/ 0x200, 0x200, 0x200, 0x200,
/*189*/ 0x200, 0x200, 0x200, 0x200,
/*190*/ 0x200, 0x200, 0x200, 0x200,
/*191*/ 0x200, 0x200, 0x200, 0x200,
/*192*/ 0x200, 0x200, 0x200, 0x200,
/*193*/ 0x200, 0x200, 0x200, 0x200,
/*194*/ 0x200, 0x200, 0x200, 0x200,
/*195*/ 0x200, 0x200, 0x200, 0x200,
/*196*/ 0x200, 0x200, 0x200, 0x200,
/*197*/ 0x200, 0x200, 0x200, 0x200,
/*198*/ 0x200, 0x200, 0x200, 0x200,
/*199*/ 0x200, 0x200, 0x200, 0x200,
/*200*/ 0x200, 0x200, 0x200, 0x200,
/*201*/ 0x200, 0x200, 0x200, 0x200,
/*202*/ 0x200, 0x200, 0x200, 0x200,
/*203*/ 0x200, 0x200, 0x200, 0x200,
/*204*/ 0x200, 0x200, 0x200, 0x200,
/*205*/ 0x200, 0x200, 0x200, 0x200,
/*206*/ 0x200, 0x200, 0x200, 0x200,
/*207*/ 0x200, 0x200, 0x200, 0x200,
/*208*/ 0x200, 0x200, 0x200, 0x200,
/*209*/ 0x200, 0x200, 0x200, 0x200,
/*210*/ 0x200, 0x200, 0x200, 0x200,
/*211*/ 0x200, 0x200, 0x200, 0x200,
/*212*/ 0x200, 0x200, 0x200, 0x200,
/*213*/ 0x200, 0x200, 0x200, 0x200,
/*214*/ 0x200, 0x200, 0x200, 0x200,
/*215*/ 0x200, 0x200, 0x200, 0x200,
/*216*/ 0x200, 0x200, 0x200, 0x200,
/*217*/ 0x200, 0x200, 0x200, 0x200,
/*218*/ 0x200, 0x200, 0x200, 0x200,
/*219*/ 0x200, 0x200, 0x200, 0x200,
/*220*/ 0x200, 0x200, 0x200, 0x200,
/*221*/ 0x200, 0x200, 0x200, 0x200,
/*222*/ 0x200, 0x200, 0x200, 0x200,
/*223*/ 0x200, 0x200, 0x200, 0x200,
/*224*/ 0x200, 0x200, 0x200, 0x200,
/*225*/ 0x200, 0x200, 0x200, 0x200,
/*226*/ 0x200, 0x200, 0x200, 0x200,
/*227*/ 0x200, 0x200, 0x200, 0x200,
/*228*/ 0x200, 0x200, 0x200, 0x200,
/*229*/ 0x200, 0x200, 0x200, 0x200,
/*230*/ 0x200, 0x200, 0x200, 0x200,
/*231*/ 0x200, 0x200, 0x200, 0x200,
/*232*/ 0x200, 0x200, 0x200, 0x200,
/*233*/ 0x200, 0x200, 0x200, 0x200,
/*234*/ 0x200, 0x200, 0x200, 0x200,
/*235*/ 0x200, 0x200, 0x200, 0x200,
/*236*/ 0x200, 0x200, 0x200, 0x200,
/*237*/ 0x200, 0x200, 0x200, 0x200,
/*238*/ 0x200, 0x200, 0x200, 0x200,
/*239*/ 0x200, 0x200, 0x200, 0x200,
/*240*/ 0x200, 0x200, 0x200, 0x200,
/*241*/ 0x200, 0x200, 0x200, 0x200,
/*242*/ 0x200, 0x200, 0x200, 0x200,
/*243*/ 0x200, 0x200, 0x200, 0x200,
/*244*/ 0x200, 0x200, 0x200, 0x200,
/*245*/ 0x200, 0x200, 0x200, 0x200,
/*246*/ 0x200, 0x200, 0x200, 0x200,
/*247*/ 0x200, 0x200, 0x200, 0x200,
};

static const KeySym linux_to_x[256] = {
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	XK_BackSpace,	XK_Tab,		XK_Linefeed,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	XK_Escape,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	XK_space,	XK_exclam,	XK_quotedbl,	XK_numbersign,
	XK_dollar,	XK_percent,	XK_ampersand,	XK_apostrophe,
	XK_parenleft,	XK_parenright,	XK_asterisk,	XK_plus,
	XK_comma,	XK_minus,	XK_period,	XK_slash,
	XK_0,		XK_1,		XK_2,		XK_3,
	XK_4,		XK_5,		XK_6,		XK_7,
	XK_8,		XK_9,		XK_colon,	XK_semicolon,
	XK_less,	XK_equal,	XK_greater,	XK_question,
	XK_at,		XK_A,		XK_B,		XK_C,
	XK_D,		XK_E,		XK_F,		XK_G,
	XK_H,		XK_I,		XK_J,		XK_K,
	XK_L,		XK_M,		XK_N,		XK_O,
	XK_P,		XK_Q,		XK_R,		XK_S,
	XK_T,		XK_U,		XK_V,		XK_W,
	XK_X,		XK_Y,		XK_Z,		XK_bracketleft,
	XK_backslash,	XK_bracketright,XK_asciicircum,	XK_underscore,
	XK_grave,	XK_a,		XK_b,		XK_c,
	XK_d,		XK_e,		XK_f,		XK_g,
	XK_h,		XK_i,		XK_j,		XK_k,
	XK_l,		XK_m,		XK_n,		XK_o,
	XK_p,		XK_q,		XK_r,		XK_s,
	XK_t,		XK_u,		XK_v,		XK_w,
	XK_x,		XK_y,		XK_z,		XK_braceleft,
	XK_bar,		XK_braceright,	XK_asciitilde,	XK_BackSpace,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	NoSymbol,	NoSymbol,	NoSymbol,	NoSymbol,
	XK_nobreakspace,XK_exclamdown,	XK_cent,	XK_sterling,
	XK_currency,	XK_yen,		XK_brokenbar,	XK_section,
	XK_diaeresis,	XK_copyright,	XK_ordfeminine,	XK_guillemotleft,
	XK_notsign,	XK_hyphen,	XK_registered,	XK_macron,
	XK_degree,	XK_plusminus,	XK_twosuperior,	XK_threesuperior,
	XK_acute,	XK_mu,		XK_paragraph,	XK_periodcentered,
	XK_cedilla,	XK_onesuperior,	XK_masculine,	XK_guillemotright,
	XK_onequarter,	XK_onehalf,	XK_threequarters,XK_questiondown,
	XK_Agrave,	XK_Aacute,	XK_Acircumflex,	XK_Atilde,
	XK_Adiaeresis,	XK_Aring,	XK_AE,		XK_Ccedilla,
	XK_Egrave,	XK_Eacute,	XK_Ecircumflex,	XK_Ediaeresis,
	XK_Igrave,	XK_Iacute,	XK_Icircumflex,	XK_Idiaeresis,
	XK_ETH,		XK_Ntilde,	XK_Ograve,	XK_Oacute,
	XK_Ocircumflex,	XK_Otilde,	XK_Odiaeresis,	XK_multiply,
	XK_Ooblique,	XK_Ugrave,	XK_Uacute,	XK_Ucircumflex,
	XK_Udiaeresis,	XK_Yacute,	XK_THORN,	XK_ssharp,
	XK_agrave,	XK_aacute,	XK_acircumflex,	XK_atilde,
	XK_adiaeresis,	XK_aring,	XK_ae,		XK_ccedilla,
	XK_egrave,	XK_eacute,	XK_ecircumflex,	XK_ediaeresis,
	XK_igrave,	XK_iacute,	XK_icircumflex,	XK_idiaeresis,
	XK_eth,		XK_ntilde,	XK_ograve,	XK_oacute,
	XK_ocircumflex,	XK_otilde,	XK_odiaeresis,	XK_division,
	XK_oslash,	XK_ugrave,	XK_uacute,	XK_ucircumflex,
	XK_udiaeresis,	XK_yacute,	XK_thorn,	XK_ydiaeresis
};

static unsigned char tbl[KD_MAX_WIDTH] =
{
    0,
    1 << KG_SHIFT,
    (1 << KG_ALTGR),
    (1 << KG_ALTGR) | (1 << KG_SHIFT)
};

#define EXT_BASE 0x80

/* Keypad keys */
#define EXT_UP EXT_BASE+1
#define EXT_DOWN EXT_BASE+2
#define EXT_LEFT EXT_BASE+3
#define EXT_RIGHT EXT_BASE+4

/* Escape key */
#define EXT_ESC EXT_BASE+5

/** What we really want is a mapping of every raw key on the keyboard.
 *  To support international keyboards, we use the range 0xA1 - 0xFF
 *  as international virtual keycodes.  We'll follow in the footsteps of X11...
 *  @brief The names of the keys
 */


//#define KTYP(x)		((x) >> 8)
//#define KVAL(x)		((x) & 0xff)

#define MYNR_KEYS 248

KdKeyboardInfo *sdlKeyboard = NULL;

static void
readKernelMapping(KdKeyboardInfo *ki)
{
    KeySym	    *k;
    int		    i, j;
    struct kbentry  kbe;
    int		    minKeyCode, maxKeyCode;
    int		    row;
    int             fd;

    if (!ki)
        return;

#if 1
    fd = NetbasConsoleFd;
    
    minKeyCode = NR_KEYS;
    maxKeyCode = 0;
    row = 0;
    ki->keySyms.mapWidth = KD_MAX_WIDTH;
	if (!ki->keySyms.map)
	{
		fprintf(stderr,"ki->keySyms.map not alloc memory,exit ..\n");
		exit(1);
	}
    for (i = 0; i < MYNR_KEYS && row < KD_MAX_LENGTH; ++i)
    {
        kbe.kb_index = (i);

        k = ki->keySyms.map + row * ki->keySyms.mapWidth;
	
for (j = 0; j < KD_MAX_WIDTH; ++j)
	{
	    unsigned short kval;

	    k[j] = NoSymbol;

	    kbe.kb_table = tbl[j];
	    kbe.kb_value = 0;		
		kbe.kb_value = __linux_keymap[i*KD_MAX_WIDTH+j];
	    //if (ioctl(fd, KDGKBENT, &kbe))
		//continue;

		//printf("0x%x, ", kbe.kb_value);

	    kval = KVAL(kbe.kb_value);
	    switch (KTYP(kbe.kb_value))
	    {
	    case KT_LATIN:
	    case KT_LETTER:
		k[j] = linux_to_x[kval];
		break;

	    case KT_FN:
		if (kval <= 19)
		    k[j] = XK_F1 + kval;
		else switch (kbe.kb_value)
		{
		case K_FIND:
		    k[j] = XK_Home; /* or XK_Find */
		    break;
		case K_INSERT:
		    k[j] = XK_Insert;
		    break;
		case K_REMOVE:
		    k[j] = XK_Delete;
		    break;
		case K_SELECT:
		    k[j] = XK_End; /* or XK_Select */
		    break;
		case K_PGUP:
		    k[j] = XK_Prior;
		    break;
		case K_PGDN:
		    k[j] = XK_Next;
		    break;
		case K_HELP:
		    k[j] = XK_Help;
		    break;
		case K_DO:
		    k[j] = XK_Execute;
		    break;
		case K_PAUSE:
		    k[j] = XK_Pause;
		    break;
		case K_MACRO:
		    k[j] = XK_Menu;
		    break;
		default:
		    break;
		}
		break;

	    case KT_SPEC:
		switch (kbe.kb_value)
		{
		case K_ENTER:
		    k[j] = XK_Return;
		    break;
		case K_BREAK:
		    k[j] = XK_Break;
		    break;
		case K_CAPS:
		    k[j] = XK_Caps_Lock;
		    break;
		case K_NUM:
		    k[j] = XK_Num_Lock;
		    break;
		case K_HOLD:
		    k[j] = XK_Scroll_Lock;
		    break;
		case K_COMPOSE:
		    k[j] = XK_Multi_key;
		    break;
		default:
		    break;
		}
		break;

	    case KT_PAD:
		switch (kbe.kb_value)
		{
		case K_PPLUS:
		    k[j] = XK_KP_Add;
		    break;
		case K_PMINUS:
		    k[j] = XK_KP_Subtract;
		    break;
		case K_PSTAR:
		    k[j] = XK_KP_Multiply;
		    break;
		case K_PSLASH:
		    k[j] = XK_KP_Divide;
		    break;
		case K_PENTER:
		    k[j] = XK_KP_Enter;
		    break;
		case K_PCOMMA:
		    k[j] = XK_KP_Separator;
		    break;
		case K_PDOT:
		    k[j] = XK_KP_Decimal;
		    break;
		case K_PPLUSMINUS:
		    k[j] = XK_KP_Subtract;
		    break;
		default:
		    if (kval <= 9)
			k[j] = XK_KP_0 + kval;
		    break;
		}
		break;

		/*
		 * KT_DEAD keys are for accelerated diacritical creation.
		 */
	    case KT_DEAD:
		switch (kbe.kb_value)
		{
		case K_DGRAVE:
		    k[j] = XK_dead_grave;
		    break;
		case K_DACUTE:
		    k[j] = XK_dead_acute;
		    break;
		case K_DCIRCM:
		    k[j] = XK_dead_circumflex;
		    break;
		case K_DTILDE:
		    k[j] = XK_dead_tilde;
		    break;
		case K_DDIERE:
		    k[j] = XK_dead_diaeresis;
		    break;
		}
		break;

	    case KT_CUR:
		switch (kbe.kb_value)
		{
		case K_DOWN:
		    k[j] = XK_Down;
		    break;
		case K_LEFT:
		    k[j] = XK_Left;
		    break;
		case K_RIGHT:
		    k[j] = XK_Right;
		    break;
		case K_UP:
		    k[j] = XK_Up;
		    break;
		}
		break;

	    case KT_SHIFT:
		switch (kbe.kb_value)
		{
		case K_ALTGR:
		    k[j] = XK_Mode_switch;
		    break;
		case K_ALT:
		    k[j] = (kbe.kb_index == 0x64 ?
			  XK_Alt_R : XK_Alt_L);
		    break;
		case K_CTRL:
		    k[j] = (kbe.kb_index == 0x61 ?
			  XK_Control_R : XK_Control_L);
		    break;
		case K_CTRLL:
		    k[j] = XK_Control_L;
		    break;
		case K_CTRLR:
		    k[j] = XK_Control_R;
		    break;
		case K_SHIFT:
		    k[j] = (kbe.kb_index == 0x36 ?
			  XK_Shift_R : XK_Shift_L);
		    break;
		case K_SHIFTL:
		    k[j] = XK_Shift_L;
		    break;
		case K_SHIFTR:
		    k[j] = XK_Shift_R;
		    break;
		default:
		    break;
		}
		break;

		/*
		 * KT_ASCII keys accumulate a 3 digit decimal number that gets
		 * emitted when the shift state changes. We can't emulate that.
		 */
	    case KT_ASCII:
		break;

	    case KT_LOCK:
		if (kbe.kb_value == K_SHIFTLOCK)
		    k[j] = XK_Shift_Lock;
		break;

#ifdef KT_X
	    case KT_X:
		/* depends on new keyboard symbols in file linux/keyboard.h */
		if(kbe.kb_value == K_XMENU) k[j] = XK_Menu;
		if(kbe.kb_value == K_XTELEPHONE) k[j] = XK_telephone;
		break;
#endif
#ifdef KT_XF
	    case KT_XF:
		/* special linux keysyms which map directly to XF86 keysyms */
		k[j] = (kbe.kb_value & 0xFF) + 0x1008FF00;
		break;
#endif
		
	    default:
		break;
	    }
	    if (i < minKeyCode)
		minKeyCode = i;
	    if (i > maxKeyCode)
		maxKeyCode = i;
	}

	if (minKeyCode == NR_KEYS)
	    continue;

	if (k[3] == k[2]) k[3] = NoSymbol;
	if (k[2] == k[1]) k[2] = NoSymbol;
	if (k[1] == k[0]) k[1] = NoSymbol;
	if (k[0] == k[2] && k[1] == k[3]) k[2] = k[3] = NoSymbol;
	if (k[3] == k[0] && k[2] == k[1] && k[2] == NoSymbol) k[3] =NoSymbol;
	row++;
    }
	
    //ki->minScanCode = 0;//minKeyCode;
    ki->minScanCode = minKeyCode;
    ki->maxScanCode = maxKeyCode;
	//ki->keySyms.minKeyCode = 8;
    //    ki->keySyms.maxKeyCode = 255;

	fprintf(stderr,"dpp minKeyCode = %d,maxKeyCode%d\n",minKeyCode,maxKeyCode);

#else
	sdlKeyboard = ki;
        ki->minScanCode = 8;
        ki->maxScanCode = 255;
        ki->keySyms.minKeyCode = 8;
        ki->keySyms.maxKeyCode = 255;
        ki->keySyms.mapWidth = 2;
        memcpy(ki->keySyms.map, sdlKeymap, sizeof(sdlKeymap));
#endif
}



static void
NetbasKeyboardRead (int fd, void *closure)
{
    unsigned char   buf[256], *b;
    int		    n;
    unsigned char    scancode = 0;

	//fprintf(stderr,"%s() fd = %d\n",__FUNCTION__, fd);

    while ((n = read (fd, buf, sizeof (buf))) > 0) {
	b = buf;
	
	while (n--) {

         scancode = b[0] & 0x7f;
	    KdEnqueueKeyboardEvent (closure , scancode, b[0] & 0x80);
	    b++;
	}
    }
}

//static int		NetbasKbdTrans;

static Status
NetbasKeyboardEnable (KdKeyboardInfo *ki)
{
    struct termios nTty;
    unsigned char   buf[256];
    int		    n;
    int             fd;

    if (!ki)
        return !Success;

    fd = NetbasConsoleFd;
    ki->driverPrivate = (void *) fd;
	fprintf(stderr,"%s() fd = %d\n",__FUNCTION__, fd);
   
    /*
     * Flush any pending keystrokes
     */
    //while ((n = read (fd, buf, sizeof (buf))) > 0)
	//;
    KdRegisterFd (fd, NetbasKeyboardRead, ki);
	fprintf(stderr,"%s() fd = %d\n",__FUNCTION__, fd);
    return Success;
}

static void
NetbasKeyboardDisable (KdKeyboardInfo *ki)
{
    int fd;
 	fprintf(stderr,"%s() fd = %d\n",__FUNCTION__, fd);
   
    if (!ki)
        return;

    fd = (int) ki->driverPrivate;

    KdUnregisterFd(ki, fd, FALSE);
    //ioctl(fd, KDSKBMODE, NetbasKbdTrans);
    //tcsetattr(fd, TCSANOW, &NetbasTermios);
}

static Status
NetbasKeyboardInit (KdKeyboardInfo *ki)
{
    if (!ki)
        return !Success;

    if (ki->path)
        xfree(ki->path);
    ki->path = KdSaveString("console");
    if (ki->name)
        xfree(ki->name);
    ki->name = KdSaveString("Netbas console keyboard");

	fprintf(stderr,"%s() ki = %p\n",__FUNCTION__, ki);
    readKernelMapping (ki);

    return Success;
}

static void
NetbasKeyboardLeds (KdKeyboardInfo *ki, int leds)
{
    if (!ki)
        return;

    ioctl ((int)ki->driverPrivate, KDSETLED, leds & 7);
}

KdKeyboardDriver NetbasKeyboardDriver = {
    "kbd",
    .Init = NetbasKeyboardInit,
    .Enable = NetbasKeyboardEnable,
    .Leds = NetbasKeyboardLeds,
    .Disable = NetbasKeyboardDisable,
};
