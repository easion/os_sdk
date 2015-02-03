	.file	"shm.c"
	.data
	.align 4
	.type	shmPixmapPrivate, @object
	.size	shmPixmapPrivate, 4
shmPixmapPrivate:
	.long	shmPixmapPrivate
	.local	miFuncs
	.comm	miFuncs,8,4
	.align 4
	.type	fbFuncs, @object
	.size	fbFuncs, 8
fbFuncs:
	.long	fbShmCreatePixmap
	.long	0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"MIT-SHM"
	.text
	.align 4
.globl ShmExtensionInit
	.type	ShmExtensionInit, @function
ShmExtensionInit:
	pushl	%esi
	xorl	%ecx, %ecx
	movl	screenInfo+48, %esi
	movl	shmPixFormat, %eax
	cmpl	%esi, %ecx
	pushl	%ebx
	movl	$1, sharedPixmaps
	movl	%eax, pixmapFormat
	jge	.L19
	movl	$1, %ebx
	movl	%eax, %edx
.L9:
	cmpl	$0, shmFuncs(,%ecx,4)
	jne	.L6
	movl	$miFuncs, shmFuncs(,%ecx,4)
.L6:
	movl	shmFuncs(,%ecx,4), %eax
	cmpl	$0, (%eax)
	jne	.L7
	xorl	%ebx, %ebx
.L7:
	movl	shmPixFormat(,%ecx,4), %eax
	testl	%eax, %eax
	je	.L4
	cmpl	%edx, %eax
	je	.L4
	xorl	%ebx, %ebx
	xorl	%edx, %edx
.L4:
	incl	%ecx
	cmpl	%esi, %ecx
	jl	.L9
	movl	%edx, pixmapFormat
	movl	%ebx, sharedPixmaps
.L19:
	cmpl	$0, pixmapFormat
	jne	.L10
	movl	$2, pixmapFormat
.L10:
	cmpl	$0, sharedPixmaps
	je	.L11
	xorl	%ecx, %ecx
	movl	screenInfo+48, %ebx
	cmpl	%ebx, %ecx
	jge	.L11
.L16:
	movl	screenInfo+52(,%ecx,4), %edx
	movl	196(%edx), %eax
	movl	%eax, destroyPixmap(,%ecx,4)
	incl	%ecx
	cmpl	%ebx, %ecx
	movl	$ShmDestroyPixmap, 196(%edx)
	jl	.L16
.L11:
	pushl	$ShmDetachSegment
	call	CreateNewResourceType
	testl	%eax, %eax
	movl	%eax, ShmSegType
	popl	%edx
	je	.L1
	pushl	$StandardMinorOpcode
	pushl	$ShmResetProc
	pushl	$SProcShmDispatch
	pushl	$ProcShmDispatch
	pushl	$1
	pushl	$1
	pushl	$.LC0
	call	AddExtension
	addl	$28, %esp
	testl	%eax, %eax
	movl	%eax, %ecx
	je	.L1
	movb	12(%eax), %al
	movb	%al, ShmReqCode
	movl	16(%ecx), %edx
	movl	24(%ecx), %eax
	movl	%edx, ShmCompletionCode
	movl	%eax, BadShmSegCode
	movl	$SShmCompletionEvent, EventSwapVector(,%edx,4)
.L1:
	popl	%ebx
	popl	%esi
	ret
	.size	ShmExtensionInit, .-ShmExtensionInit
	.align 4
	.type	ShmResetProc, @function
ShmResetProc:
	xorl	%eax, %eax
.L27:
	movl	$0, shmFuncs(,%eax,4)
	movl	$0, shmPixFormat(,%eax,4)
	incl	%eax
	cmpl	$15, %eax
	jle	.L27
	ret
	.size	ShmResetProc, .-ShmResetProc
	.align 4
.globl ShmRegisterFuncs
	.type	ShmRegisterFuncs, @function
ShmRegisterFuncs:
	movl	4(%esp), %eax
	movl	(%eax), %edx
	movl	8(%esp), %eax
	movl	%eax, shmFuncs(,%edx,4)
	ret
	.size	ShmRegisterFuncs, .-ShmRegisterFuncs
	.align 4
.globl ShmSetPixmapFormat
	.type	ShmSetPixmapFormat, @function
ShmSetPixmapFormat:
	movl	4(%esp), %eax
	movl	(%eax), %edx
	movl	8(%esp), %eax
	movl	%eax, shmPixFormat(,%edx,4)
	ret
	.size	ShmSetPixmapFormat, .-ShmSetPixmapFormat
	.align 4
	.type	ShmDestroyPixmap, @function
ShmDestroyPixmap:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %esi
	cmpl	$1, 28(%esi)
	movl	16(%esi), %ebx
	jne	.L33
	pushl	shmPixmapPrivate
	leal	24(%esi), %eax
	pushl	%eax
	call	dixLookupPrivate
	testl	%eax, %eax
	popl	%ecx
	popl	%edx
	je	.L33
	pushl	4(%esi)
	pushl	%eax
	call	ShmDetachSegment
	popl	%eax
	popl	%edx
.L33:
	movl	(%ebx), %eax
	movl	destroyPixmap(,%eax,4), %eax
	movl	%eax, 196(%ebx)
	pushl	%esi
	call	*196(%ebx)
	movl	(%ebx), %ecx
	movl	196(%ebx), %edx
	movl	%edx, destroyPixmap(,%ecx,4)
	movl	$ShmDestroyPixmap, 196(%ebx)
	popl	%ecx
	popl	%ebx
	popl	%esi
	ret
	.size	ShmDestroyPixmap, .-ShmDestroyPixmap
	.align 4
.globl ShmRegisterFbFuncs
	.type	ShmRegisterFbFuncs, @function
ShmRegisterFbFuncs:
	movl	4(%esp), %eax
	movl	(%eax), %eax
	movl	$fbFuncs, shmFuncs(,%eax,4)
	ret
	.size	ShmRegisterFbFuncs, .-ShmRegisterFbFuncs
	.align 4
	.type	ProcShmQueryVersion, @function
ProcShmQueryVersion:
	pushl	%ebx
	subl	$32, %esp
	movl	40(%esp), %ebx
	cmpl	$1, 120(%ebx)
	je	.L37
	movl	$16, %eax
	jmp	.L36
.L37:
	movb	$1, (%esp)
	movw	28(%ebx), %ax
	movw	%ax, 2(%esp)
	movb	sharedPixmaps, %al
	movb	%al, 1(%esp)
	movb	pixmapFormat, %al
	movl	$0, 4(%esp)
	movb	%al, 16(%esp)
	movw	$1, 8(%esp)
	movw	$1, 10(%esp)
	call	geteuid
	movw	%ax, 12(%esp)
	call	getegid
	cmpl	$0, 16(%ebx)
	movw	%ax, 14(%esp)
	je	.L38
	movsbl	2(%esp),%edx
	movb	3(%esp), %al
	movb	%al, 2(%esp)
	movb	%dl, 3(%esp)
	movb	7(%esp), %al
	movsbl	4(%esp),%edx
	movb	%dl, 7(%esp)
	movb	%al, 4(%esp)
	movsbl	5(%esp),%edx
	movb	6(%esp), %al
	movb	%al, 5(%esp)
	movb	%dl, 6(%esp)
	movb	9(%esp), %al
	movsbl	8(%esp),%edx
	movb	%dl, 9(%esp)
	movb	%al, 8(%esp)
	movsbl	10(%esp),%edx
	movb	11(%esp), %al
	movb	%al, 10(%esp)
	movb	%dl, 11(%esp)
	movb	13(%esp), %al
	movsbl	12(%esp),%edx
	movb	%dl, 13(%esp)
	movb	%al, 12(%esp)
	movsbl	14(%esp),%edx
	movb	15(%esp), %al
	movb	%al, 14(%esp)
	movb	%dl, 15(%esp)
.L38:
	movl	%esp, %eax
	pushl	%eax
	pushl	$32
	pushl	%ebx
	call	WriteToClient
	movl	40(%ebx), %eax
	addl	$12, %esp
.L36:
	addl	$32, %esp
	popl	%ebx
	ret
	.size	ProcShmQueryVersion, .-ProcShmQueryVersion
	.align 4
	.type	shm_access, @function
shm_access:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	leal	8(%esp), %eax
	movl	36(%esp), %esi
	movl	40(%esp), %edi
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	pushl	%eax
	pushl	36(%esp)
	call	GetLocalClientCreds
	incl	%eax
	popl	%edx
	popl	%ecx
	je	.L40
	movl	8(%esp), %eax
	movl	(%eax), %edx
	testb	$1, %dl
	je	.L41
	movl	4(%eax), %ebx
	movl	$1, 4(%esp)
.L41:
	andb	$2, %dl
	je	.L42
	movl	8(%eax), %ebp
	movl	$1, (%esp)
.L42:
	pushl	%eax
	call	FreeLocalClientCreds
	popl	%ecx
	cmpl	$0, 4(%esp)
	je	.L43
	xorl	%eax, %eax
	testl	%ebx, %ebx
	je	.L39
	movzwl	4(%esi), %eax
	cmpl	%ebx, %eax
	je	.L46
	movzwl	8(%esi), %eax
	cmpl	%ebx, %eax
	jne	.L43
.L46:
	testl	%edi, %edi
	movl	$256, %edx
	jne	.L59
	movl	$384, %edx
	jmp	.L59
.L43:
	cmpl	$0, (%esp)
	je	.L40
	movzwl	6(%esi), %eax
	cmpl	%ebp, %eax
	je	.L52
	movzwl	10(%esi), %eax
	cmpl	%ebp, %eax
	jne	.L40
.L52:
	testl	%edi, %edi
	movl	$32, %edx
	jne	.L59
	movl	$48, %edx
	jmp	.L59
.L40:
	xorl	%edx, %edx
	testl	%edi, %edi
	sete	%dl
	leal	4(%edx,%edx), %edx
.L59:
	movzwl	12(%esi), %eax
	andl	%edx, %eax
	cmpl	%edx, %eax
	sete	%al
	movzbl	%al, %eax
	decl	%eax
.L39:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	shm_access, .-shm_access
	.align 4
	.type	ProcShmAttach, @function
ProcShmAttach:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$48, %esp
	movl	68(%esp), %ebp
	cmpl	$4, 120(%ebp)
	movl	8(%ebp), %esi
	je	.L61
	movl	$16, %edx
	jmp	.L60
.L61:
	pushl	%ebp
	pushl	4(%esi)
	call	LegalNewID
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L62
	movl	4(%esi), %eax
	movl	$14, %edx
	jmp	.L81
.L62:
	movb	12(%esi), %al
	cmpb	$1, %al
	jbe	.L63
	movzbl	%al, %eax
	movl	$2, %edx
.L81:
	movl	%eax, 24(%ebp)
	jmp	.L60
.L63:
	movl	Shmsegs, %ebx
	testl	%ebx, %ebx
	je	.L70
	movl	8(%esi), %edx
	cmpl	%edx, 4(%ebx)
	je	.L65
.L69:
	movl	(%ebx), %ebx
	testl	%ebx, %ebx
	je	.L70
	cmpl	%edx, 4(%ebx)
	jne	.L69
.L65:
	testl	%ebx, %ebx
	je	.L70
	testb	%al, %al
	jne	.L71
	cmpl	$0, 16(%ebx)
	jne	.L71
	movl	$10, %edx
	jmp	.L60
.L71:
	incl	8(%ebx)
	jmp	.L72
.L70:
	pushl	$24
	call	Xalloc
	movl	%eax, %ebx
	testl	%ebx, %ebx
	popl	%eax
	movl	$11, %edx
	je	.L60
	xorl	%eax, %eax
	cmpb	$0, 12(%esi)
	setne	%al
	sall	$12, %eax
	pushl	%eax
	pushl	$0
	pushl	8(%esi)
	call	shmat
	movl	%eax, 12(%ebx)
	addl	$12, %esp
	incl	%eax
	je	.L77
	movl	%esp, %edi
	pushl	%edi
	pushl	$2
	pushl	8(%esi)
	call	shmctl
	addl	$12, %esp
	testl	%eax, %eax
	je	.L76
.L77:
	pushl	%ebx
	call	Xfree
	movl	$10, %edx
	popl	%edi
	jmp	.L60
.L76:
	movzbl	12(%esi), %eax
	pushl	%eax
	pushl	%edi
	pushl	%ebp
	call	shm_access
	addl	$12, %esp
	incl	%eax
	jne	.L78
	pushl	12(%ebx)
	call	shmdt
	pushl	%ebx
	call	Xfree
	popl	%ebx
	movl	$10, %edx
	popl	%esi
	jmp	.L60
.L78:
	movl	8(%esi), %eax
	movl	%eax, 4(%ebx)
	movl	$1, 8(%ebx)
	xorl	%eax, %eax
	cmpb	$0, 12(%esi)
	sete	%al
	movl	%eax, 16(%ebx)
	movl	16(%esp), %eax
	movl	%eax, 20(%ebx)
	movl	Shmsegs, %eax
	movl	%eax, (%ebx)
	movl	%ebx, Shmsegs
.L72:
	pushl	%ebx
	pushl	ShmSegType
	pushl	4(%esi)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	movl	$11, %edx
	je	.L60
	movl	40(%ebp), %edx
.L60:
	addl	$48, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	ProcShmAttach, .-ProcShmAttach
	.align 4
	.type	ShmDetachSegment, @function
ShmDetachSegment:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %eax
	decl	%eax
	testl	%eax, %eax
	movl	%eax, 8(%ebx)
	movl	$1, %edx
	jne	.L82
	pushl	12(%ebx)
	call	shmdt
	cmpl	%ebx, Shmsegs
	movl	$Shmsegs, %edx
	popl	%eax
	je	.L90
.L88:
	movl	(%edx), %edx
	cmpl	%ebx, (%edx)
	jne	.L88
.L90:
	movl	(%ebx), %eax
	movl	%eax, (%edx)
	pushl	%ebx
	call	Xfree
	xorl	%edx, %edx
	popl	%ebx
.L82:
	movl	%edx, %eax
	popl	%ebx
	ret
	.size	ShmDetachSegment, .-ShmDetachSegment
	.align 4
	.type	ProcShmDetach, @function
ProcShmDetach:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	je	.L92
	movl	$16, %eax
	jmp	.L91
.L92:
	pushl	ShmSegType
	pushl	4(%ebx)
	call	LookupIDByType
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L93
	movl	4(%ebx), %eax
	movl	%eax, 24(%esi)
	movl	BadShmSegCode, %eax
	jmp	.L91
.L93:
	pushl	$0
	pushl	4(%ebx)
	call	FreeResource
	popl	%edx
	movl	40(%esi), %eax
	popl	%ecx
.L91:
	popl	%ebx
	popl	%esi
	ret
	.size	ProcShmDetach, .-ProcShmDetach
	.align 4
	.type	doShmPutImage, @function
doShmPutImage:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	56(%esp), %eax
	movl	%eax, 32(%esp)
	movl	80(%esp), %eax
	movl	60(%esp), %edx
	movl	76(%esp), %ecx
	movl	64(%esp), %esi
	movl	%eax, 20(%esp)
	movl	92(%esp), %eax
	movl	%edx, 28(%esp)
	movl	%ecx, 24(%esp)
	movl	84(%esp), %edx
	movl	88(%esp), %ecx
	movl	%eax, 8(%esp)
	imull	$24, %esi, %eax
	movl	%edx, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	96(%esp), %edx
	movl	100(%esp), %ecx
	cmpl	$0, PixmapWidthPaddingInfo+12(%eax)
	movl	72(%esp), %edi
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	movl	104(%esp), %ebp
	movl	PixmapWidthPaddingInfo+8(%eax), %ebx
	je	.L95
	movl	%edi, %edx
	imull	PixmapWidthPaddingInfo+16(%eax), %edx
	addl	PixmapWidthPaddingInfo+16(%eax), %edx
	movb	%bl, %cl
	sarl	%cl, %edx
	jmp	.L98
.L95:
	movl	%edi, %edx
	movl	PixmapWidthPaddingInfo+4(%eax), %ecx
	addl	PixmapWidthPaddingInfo(%eax), %edx
	sarl	%cl, %edx
	movb	%bl, %cl
.L98:
	pushl	%ebp
	sall	%cl, %edx
	pushl	%edx
	imull	$24, %esi, %eax
	pushl	PixmapWidthPaddingInfo+20(%eax)
	pushl	%esi
	pushl	40(%esp)
	pushl	%edi
	movl	56(%esp), %eax
	pushl	16(%eax)
	call	GetScratchPixmapHeader
	addl	$28, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	je	.L94
	movl	28(%esp), %edx
	movl	72(%edx), %eax
	pushl	(%esp)
	pushl	8(%esp)
	pushl	16(%esp)
	pushl	24(%esp)
	pushl	32(%esp)
	pushl	40(%esp)
	pushl	%edx
	pushl	60(%esp)
	pushl	%ebx
	call	*12(%eax)
	movl	%ebx, 92(%esp)
	addl	$72, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	FreeScratchPixmapHeader
.L94:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	doShmPutImage, .-doShmPutImage
	.align 4
	.type	ProcShmPutImage, @function
ProcShmPutImage:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$68, %esp
	movl	88(%esp), %eax
	cmpl	$10, 120(%eax)
	movl	8(%eax), %edi
	je	.L100
	movl	$16, %eax
	jmp	.L99
.L100:
	pushl	$2
	pushl	$-1
	pushl	96(%esp)
	pushl	4(%edi)
	leal	48(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L99
	pushl	$16777216
	pushl	92(%esp)
	pushl	8(%edi)
	leal	40(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L99
	movl	32(%esp), %ecx
	movl	28(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L141
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	jne	.L141
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L105
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%ebp
	popl	%eax
.L105:
	pushl	ShmSegType
	pushl	32(%edi)
	call	LookupIDByType
	movl	%eax, 32(%esp)
	popl	%ebx
	popl	%esi
	cmpl	$0, 24(%esp)
	jne	.L106
	movl	32(%edi), %eax
	movl	88(%esp), %edx
	movl	%eax, 24(%edx)
	movl	BadShmSegCode, %eax
	jmp	.L99
.L106:
	movl	36(%edi), %ecx
	testb	$3, %cl
	movl	%ecx, 20(%esp)
	jne	.L108
	movl	24(%esp), %ebx
	movl	20(%ebx), %ebx
	cmpl	%ebx, %ecx
	movl	%ebx, 16(%esp)
	jbe	.L109
.L108:
	movl	20(%esp), %edx
	movl	88(%esp), %eax
	movl	%edx, 24(%eax)
	jmp	.L140
.L109:
	cmpb	$1, 30(%edi)
	ja	.L140
	movb	29(%edi), %cl
	testb	%cl, %cl
	movb	%cl, 15(%esp)
	jne	.L111
	cmpb	$1, 28(%edi)
	jne	.L141
	cmpl	$0, PixmapWidthPaddingInfo+36
	movl	PixmapWidthPaddingInfo+32, %eax
	movw	12(%edi), %dx
	je	.L113
	movzwl	%dx, %esi
	imull	PixmapWidthPaddingInfo+40, %esi
	addl	PixmapWidthPaddingInfo+40, %esi
	movb	%al, %cl
	jmp	.L142
.L113:
	movzwl	%dx, %esi
	movl	PixmapWidthPaddingInfo+28, %ecx
	addl	PixmapWidthPaddingInfo+24, %esi
	sarl	%cl, %esi
	movb	%al, %cl
	jmp	.L138
.L111:
	cmpb	$1, 15(%esp)
	jne	.L116
	movb	28(%edi), %bl
	movl	32(%esp), %eax
	cmpb	%bl, 2(%eax)
	jne	.L141
	cmpl	$0, PixmapWidthPaddingInfo+36
	movl	PixmapWidthPaddingInfo+32, %eax
	movw	12(%edi), %dx
	je	.L118
	movzwl	%dx, %esi
	imull	PixmapWidthPaddingInfo+40, %esi
	addl	PixmapWidthPaddingInfo+40, %esi
	movb	%al, %cl
	sarl	%cl, %esi
	jmp	.L137
.L118:
	movzwl	%dx, %esi
	movl	PixmapWidthPaddingInfo+28, %ecx
	addl	PixmapWidthPaddingInfo+24, %esi
	sarl	%cl, %esi
	movb	%al, %cl
.L137:
	sall	%cl, %esi
	movzbl	%bl, %eax
	imull	%eax, %esi
	jmp	.L115
.L116:
	cmpb	$2, 15(%esp)
	jne	.L121
	movl	32(%esp), %eax
	movb	2(%eax), %al
	cmpb	28(%edi), %al
	je	.L122
.L141:
	movl	$8, %eax
	jmp	.L99
.L122:
	movzbl	%al, %eax
	imull	$24, %eax, %eax
	cmpl	$0, PixmapWidthPaddingInfo+12(%eax)
	movl	PixmapWidthPaddingInfo+8(%eax), %ebx
	movw	12(%edi), %dx
	je	.L123
	movzwl	%dx, %esi
	imull	PixmapWidthPaddingInfo+16(%eax), %esi
	addl	PixmapWidthPaddingInfo+16(%eax), %esi
	movb	%bl, %cl
.L142:
	sarl	%cl, %esi
	jmp	.L138
.L123:
	movzwl	%dx, %esi
	movl	PixmapWidthPaddingInfo+4(%eax), %ecx
	addl	PixmapWidthPaddingInfo(%eax), %esi
	sarl	%cl, %esi
	movb	%bl, %cl
.L138:
	sall	%cl, %esi
	jmp	.L115
.L121:
	movzbl	15(%esp), %eax
	jmp	.L143
.L115:
	movw	14(%edi), %bp
	testw	%bp, %bp
	je	.L126
	movl	20(%esp), %eax
	subl	%eax, 16(%esp)
	movzwl	%bp, %edx
	movl	%edx, %ebx
	movl	16(%esp), %eax
	xorl	%edx, %edx
	divl	%ebx
	cmpl	%eax, %esi
	jbe	.L126
	movzwl	12(%edi), %eax
	jmp	.L144
.L126:
	movw	12(%edi), %cx
	movw	16(%edi), %bx
	cmpw	%cx, %bx
	movw	%cx, 12(%esp)
	jbe	.L127
	movzwl	%bx, %eax
.L143:
	movl	88(%esp), %ebx
	movl	%eax, 24(%ebx)
	jmp	.L140
.L127:
	movw	18(%edi), %ax
	cmpw	%bp, %ax
	movw	%ax, 10(%esp)
	jbe	.L128
	movzwl	%ax, %eax
.L144:
	movl	88(%esp), %edx
	movl	%eax, 24(%edx)
	jmp	.L140
.L128:
	movzwl	%bx, %ecx
	movw	20(%edi), %ax
	movl	%ecx, 4(%esp)
	movl	4(%esp), %edx
	movzwl	%ax, %ecx
	movw	%ax, 2(%esp)
	addl	%ecx, %edx
	movzwl	12(%esp), %eax
	cmpl	%eax, %edx
	jle	.L129
	movl	88(%esp), %edx
	movl	%ecx, 24(%edx)
	jmp	.L140
.L129:
	movw	22(%edi), %cx
	movzwl	10(%esp), %edx
	movw	%cx, (%esp)
	movzwl	%cx, %ecx
	addl	%ecx, %edx
	movzwl	%bp, %eax
	cmpl	%eax, %edx
	jle	.L130
	movl	88(%esp), %ebx
	movl	%ecx, 24(%ebx)
.L140:
	movl	$2, %eax
	jmp	.L99
.L130:
	cmpb	$2, 15(%esp)
	jne	.L136
	testw	%bx, %bx
	jmp	.L139
.L136:
	movl	4(%esp), %eax
	cmpl	screenInfo+8, %eax
	jge	.L131
	cmpb	$0, 15(%esp)
	je	.L132
	cmpw	$0, 10(%esp)
	jne	.L131
	cmpw	%bp, (%esp)
.L139:
	jne	.L131
.L132:
	movzwl	2(%esp), %edx
	movzwl	%bx, %eax
	addl	%edx, %eax
	movzwl	12(%esp), %edx
	cmpl	%edx, %eax
	jne	.L131
	movl	24(%esp), %eax
	movl	36(%edi), %edx
	addl	12(%eax), %edx
	movzwl	10(%esp), %eax
	imull	%esi, %eax
	movl	28(%esp), %ecx
	addl	%eax, %edx
	movl	72(%ecx), %ebx
	pushl	%edx
	movzbl	29(%edi), %eax
	pushl	%eax
	movzwl	16(%edi), %eax
	pushl	%eax
	movzwl	22(%edi), %eax
	pushl	%eax
	movzwl	12(%edi), %eax
	pushl	%eax
	movswl	26(%edi),%eax
	pushl	%eax
	movswl	24(%edi),%eax
	pushl	%eax
	movzbl	28(%edi), %eax
	pushl	%eax
	pushl	%ecx
	pushl	68(%esp)
	call	*8(%ebx)
	addl	$40, %esp
	jmp	.L134
.L131:
	movl	24(%esp), %edx
	movl	36(%edi), %eax
	addl	12(%edx), %eax
	pushl	%eax
	movswl	26(%edi),%eax
	pushl	%eax
	movswl	24(%edi),%eax
	pushl	%eax
	movzwl	22(%edi), %eax
	pushl	%eax
	movzwl	20(%edi), %eax
	pushl	%eax
	movzwl	18(%edi), %eax
	pushl	%eax
	movzwl	16(%edi), %eax
	pushl	%eax
	movzwl	14(%edi), %eax
	pushl	%eax
	movzwl	12(%edi), %eax
	pushl	%eax
	movzbl	29(%edi), %eax
	pushl	%eax
	movzbl	28(%edi), %eax
	pushl	%eax
	pushl	72(%esp)
	pushl	80(%esp)
	call	doShmPutImage
	addl	$52, %esp
.L134:
	cmpb	$0, 30(%edi)
	je	.L135
	movb	ShmCompletionCode, %al
	movb	%al, 36(%esp)
	movl	4(%edi), %eax
	movl	88(%esp), %ecx
	movl	%eax, 40(%esp)
	movw	28(%ecx), %ax
	movw	%ax, 38(%esp)
	movb	ShmReqCode, %al
	movb	%al, 46(%esp)
	movl	32(%edi), %eax
	movl	%eax, 48(%esp)
	movl	36(%edi), %eax
	movl	%eax, 52(%esp)
	leal	36(%esp), %eax
	movw	$3, 44(%esp)
	pushl	%eax
	pushl	$1
	pushl	%ecx
	call	WriteEventsToClient
	addl	$12, %esp
.L135:
	movl	88(%esp), %ebx
	movl	40(%ebx), %eax
.L99:
	addl	$68, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcShmPutImage, .-ProcShmPutImage
	.align 4
	.type	ProcShmGetImage, @function
ProcShmGetImage:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$64, %esp
	movl	84(%esp), %eax
	cmpl	$8, 120(%eax)
	movl	$0, 24(%esp)
	movl	$0, 20(%esp)
	movl	8(%eax), %esi
	je	.L146
	movl	$16, %eax
	jmp	.L145
.L146:
	movb	20(%esi), %dl
	leal	-1(%edx), %eax
	cmpb	$1, %al
	jbe	.L147
	movzbl	%dl, %eax
	movl	84(%esp), %edx
	movl	%eax, 24(%edx)
	jmp	.L184
.L147:
	pushl	$1
	pushl	$0
	pushl	92(%esp)
	pushl	4(%esi)
	leal	44(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L145
	pushl	ShmSegType
	pushl	24(%esi)
	call	LookupIDByType
	movl	%eax, 24(%esp)
	popl	%ecx
	popl	%ebx
	cmpl	$0, 16(%esp)
	jne	.L149
	movl	24(%esi), %eax
	movl	84(%esp), %ecx
	movl	%eax, 24(%ecx)
	movl	BadShmSegCode, %eax
	jmp	.L145
.L149:
	movl	28(%esi), %eax
	testb	$3, %al
	jne	.L151
	movl	16(%esp), %ebx
	cmpl	20(%ebx), %eax
	jbe	.L150
.L151:
	movl	84(%esp), %edi
	movl	%eax, 24(%edi)
.L184:
	movl	$2, %eax
	jmp	.L145
.L150:
	movl	16(%esp), %eax
	cmpl	$0, 16(%eax)
	je	.L183
	movl	28(%esp), %ecx
	cmpb	$0, (%ecx)
	jne	.L153
	testb	$16, 130(%ecx)
	je	.L160
	movswl	8(%ecx),%eax
	movswl	8(%esi),%ebp
	addl	%ebp, %eax
	js	.L160
	movzwl	12(%esi), %edx
	movl	16(%ecx), %ebx
	movl	%edx, 12(%esp)
	leal	(%edx,%eax), %edx
	movswl	8(%ebx),%eax
	cmpl	%eax, %edx
	jg	.L160
	movswl	10(%ecx),%eax
	movswl	10(%esi),%edi
	addl	%edi, %eax
	js	.L160
	movzwl	14(%esi), %edx
	addl	%edx, %eax
	movl	%eax, (%esp)
	movswl	10(%ebx),%eax
	cmpl	%eax, (%esp)
	movl	%edx, 8(%esp)
	jg	.L160
	movzwl	104(%ecx), %ebx
	movl	%ebx, %eax
	negl	%eax
	cmpl	%eax, %ebp
	movl	%eax, 4(%esp)
	jl	.L160
	movl	12(%esp), %eax
	leal	(%eax,%ebp), %edx
	movzwl	12(%ecx), %eax
	leal	(%eax,%ebx), %eax
	cmpl	%eax, %edx
	jg	.L160
	cmpl	4(%esp), %edi
	jl	.L160
	movl	8(%esp), %eax
	leal	(%eax,%edi), %edx
	movzwl	14(%ecx), %eax
	leal	(%eax,%ebx), %eax
	cmpl	%eax, %edx
	jg	.L160
	movl	124(%ecx), %eax
	testl	%eax, %eax
	jne	.L180
	pushl	%ecx
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%edx
.L180:
	movl	(%eax), %eax
	movl	%eax, 40(%esp)
	jmp	.L158
.L153:
	movw	8(%esi), %ax
	testw	%ax, %ax
	js	.L160
	movzwl	12(%esi), %edx
	cwtl
	addl	%edx, %eax
	movzwl	12(%ecx), %edx
	cmpl	%edx, %eax
	jg	.L160
	movw	10(%esi), %ax
	testw	%ax, %ax
	js	.L160
	movzwl	14(%esi), %edx
	cwtl
	addl	%edx, %eax
	movzwl	14(%ecx), %edx
	cmpl	%edx, %eax
	jle	.L159
.L160:
	movl	$8, %eax
	jmp	.L145
.L159:
	movl	$0, 40(%esp)
.L158:
	movb	$1, 32(%esp)
	movl	84(%esp), %edx
	movw	28(%edx), %ax
	movw	%ax, 34(%esp)
	movl	$0, 36(%esp)
	movl	28(%esp), %ebx
	movb	2(%ebx), %al
	movb	%al, 33(%esp)
	cmpb	$2, 20(%esi)
	movw	14(%esi), %dx
	jne	.L161
	movzbl	2(%ebx), %eax
	imull	$24, %eax, %eax
	cmpl	$0, PixmapWidthPaddingInfo+12(%eax)
	movzwl	%dx, %ebp
	movl	PixmapWidthPaddingInfo+8(%eax), %edi
	movw	12(%esi), %dx
	je	.L162
	movzwl	%dx, %ebx
	imull	PixmapWidthPaddingInfo+16(%eax), %ebx
	addl	PixmapWidthPaddingInfo+16(%eax), %ebx
	movl	%edi, %ecx
	sarl	%cl, %ebx
	jmp	.L182
.L162:
	movzwl	%dx, %ebx
	movl	PixmapWidthPaddingInfo+4(%eax), %ecx
	addl	PixmapWidthPaddingInfo(%eax), %ebx
	sarl	%cl, %ebx
	movl	%edi, %ecx
.L182:
	sall	%cl, %ebx
	imull	%ebp, %ebx
	jmp	.L164
.L161:
	cmpl	$0, PixmapWidthPaddingInfo+36
	movzwl	%dx, %ebp
	movl	PixmapWidthPaddingInfo+32, %eax
	movw	12(%esi), %dx
	movl	16(%esi), %edi
	je	.L165
	movzwl	%dx, %edx
	movl	PixmapWidthPaddingInfo+40, %ecx
	imull	PixmapWidthPaddingInfo+40, %edx
	addl	%ecx, %edx
	movb	%al, %cl
	sarl	%cl, %edx
	jmp	.L181
.L165:
	movl	PixmapWidthPaddingInfo+24, %ecx
	movzwl	%dx, %edx
	addl	%ecx, %edx
	movl	PixmapWidthPaddingInfo+28, %ecx
	sarl	%cl, %edx
	movb	%al, %cl
.L181:
	sall	%cl, %edx
	imull	%edx, %ebp
	movl	%ebp, 24(%esp)
	movzbl	2(%ebx), %ecx
	decl	%ecx
	movl	$1, 20(%esp)
	sall	%cl, 20(%esp)
	movl	20(%esp), %eax
	decl	%eax
	orl	20(%esp), %eax
	andl	%eax, %edi
	pushl	%edi
	call	Ones
	movl	28(%esp), %ebx
	imull	%eax, %ebx
	popl	%eax
.L164:
	movl	28(%esi), %eax
	addl	%ebx, %eax
	movl	16(%esp), %edi
	cmpl	20(%edi), %eax
	jbe	.L167
.L183:
	movl	$10, %eax
	jmp	.L145
.L167:
	testl	%ebx, %ebx
	movl	%ebx, 44(%esp)
	je	.L169
	cmpb	$2, 20(%esi)
	movl	28(%esi), %eax
	jne	.L170
	movl	16(%esp), %ebx
	movl	28(%esp), %edx
	addl	12(%ebx), %eax
	movl	16(%edx), %ecx
	pushl	%eax
	pushl	16(%esi)
	movzbl	20(%esi), %eax
	pushl	%eax
	movzwl	14(%esi), %eax
	pushl	%eax
	movzwl	12(%esi), %eax
	pushl	%eax
	movswl	10(%esi),%eax
	pushl	%eax
	movswl	8(%esi),%eax
	pushl	%eax
	pushl	%edx
	call	*116(%ecx)
	addl	$32, %esp
	jmp	.L169
.L170:
	cmpl	$0, 20(%esp)
	movl	%eax, %ebx
	je	.L169
.L177:
	movl	20(%esp), %edi
	testl	%edi, 16(%esi)
	je	.L174
	movl	16(%esp), %edi
	movl	12(%edi), %eax
	movl	28(%esp), %edx
	addl	%ebx, %eax
	movl	16(%edx), %ecx
	pushl	%eax
	pushl	24(%esp)
	movzbl	20(%esi), %eax
	pushl	%eax
	movzwl	14(%esi), %eax
	pushl	%eax
	movzwl	12(%esi), %eax
	pushl	%eax
	movswl	10(%esi),%eax
	pushl	%eax
	movswl	8(%esi),%eax
	pushl	%eax
	pushl	%edx
	call	*116(%ecx)
	addl	56(%esp), %ebx
	addl	$32, %esp
.L174:
	shrl	20(%esp)
	jne	.L177
.L169:
	movl	84(%esp), %eax
	cmpl	$0, 16(%eax)
	je	.L178
	movsbl	34(%esp),%edx
	movb	35(%esp), %al
	movb	%al, 34(%esp)
	movb	%dl, 35(%esp)
	movb	39(%esp), %al
	movsbl	36(%esp),%edx
	movb	%dl, 39(%esp)
	movb	%al, 36(%esp)
	movsbl	37(%esp),%edx
	movb	38(%esp), %al
	movb	%al, 37(%esp)
	movb	%dl, 38(%esp)
	movb	43(%esp), %al
	movsbl	40(%esp),%edx
	movb	%dl, 43(%esp)
	movb	%al, 40(%esp)
	movsbl	41(%esp),%edx
	movb	42(%esp), %al
	movb	%al, 41(%esp)
	movb	%dl, 42(%esp)
	movb	47(%esp), %al
	movsbl	44(%esp),%edx
	movb	%dl, 47(%esp)
	movb	%al, 44(%esp)
	movsbl	45(%esp),%edx
	movb	46(%esp), %al
	movb	%al, 45(%esp)
	movb	%dl, 46(%esp)
.L178:
	leal	32(%esp), %eax
	pushl	%eax
	pushl	$32
	pushl	92(%esp)
	call	WriteToClient
	movl	96(%esp), %edx
	movl	40(%edx), %eax
	addl	$12, %esp
.L145:
	addl	$64, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcShmGetImage, .-ProcShmGetImage
	.align 4
	.type	fbShmCreatePixmap, @function
fbShmCreatePixmap:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %edi
	movl	32(%esp), %ebp
	pushl	$0
	movzbl	18(%edi), %eax
	pushl	%eax
	pushl	$0
	pushl	$0
	pushl	%edi
	call	*192(%edi)
	addl	$20, %esp
	xorl	%edx, %edx
	testl	%eax, %eax
	movl	%eax, %esi
	je	.L185
	imull	$24, %ebp, %eax
	cmpl	$0, PixmapWidthPaddingInfo+12(%eax)
	pushl	36(%esp)
	movl	PixmapWidthPaddingInfo+8(%eax), %ebx
	je	.L188
	movl	28(%esp), %edx
	imull	PixmapWidthPaddingInfo+16(%eax), %edx
	addl	PixmapWidthPaddingInfo+16(%eax), %edx
	movb	%bl, %cl
	sarl	%cl, %edx
	jmp	.L190
.L188:
	movl	28(%esp), %edx
	movl	PixmapWidthPaddingInfo+4(%eax), %ecx
	addl	PixmapWidthPaddingInfo(%eax), %edx
	sarl	%cl, %edx
	movb	%bl, %cl
.L190:
	sall	%cl, %edx
	pushl	%edx
	imull	$24, %ebp, %eax
	pushl	PixmapWidthPaddingInfo+20(%eax)
	pushl	%ebp
	pushl	44(%esp)
	pushl	44(%esp)
	pushl	%esi
	call	*344(%edi)
	addl	$28, %esp
	testl	%eax, %eax
	movl	%esi, %edx
	jne	.L185
	pushl	%esi
	call	*196(%edi)
	xorl	%edx, %edx
	popl	%esi
.L185:
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	fbShmCreatePixmap, .-fbShmCreatePixmap
	.align 4
	.type	ProcShmCreatePixmap, @function
ProcShmCreatePixmap:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	52(%esp), %eax
	cmpl	$7, 120(%eax)
	movl	8(%eax), %ebx
	je	.L192
	movl	$16, %eax
	jmp	.L191
.L192:
	movl	4(%ebx), %eax
	movl	52(%esp), %edx
	cmpl	$0, sharedPixmaps
	movl	%eax, 24(%edx)
	jne	.L193
	movl	$17, %eax
	jmp	.L191
.L193:
	pushl	52(%esp)
	pushl	4(%ebx)
	call	LegalNewID
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L194
	movl	4(%ebx), %eax
	movl	52(%esp), %ecx
	movl	%eax, 24(%ecx)
	movl	$14, %eax
	jmp	.L191
.L194:
	pushl	$16
	pushl	$-1
	pushl	60(%esp)
	pushl	8(%ebx)
	leal	44(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	movl	%eax, 44(%esp)
	addl	$20, %esp
	movl	24(%esp), %eax
	testl	%eax, %eax
	jne	.L191
	pushl	ShmSegType
	pushl	20(%ebx)
	call	LookupIDByType
	movl	%eax, 28(%esp)
	popl	%ebp
	popl	%eax
	cmpl	$0, 20(%esp)
	jne	.L196
	movl	20(%ebx), %eax
	movl	52(%esp), %edx
	movl	%eax, 24(%edx)
	movl	BadShmSegCode, %eax
	jmp	.L191
.L196:
	movl	24(%ebx), %edi
	testl	$3, %edi
	jne	.L198
	movl	20(%esp), %ecx
	movl	20(%ecx), %ecx
	cmpl	%ecx, %edi
	movl	%ecx, 8(%esp)
	jbe	.L197
.L198:
	movl	52(%esp), %eax
	movl	%edi, 24(%eax)
	jmp	.L226
.L197:
	movl	20(%esp), %edx
	cmpl	$0, 16(%edx)
	jne	.L199
	movl	$10, %eax
	jmp	.L191
.L199:
	movzwl	14(%ebx), %ecx
	movl	%ecx, 16(%esp)
	movb	16(%ebx), %al
	movzwl	12(%ebx), %esi
	movzbl	%al, %edx
	testl	%esi, %esi
	movb	%al, 7(%esp)
	movl	%edx, 12(%esp)
	je	.L201
	testl	%ecx, %ecx
	je	.L201
	testl	%edx, %edx
	jne	.L200
.L201:
	movl	52(%esp), %ecx
	movl	$0, 24(%ecx)
	jmp	.L226
.L200:
	cmpl	$32767, %esi
	ja	.L218
	cmpl	$32767, 16(%esp)
	ja	.L218
	cmpb	$1, 7(%esp)
	je	.L210
	movl	28(%esp), %eax
	movl	16(%eax), %eax
	movw	16(%eax), %bp
	movl	20(%eax), %edx
	movswl	%bp,%eax
	xorl	%ecx, %ecx
	cmpl	%eax, 24(%esp)
	jge	.L224
.L211:
	movb	7(%esp), %al
	cmpb	%al, (%edx)
	je	.L210
	incl	%ecx
	movswl	%bp,%eax
	addl	$8, %edx
	cmpl	%eax, %ecx
	jl	.L211
.L224:
	movzbl	16(%ebx), %eax
	movl	52(%esp), %edx
	movl	%eax, 24(%edx)
.L226:
	movl	$2, %eax
	jmp	.L191
.L210:
	imull	$24, 12(%esp), %eax
	cmpl	$0, PixmapWidthPaddingInfo+12(%eax)
	movl	PixmapWidthPaddingInfo+8(%eax), %ebp
	je	.L212
	movl	%esi, %edx
	imull	PixmapWidthPaddingInfo+16(%eax), %edx
	addl	PixmapWidthPaddingInfo+16(%eax), %edx
	movl	%ebp, %ecx
	sarl	%cl, %edx
	jmp	.L225
.L212:
	movl	%esi, %edx
	addl	PixmapWidthPaddingInfo(%eax), %edx
	movl	PixmapWidthPaddingInfo+4(%eax), %eax
	movl	%eax, (%esp)
	movb	(%esp), %cl
	sarl	%cl, %edx
	movl	%ebp, %ecx
.L225:
	sall	%cl, %edx
	imull	$24, 12(%esp), %eax
	imull	16(%esp), %edx
	cmpl	$8, PixmapWidthPaddingInfo+20(%eax)
	jle	.L214
	imull	16(%esp), %esi
	cmpl	%esi, %edx
	movl	$11, %eax
	jb	.L191
.L214:
	leal	(%edx,%edi), %ecx
	cmpl	%edx, %ecx
	movl	$11, %eax
	jb	.L191
	cmpl	8(%esp), %ecx
	movl	$10, %eax
	ja	.L191
	movl	28(%esp), %edx
	movl	16(%edx), %eax
	movl	(%eax), %eax
	movl	shmFuncs(,%eax,4), %esi
	movl	20(%esp), %eax
	addl	12(%eax), %edi
	pushl	%edi
	movzbl	16(%ebx), %eax
	pushl	%eax
	movzwl	14(%ebx), %eax
	pushl	%eax
	movzwl	12(%ebx), %eax
	pushl	%eax
	pushl	16(%edx)
	call	*(%esi)
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %esi
	je	.L218
	pushl	20(%esp)
	pushl	shmPixmapPrivate
	leal	24(%eax), %eax
	pushl	%eax
	call	dixSetPrivate
	movl	globalSerialNumber, %eax
	movl	32(%esp), %edx
	incl	%eax
	incl	8(%edx)
	addl	$12, %esp
	cmpl	$268435456, %eax
	movl	%eax, globalSerialNumber
	jbe	.L221
	movl	$1, globalSerialNumber
	movl	$1, %eax
.L221:
	movl	%eax, 20(%esi)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esi)
	pushl	%esi
	pushl	$1073741826
	pushl	4(%ebx)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	je	.L222
	movl	52(%esp), %ecx
	movl	40(%ecx), %eax
	jmp	.L191
.L222:
	movl	28(%esp), %eax
	movl	16(%eax), %eax
	pushl	%esi
	call	*196(%eax)
	popl	%edi
.L218:
	movl	$11, %eax
.L191:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcShmCreatePixmap, .-ProcShmCreatePixmap
	.align 4
	.type	ProcShmDispatch, @function
ProcShmDispatch:
	movl	4(%esp), %edx
	movl	8(%edx), %eax
	movzbl	1(%eax), %eax
	cmpl	$5, %eax
	ja	.L235
	jmp	*.L236(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L236:
	.long	.L229
	.long	.L230
	.long	.L231
	.long	.L232
	.long	.L233
	.long	.L234
	.text
.L229:
	movl	%edx, 4(%esp)
	jmp	ProcShmQueryVersion
.L230:
	movl	%edx, 4(%esp)
	jmp	ProcShmAttach
.L231:
	movl	%edx, 4(%esp)
	jmp	ProcShmDetach
.L232:
	movl	%edx, 4(%esp)
	jmp	ProcShmPutImage
.L233:
	movl	%edx, 4(%esp)
	jmp	ProcShmGetImage
.L234:
	movl	%edx, 4(%esp)
	jmp	ProcShmCreatePixmap
.L235:
	movl	$1, %eax
	ret
	.size	ProcShmDispatch, .-ProcShmDispatch
	.align 4
	.type	SShmCompletionEvent, @function
SShmCompletionEvent:
	movl	4(%esp), %eax
	movl	8(%esp), %edx
	movb	(%eax), %cl
	movb	%cl, (%edx)
	movb	3(%eax), %cl
	movb	%cl, 2(%edx)
	movb	2(%eax), %cl
	movb	%cl, 3(%edx)
	movb	7(%eax), %cl
	movb	%cl, 4(%edx)
	movb	6(%eax), %cl
	movb	%cl, 5(%edx)
	movb	5(%eax), %cl
	movb	%cl, 6(%edx)
	movb	4(%eax), %cl
	movb	%cl, 7(%edx)
	movb	9(%eax), %cl
	movb	%cl, 8(%edx)
	movb	8(%eax), %cl
	movb	%cl, 9(%edx)
	movb	10(%eax), %cl
	movb	%cl, 10(%edx)
	movb	15(%eax), %cl
	movb	%cl, 12(%edx)
	movb	14(%eax), %cl
	movb	%cl, 13(%edx)
	movb	13(%eax), %cl
	movb	%cl, 14(%edx)
	movb	12(%eax), %cl
	movb	%cl, 15(%edx)
	movb	19(%eax), %cl
	movb	%cl, 16(%edx)
	movb	18(%eax), %cl
	movb	%cl, 17(%edx)
	movb	17(%eax), %cl
	movb	%cl, 18(%edx)
	movb	16(%eax), %al
	movb	%al, 19(%edx)
	ret
	.size	SShmCompletionEvent, .-SShmCompletionEvent
	.align 4
	.type	SProcShmQueryVersion, @function
SProcShmQueryVersion:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %eax
	movsbl	2(%eax),%ecx
	movb	3(%eax), %dl
	movb	%dl, 2(%eax)
	movb	%cl, 3(%eax)
	pushl	%ebx
	call	ProcShmQueryVersion
	popl	%ebx
	popl	%ebx
	ret
	.size	SProcShmQueryVersion, .-SProcShmQueryVersion
	.align 4
	.type	SProcShmAttach, @function
SProcShmAttach:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %edx
	movsbl	2(%edx),%ecx
	movb	3(%edx), %al
	movb	%al, 2(%edx)
	movb	%cl, 3(%edx)
	cmpl	$4, 120(%ebx)
	jne	.L241
	movsbl	4(%edx),%ecx
	movb	7(%edx), %al
	movb	%al, 4(%edx)
	movb	%cl, 7(%edx)
	movb	6(%edx), %al
	movsbl	5(%edx),%ecx
	movb	%cl, 6(%edx)
	movb	%al, 5(%edx)
	movsbl	8(%edx),%ecx
	movb	11(%edx), %al
	movb	%al, 8(%edx)
	movb	%cl, 11(%edx)
	movb	10(%edx), %al
	movsbl	9(%edx),%ecx
	movb	%cl, 10(%edx)
	movb	%al, 9(%edx)
	movl	%ebx, 8(%esp)
	popl	%ebx
	jmp	ProcShmAttach
.L241:
	movl	$16, %eax
	popl	%ebx
	ret
	.size	SProcShmAttach, .-SProcShmAttach
	.align 4
	.type	SProcShmDetach, @function
SProcShmDetach:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %edx
	movsbl	2(%edx),%ecx
	movb	3(%edx), %al
	movb	%al, 2(%edx)
	movb	%cl, 3(%edx)
	cmpl	$2, 120(%ebx)
	jne	.L244
	movsbl	4(%edx),%ecx
	movb	7(%edx), %al
	movb	%al, 4(%edx)
	movb	%cl, 7(%edx)
	movb	6(%edx), %al
	movsbl	5(%edx),%ecx
	movb	%cl, 6(%edx)
	movb	%al, 5(%edx)
	movl	%ebx, 8(%esp)
	popl	%ebx
	jmp	ProcShmDetach
.L244:
	movl	$16, %eax
	popl	%ebx
	ret
	.size	SProcShmDetach, .-SProcShmDetach
	.align 4
	.type	SProcShmPutImage, @function
SProcShmPutImage:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %edx
	movsbl	2(%edx),%ecx
	movb	3(%edx), %al
	movb	%al, 2(%edx)
	movb	%cl, 3(%edx)
	cmpl	$10, 120(%ebx)
	jne	.L247
	movsbl	4(%edx),%ecx
	movb	7(%edx), %al
	movb	%al, 4(%edx)
	movb	%cl, 7(%edx)
	movb	6(%edx), %al
	movsbl	5(%edx),%ecx
	movb	%cl, 6(%edx)
	movb	%al, 5(%edx)
	movsbl	8(%edx),%ecx
	movb	11(%edx), %al
	movb	%al, 8(%edx)
	movb	%cl, 11(%edx)
	movb	10(%edx), %al
	movsbl	9(%edx),%ecx
	movb	%cl, 10(%edx)
	movb	%al, 9(%edx)
	movsbl	12(%edx),%ecx
	movb	13(%edx), %al
	movb	%al, 12(%edx)
	movb	%cl, 13(%edx)
	movb	15(%edx), %al
	movsbl	14(%edx),%ecx
	movb	%cl, 15(%edx)
	movb	%al, 14(%edx)
	movsbl	16(%edx),%ecx
	movb	17(%edx), %al
	movb	%al, 16(%edx)
	movb	%cl, 17(%edx)
	movb	19(%edx), %al
	movsbl	18(%edx),%ecx
	movb	%cl, 19(%edx)
	movb	%al, 18(%edx)
	movsbl	20(%edx),%ecx
	movb	21(%edx), %al
	movb	%al, 20(%edx)
	movb	23(%edx), %al
	movb	%cl, 21(%edx)
	movsbl	22(%edx),%ecx
	movb	%cl, 23(%edx)
	movb	%al, 22(%edx)
	movsbl	24(%edx),%ecx
	movb	25(%edx), %al
	movb	%al, 24(%edx)
	movb	%cl, 25(%edx)
	movb	27(%edx), %al
	movsbl	26(%edx),%ecx
	movb	%cl, 27(%edx)
	movb	%al, 26(%edx)
	movsbl	32(%edx),%ecx
	movb	35(%edx), %al
	movb	%al, 32(%edx)
	movb	%cl, 35(%edx)
	movb	34(%edx), %al
	movsbl	33(%edx),%ecx
	movb	%cl, 34(%edx)
	movb	%al, 33(%edx)
	movsbl	36(%edx),%ecx
	movb	39(%edx), %al
	movb	%al, 36(%edx)
	movb	%cl, 39(%edx)
	movb	38(%edx), %al
	movsbl	37(%edx),%ecx
	movb	%cl, 38(%edx)
	movb	%al, 37(%edx)
	movl	%ebx, 8(%esp)
	popl	%ebx
	jmp	ProcShmPutImage
.L247:
	movl	$16, %eax
	popl	%ebx
	ret
	.size	SProcShmPutImage, .-SProcShmPutImage
	.align 4
	.type	SProcShmGetImage, @function
SProcShmGetImage:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %edx
	movsbl	2(%edx),%ecx
	movb	3(%edx), %al
	movb	%al, 2(%edx)
	movb	%cl, 3(%edx)
	cmpl	$8, 120(%ebx)
	jne	.L250
	movsbl	4(%edx),%ecx
	movb	7(%edx), %al
	movb	%al, 4(%edx)
	movb	%cl, 7(%edx)
	movb	6(%edx), %al
	movsbl	5(%edx),%ecx
	movb	%cl, 6(%edx)
	movb	%al, 5(%edx)
	movsbl	8(%edx),%ecx
	movb	9(%edx), %al
	movb	%al, 8(%edx)
	movb	%cl, 9(%edx)
	movb	11(%edx), %al
	movsbl	10(%edx),%ecx
	movb	%cl, 11(%edx)
	movb	%al, 10(%edx)
	movsbl	12(%edx),%ecx
	movb	13(%edx), %al
	movb	%al, 12(%edx)
	movb	%cl, 13(%edx)
	movb	15(%edx), %al
	movsbl	14(%edx),%ecx
	movb	%cl, 15(%edx)
	movb	%al, 14(%edx)
	movsbl	16(%edx),%ecx
	movb	19(%edx), %al
	movb	%al, 16(%edx)
	movb	%cl, 19(%edx)
	movb	18(%edx), %al
	movsbl	17(%edx),%ecx
	movb	%cl, 18(%edx)
	movb	%al, 17(%edx)
	movsbl	24(%edx),%ecx
	movb	27(%edx), %al
	movb	%al, 24(%edx)
	movb	26(%edx), %al
	movb	%cl, 27(%edx)
	movsbl	25(%edx),%ecx
	movb	%cl, 26(%edx)
	movb	%al, 25(%edx)
	movsbl	28(%edx),%ecx
	movb	31(%edx), %al
	movb	%al, 28(%edx)
	movb	%cl, 31(%edx)
	movb	30(%edx), %al
	movsbl	29(%edx),%ecx
	movb	%cl, 30(%edx)
	movb	%al, 29(%edx)
	movl	%ebx, 8(%esp)
	popl	%ebx
	jmp	ProcShmGetImage
.L250:
	movl	$16, %eax
	popl	%ebx
	ret
	.size	SProcShmGetImage, .-SProcShmGetImage
	.align 4
	.type	SProcShmCreatePixmap, @function
SProcShmCreatePixmap:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %edx
	movsbl	2(%edx),%ecx
	movb	3(%edx), %al
	movb	%al, 2(%edx)
	movb	%cl, 3(%edx)
	cmpl	$7, 120(%ebx)
	jne	.L253
	movsbl	4(%edx),%ecx
	movb	7(%edx), %al
	movb	%al, 4(%edx)
	movb	%cl, 7(%edx)
	movb	6(%edx), %al
	movsbl	5(%edx),%ecx
	movb	%cl, 6(%edx)
	movb	%al, 5(%edx)
	movsbl	8(%edx),%ecx
	movb	11(%edx), %al
	movb	%al, 8(%edx)
	movb	%cl, 11(%edx)
	movb	10(%edx), %al
	movsbl	9(%edx),%ecx
	movb	%cl, 10(%edx)
	movb	%al, 9(%edx)
	movsbl	12(%edx),%ecx
	movb	13(%edx), %al
	movb	%al, 12(%edx)
	movb	%cl, 13(%edx)
	movb	15(%edx), %al
	movsbl	14(%edx),%ecx
	movb	%cl, 15(%edx)
	movb	%al, 14(%edx)
	movsbl	20(%edx),%ecx
	movb	23(%edx), %al
	movb	%al, 20(%edx)
	movb	%cl, 23(%edx)
	movb	22(%edx), %al
	movsbl	21(%edx),%ecx
	movb	%cl, 22(%edx)
	movb	%al, 21(%edx)
	movsbl	24(%edx),%ecx
	movb	27(%edx), %al
	movb	%al, 24(%edx)
	movb	%cl, 27(%edx)
	movb	26(%edx), %al
	movsbl	25(%edx),%ecx
	movb	%cl, 26(%edx)
	movb	%al, 25(%edx)
	movl	%ebx, 8(%esp)
	popl	%ebx
	jmp	ProcShmCreatePixmap
.L253:
	movl	$16, %eax
	popl	%ebx
	ret
	.size	SProcShmCreatePixmap, .-SProcShmCreatePixmap
	.align 4
	.type	SProcShmDispatch, @function
SProcShmDispatch:
	movl	4(%esp), %edx
	movl	8(%edx), %eax
	movzbl	1(%eax), %eax
	cmpl	$5, %eax
	ja	.L262
	jmp	*.L263(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L263:
	.long	.L256
	.long	.L257
	.long	.L258
	.long	.L259
	.long	.L260
	.long	.L261
	.text
.L256:
	movl	%edx, 4(%esp)
	jmp	SProcShmQueryVersion
.L257:
	movl	%edx, 4(%esp)
	jmp	SProcShmAttach
.L258:
	movl	%edx, 4(%esp)
	jmp	SProcShmDetach
.L259:
	movl	%edx, 4(%esp)
	jmp	SProcShmPutImage
.L260:
	movl	%edx, 4(%esp)
	jmp	SProcShmGetImage
.L261:
	movl	%edx, 4(%esp)
	jmp	SProcShmCreatePixmap
.L262:
	movl	$1, %eax
	ret
	.size	SProcShmDispatch, .-SProcShmDispatch
	.local	ShmReqCode
	.comm	ShmReqCode,1,1
	.comm	ShmCompletionCode,4,4
	.comm	BadShmSegCode,4,4
	.comm	ShmSegType,4,4
	.local	Shmsegs
	.comm	Shmsegs,4,4
	.local	sharedPixmaps
	.comm	sharedPixmaps,4,4
	.local	pixmapFormat
	.comm	pixmapFormat,4,4
	.local	shmPixFormat
	.comm	shmPixFormat,64,32
	.local	shmFuncs
	.comm	shmFuncs,64,32
	.local	destroyPixmap
	.comm	destroyPixmap,64,32
	.ident	"GCC: (GNU) 3.3.2"
