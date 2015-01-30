;;
;;
;;  Jicama OS  
;;  Copyright (C) 2005  DengPingPing     All rights reserved.     
;;
	SECTION .text		
	bits    32	
extern	main, environ, brksize, penviron, ___main
global _start;;, 
global asm_sig_restore;;, __alloca

_start:
  	finit

	;;mov	[penviron],esp
	mov eax, [esp+8]
	mov [environ], eax
	;;mov [penviron], eax
	
	xor	ebx,ebx
	mov	eax,45
	int	0x80	
	mov	[brksize], eax
	
	;push esp
	call main
	
exit_program:
	movzx	ebx,al
	mov	eax,1
	int	0x80

asm_sig_restore:
	add esp,8
	mov ebx, [esp+4]
	mov ecx, [esp]
	mov eax, 75
	int 0x80
	ret


;;SECTION .data
;;global _penviron, 
;;	_penviron dd 0

