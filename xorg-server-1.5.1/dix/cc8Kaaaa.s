	.file	"window.c"
	.data
	.type	_back_lsb, @object
	.size	_back_lsb, 4
_back_lsb:
	.byte	-120
	.byte	34
	.byte	68
	.byte	17
	.type	_back_msb, @object
	.size	_back_msb, 4
_back_msb:
	.byte	17
	.byte	68
	.byte	34
	.byte	-120
.globl screenIsSaved
	.align 4
	.type	screenIsSaved, @object
	.size	screenIsSaved, 4
screenIsSaved:
	.long	1
.globl numSaveUndersViewable
	.section	.bss
	.align 4
	.type	numSaveUndersViewable, @object
	.size	numSaveUndersViewable, 4
numSaveUndersViewable:
	.zero	4
.globl deltaSaveUndersViewable
	.align 4
	.type	deltaSaveUndersViewable, @object
	.size	deltaSaveUndersViewable, 4
deltaSaveUndersViewable:
	.zero	4
	.text
	.align 4
.globl TraverseTree
	.type	TraverseTree, @function
TraverseTree:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %esi
	testl	%esi, %esi
	movl	24(%esp), %ebp
	movl	28(%esp), %edi
	movl	%esi, %ebx
	movl	$3, %eax
	je	.L1
.L17:
	pushl	%edi
	pushl	%ebx
	call	*%ebp
	movl	%eax, %edx
	popl	%eax
	xorl	%eax, %eax
	testl	%edx, %edx
	popl	%ecx
	je	.L1
	decl	%edx
	jne	.L7
	movl	40(%ebx), %eax
	testl	%eax, %eax
	je	.L7
	movl	%eax, %ebx
	jmp	.L17
.L7:
	cmpl	$0, 32(%ebx)
	jne	.L9
	cmpl	%esi, %ebx
	je	.L4
.L12:
	movl	28(%ebx), %ebx
	cmpl	$0, 32(%ebx)
	jne	.L9
	cmpl	%esi, %ebx
	jne	.L12
	jmp	.L4
.L9:
	cmpl	%esi, %ebx
	je	.L4
	movl	32(%ebx), %ebx
	jmp	.L17
.L4:
	movl	$3, %eax
.L1:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	TraverseTree, .-TraverseTree
	.align 4
.globl WalkTree
	.type	WalkTree, @function
WalkTree:
	pushl	12(%esp)
	pushl	12(%esp)
	movl	12(%esp), %eax
	movl	(%eax), %edx
	movl	WindowTable, %eax
	pushl	(%eax,%edx,4)
	call	TraverseTree
	addl	$12, %esp
	ret
	.size	WalkTree, .-WalkTree
.globl defaultBackingStore
	.section	.bss
	.align 4
	.type	defaultBackingStore, @object
	.size	defaultBackingStore, 4
defaultBackingStore:
	.zero	4
.globl disableBackingStore
	.align 4
	.type	disableBackingStore, @object
	.size	disableBackingStore, 4
disableBackingStore:
	.zero	4
.globl enableBackingStore
	.align 4
	.type	enableBackingStore, @object
	.size	enableBackingStore, 4
enableBackingStore:
	.zero	4
.globl disableSaveUnders
	.align 4
	.type	disableSaveUnders, @object
	.size	disableSaveUnders, 4
disableSaveUnders:
	.zero	4
	.text
	.align 4
	.type	SetWindowToDefaults, @function
SetWindowToDefaults:
	movl	4(%esp), %eax
	movb	130(%eax), %dl
	orl	$6, %edx
	andl	$-58, %edx
	movb	128(%eax), %cl
	movb	%dl, 130(%eax)
	orl	$8, %ecx
	andw	$-449, 130(%eax)
	andl	$15, %ecx
	andb	$-31, 131(%eax)
	movl	$0, 36(%eax)
	movl	$0, 40(%eax)
	movl	$0, 44(%eax)
	movl	$0, 72(%eax)
	movl	$0, 124(%eax)
	movl	$0, 120(%eax)
	movb	%cl, 128(%eax)
	movb	$16, 129(%eax)
	movl	$0, 108(%eax)
	movw	$0, 106(%eax)
	ret
	.size	SetWindowToDefaults, .-SetWindowToDefaults
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"could not create root tile"
	.text
	.align 4
	.type	MakeRootTile, @function
MakeRootTile:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$136, %esp
	movl	156(%esp), %ebp
	movl	16(%ebp), %ebx
	pushl	$0
	movzbl	18(%ebx), %eax
	pushl	%eax
	pushl	$4
	pushl	$4
	pushl	%ebx
	call	*192(%ebx)
	movl	%eax, 112(%ebp)
	orb	$3, 128(%ebp)
	pushl	%ebx
	movzbl	18(%ebx), %eax
	pushl	%eax
	call	GetScratchGC
	addl	$28, %esp
	cmpl	$0, 112(%ebp)
	movl	%eax, %edi
	je	.L22
	testl	%eax, %eax
	jne	.L21
.L22:
	pushl	$.LC0
	call	FatalError
.L21:
	movl	40(%ebx), %eax
	movl	%eax, (%esp)
	movl	44(%ebx), %eax
	movl	%eax, 4(%esp)
	movl	%esp, %eax
	pushl	%eax
	pushl	$12
	pushl	%edi
	call	ChangeGC
	pushl	%edi
	pushl	112(%ebp)
	call	ValidateGC
	addl	$20, %esp
	cmpl	$0, screenInfo+12
	jne	.L23
	movl	$_back_lsb, %ebx
	jmp	.L24
.L23:
	movl	$_back_msb, %ebx
.L24:
	leal	8(%esp), %esi
	movl	$4, %ecx
.L34:
	movl	$4, %edx
.L33:
	movb	(%ebx), %al
	decl	%edx
	movb	%al, (%esi)
	incl	%esi
	testl	%edx, %edx
	jg	.L33
	decl	%ecx
	incl	%ebx
	testl	%ecx, %ecx
	jg	.L34
	leal	8(%esp), %eax
	movl	72(%edi), %edx
	pushl	%eax
	pushl	$0
	pushl	$0
	pushl	$4
	pushl	$4
	pushl	$0
	pushl	$0
	pushl	$1
	pushl	%edi
	pushl	112(%ebp)
	call	*8(%edx)
	addl	$40, %esp
	pushl	%edi
	call	FreeScratchGC
	addl	$140, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	MakeRootTile, .-MakeRootTile
	.align 4
.globl CreateRootWindow
	.type	CreateRootWindow, @function
CreateRootWindow:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	pushl	%eax
	movl	24(%esp), %edi
	pushl	$132
	call	Xalloc
	movl	%eax, %esi
	xorl	%ecx, %ecx
	testl	%esi, %esi
	popl	%eax
	je	.L39
	movl	(%edi), %ebx
	sall	$4, %ebx
	pushl	$0
	movl	$0, savedScreenInfo(%ebx)
	call	FakeClientID
	movl	(%edi), %edx
	movl	%eax, savedScreenInfo+4(%ebx)
	movl	%edx, %eax
	sall	$4, %eax
	movl	$0, savedScreenInfo+12(%eax)
	movl	WindowTable, %eax
	movl	%esi, (%eax,%edx,4)
	movl	%edi, 16(%esi)
	movl	$0, 24(%esi)
	movl	$1, screenIsSaved
	movb	$0, (%esi)
	movb	18(%edi), %al
	movb	%al, 2(%esi)
	movb	18(%edi), %dl
	cmpb	%dl, screenInfo+20
	movl	$screenInfo+20, %eax
	popl	%ebx
	je	.L72
.L45:
	addl	$3, %eax
	cmpb	%dl, (%eax)
	jne	.L45
.L72:
	movb	1(%eax), %al
	movb	%al, 3(%esi)
	movl	globalSerialNumber, %eax
	incl	%eax
	cmpl	$268435456, %eax
	movl	%eax, globalSerialNumber
	jbe	.L47
	movl	$1, globalSerialNumber
	movl	$1, %eax
.L47:
	movl	%eax, 20(%esi)
	movl	$0, 28(%esi)
	pushl	%esi
	call	SetWindowToDefaults
	pushl	$56
	call	Xalloc
	movl	%eax, 124(%esi)
	movl	%eax, %edx
	popl	%eax
	popl	%ecx
	xorl	%ecx, %ecx
	testl	%edx, %edx
	je	.L39
	movl	$0, 12(%edx)
	movl	$0, 16(%edx)
	movl	$-1, 32(%edx)
	movl	$0, 36(%edx)
	movl	28(%edi), %eax
	movl	%eax, 8(%edx)
	movl	24(%edi), %eax
	movl	$0, 20(%edx)
	movl	$0, 24(%edx)
	movl	$0, 28(%edx)
	movl	$0, 40(%edx)
	movl	$0, 44(%edx)
	movl	$0, 48(%edx)
	movl	$0, 52(%edx)
	movl	%eax, (%edx)
	movl	$0, 32(%esi)
	pushl	$0
	call	FakeClientID
	movw	$0, 102(%esi)
	movw	$0, 100(%esi)
	movl	%eax, 4(%esi)
	movw	10(%edi), %ax
	movw	%ax, 14(%esi)
	movw	8(%edi), %ax
	movw	%ax, 12(%esi)
	movw	$0, 10(%esi)
	movw	$0, 8(%esi)
	movw	$0, 4(%esp)
	movw	$0, 6(%esp)
	movw	8(%edi), %ax
	movw	%ax, 8(%esp)
	movw	10(%edi), %ax
	movw	%ax, 10(%esp)
	movl	8(%esp), %edx
	movl	4(%esp), %eax
	movl	%eax, 48(%esi)
	movl	%edx, 52(%esi)
	movl	$0, 56(%esi)
	popl	%eax
	movl	(%esp), %eax
	movl	4(%esp), %edx
	movl	%edx, 80(%esi)
	movl	%eax, 76(%esi)
	movl	(%esp), %eax
	movl	4(%esp), %edx
	movl	%edx, 92(%esi)
	movl	%eax, 88(%esi)
	movl	(%esp), %eax
	movl	4(%esp), %edx
	movl	$0, 84(%esi)
	movl	$0, 96(%esi)
	movl	%eax, 60(%esi)
	movb	$1, 1(%esi)
	movl	24(%edi), %eax
	movl	%edx, 64(%esi)
	movl	124(%esi), %edx
	movl	%eax, (%edx)
	movb	128(%esi), %al
	andl	$-4, %eax
	orl	$2, %eax
	movb	%al, 128(%esi)
	movl	40(%edi), %edx
	orl	$4, %eax
	movl	%edx, 112(%esi)
	movb	%al, 128(%esi)
	movl	44(%edi), %eax
	movl	$0, 68(%esi)
	movl	%eax, 116(%esi)
	movw	$0, 104(%esi)
	pushl	%esi
	pushl	$1073741825
	pushl	4(%esi)
	call	AddResource
	addl	$12, %esp
	xorl	%ecx, %ecx
	testl	%eax, %eax
	je	.L39
	cmpl	$0, disableBackingStore
	je	.L67
	movb	$0, 36(%edi)
.L67:
	cmpl	$0, enableBackingStore
	je	.L68
	movb	$2, 36(%edi)
.L68:
	cmpb	$0, 36(%edi)
	je	.L69
	cmpb	$0, 37(%edi)
	jne	.L69
	movb	$64, 37(%edi)
.L69:
	cmpl	$0, disableSaveUnders
	je	.L70
	movb	$0, 37(%edi)
.L70:
	movl	$1, %ecx
.L39:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	movl	%ecx, %eax
	popl	%edi
	ret
	.size	CreateRootWindow, .-CreateRootWindow
	.align 4
.globl InitRootWindow
	.type	InitRootWindow, @function
InitRootWindow:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %ebx
	movl	16(%ebx), %esi
	pushl	%ebx
	call	*132(%esi)
	testl	%eax, %eax
	popl	%edx
	je	.L73
	pushl	$0
	pushl	$0
	pushl	%ebx
	call	*140(%esi)
	andb	$-9, 128(%ebx)
	movl	rootCursor, %eax
	movl	124(%ebx), %edx
	incl	16(%eax)
	addl	$12, %esp
	cmpl	$0, blackRoot
	movl	%eax, 4(%edx)
	jne	.L79
	cmpl	$0, whiteRoot
	jne	.L75
	pushl	%ebx
	call	MakeRootTile
	movl	$16457, %ecx
	popl	%eax
	jmp	.L76
.L79:
	movl	44(%esi), %eax
	jmp	.L80
.L75:
	movl	40(%esi), %eax
.L80:
	movl	%eax, 112(%ebx)
	movl	$16458, %ecx
.L76:
	movb	defaultBackingStore, %dl
	movb	128(%ebx), %al
	andl	$3, %edx
	sall	$4, %edx
	andl	$-49, %eax
	orl	%edx, %eax
	movb	%al, 128(%ebx)
	cmpl	$0, defaultBackingStore
	setne	%dl
	movb	131(%ebx), %al
	sall	%edx
	andl	$-3, %eax
	orl	%edx, %eax
	movb	%al, 131(%ebx)
	pushl	%ecx
	pushl	%ebx
	call	*144(%esi)
	pushl	serverClient
	pushl	%ebx
	call	MapWindow
	addl	$16, %esp
.L73:
	popl	%ebx
	popl	%esi
	ret
	.size	InitRootWindow, .-InitRootWindow
	.align 4
	.type	ClippedRegionFromBox, @function
ClippedRegionFromBox:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	pushl	%ebx
	movl	24(%esp), %edi
	movl	76(%edi), %eax
	movl	80(%edi), %edx
	movl	%eax, (%esp)
	movl	32(%esp), %ecx
	movswl	(%esp),%eax
	cmpl	%eax, %ecx
	movl	28(%esp), %esi
	movl	36(%esp), %ebx
	movl	%edx, 4(%esp)
	jle	.L82
	movw	%cx, (%esp)
.L82:
	movswl	2(%esp),%eax
	cmpl	%eax, %ebx
	jle	.L83
	movw	%bx, 2(%esp)
.L83:
	addl	40(%esp), %ecx
	movswl	4(%esp),%eax
	cmpl	%eax, %ecx
	jge	.L84
	movw	%cx, 4(%esp)
.L84:
	addl	44(%esp), %ebx
	movswl	6(%esp),%eax
	cmpl	%eax, %ebx
	jge	.L85
	movw	%bx, 6(%esp)
.L85:
	movl	(%esp), %eax
	cmpw	4(%esp), %ax
	jle	.L86
	movw	%ax, 4(%esp)
.L86:
	movw	2(%esp), %ax
	cmpw	6(%esp), %ax
	jle	.L87
	movw	%ax, 6(%esp)
.L87:
	movl	(%esp), %eax
	movl	4(%esp), %edx
	movl	%eax, (%esi)
	movl	8(%esi), %eax
	testl	%eax, %eax
	movl	%edx, 4(%esi)
	je	.L88
	cmpl	$0, (%eax)
	je	.L88
	pushl	%eax
	call	Xfree
	movl	$0, 8(%esi)
	popl	%ecx
.L88:
	leal	76(%edi), %eax
	movl	$0, 8(%esi)
	pushl	%eax
	pushl	%esi
	pushl	%esi
	call	miIntersect
	addl	$20, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ClippedRegionFromBox, .-ClippedRegionFromBox
	.local	realChildHeadProc
	.comm	realChildHeadProc,4,4
	.align 4
.globl RegisterRealChildHeadProc
	.type	RegisterRealChildHeadProc, @function
RegisterRealChildHeadProc:
	movl	4(%esp), %eax
	movl	%eax, realChildHeadProc
	ret
	.size	RegisterRealChildHeadProc, .-RegisterRealChildHeadProc
	.align 4
.globl RealChildHead
	.type	RealChildHead, @function
RealChildHead:
	movl	realChildHeadProc, %eax
	testl	%eax, %eax
	movl	4(%esp), %edx
	je	.L91
	pushl	%edx
	call	*%eax
	popl	%edx
	ret
.L91:
	cmpl	$0, 28(%edx)
	jne	.L92
	cmpl	$0, screenIsSaved
	jne	.L92
	movl	16(%edx), %eax
	movl	(%eax), %eax
	sall	$4, %eax
	cmpl	$0, savedScreenInfo(%eax)
	je	.L92
	movl	40(%edx), %eax
	ret
.L92:
	xorl	%eax, %eax
	ret
	.size	RealChildHead, .-RealChildHead
	.align 4
.globl CreateWindow
	.type	CreateWindow, @function
CreateWindow:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$56, %esp
	cmpl	$0, 104(%esp)
	movl	80(%esp), %ebp
	jne	.L95
	movzbl	1(%ebp), %eax
	movl	%eax, 104(%esp)
.L95:
	movl	104(%esp), %eax
	decl	%eax
	cmpl	$1, %eax
	jbe	.L96
	movl	128(%esp), %edx
	movl	$2, (%edx)
	movl	120(%esp), %eax
	movl	104(%esp), %ecx
	movl	%ecx, 24(%eax)
	jmp	.L162
.L96:
	cmpl	$2, 104(%esp)
	je	.L152
	cmpb	$2, 1(%ebp)
	jne	.L98
	movl	128(%esp), %ebx
	movl	$8, (%ebx)
	jmp	.L162
.L152:
	cmpl	$0, 100(%esp)
	jne	.L121
	cmpl	$0, 116(%esp)
	jne	.L121
.L98:
	movl	16(%ebp), %edx
	cmpl	$1, 104(%esp)
	movl	%edx, 16(%esp)
	jne	.L100
	cmpl	$0, 116(%esp)
	jne	.L100
	movzbl	2(%ebp), %ecx
	movl	%ecx, 116(%esp)
.L100:
	movl	124(%ebp), %ebx
	testl	%ebx, %ebx
	movl	%ebx, 8(%esp)
	jne	.L101
	pushl	%ebp
	call	FindWindowWithOptional
	movl	124(%eax), %edx
	movl	%edx, 12(%esp)
	popl	%edi
.L101:
	cmpl	$0, 124(%esp)
	jne	.L102
	movl	8(%esp), %ecx
	movl	(%ecx), %ecx
	movl	%ecx, 124(%esp)
.L102:
	movl	8(%esp), %ebx
	movl	(%ebx), %ebx
	cmpl	%ebx, 124(%esp)
	movl	%ebx, 4(%esp)
	jne	.L104
	movzbl	2(%ebp), %eax
	cmpl	%eax, 116(%esp)
	je	.L103
.L104:
	movl	16(%esp), %eax
	movw	16(%eax), %di
	xorl	%esi, %esi
	testw	%di, %di
	movl	$0, 12(%esp)
	jle	.L121
.L117:
	movl	16(%esp), %edx
	movl	20(%edx), %eax
	leal	(%eax,%esi,8), %ecx
	movzbl	(%ecx), %eax
	cmpl	%eax, 116(%esp)
	je	.L110
	cmpl	$0, 116(%esp)
	jne	.L107
.L110:
	movw	2(%ecx), %bx
	xorl	%edx, %edx
	testw	%bx, %bx
	movw	%bx, 2(%esp)
	jle	.L107
.L116:
	movl	124(%esp), %ebx
	movl	4(%ecx), %eax
	cmpl	(%eax,%edx,4), %ebx
	jne	.L113
	movl	$1, 12(%esp)
	jmp	.L107
.L113:
	incl	%edx
	movswl	2(%esp),%eax
	cmpl	%eax, %edx
	jl	.L116
.L107:
	incl	%esi
	movswl	%di,%eax
	cmpl	%eax, %esi
	jl	.L117
	cmpl	$0, 12(%esp)
	je	.L121
.L103:
	testb	$12, 108(%esp)
	jne	.L119
	cmpl	$2, 104(%esp)
	je	.L119
	movzbl	2(%ebp), %eax
	cmpl	%eax, 116(%esp)
	je	.L119
	movl	128(%esp), %edx
	movl	$8, (%edx)
	jmp	.L162
.L119:
	testl	$8192, 108(%esp)
	jne	.L120
	cmpl	$2, 104(%esp)
	je	.L120
	movl	4(%esp), %ecx
	cmpl	%ecx, 124(%esp)
	jne	.L121
	movl	8(%esp), %ebx
	cmpl	$0, 8(%ebx)
	jne	.L120
.L121:
	movl	128(%esp), %eax
	movl	$8, (%eax)
	jmp	.L162
.L120:
	pushl	$132
	call	Xalloc
	testl	%eax, %eax
	movl	%eax, %ebx
	popl	%esi
	jne	.L122
	movl	128(%esp), %edx
	movl	$11, (%edx)
.L162:
	xorl	%edi, %edi
	jmp	.L94
.L122:
	movl	%eax, %edi
	cld
	movl	$6, %ecx
	movl	%ebp, %esi
	rep
	movsl
	movb	116(%esp), %cl
	movb	%cl, 2(%eax)
	movl	$0, 24(%eax)
	movzbl	2(%ebp), %eax
	cmpl	%eax, 116(%esp)
	jne	.L123
	movb	3(%ebp), %al
	jmp	.L160
.L123:
	movzbl	screenInfo+20, %eax
	cmpl	116(%esp), %eax
	movl	$screenInfo+20, %edx
	je	.L157
.L129:
	addl	$3, %edx
	movzbl	(%edx), %eax
	cmpl	116(%esp), %eax
	jne	.L129
.L157:
	movb	1(%edx), %al
.L160:
	movb	%al, 3(%ebx)
	cmpl	$2, 104(%esp)
	jne	.L130
	movb	$2, (%ebx)
.L130:
	movl	globalSerialNumber, %eax
	incl	%eax
	cmpl	$268435456, %eax
	movl	%eax, globalSerialNumber
	jbe	.L132
	movl	$1, globalSerialNumber
	movl	$1, %eax
.L132:
	movl	%eax, 20(%ebx)
	movl	76(%esp), %eax
	movb	104(%esp), %dl
	movl	%eax, 4(%ebx)
	movb	%dl, 1(%ebx)
	movl	%ebp, 28(%ebx)
	pushl	%ebx
	call	SetWindowToDefaults
	popl	%ecx
	movl	124(%esp), %eax
	movl	8(%esp), %ecx
	cmpl	(%ecx), %eax
	je	.L133
	pushl	%ebx
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%edx
	jne	.L134
	pushl	%ebx
	call	Xfree
	movl	132(%esp), %edx
	movl	$11, (%edx)
	xorl	%edi, %edi
	popl	%ebp
	jmp	.L94
.L134:
	movl	124(%ebx), %eax
	movl	124(%esp), %ecx
	movl	%ecx, (%eax)
	movl	$0, 8(%eax)
.L133:
	movl	128(%esp), %edx
	movl	100(%esp), %eax
	movl	$0, (%edx)
	movw	%ax, 104(%ebx)
	movb	128(%ebx), %al
	andl	$-4, %eax
	movb	%al, 128(%ebx)
	movl	16(%esp), %ecx
	movl	40(%ecx), %edx
	movl	%edx, 112(%ebx)
	movb	128(%ebp), %dl
	andl	$4, %edx
	andl	$-5, %eax
	orl	%edx, %eax
	movb	%al, 128(%ebx)
	movl	116(%ebp), %edx
	testb	$4, %al
	movl	%edx, 116(%ebx)
	jne	.L136
	incl	28(%edx)
.L136:
	movl	84(%esp), %eax
	addl	100(%esp), %eax
	movw	%ax, 100(%ebx)
	movl	88(%esp), %eax
	addl	100(%esp), %eax
	movw	%ax, 102(%ebx)
	movl	92(%esp), %eax
	movw	%ax, 12(%ebx)
	movl	84(%esp), %eax
	addl	8(%ebp), %eax
	addl	100(%esp), %eax
	movw	%ax, 8(%ebx)
	movl	88(%esp), %eax
	addw	10(%ebp), %ax
	addl	100(%esp), %eax
	movl	96(%esp), %edx
	movw	%dx, 14(%ebx)
	movw	%ax, 10(%ebx)
	movl	miEmptyBox, %eax
	movl	miEmptyBox+4, %edx
	movl	%edx, 52(%ebx)
	movl	%eax, 48(%ebx)
	movl	miEmptyBox, %eax
	movl	miEmptyBox+4, %edx
	movl	%edx, 64(%ebx)
	movl	%eax, 60(%ebx)
	movl	miEmptyBox, %eax
	movl	miEmptyBox+4, %edx
	movl	%edx, 80(%ebx)
	movl	%eax, 76(%ebx)
	movl	miEmptyBox+4, %edx
	movl	miEmptyBox, %eax
	movl	$miEmptyData, 56(%ebx)
	movl	$miEmptyData, 68(%ebx)
	movl	$miEmptyData, 84(%ebx)
	movl	%eax, 88(%ebx)
	movl	%edx, 92(%ebx)
	movl	$miEmptyData, 96(%ebx)
	pushl	%ebp
	call	RealChildHead
	testl	%eax, %eax
	movl	%eax, %edx
	popl	%edi
	je	.L137
	movl	32(%eax), %eax
	movl	%eax, 32(%ebx)
	movl	32(%edx), %eax
	testl	%eax, %eax
	je	.L138
	movl	%ebx, 36(%eax)
	jmp	.L139
.L138:
	movl	%ebx, 44(%ebp)
.L139:
	movl	%ebx, 32(%edx)
	movl	%edx, 36(%ebx)
	jmp	.L140
.L137:
	movl	40(%ebp), %eax
	testl	%eax, %eax
	movl	%eax, 32(%ebx)
	je	.L141
	movl	%ebx, 36(%eax)
	jmp	.L142
.L141:
	movl	%ebx, 44(%ebp)
.L142:
	movl	%ebx, 40(%ebp)
.L140:
	pushl	%ebx
	call	SetWinSize
	pushl	%ebx
	call	SetBorderSize
	pushl	%ebx
	movl	28(%esp), %ecx
	call	*132(%ecx)
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L143
	movl	128(%esp), %eax
	movl	$11, (%eax)
	jmp	.L161
.L143:
	movswl	10(%ebx),%eax
	pushl	%eax
	movswl	8(%ebx),%eax
	pushl	%eax
	pushl	%ebx
	movl	28(%esp), %edx
	call	*140(%edx)
	addl	$12, %esp
	testl	$2048, 108(%esp)
	jne	.L144
	pushl	%ebx
	call	RecalculateDeliverableEvents
	popl	%esi
.L144:
	cmpl	$0, 108(%esp)
	je	.L145
	movl	4(%ebx), %eax
	andl	$534773760, %eax
	shrl	$21, %eax
	movl	clients, %edx
	pushl	(%edx,%eax,4)
	pushl	116(%esp)
	pushl	116(%esp)
	pushl	%ebx
	call	ChangeWindowAttributes
	movl	144(%esp), %ecx
	addl	$16, %esp
	movl	%eax, (%ecx)
	jmp	.L146
.L145:
	movl	128(%esp), %eax
	movl	$0, (%eax)
.L146:
	movl	128(%esp), %edx
	cmpl	$0, (%edx)
	je	.L147
.L161:
	pushl	$0
	pushl	%ebx
	call	DeleteWindow
	popl	%ecx
	xorl	%edi, %edi
	popl	%ebx
	jmp	.L94
.L147:
	testb	$64, 108(%esp)
	jne	.L148
	movl	defaultBackingStore, %eax
	testl	%eax, %eax
	je	.L148
	movl	%eax, 20(%esp)
	movl	4(%ebx), %eax
	andl	$534773760, %eax
	shrl	$21, %eax
	movl	clients, %edx
	pushl	(%edx,%eax,4)
	leal	24(%esp), %eax
	pushl	%eax
	pushl	$64
	pushl	%ebx
	call	ChangeWindowAttributes
	orb	$2, 131(%ebx)
	addl	$16, %esp
.L148:
	movl	124(%ebp), %edx
	testl	%edx, %edx
	movl	108(%ebp), %eax
	je	.L150
	orl	16(%edx), %eax
.L150:
	testl	$524288, %eax
	je	.L149
	movl	76(%esp), %ecx
	movl	%ecx, 32(%esp)
	movb	$16, 24(%esp)
	movl	4(%ebp), %eax
	movl	%eax, 28(%esp)
	movl	88(%esp), %edx
	movl	84(%esp), %eax
	movw	%ax, 36(%esp)
	movw	%dx, 38(%esp)
	movl	96(%esp), %eax
	movl	92(%esp), %ecx
	movl	100(%esp), %edx
	movw	%cx, 40(%esp)
	movw	%ax, 42(%esp)
	movw	%dx, 44(%esp)
	movzbl	130(%ebx), %eax
	andl	$1, %eax
	movb	%al, 46(%esp)
	pushl	$0
	pushl	$1
	leal	32(%esp), %eax
	pushl	%eax
	pushl	%ebp
	call	DeliverEvents
	addl	$16, %esp
.L149:
	movl	%ebx, %edi
.L94:
	addl	$56, %esp
	popl	%ebx
	popl	%esi
	movl	%edi, %eax
	popl	%edi
	popl	%ebp
	ret
	.size	CreateWindow, .-CreateWindow
	.align 4
	.type	DisposeWindowOptional, @function
DisposeWindowOptional:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	124(%ebx), %eax
	testl	%eax, %eax
	je	.L163
	cmpl	$0, 4(%eax)
	je	.L165
	pushl	$0
	pushl	4(%eax)
	call	FreeCursor
	andb	$-9, 128(%ebx)
	popl	%eax
	popl	%edx
	jmp	.L166
.L165:
	orb	$8, 128(%ebx)
.L166:
	pushl	124(%ebx)
	call	Xfree
	movl	$0, 124(%ebx)
	popl	%eax
.L163:
	popl	%ebx
	ret
	.size	DisposeWindowOptional, .-DisposeWindowOptional
	.align 4
	.type	FreeWindowResources, @function
FreeWindowResources:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %ebx
	movl	16(%ebx), %esi
	pushl	%ebx
	call	DeleteWindowFromAnySaveSet
	pushl	%ebx
	call	DeleteWindowFromAnySelections
	pushl	$1
	pushl	%ebx
	call	DeleteWindowFromAnyEvents
	movl	56(%ebx), %eax
	addl	$16, %esp
	testl	%eax, %eax
	je	.L168
	cmpl	$0, (%eax)
	je	.L168
	pushl	%eax
	call	Xfree
	movl	$0, 56(%ebx)
	popl	%eax
.L168:
	movl	84(%ebx), %eax
	testl	%eax, %eax
	je	.L169
	cmpl	$0, (%eax)
	je	.L169
	pushl	%eax
	call	Xfree
	movl	$0, 84(%ebx)
	popl	%ecx
.L169:
	movl	68(%ebx), %eax
	testl	%eax, %eax
	je	.L170
	cmpl	$0, (%eax)
	je	.L170
	pushl	%eax
	call	Xfree
	movl	$0, 68(%ebx)
	popl	%edx
.L170:
	movl	96(%ebx), %eax
	testl	%eax, %eax
	je	.L171
	cmpl	$0, (%eax)
	je	.L171
	pushl	%eax
	call	Xfree
	movl	$0, 96(%ebx)
	popl	%eax
.L171:
	movl	124(%ebx), %eax
	testl	%eax, %eax
	je	.L172
	movl	40(%eax), %eax
	testl	%eax, %eax
	je	.L172
	pushl	%eax
	call	miRegionDestroy
	popl	%eax
.L172:
	movl	124(%ebx), %eax
	testl	%eax, %eax
	je	.L177
	movl	44(%eax), %eax
	testl	%eax, %eax
	je	.L177
	pushl	%eax
	call	miRegionDestroy
	popl	%eax
.L177:
	movl	124(%ebx), %eax
	testl	%eax, %eax
	je	.L182
	movl	48(%eax), %eax
	testl	%eax, %eax
	je	.L182
	pushl	%eax
	call	miRegionDestroy
	popl	%eax
.L182:
	testb	$4, 128(%ebx)
	jne	.L187
	pushl	116(%ebx)
	call	*196(%esi)
	popl	%eax
.L187:
	movzbl	128(%ebx), %eax
	andl	$3, %eax
	cmpl	$3, %eax
	jne	.L188
	pushl	112(%ebx)
	call	*196(%esi)
	popl	%eax
.L188:
	pushl	%ebx
	call	DeleteAllWindowProperties
	pushl	%ebx
	call	*136(%esi)
	popl	%ecx
	popl	%esi
	movl	%ebx, 12(%esp)
	popl	%ebx
	popl	%esi
	jmp	DisposeWindowOptional
	.size	FreeWindowResources, .-FreeWindowResources
	.align 4
	.type	CrushTree, @function
CrushTree:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	56(%esp), %ebp
	movl	40(%ebp), %ebx
	testl	%ebx, %ebx
	je	.L189
	movl	16(%ebp), %eax
	movl	152(%eax), %eax
	movl	%eax, (%esp)
.L210:
	movl	40(%ebx), %eax
	testl	%eax, %eax
	je	.L208
	movl	%eax, %ebx
	jmp	.L210
.L208:
	movl	124(%ebx), %edx
	testl	%edx, %edx
	movl	28(%ebx), %esi
	movl	108(%ebx), %eax
	je	.L200
	orl	16(%edx), %eax
.L200:
	testl	$131072, %eax
	jne	.L199
	movl	124(%esi), %edx
	testl	%edx, %edx
	movl	108(%esi), %eax
	je	.L202
	orl	16(%edx), %eax
.L202:
	testl	$524288, %eax
	je	.L198
.L199:
	movb	$17, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 12(%esp)
	pushl	$0
	pushl	$1
	leal	12(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	DeliverEvents
	addl	$16, %esp
.L198:
	pushl	$1073741825
	pushl	4(%ebx)
	call	FreeResource
	movl	128(%ebx), %eax
	andl	$2097216, %eax
	popl	%edx
	cmpl	$2097216, %eax
	movl	32(%ebx), %edi
	popl	%ecx
	jne	.L204
	decl	deltaSaveUndersViewable
.L204:
	movb	130(%ebx), %dl
	movb	%dl, %al
	andl	$-33, %eax
	testb	$16, %al
	movb	%al, 130(%ebx)
	je	.L205
	andl	$-49, %edx
	movb	%dl, 130(%ebx)
	pushl	%ebx
	call	*4(%esp)
	popl	%eax
.L205:
	pushl	%ebx
	call	FreeWindowResources
	pushl	24(%ebx)
	call	dixFreePrivates
	pushl	%ebx
	call	Xfree
	addl	$12, %esp
	testl	%edi, %edi
	movl	%edi, %ebx
	jne	.L210
	cmpl	%ebp, %esi
	movl	%esi, %ebx
	movl	$0, 40(%esi)
	movl	$0, 44(%esi)
	jne	.L208
.L189:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	CrushTree, .-CrushTree
	.align 4
.globl DeleteWindow
	.type	DeleteWindow, @function
DeleteWindow:
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	44(%esp), %esi
	pushl	$0
	pushl	%esi
	call	UnmapWindow
	pushl	%esi
	call	CrushTree
	addl	$12, %esp
	cmpl	$0, 48(%esp)
	movl	28(%esi), %ebx
	je	.L212
	testl	%ebx, %ebx
	je	.L212
	movl	124(%esi), %edx
	testl	%edx, %edx
	movl	108(%esi), %eax
	je	.L214
	orl	16(%edx), %eax
.L214:
	testl	$131072, %eax
	jne	.L213
	movl	124(%ebx), %edx
	testl	%edx, %edx
	movl	108(%ebx), %eax
	je	.L216
	orl	16(%edx), %eax
.L216:
	testl	$524288, %eax
	je	.L212
.L213:
	movb	$17, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 8(%esp)
	pushl	$0
	pushl	$1
	leal	8(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	DeliverEvents
	addl	$16, %esp
.L212:
	pushl	%esi
	call	FreeWindowResources
	testl	%ebx, %ebx
	popl	%eax
	je	.L218
	cmpl	%esi, 40(%ebx)
	jne	.L219
	movl	32(%esi), %eax
	movl	%eax, 40(%ebx)
.L219:
	cmpl	%esi, 44(%ebx)
	jne	.L220
	movl	36(%esi), %eax
	movl	%eax, 44(%ebx)
.L220:
	movl	32(%esi), %edx
	testl	%edx, %edx
	je	.L221
	movl	36(%esi), %eax
	movl	%eax, 36(%edx)
.L221:
	movl	36(%esi), %eax
	testl	%eax, %eax
	je	.L218
	movl	%edx, 32(%eax)
.L218:
	pushl	24(%esi)
	call	dixFreePrivates
	pushl	%esi
	call	Xfree
	addl	$40, %esp
	popl	%ebx
	xorl	%eax, %eax
	popl	%esi
	ret
	.size	DeleteWindow, .-DeleteWindow
	.align 4
.globl DestroySubwindows
	.type	DestroySubwindows, @function
DestroySubwindows:
	pushl	%ebx
	movl	8(%esp), %ebx
	pushl	%ebx
	call	UnmapSubwindows
	cmpl	$0, 44(%ebx)
	popl	%ecx
	je	.L230
.L228:
	pushl	$0
	movl	44(%ebx), %eax
	pushl	4(%eax)
	call	FreeResource
	popl	%eax
	cmpl	$0, 44(%ebx)
	popl	%edx
	jne	.L228
.L230:
	xorl	%eax, %eax
	popl	%ebx
	ret
	.size	DestroySubwindows, .-DestroySubwindows
	.align 4
.globl ChangeWindowAttributes
	.type	ChangeWindowAttributes, @function
ChangeWindowAttributes:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$88, %esp
	movl	108(%esp), %edi
	movl	$0, 4(%esp)
	movl	$0, 32(%esp)
	movl	$0, (%esp)
	cmpb	$2, 1(%edi)
	jne	.L232
	testl	$-23073, 112(%esp)
	movl	$8, %eax
	jne	.L231
	jmp	.L232
.L425:
	movl	%eax, 20(%esp)
	jmp	.L246
.L426:
	movl	120(%esp), %eax
	movl	$2, 20(%esp)
	movl	%edx, 24(%eax)
	jmp	.L246
.L232:
	movl	112(%esp), %eax
	movl	16(%edi), %edx
	testl	%eax, %eax
	movl	$0, 20(%esp)
	movl	%edx, 16(%esp)
	movl	116(%esp), %ebp
	movl	%eax, 8(%esp)
	je	.L246
.L402:
	movl	8(%esp), %edx
	movl	8(%esp), %eax
	negl	%edx
	andl	%eax, %edx
	movl	%edx, %eax
	notl	%eax
	andl	%eax, 8(%esp)
	cmpl	$128, %edx
	movl	%edx, 12(%esp)
	je	.L283
	cmpl	$128, %edx
	ja	.L395
	cmpl	$8, %edx
	je	.L275
	cmpl	$8, %edx
	ja	.L396
	cmpl	$2, %edx
	je	.L258
	cmpl	$2, %edx
	ja	.L397
	decl	%edx
	je	.L237
	jmp	.L393
.L397:
	cmpl	$4, 12(%esp)
	je	.L261
	jmp	.L393
.L396:
	cmpl	$32, 12(%esp)
	je	.L279
	cmpl	$32, 12(%esp)
	ja	.L398
	cmpl	$16, 12(%esp)
	je	.L277
	jmp	.L393
.L398:
	cmpl	$64, 12(%esp)
	je	.L281
	jmp	.L393
.L395:
	cmpl	$2048, 12(%esp)
	je	.L303
	cmpl	$2048, 12(%esp)
	ja	.L399
	cmpl	$512, 12(%esp)
	je	.L307
	cmpl	$512, 12(%esp)
	ja	.L400
	cmpl	$256, 12(%esp)
	je	.L288
	jmp	.L393
.L400:
	cmpl	$1024, 12(%esp)
	je	.L293
	jmp	.L393
.L399:
	cmpl	$8192, 12(%esp)
	je	.L311
	cmpl	$8192, 12(%esp)
	ja	.L401
	cmpl	$4096, 12(%esp)
	je	.L305
	jmp	.L393
.L401:
	cmpl	$16384, 12(%esp)
	je	.L355
	jmp	.L393
.L237:
	movzbl	128(%edi), %edx
	andl	$3, %edx
	movl	(%ebp), %ebx
	addl	$4, %ebp
	cmpl	$1, %edx
	jne	.L238
	movl	$1, (%esp)
.L238:
	testl	%ebx, %ebx
	jne	.L239
	cmpl	$3, %edx
	jne	.L240
	pushl	112(%edi)
	movl	20(%esp), %edx
	call	*196(%edx)
	popl	%ebx
.L240:
	cmpl	$0, 28(%edi)
	jne	.L241
	pushl	%edi
	call	MakeRootTile
	popl	%ecx
	jmp	.L236
.L241:
	andb	$-4, 128(%edi)
	movl	16(%esp), %edx
	movl	40(%edx), %eax
	movl	%eax, 112(%edi)
	jmp	.L236
.L239:
	cmpl	$1, %ebx
	jne	.L244
	movl	28(%edi), %eax
	testl	%eax, %eax
	je	.L245
	movb	2(%eax), %al
	cmpb	%al, 2(%edi)
	jne	.L327
.L245:
	cmpl	$3, %edx
	jne	.L247
	pushl	112(%edi)
	movl	20(%esp), %edx
	call	*196(%edx)
	popl	%edx
.L247:
	cmpl	$0, 28(%edi)
	jne	.L248
	pushl	%edi
	call	MakeRootTile
	popl	%eax
	jmp	.L249
.L248:
	movb	128(%edi), %al
	andl	$-4, %eax
	orl	$1, %eax
	movb	%al, 128(%edi)
.L249:
	movl	$1, (%esp)
	jmp	.L236
.L244:
	pushl	$1
	pushl	124(%esp)
	pushl	$1073741826
	pushl	%ebx
	leal	52(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L268
	movl	36(%esp), %edx
	movb	2(%edi), %al
	cmpb	%al, 2(%edx)
	jne	.L327
	movl	16(%esp), %eax
	cmpl	%eax, 16(%edx)
	jne	.L327
	movzbl	128(%edi), %eax
	andl	$3, %eax
	cmpl	$3, %eax
	jne	.L254
	pushl	112(%edi)
	movl	20(%esp), %edx
	call	*196(%edx)
	popl	%eax
.L254:
	orb	$3, 128(%edi)
	movl	36(%esp), %eax
	movl	%eax, 112(%edi)
	jmp	.L439
.L258:
	movzbl	128(%edi), %eax
	andl	$3, %eax
	cmpl	$1, %eax
	jne	.L259
	movl	$1, (%esp)
.L259:
	cmpl	$3, %eax
	jne	.L260
	pushl	112(%edi)
	movl	20(%esp), %edx
	call	*196(%edx)
	popl	%eax
.L260:
	movb	128(%edi), %al
	andl	$-4, %eax
	orl	$2, %eax
	movb	%al, 128(%edi)
	movl	(%ebp), %eax
	movl	%eax, 112(%edi)
	andl	$-2, 4(%esp)
	jmp	.L436
.L261:
	movl	(%ebp), %ebx
	addl	$4, %ebp
	testl	%ebx, %ebx
	jne	.L262
	movl	28(%edi), %edx
	testl	%edx, %edx
	je	.L327
	movb	2(%edx), %al
	cmpb	%al, 2(%edi)
	jne	.L327
	testb	$4, 128(%edx)
	je	.L265
	testb	$4, 128(%edi)
	jne	.L266
	pushl	116(%edi)
	movl	20(%esp), %edx
	call	*196(%edx)
	popl	%eax
.L266:
	movl	28(%edi), %eax
	movl	116(%eax), %eax
	orb	$4, 128(%edi)
	movl	%eax, 116(%edi)
	movl	$8, 12(%esp)
	jmp	.L236
.L265:
	movl	116(%edx), %eax
	movl	4(%eax), %ebx
.L262:
	pushl	$1
	pushl	124(%esp)
	pushl	$1073741826
	pushl	%ebx
	leal	52(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L268
	movl	36(%esp), %edx
	movb	2(%edi), %al
	cmpb	%al, 2(%edx)
	jne	.L327
	movl	16(%esp), %eax
	cmpl	%eax, 16(%edx)
	jne	.L327
	testb	$4, 128(%edi)
	jne	.L271
	pushl	116(%edi)
	movl	20(%esp), %edx
	call	*196(%edx)
	popl	%eax
.L271:
	andb	$-5, 128(%edi)
	movl	36(%esp), %eax
	movl	%eax, 116(%edi)
.L439:
	incl	28(%eax)
	jmp	.L236
.L268:
	cmpl	$2, %eax
	movl	%eax, 20(%esp)
	jne	.L362
	movl	$4, 20(%esp)
	jmp	.L362
.L275:
	testb	$4, 128(%edi)
	jne	.L276
	pushl	116(%edi)
	movl	20(%esp), %edx
	call	*196(%edx)
	popl	%eax
.L276:
	orb	$4, 128(%edi)
	movl	(%ebp), %eax
	movl	%eax, 116(%edi)
	andl	$-5, 4(%esp)
	jmp	.L436
.L277:
	movzbl	(%ebp), %edx
	addl	$4, %ebp
	cmpl	$10, %edx
	ja	.L426
	movb	129(%edi), %al
	andl	$15, %edx
	andl	$-16, %eax
	jmp	.L438
.L279:
	movzbl	(%ebp), %edx
	addl	$4, %ebp
	cmpl	$10, %edx
	ja	.L426
	movb	129(%edi), %al
	sall	$4, %edx
	andl	$15, %eax
.L438:
	orl	%edx, %eax
	movb	%al, 129(%edi)
	jmp	.L236
.L281:
	movzbl	(%ebp), %edx
	addl	$4, %ebp
	cmpl	$2, %edx
	ja	.L426
	movb	128(%edi), %al
	andl	$3, %edx
	sall	$4, %edx
	andl	$-49, %eax
	orl	%edx, %eax
	andb	$-3, 131(%edi)
	jmp	.L448
.L283:
	cmpl	$0, 124(%edi)
	jne	.L286
	cmpl	$-1, (%ebp)
	je	.L436
	pushl	%edi
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%esi
	je	.L440
.L286:
	movl	124(%edi), %edx
	movl	(%ebp), %eax
	movl	%eax, 32(%edx)
	cmpl	$-1, (%ebp)
	jmp	.L447
.L288:
	cmpl	$0, 124(%edi)
	jne	.L291
	cmpl	$0, (%ebp)
	je	.L436
	pushl	%edi
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%ebx
	je	.L440
.L291:
	movl	124(%edi), %edx
	movl	(%ebp), %eax
	movl	%eax, 36(%edx)
	cmpl	$0, (%ebp)
.L447:
	jne	.L436
	movl	$1, 32(%esp)
	jmp	.L436
.L293:
	movzbl	(%ebp), %edx
	addl	$4, %ebp
	cmpl	$1, %edx
	ja	.L426
	cmpl	$0, 28(%edi)
	je	.L295
	movb	128(%edi), %al
	shrb	$6, %al
	movl	%eax, %ecx
	andl	$1, %ecx
	cmpl	%edx, %ecx
	je	.L295
	testb	$32, 130(%edi)
	je	.L295
	movl	16(%edi), %eax
	cmpb	$64, 37(%eax)
	jne	.L295
	testl	%ecx, %ecx
	movl	deltaSaveUndersViewable, %eax
	movl	40(%edi), %ecx
	je	.L296
	decl	%eax
	jmp	.L429
.L296:
	incl	%eax
.L429:
	movl	%eax, deltaSaveUndersViewable
	andl	$1, %edx
	movb	128(%edi), %al
	sall	$6, %edx
	andl	$-65, %eax
	orl	%edx, %eax
	testl	%ecx, %ecx
	movb	%al, 128(%edi)
	je	.L298
	pushl	%edi
	movl	20(%esp), %edx
	call	*396(%edx)
	pushl	32(%edi)
	pushl	28(%eax)
	movl	28(%esp), %edx
	movl	%eax, %ebx
	call	*380(%edx)
	addl	$12, %esp
	testl	%eax, %eax
	je	.L236
	pushl	32(%edi)
	pushl	28(%ebx)
	jmp	.L446
.L298:
	pushl	32(%edi)
	pushl	%edi
	movl	24(%esp), %edx
	call	*380(%edx)
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	je	.L236
	pushl	32(%edi)
	pushl	%edi
.L446:
	movl	24(%esp), %eax
	call	*384(%eax)
	jmp	.L437
.L295:
	movb	128(%edi), %al
	andl	$1, %edx
	sall	$6, %edx
	andl	$-65, %eax
	orl	%edx, %eax
.L448:
	movb	%al, 128(%edi)
	jmp	.L236
.L303:
	pushl	(%ebp)
	pushl	124(%esp)
	pushl	%edi
	call	EventSelectForWindow
	addl	$12, %esp
	jmp	.L442
.L305:
	leal	32(%esp), %eax
	pushl	%eax
	pushl	(%ebp)
	pushl	128(%esp)
	pushl	%edi
	call	EventSuppressForWindow
	addl	$16, %esp
.L442:
	testl	%eax, %eax
	jne	.L425
.L436:
	addl	$4, %ebp
	jmp	.L236
.L307:
	movzbl	(%ebp), %edx
	addl	$4, %ebp
	cmpl	$1, %edx
	ja	.L426
	movb	130(%edi), %al
	andl	$1, %edx
	andl	$-2, %eax
	orl	%edx, %eax
	movb	%al, 130(%edi)
	jmp	.L236
.L311:
	movl	(%ebp), %esi
	addl	$4, %ebp
	testl	%esi, %esi
	jne	.L322
	movl	28(%edi), %edx
	testl	%edx, %edx
	je	.L313
	movl	124(%edi), %eax
	testl	%eax, %eax
	je	.L314
	movl	(%eax), %ebx
	movl	124(%edx), %eax
	testl	%eax, %eax
	jne	.L430
	pushl	%edx
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%esi
.L430:
	cmpl	(%eax), %ebx
	jne	.L313
.L314:
	movl	28(%edi), %eax
	cmpb	$2, 1(%eax)
	je	.L327
	movl	124(%eax), %edx
	testl	%edx, %edx
	je	.L319
	movl	8(%edx), %esi
	jmp	.L312
.L319:
	pushl	%eax
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%ebx
	movl	8(%eax), %esi
	jmp	.L312
.L313:
	xorl	%esi, %esi
.L312:
	testl	%esi, %esi
	je	.L327
.L322:
	pushl	$16777216
	pushl	124(%esp)
	pushl	$6
	pushl	%esi
	leal	44(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	je	.L323
	cmpl	$2, %eax
	movl	%eax, 20(%esp)
	jne	.L325
	movl	$12, 20(%esp)
.L325:
	movl	120(%esp), %edx
	movl	%esi, 24(%edx)
	jmp	.L246
.L323:
	movl	28(%esp), %eax
	movl	(%eax), %eax
	movl	(%eax), %ebx
	movl	124(%edi), %eax
	testl	%eax, %eax
	jne	.L431
	pushl	%edi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%ecx
.L431:
	cmpl	(%eax), %ebx
	jne	.L327
	movl	28(%esp), %eax
	movl	16(%esp), %edx
	cmpl	%edx, 12(%eax)
	je	.L326
.L327:
	movl	$8, 20(%esp)
	jmp	.L246
.L326:
	cmpb	$2, 1(%edi)
	je	.L331
	movl	124(%edi), %eax
	testl	%eax, %eax
	jne	.L443
	pushl	%edi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%edx
.L443:
	cmpl	8(%eax), %esi
	jmp	.L432
.L331:
	testl	%esi, %esi
.L432:
	je	.L236
	cmpl	$0, 124(%edi)
	jne	.L335
	pushl	%edi
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%ebx
	jne	.L337
	jmp	.L440
.L335:
	movl	28(%edi), %eax
	testl	%eax, %eax
	je	.L337
	cmpb	$2, 1(%eax)
	je	.L339
	movl	124(%eax), %edx
	testl	%edx, %edx
	je	.L341
	cmpl	8(%edx), %esi
	jmp	.L433
.L341:
	pushl	%eax
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%ecx
	cmpl	8(%eax), %esi
	jmp	.L433
.L339:
	testl	%esi, %esi
.L433:
	jne	.L337
	movl	$1, 32(%esp)
.L337:
	movl	40(%edi), %ebx
	testl	%ebx, %ebx
	je	.L410
.L348:
	cmpl	$0, 124(%ebx)
	jne	.L345
	pushl	%ebx
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%edx
	je	.L440
.L345:
	movl	32(%ebx), %ebx
	testl	%ebx, %ebx
	jne	.L348
.L410:
	movl	40(%edi), %ebx
	movl	124(%edi), %eax
	testl	%ebx, %ebx
	movl	%esi, 8(%eax)
	je	.L412
.L354:
	movl	124(%ebx), %eax
	cmpl	%esi, 8(%eax)
	jne	.L351
	pushl	%ebx
	call	CheckWindowOptionalNeed
	popl	%ecx
.L351:
	movl	32(%ebx), %ebx
	testl	%ebx, %ebx
	jne	.L354
.L412:
	movb	$32, 56(%esp)
	movl	4(%edi), %eax
	movl	%eax, 60(%esp)
	movl	%esi, 64(%esp)
	movb	$1, 68(%esp)
	pushl	%edi
	pushl	%esi
	call	IsMapInstalled
	movb	%al, 77(%esp)
	pushl	$0
	pushl	$1
	leal	72(%esp), %eax
	pushl	%eax
	pushl	%edi
	call	DeliverEvents
	addl	$24, %esp
	jmp	.L236
.L355:
	movl	(%ebp), %ebx
	addl	$4, %ebp
	testl	%ebx, %ebx
	jne	.L356
	movl	16(%edi), %eax
	movl	(%eax), %edx
	movl	WindowTable, %eax
	cmpl	(%eax,%edx,4), %edi
	jne	.L357
	movl	rootCursor, %eax
	movl	%eax, 24(%esp)
	jmp	.L359
.L357:
	movl	$0, 24(%esp)
	jmp	.L359
.L356:
	pushl	$16777216
	pushl	124(%esp)
	pushl	$5
	pushl	%ebx
	leal	40(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	je	.L359
	cmpl	$2, %eax
	movl	%eax, 20(%esp)
	jne	.L362
	movl	$6, 20(%esp)
.L362:
	movl	120(%esp), %eax
	movl	%ebx, 24(%eax)
	jmp	.L246
.L359:
	testb	$8, 128(%edi)
	jne	.L364
	movl	124(%edi), %eax
	testl	%eax, %eax
	je	.L366
	movl	4(%eax), %eax
	jmp	.L445
.L366:
	pushl	%edi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	movl	4(%eax), %eax
	popl	%edx
.L445:
	cmpl	%eax, 24(%esp)
	jmp	.L434
.L364:
	cmpl	$0, 24(%esp)
.L434:
	je	.L236
	movl	40(%edi), %ebx
	testl	%ebx, %ebx
	je	.L414
.L373:
	cmpl	$0, 124(%ebx)
	jne	.L370
	testb	$8, 128(%ebx)
	jne	.L370
	pushl	%ebx
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%esi
	je	.L440
.L370:
	movl	32(%ebx), %ebx
	testl	%ebx, %ebx
	jne	.L373
.L414:
	movl	24(%esp), %ecx
	xorl	%esi, %esi
	testl	%ecx, %ecx
	movl	124(%edi), %eax
	jne	.L374
	orb	$8, 128(%edi)
	testl	%eax, %eax
	je	.L376
	movl	4(%eax), %esi
	movl	$1, 32(%esp)
	movl	$0, 4(%eax)
	jmp	.L376
.L374:
	testl	%eax, %eax
	jne	.L377
	pushl	%edi
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%ecx
	jne	.L379
.L440:
	movl	$11, 20(%esp)
	jmp	.L246
.L377:
	movl	28(%edi), %eax
	testl	%eax, %eax
	je	.L379
	testb	$8, 128(%eax)
	jne	.L379
	movl	124(%eax), %edx
	testl	%edx, %edx
	je	.L383
	cmpl	4(%edx), %ecx
	jmp	.L435
.L383:
	pushl	%eax
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	movl	4(%eax), %eax
	popl	%edx
	cmpl	%eax, 24(%esp)
.L435:
	jne	.L379
	movl	$1, 32(%esp)
.L379:
	movl	24(%esp), %eax
	movl	124(%edi), %edx
	movl	4(%edx), %esi
	incl	16(%eax)
	movl	%eax, 4(%edx)
	movl	40(%edi), %ebx
	andb	$-9, 128(%edi)
	testl	%ebx, %ebx
	je	.L376
.L390:
	movl	124(%ebx), %edx
	testl	%edx, %edx
	je	.L387
	movl	24(%esp), %eax
	cmpl	%eax, 4(%edx)
	jne	.L387
	pushl	%ebx
	call	CheckWindowOptionalNeed
	popl	%eax
.L387:
	movl	32(%ebx), %ebx
	testl	%ebx, %ebx
	jne	.L390
.L376:
	testb	$16, 130(%edi)
	je	.L391
	pushl	%edi
	call	WindowHasNewCursor
	popl	%ecx
.L391:
	testl	%esi, %esi
	je	.L236
	pushl	$0
	pushl	%esi
	call	FreeCursor
.L437:
	popl	%eax
	popl	%edx
	jmp	.L236
.L393:
	movl	112(%esp), %eax
	movl	120(%esp), %edx
	movl	$2, 20(%esp)
	movl	%eax, 24(%edx)
	jmp	.L246
.L236:
	movl	12(%esp), %edx
	orl	%edx, 4(%esp)
	cmpl	$0, 8(%esp)
	jne	.L402
.L246:
	cmpl	$0, 32(%esp)
	je	.L403
	pushl	%edi
	call	CheckWindowOptionalNeed
	popl	%eax
.L403:
	pushl	4(%esp)
	pushl	%edi
	movl	24(%esp), %edx
	call	*144(%edx)
	popl	%esi
	popl	%ebp
	testb	$12, 4(%esp)
	jne	.L405
	cmpl	$0, (%esp)
	je	.L404
.L405:
	testb	$32, 130(%edi)
	je	.L404
	cmpw	$0, 104(%edi)
	jne	.L406
	movl	124(%edi), %eax
	testl	%eax, %eax
	je	.L404
	cmpl	$0, 44(%eax)
	je	.L404
.L406:
	movl	miEmptyBox, %eax
	movl	%eax, 40(%esp)
	movl	miEmptyBox+4, %edx
	leal	76(%edi), %eax
	movl	%edx, 44(%esp)
	movl	$miEmptyData, 48(%esp)
	pushl	%eax
	leal	60(%edi), %eax
	pushl	%eax
	leal	48(%esp), %ebx
	pushl	%ebx
	call	miSubtract
	pushl	$1
	pushl	%ebx
	pushl	%edi
	call	miPaintWindow
	addl	$24, %esp
	movl	48(%esp), %eax
	testl	%eax, %eax
	je	.L404
	cmpl	$0, (%eax)
	je	.L404
	pushl	%eax
	call	Xfree
	movl	$0, 52(%esp)
	popl	%ebx
.L404:
	movl	20(%esp), %eax
.L231:
	addl	$88, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ChangeWindowAttributes, .-ChangeWindowAttributes
	.align 4
.globl GetWindowAttributes
	.type	GetWindowAttributes, @function
GetWindowAttributes:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	24(%esp), %ebx
	movl	16(%esp), %esi
	movl	20(%esp), %edi
	movb	$1, (%ebx)
	movzbl	129(%esi), %eax
	andl	$15, %eax
	movb	%al, 14(%ebx)
	movb	129(%esi), %al
	shrb	$4, %al
	movb	%al, 15(%ebx)
	testb	$2, 131(%esi)
	je	.L450
	movb	128(%esi), %al
	shrb	$4, %al
	andl	$3, %eax
	cmpl	$2, %eax
	je	.L450
	movb	$0, 1(%ebx)
	jmp	.L451
.L450:
	movb	128(%esi), %al
	shrb	$4, %al
	andl	$3, %eax
	movb	%al, 1(%ebx)
.L451:
	movw	28(%edi), %ax
	movw	%ax, 2(%ebx)
	movl	124(%esi), %eax
	orl	$-1, %edx
	testl	%eax, %eax
	movl	$3, 4(%ebx)
	je	.L453
	movl	32(%eax), %edx
.L453:
	movl	%edx, 16(%ebx)
	xorl	%edx, %edx
	testl	%eax, %eax
	je	.L455
	movl	36(%eax), %edx
.L455:
	movl	%edx, 20(%ebx)
	movb	128(%esi), %al
	shrb	$6, %al
	andl	$1, %eax
	movb	%al, 24(%ebx)
	movzbl	130(%esi), %eax
	andl	$1, %eax
	movb	%al, 27(%ebx)
	movb	130(%esi), %al
	testb	$8, %al
	jne	.L456
	movb	$0, 26(%ebx)
	jmp	.L457
.L456:
	testb	$16, %al
	sete	%dl
	movb	$2, %al
	subb	%dl, %al
	movb	%al, 26(%ebx)
.L457:
	cmpb	$2, 1(%esi)
	je	.L460
	movl	124(%esi), %eax
	testl	%eax, %eax
	jne	.L471
	pushl	%esi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%edx
.L471:
	movl	8(%eax), %edx
	jmp	.L461
.L460:
	xorl	%edx, %edx
.L461:
	xorl	%eax, %eax
	testl	%edx, %edx
	movl	%edx, 28(%ebx)
	je	.L465
	pushl	%esi
	pushl	%edx
	call	IsMapInstalled
	popl	%edx
	popl	%ecx
.L465:
	movb	%al, 25(%ebx)
	pushl	%edi
	pushl	%esi
	call	EventMaskForClient
	movl	%eax, 36(%ebx)
	movl	124(%esi), %edx
	popl	%edi
	testl	%edx, %edx
	popl	%eax
	movl	108(%esi), %eax
	je	.L466
	orl	16(%edx), %eax
.L466:
	testl	%edx, %edx
	movl	%eax, 32(%ebx)
	je	.L467
	movw	12(%edx), %ax
	jmp	.L468
.L467:
	movw	130(%esi), %ax
	shrw	$6, %ax
	andl	$7, %eax
	movw	DontPropagateMasks(,%eax,4), %ax
.L468:
	movw	%ax, 40(%ebx)
	movzbw	1(%esi), %ax
	testl	%edx, %edx
	movw	%ax, 12(%ebx)
	je	.L469
	movl	(%edx), %eax
	jmp	.L470
.L469:
	pushl	%esi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%esi
	movl	(%eax), %eax
.L470:
	movl	%eax, 8(%ebx)
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	GetWindowAttributes, .-GetWindowAttributes
	.align 4
.globl MoveWindowInStack
	.type	MoveWindowInStack, @function
MoveWindowInStack:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %ecx
	movl	24(%esp), %edi
	movl	32(%ecx), %ebp
	cmpl	%edi, %ebp
	movl	28(%ecx), %esi
	movl	%ecx, %ebx
	je	.L473
	testl	%edi, %edi
	movl	40(%esi), %eax
	jne	.L474
	cmpl	%ecx, %eax
	jne	.L475
	movl	%ebp, 40(%esi)
.L475:
	movl	36(%ecx), %eax
	movl	32(%ebx), %ebx
	movl	%eax, 36(%ebx)
	movl	36(%ecx), %eax
	testl	%eax, %eax
	je	.L476
	movl	%ebx, 32(%eax)
.L476:
	movl	44(%esi), %eax
	movl	%ecx, 32(%eax)
	movl	%eax, 36(%ecx)
	movl	$0, 32(%ecx)
	movl	%ecx, 44(%esi)
	jmp	.L477
.L474:
	cmpl	%edi, %eax
	jne	.L478
	cmpl	%ecx, 44(%esi)
	jne	.L479
	movl	36(%ecx), %eax
	movl	%eax, 44(%esi)
.L479:
	movl	32(%ebx), %edx
	testl	%edx, %edx
	je	.L480
	movl	36(%ebx), %eax
	movl	%eax, 36(%edx)
.L480:
	movl	36(%ebx), %eax
	testl	%eax, %eax
	je	.L481
	movl	%edx, 32(%eax)
.L481:
	movl	$0, 36(%ebx)
	movl	%edi, 32(%ebx)
	movl	%ebx, 36(%edi)
	movl	%ebx, 40(%esi)
	jmp	.L477
.L478:
	xorl	%ebx, %ebx
	cmpl	%ecx, %eax
	jne	.L483
	movl	32(%ecx), %eax
	movl	%eax, 40(%esi)
	movl	%eax, %ebx
.L483:
	cmpl	%ecx, 44(%esi)
	jne	.L484
	movl	36(%ecx), %eax
	movl	%ecx, %ebx
	movl	%eax, 44(%esi)
.L484:
	movl	32(%ecx), %edx
	testl	%edx, %edx
	je	.L485
	movl	36(%ecx), %eax
	movl	%eax, 36(%edx)
.L485:
	movl	36(%ecx), %eax
	testl	%eax, %eax
	je	.L486
	movl	%edx, 32(%eax)
.L486:
	movl	36(%edi), %eax
	movl	%eax, 36(%ecx)
	movl	36(%edi), %eax
	testl	%eax, %eax
	movl	%edi, 32(%ecx)
	je	.L487
	movl	%ecx, 32(%eax)
.L487:
	testl	%ebx, %ebx
	movl	%ecx, 36(%edi)
	jne	.L477
	movl	40(%esi), %ebx
	cmpl	%ecx, %ebx
	je	.L477
	cmpl	%ebp, %ebx
	je	.L477
.L493:
	movl	32(%ebx), %ebx
	cmpl	%ecx, %ebx
	je	.L477
	cmpl	%ebp, %ebx
	jne	.L493
.L477:
	movl	16(%ecx), %eax
	cmpl	$0, 188(%eax)
	je	.L473
	pushl	%ebp
	pushl	%ecx
	call	*188(%eax)
	popl	%ecx
	popl	%esi
.L473:
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	MoveWindowInStack, .-MoveWindowInStack
	.align 4
.globl CreateUnclippedWinSize
	.type	CreateUnclippedWinSize, @function
CreateUnclippedWinSize:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	20(%esp), %esi
	movw	8(%esi), %ax
	movw	%ax, (%esp)
	movw	10(%esi), %dx
	movw	%dx, 2(%esp)
	addw	12(%esi), %ax
	movw	%ax, 4(%esp)
	addw	14(%esi), %dx
	movw	%dx, 6(%esp)
	pushl	$1
	leal	4(%esp), %eax
	pushl	%eax
	call	miRegionCreate
	movl	%eax, %ebx
	popl	%eax
	movl	124(%esi), %eax
	testl	%eax, %eax
	popl	%edx
	je	.L497
	cmpl	$0, 40(%eax)
	jne	.L498
	cmpl	$0, 44(%eax)
	je	.L497
.L498:
	movswl	10(%esi),%eax
	negl	%eax
	pushl	%eax
	movswl	8(%esi),%eax
	negl	%eax
	pushl	%eax
	pushl	%ebx
	call	miTranslateRegion
	movl	124(%esi), %eax
	addl	$12, %esp
	testl	%eax, %eax
	je	.L499
	movl	40(%eax), %eax
	testl	%eax, %eax
	je	.L499
	pushl	%eax
	pushl	%ebx
	pushl	%ebx
	call	miIntersect
	addl	$12, %esp
.L499:
	movl	124(%esi), %eax
	testl	%eax, %eax
	je	.L502
	movl	44(%eax), %eax
	testl	%eax, %eax
	je	.L502
	pushl	%eax
	pushl	%ebx
	pushl	%ebx
	call	miIntersect
	addl	$12, %esp
.L502:
	movswl	10(%esi),%eax
	pushl	%eax
	movswl	8(%esi),%eax
	pushl	%eax
	pushl	%ebx
	call	miTranslateRegion
	addl	$12, %esp
.L497:
	popl	%edx
	popl	%ecx
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	ret
	.size	CreateUnclippedWinSize, .-CreateUnclippedWinSize
	.align 4
.globl SetWinSize
	.type	SetWinSize, @function
SetWinSize:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	pushl	%eax
	movl	24(%esp), %esi
	testb	$12, 131(%esi)
	movw	8(%esi), %cx
	movw	10(%esi), %dx
	movw	12(%esi), %di
	movw	14(%esi), %bx
	je	.L506
	leal	(%edi,%ecx), %eax
	movw	%dx, 2(%esp)
	movw	%ax, 4(%esp)
	movw	%cx, (%esp)
	leal	(%ebx,%edx), %eax
	movw	%ax, 6(%esp)
	movl	(%esp), %eax
	movl	4(%esp), %edx
	movl	%eax, 76(%esi)
	movl	84(%esi), %eax
	testl	%eax, %eax
	movl	%edx, 80(%esi)
	je	.L507
	cmpl	$0, (%eax)
	je	.L507
	pushl	%eax
	call	Xfree
	movl	$0, 84(%esi)
	popl	%edi
.L507:
	movl	$0, 84(%esi)
	jmp	.L508
.L506:
	movzwl	%bx, %eax
	pushl	%eax
	movzwl	%di, %eax
	pushl	%eax
	movswl	%dx,%eax
	pushl	%eax
	movswl	%cx,%eax
	pushl	%eax
	leal	76(%esi), %eax
	pushl	%eax
	pushl	28(%esi)
	call	ClippedRegionFromBox
	addl	$24, %esp
.L508:
	movl	124(%esi), %eax
	testl	%eax, %eax
	je	.L505
	cmpl	$0, 40(%eax)
	jne	.L510
	cmpl	$0, 44(%eax)
	je	.L505
.L510:
	movswl	10(%esi),%eax
	negl	%eax
	pushl	%eax
	movswl	8(%esi),%eax
	negl	%eax
	pushl	%eax
	leal	76(%esi), %ebx
	pushl	%ebx
	call	miTranslateRegion
	movl	124(%esi), %eax
	addl	$12, %esp
	testl	%eax, %eax
	je	.L511
	movl	40(%eax), %eax
	testl	%eax, %eax
	je	.L511
	pushl	%eax
	pushl	%ebx
	pushl	%ebx
	call	miIntersect
	addl	$12, %esp
.L511:
	movl	124(%esi), %eax
	testl	%eax, %eax
	je	.L514
	movl	44(%eax), %eax
	testl	%eax, %eax
	je	.L514
	pushl	%eax
	leal	76(%esi), %eax
	pushl	%eax
	pushl	%eax
	call	miIntersect
	addl	$12, %esp
.L514:
	movswl	10(%esi),%eax
	pushl	%eax
	movswl	8(%esi),%eax
	pushl	%eax
	leal	76(%esi), %eax
	pushl	%eax
	call	miTranslateRegion
	addl	$12, %esp
.L505:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	SetWinSize, .-SetWinSize
	.align 4
.globl SetBorderSize
	.type	SetBorderSize, @function
SetBorderSize:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebp
	pushl	%ebp
	movl	28(%esp), %esi
	movw	104(%esi), %dx
	testw	%dx, %dx
	jne	.L519
	movl	124(%esi), %eax
	testl	%eax, %eax
	je	.L518
	cmpl	$0, 44(%eax)
	je	.L518
.L519:
	testb	$12, 131(%esi)
	movzwl	%dx, %ecx
	movw	8(%esi), %di
	movw	10(%esi), %bx
	movw	12(%esi), %bp
	movw	14(%esi), %dx
	je	.L520
	movl	%edi, %eax
	subw	%cx, %ax
	movw	%ax, (%esp)
	movl	%ebx, %eax
	subw	%cx, %ax
	movw	%ax, 2(%esp)
	leal	(%ebp,%edi), %eax
	addl	%ecx, %eax
	movw	%ax, 4(%esp)
	leal	(%edx,%ebx), %eax
	addl	%ecx, %eax
	movw	%ax, 6(%esp)
	movl	(%esp), %eax
	movl	4(%esp), %edx
	movl	%eax, 88(%esi)
	movl	96(%esi), %eax
	testl	%eax, %eax
	movl	%edx, 92(%esi)
	je	.L521
	cmpl	$0, (%eax)
	je	.L521
	pushl	%eax
	call	Xfree
	movl	$0, 96(%esi)
	popl	%edi
.L521:
	movl	$0, 96(%esi)
	jmp	.L522
.L520:
	movzwl	%dx, %eax
	leal	(%ecx,%ecx), %edx
	addl	%edx, %eax
	pushl	%eax
	movzwl	%bp, %eax
	addl	%edx, %eax
	pushl	%eax
	movswl	%bx,%eax
	subl	%ecx, %eax
	pushl	%eax
	movswl	%di,%eax
	subl	%ecx, %eax
	pushl	%eax
	leal	88(%esi), %eax
	pushl	%eax
	pushl	28(%esi)
	call	ClippedRegionFromBox
	addl	$24, %esp
.L522:
	movl	124(%esi), %eax
	testl	%eax, %eax
	je	.L517
	cmpl	$0, 40(%eax)
	je	.L517
	movswl	10(%esi),%eax
	negl	%eax
	pushl	%eax
	movswl	8(%esi),%eax
	negl	%eax
	pushl	%eax
	leal	88(%esi), %eax
	pushl	%eax
	call	miTranslateRegion
	movl	124(%esi), %eax
	xorl	%edx, %edx
	testl	%eax, %eax
	je	.L525
	movl	40(%eax), %edx
.L525:
	pushl	%edx
	leal	88(%esi), %ebx
	pushl	%ebx
	pushl	%ebx
	call	miIntersect
	movswl	10(%esi),%eax
	pushl	%eax
	movswl	8(%esi),%eax
	pushl	%eax
	pushl	%ebx
	call	miTranslateRegion
	addl	$36, %esp
	leal	76(%esi), %eax
	pushl	%eax
	pushl	%ebx
	pushl	%ebx
	call	miUnion
	addl	$12, %esp
	jmp	.L517
.L518:
	leal	76(%esi), %eax
	pushl	%eax
	leal	88(%esi), %eax
	pushl	%eax
	call	miRegionCopy
	popl	%ecx
	popl	%ebx
.L517:
	popl	%eax
	popl	%edx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	SetBorderSize, .-SetBorderSize
	.align 4
.globl GravityTranslate
	.type	GravityTranslate, @function
GravityTranslate:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	56(%esp), %eax
	subl	$2, %eax
	cmpl	$8, %eax
	movl	32(%esp), %ebp
	movl	48(%esp), %ecx
	movl	52(%esp), %ebx
	movl	60(%esp), %edi
	ja	.L538
	jmp	*.L539(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L539:
	.long	.L529
	.long	.L530
	.long	.L531
	.long	.L532
	.long	.L533
	.long	.L534
	.long	.L535
	.long	.L536
	.long	.L537
	.text
.L529:
	movl	$2, %edx
	movl	%ecx, %eax
	movl	%edx, %ebx
	cltd
	idivl	%ebx
	addl	%eax, %ebp
	movl	%ebp, (%edi)
	movl	%eax, 8(%esp)
	movl	36(%esp), %eax
	jmp	.L543
.L530:
	addl	%ecx, %ebp
	jmp	.L538
.L531:
	movl	%ebx, %eax
	movl	$2, %edx
	movl	%ebp, (%edi)
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	movl	36(%esp), %ebx
	addl	%eax, %ebx
	movl	64(%esp), %esi
	movl	%eax, 4(%esp)
	movl	%ebx, (%esi)
	jmp	.L527
.L532:
	movl	%ecx, %eax
	movl	$2, %esi
	cltd
	idivl	%esi
	leal	(%eax,%ebp), %edx
	movl	%ebx, %eax
	movl	%edx, (%edi)
	cltd
	idivl	%esi
	movl	36(%esp), %edx
	addl	%eax, %edx
	jmp	.L542
.L533:
	leal	(%ecx,%ebp), %edx
	movl	%edx, (%edi)
	movl	%ebx, %eax
	movl	$2, %edx
	movl	%edx, %esi
	cltd
	idivl	%esi
	movl	36(%esp), %edx
	addl	%eax, %edx
	jmp	.L541
.L534:
	movl	%ebp, (%edi)
	jmp	.L540
.L535:
	movl	$2, %edx
	movl	%ecx, %eax
	movl	%edx, %esi
	cltd
	idivl	%esi
	leal	(%eax,%ebp), %edx
	movl	%edx, (%edi)
	movl	36(%esp), %edx
	addl	%ebx, %edx
.L541:
	movl	64(%esp), %eax
	movl	%edx, (%eax)
	jmp	.L527
.L536:
	leal	(%ecx,%ebp), %edx
	movl	%edx, (%edi)
.L540:
	movl	36(%esp), %edx
	addl	%ebx, %edx
.L542:
	movl	64(%esp), %ecx
	movl	%edx, (%ecx)
	jmp	.L527
.L537:
	movl	40(%esp), %ebx
	movl	%ebx, (%edi)
	movl	44(%esp), %eax
.L543:
	movl	64(%esp), %esi
	movl	%eax, (%esi)
	jmp	.L527
.L538:
	movl	%ebp, (%edi)
	movl	36(%esp), %ecx
	movl	64(%esp), %edx
	movl	%ecx, (%edx)
.L527:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	GravityTranslate, .-GravityTranslate
	.align 4
.globl ResizeChildrenWinSize
	.type	ResizeChildrenWinSize, @function
ResizeChildrenWinSize:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	cmpl	$0, 76(%esp)
	movl	64(%esp), %edi
	movl	$0, (%esp)
	jne	.L546
	cmpl	$0, 80(%esp)
	je	.L545
.L546:
	movl	$1, (%esp)
.L545:
	movl	40(%edi), %esi
	testl	%esi, %esi
	movl	16(%edi), %ebp
	je	.L568
.L566:
	cmpl	$0, (%esp)
	je	.L551
	movb	129(%esi), %al
	shrb	$4, %al
	movzbl	%al, %eax
	decl	%eax
	jle	.L551
	movswl	100(%esi),%ecx
	movswl	102(%esi),%edx
	leal	8(%esp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, 8(%esp)
	pushl	%eax
	leal	8(%esp), %eax
	pushl	%eax
	movb	129(%esi), %al
	shrb	$4, %al
	movzbl	%al, %eax
	pushl	%eax
	pushl	92(%esp)
	pushl	92(%esp)
	movl	%edx, %eax
	subl	92(%esp), %eax
	pushl	%eax
	movl	%ecx, %eax
	subl	92(%esp), %eax
	pushl	%eax
	pushl	%edx
	pushl	%ecx
	call	GravityTranslate
	movswl	100(%esi),%eax
	addl	$36, %esp
	cmpl	%eax, 4(%esp)
	jne	.L553
	movswl	102(%esi),%eax
	cmpl	%eax, 8(%esp)
	je	.L551
.L553:
	movb	$24, 12(%esp)
	movl	4(%esi), %eax
	movl	%eax, 20(%esp)
	movl	4(%esp), %eax
	subw	104(%esi), %ax
	movw	%ax, 24(%esp)
	movl	8(%esp), %eax
	subw	104(%esi), %ax
	movw	%ax, 26(%esp)
	pushl	$0
	pushl	$1
	leal	20(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	DeliverEvents
	movl	20(%esp), %eax
	movw	%ax, 100(%esi)
	movl	24(%esp), %eax
	movw	%ax, 102(%esi)
	addl	$16, %esp
.L551:
	movw	100(%esi), %ax
	addw	8(%edi), %ax
	movw	%ax, 8(%esi)
	movw	102(%esi), %ax
	addw	10(%edi), %ax
	movw	%ax, 10(%esi)
	pushl	%esi
	call	SetWinSize
	pushl	%esi
	call	SetBorderSize
	movswl	10(%esi),%eax
	pushl	%eax
	movswl	8(%esi),%eax
	pushl	%eax
	pushl	%esi
	call	*140(%ebp)
	movl	40(%esi), %ebx
	addl	$20, %esp
	testl	%ebx, %ebx
	je	.L549
.L570:
	movl	28(%ebx), %edx
	movw	100(%ebx), %ax
	addw	8(%edx), %ax
	movw	%ax, 8(%ebx)
	movw	102(%ebx), %ax
	addw	10(%edx), %ax
	movw	%ax, 10(%ebx)
	pushl	%ebx
	call	SetWinSize
	pushl	%ebx
	call	SetBorderSize
	movswl	10(%ebx),%eax
	pushl	%eax
	movswl	8(%ebx),%eax
	pushl	%eax
	pushl	%ebx
	call	*140(%ebp)
	movl	40(%ebx), %eax
	addl	$20, %esp
	testl	%eax, %eax
	je	.L558
	movl	%eax, %ebx
	jmp	.L570
.L558:
	cmpl	$0, 32(%ebx)
	jne	.L560
	cmpl	%esi, %ebx
	je	.L549
.L563:
	movl	28(%ebx), %ebx
	cmpl	$0, 32(%ebx)
	jne	.L560
	cmpl	%esi, %ebx
	jne	.L563
	jmp	.L549
.L560:
	cmpl	%esi, %ebx
	je	.L549
	movl	32(%ebx), %ebx
	jmp	.L570
.L549:
	movl	32(%esi), %esi
	testl	%esi, %esi
	jne	.L566
.L568:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ResizeChildrenWinSize, .-ResizeChildrenWinSize
	.align 4
	.type	IsSiblingAboveMe, @function
IsSiblingAboveMe:
	pushl	%ebx
	movl	8(%esp), %ecx
	movl	28(%ecx), %eax
	movl	40(%eax), %edx
	testl	%edx, %edx
	movl	12(%esp), %ebx
	je	.L580
.L578:
	xorl	%eax, %eax
	cmpl	%ebx, %edx
	je	.L571
	cmpl	%ecx, %edx
	movl	$1, %eax
	je	.L571
	movl	32(%edx), %edx
	testl	%edx, %edx
	jne	.L578
.L580:
	movl	$1, %eax
.L571:
	popl	%ebx
	ret
	.size	IsSiblingAboveMe, .-IsSiblingAboveMe
	.align 4
	.type	WindowExtents, @function
WindowExtents:
	movl	4(%esp), %ecx
	movw	8(%ecx), %dx
	subw	104(%ecx), %dx
	movl	8(%esp), %eax
	movw	%dx, (%eax)
	movw	10(%ecx), %dx
	subw	104(%ecx), %dx
	movw	%dx, 2(%eax)
	movw	12(%ecx), %dx
	addw	8(%ecx), %dx
	addw	104(%ecx), %dx
	movw	%dx, 4(%eax)
	movw	14(%ecx), %dx
	addw	10(%ecx), %dx
	addw	104(%ecx), %dx
	movw	%dx, 6(%eax)
	ret
	.size	WindowExtents, .-WindowExtents
	.align 4
	.type	MakeBoundingRegion, @function
MakeBoundingRegion:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %esi
	pushl	$1
	pushl	20(%esp)
	call	miRegionCreate
	movl	%eax, %ebx
	popl	%eax
	movl	124(%esi), %eax
	testl	%eax, %eax
	popl	%edx
	je	.L583
	cmpl	$0, 40(%eax)
	je	.L583
	movswl	102(%esi),%eax
	negl	%eax
	pushl	%eax
	movswl	100(%esi),%eax
	negl	%eax
	pushl	%eax
	pushl	%ebx
	call	miTranslateRegion
	movl	124(%esi), %eax
	xorl	%edx, %edx
	testl	%eax, %eax
	je	.L585
	movl	40(%eax), %edx
.L585:
	pushl	%edx
	pushl	%ebx
	pushl	%ebx
	call	miIntersect
	movswl	102(%esi),%eax
	pushl	%eax
	movswl	100(%esi),%eax
	pushl	%eax
	pushl	%ebx
	call	miTranslateRegion
	addl	$36, %esp
.L583:
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	ret
	.size	MakeBoundingRegion, .-MakeBoundingRegion
	.align 4
	.type	ShapeOverlap, @function
ShapeOverlap:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp), %edx
	movl	124(%edx), %eax
	testl	%eax, %eax
	movl	24(%esp), %esi
	je	.L588
	cmpl	$0, 40(%eax)
	jne	.L587
.L588:
	movl	124(%esi), %eax
	testl	%eax, %eax
	je	.L589
	cmpl	$0, 40(%eax)
	jne	.L587
.L589:
	movl	$1, %eax
	jmp	.L586
.L587:
	pushl	20(%esp)
	pushl	%edx
	call	MakeBoundingRegion
	pushl	36(%esp)
	pushl	%esi
	movl	%eax, %ebx
	call	MakeBoundingRegion
	pushl	%eax
	pushl	%ebx
	pushl	%ebx
	movl	%eax, %esi
	call	miIntersect
	movl	8(%ebx), %eax
	xorl	%edi, %edi
	addl	$28, %esp
	testl	%eax, %eax
	je	.L591
	cmpl	$0, 4(%eax)
	je	.L590
.L591:
	movl	$1, %edi
.L590:
	pushl	%ebx
	call	miRegionDestroy
	pushl	%esi
	call	miRegionDestroy
	popl	%ecx
	movl	%edi, %eax
	popl	%ebx
.L586:
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ShapeOverlap, .-ShapeOverlap
	.align 4
	.type	AnyWindowOverlapsMe, @function
AnyWindowOverlapsMe:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	pushl	%ebx
	movl	28(%esp), %ebp
	movl	32(%esp), %edi
	movl	36(%ebp), %ebx
	cmpl	%edi, %ebx
	movl	36(%esp), %esi
	je	.L601
.L599:
	testb	$8, 130(%ebx)
	je	.L595
	movl	%esp, %eax
	pushl	%eax
	pushl	%ebx
	call	WindowExtents
	movl	%eax, %edx
	movw	(%esi), %ax
	popl	%ecx
	cmpw	%ax, 4(%edx)
	popl	%ecx
	jle	.L595
	movw	4(%esi), %ax
	cmpw	%ax, (%edx)
	jge	.L595
	movw	2(%esi), %ax
	cmpw	%ax, 6(%edx)
	jle	.L595
	movw	6(%esi), %ax
	cmpw	%ax, 2(%edx)
	jge	.L595
	pushl	%edx
	pushl	%ebx
	pushl	%esi
	pushl	%ebp
	call	ShapeOverlap
	addl	$16, %esp
	testl	%eax, %eax
	movl	$1, %edx
	jne	.L592
.L595:
	movl	36(%ebx), %ebx
	cmpl	%edi, %ebx
	jne	.L599
.L601:
	xorl	%edx, %edx
.L592:
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	AnyWindowOverlapsMe, .-AnyWindowOverlapsMe
	.align 4
	.type	IOverlapAnyWindow, @function
IOverlapAnyWindow:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	pushl	%ebx
	movl	24(%esp), %edi
	movl	32(%edi), %ebx
	testl	%ebx, %ebx
	movl	28(%esp), %esi
	je	.L611
.L609:
	testb	$8, 130(%ebx)
	je	.L605
	movl	%esp, %eax
	pushl	%eax
	pushl	%ebx
	call	WindowExtents
	movl	%eax, %edx
	movw	(%esi), %ax
	popl	%ecx
	cmpw	%ax, 4(%edx)
	popl	%ecx
	jle	.L605
	movw	4(%esi), %ax
	cmpw	%ax, (%edx)
	jge	.L605
	movw	2(%esi), %ax
	cmpw	%ax, 6(%edx)
	jle	.L605
	movw	6(%esi), %ax
	cmpw	%ax, 2(%edx)
	jge	.L605
	pushl	%edx
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	call	ShapeOverlap
	addl	$16, %esp
	testl	%eax, %eax
	movl	$1, %edx
	jne	.L602
.L605:
	movl	32(%ebx), %ebx
	testl	%ebx, %ebx
	jne	.L609
.L611:
	xorl	%edx, %edx
.L602:
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%esi
	movl	%edx, %eax
	popl	%edi
	ret
	.size	IOverlapAnyWindow, .-IOverlapAnyWindow
	.align 4
	.type	WhereDoIGoInTheStack, @function
WhereDoIGoInTheStack:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	44(%esp), %eax
	movw	%ax, 6(%esp)
	movl	48(%esp), %eax
	movw	%ax, 4(%esp)
	movl	52(%esp), %eax
	movl	36(%esp), %esi
	movw	%ax, 2(%esp)
	movl	56(%esp), %eax
	movw	%ax, (%esp)
	movl	28(%esi), %eax
	cmpl	40(%eax), %esi
	movl	40(%esp), %ebx
	jne	.L613
	cmpl	44(%eax), %esi
	je	.L663
.L613:
	pushl	28(%esi)
	call	RealChildHead
	testl	%eax, %eax
	movl	%eax, %edx
	popl	%edi
	je	.L614
	movl	32(%eax), %ebp
	jmp	.L615
.L614:
	movl	28(%esi), %eax
	movl	40(%eax), %ebp
.L615:
	movw	6(%esp), %ax
	movw	%ax, 8(%esp)
	movl	4(%esp), %eax
	movw	%ax, 10(%esp)
	movw	6(%esp), %ax
	addw	2(%esp), %ax
	movw	%ax, 12(%esp)
	movl	4(%esp), %eax
	addl	(%esp), %eax
	cmpl	$4, 60(%esp)
	leal	8(%esp), %edi
	movw	%ax, 14(%esp)
	ja	.L661
	movl	60(%esp), %eax
	jmp	*.L662(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L662:
	.long	.L617
	.long	.L622
	.long	.L627
	.long	.L637
	.long	.L647
	.text
.L617:
	testl	%ebx, %ebx
	movl	%ebx, %edx
	jne	.L612
	movl	%ebp, %edx
	cmpl	%ebp, %esi
	jmp	.L664
.L622:
	xorl	%edx, %edx
	testl	%ebx, %ebx
	je	.L612
	movl	32(%ebx), %eax
	movl	%eax, %edx
	cmpl	%esi, %eax
	jmp	.L664
.L627:
	testb	$8, 130(%esi)
	je	.L661
	testl	%ebx, %ebx
	je	.L631
	testb	$8, 130(%ebx)
	je	.L661
	pushl	%ebx
	pushl	%esi
	call	IsSiblingAboveMe
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L661
	pushl	%edi
	leal	88(%ebx), %eax
	pushl	%eax
	call	miRectIn
	popl	%edx
	popl	%ecx
	jmp	.L668
.L631:
	pushl	%edi
	pushl	%edx
	pushl	%esi
	call	AnyWindowOverlapsMe
	addl	$12, %esp
.L668:
	movl	%ebp, %edx
	jmp	.L667
.L637:
	testb	$8, 130(%esi)
	je	.L661
	testl	%ebx, %ebx
	je	.L665
	testb	$8, 130(%ebx)
	je	.L661
	pushl	%ebx
	pushl	%esi
	call	IsSiblingAboveMe
	decl	%eax
	popl	%ecx
	popl	%ebp
	jne	.L661
	pushl	%edi
	leal	88(%ebx), %eax
	pushl	%eax
	call	miRectIn
	jmp	.L666
.L647:
	testb	$8, 130(%esi)
	je	.L661
	testl	%ebx, %ebx
	je	.L651
	testb	$8, 130(%ebx)
	je	.L661
	pushl	%edi
	leal	88(%ebx), %eax
	pushl	%eax
	call	miRectIn
	testl	%eax, %eax
	popl	%edi
	popl	%edx
	je	.L661
	pushl	%ebx
	pushl	%esi
	call	IsSiblingAboveMe
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	movl	%ebp, %edx
	je	.L612
.L663:
	xorl	%edx, %edx
	jmp	.L612
.L651:
	pushl	%edi
	pushl	%edx
	pushl	%esi
	call	AnyWindowOverlapsMe
	addl	$12, %esp
	testl	%eax, %eax
	movl	%ebp, %edx
	jne	.L612
.L665:
	pushl	%edi
	pushl	%esi
	call	IOverlapAnyWindow
.L666:
	popl	%edi
	popl	%ebp
	xorl	%edx, %edx
.L667:
	testl	%eax, %eax
.L664:
	jne	.L612
.L661:
	movl	32(%esi), %edx
.L612:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	WhereDoIGoInTheStack, .-WhereDoIGoInTheStack
	.align 4
	.type	ReflectStackChange, @function
ReflectStackChange:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	28(%esp), %edi
	movb	130(%edi), %al
	shrb	$5, %al
	movl	$1, %ebp
	andl	%eax, %ebp
	cmpl	$0, 28(%edi)
	movl	$0, (%esp)
	movl	16(%edi), %esi
	je	.L669
	pushl	32(%esp)
	pushl	%edi
	call	MoveWindowInStack
	movl	%eax, %ebx
	testl	%ebp, %ebp
	popl	%eax
	popl	%edx
	je	.L671
	leal	4(%esp), %eax
	pushl	%eax
	pushl	%ebx
	pushl	%edi
	call	*376(%esi)
	movl	16(%esp), %edx
	addl	$12, %esp
	cmpl	%edi, %edx
	movl	%eax, %ebp
	je	.L672
	movl	%edx, %ebx
.L672:
	movl	16(%edi), %eax
	cmpb	$64, 37(%eax)
	jne	.L673
	pushl	%ebx
	pushl	%edx
	call	*380(%esi)
	movl	%eax, 8(%esp)
	popl	%ecx
	popl	%eax
.L673:
	testl	%ebp, %ebp
	je	.L674
	pushl	36(%esp)
	pushl	%ebx
	movl	12(%esp), %eax
	pushl	28(%eax)
	call	*156(%esi)
	movl	16(%esp), %eax
	pushl	28(%eax)
	call	*400(%esi)
	addl	$16, %esp
.L674:
	cmpl	$0, (%esp)
	je	.L675
	pushl	%ebx
	pushl	8(%esp)
	call	*384(%esi)
	popl	%eax
	popl	%edx
.L675:
	testl	%ebp, %ebp
	je	.L671
	movl	16(%edi), %eax
	cmpl	$0, 160(%eax)
	je	.L671
	pushl	36(%esp)
	pushl	%ebx
	movl	12(%esp), %eax
	pushl	28(%eax)
	call	*160(%esi)
	addl	$12, %esp
.L671:
	testb	$16, 130(%edi)
	je	.L669
	call	WindowsRestructured
.L669:
	popl	%ebp
	popl	%eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ReflectStackChange, .-ReflectStackChange
	.align 4
.globl ConfigureWindow
	.type	ConfigureWindow, @function
ConfigureWindow:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$100, %esp
	movl	120(%esp), %esi
	movl	$0, 32(%esp)
	movl	28(%esi), %eax
	movl	%eax, 28(%esp)
	movw	12(%esi), %dx
	movw	14(%esi), %di
	movw	104(%esi), %ax
	movl	$0, 24(%esp)
	movw	%dx, 14(%esp)
	movw	%di, 12(%esp)
	movw	%ax, 10(%esp)
	movl	$0, (%esp)
	cmpb	$2, 1(%esi)
	movl	124(%esp), %ebp
	movl	128(%esp), %ecx
	jne	.L679
	testl	$16, %ebp
	movl	$8, %edx
	jne	.L678
.L679:
	movl	%ebp, %eax
	andl	$96, %eax
	cmpl	$32, %eax
	movl	$8, %edx
	je	.L678
	cmpl	$0, 28(%esp)
	movl	%ecx, %ebx
	movw	8(%esi), %ax
	movw	10(%esi), %dx
	je	.L681
	movl	28(%esp), %edi
	subw	8(%edi), %ax
	movw	10(%esp), %di
	subw	%di, %ax
	movw	%ax, 22(%esp)
	movl	28(%esp), %eax
	subw	10(%eax), %dx
	subw	%di, %dx
	jmp	.L769
.L681:
	movw	%ax, 22(%esp)
.L769:
	movw	%dx, 20(%esp)
	movl	20(%esp), %edi
	movw	22(%esp), %dx
	testl	$3, %ebp
	movw	%dx, 18(%esp)
	movw	%di, 16(%esp)
	movl	$0, 4(%esp)
	je	.L683
	testl	$12, %ebp
	jne	.L683
	testl	$1, %ebp
	je	.L684
	movw	(%ecx), %ax
	movw	%ax, 22(%esp)
	leal	4(%ecx), %ebx
.L684:
	testl	$2, %ebp
	je	.L685
	movw	(%ebx), %dx
	movw	%dx, 20(%esp)
	addl	$4, %ebx
.L685:
	movl	$1, 4(%esp)
	jmp	.L686
.L683:
	testl	$15, %ebp
	je	.L686
	testl	$1, %ebp
	je	.L688
	movw	(%ecx), %di
	movw	%di, 22(%esp)
	leal	4(%ecx), %ebx
.L688:
	testl	$2, %ebp
	je	.L689
	movw	(%ebx), %ax
	movw	%ax, 20(%esp)
	addl	$4, %ebx
.L689:
	testl	$4, %ebp
	je	.L690
	movw	(%ebx), %dx
	movw	%dx, 14(%esp)
	addl	$4, %ebx
.L690:
	testl	$8, %ebp
	je	.L691
	movw	(%ebx), %cx
	movw	%cx, 12(%esp)
	addl	$4, %ebx
.L691:
	cmpw	$0, 14(%esp)
	je	.L693
	cmpw	$0, 12(%esp)
	movl	$2, 4(%esp)
	jne	.L686
.L693:
	movl	132(%esp), %edi
	movl	$0, 24(%edi)
	jmp	.L770
.L686:
	movl	%ebp, %edi
	andl	$-16, %edi
	je	.L764
.L710:
	movl	%edi, %edx
	negl	%edx
	andl	%edi, %edx
	movl	%edx, %eax
	notl	%eax
	andl	%eax, %edi
	cmpl	$32, %edx
	je	.L700
	cmpl	$32, %edx
	ja	.L709
	cmpl	$16, %edx
	je	.L698
	jmp	.L707
.L709:
	cmpl	$64, %edx
	je	.L704
	jmp	.L707
.L698:
	testl	$16, %ebp
	je	.L694
	movw	(%ebx), %ax
	addl	$4, %ebx
	movw	%ax, 10(%esp)
	jmp	.L694
.L700:
	movl	(%ebx), %edx
	movl	%edx, 24(%esp)
	pushl	$16
	pushl	136(%esp)
	pushl	%edx
	leal	44(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$4, %ebx
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L767
	movl	32(%esp), %eax
	movl	28(%esp), %ecx
	cmpl	%ecx, 28(%eax)
	jne	.L768
	cmpl	%esi, %eax
	movl	$8, %edx
	je	.L678
	jmp	.L694
.L704:
	testl	$64, %ebp
	je	.L705
	movzbl	(%ebx), %eax
	movl	%eax, (%esp)
	addl	$4, %ebx
.L705:
	movl	(%esp), %eax
	subl	$2, %eax
	cmpl	$2, %eax
	jbe	.L694
	cmpl	$0, (%esp)
	je	.L694
	cmpl	$1, (%esp)
	je	.L694
	movl	(%esp), %edx
	movl	132(%esp), %ecx
	movl	%edx, 24(%ecx)
	jmp	.L770
.L707:
	movl	132(%esp), %edi
	movl	%ebp, 24(%edi)
.L770:
	movl	$2, %edx
	jmp	.L678
.L694:
	testl	%edi, %edi
	jne	.L710
.L764:
	xorl	%edx, %edx
	cmpl	$0, 28(%esp)
	je	.L678
	testl	$64, %ebp
	je	.L712
	pushl	(%esp)
	movzwl	14(%esp), %edx
	movl	16(%esp), %eax
	sall	%edx
	addl	%edx, %eax
	movzwl	%ax, %eax
	pushl	%eax
	addw	22(%esp), %dx
	movzwl	%dx, %edx
	pushl	%edx
	movl	40(%esp), %edx
	movw	10(%edx), %ax
	addl	32(%esp), %eax
	cwtl
	pushl	%eax
	movw	8(%edx), %ax
	addw	38(%esp), %ax
	cwtl
	pushl	%eax
	pushl	52(%esp)
	pushl	%esi
	call	WhereDoIGoInTheStack
	movl	%eax, 60(%esp)
	addl	$28, %esp
	jmp	.L713
.L712:
	movl	32(%esi), %eax
	movl	%eax, 32(%esp)
.L713:
	testb	$1, 130(%esi)
	jne	.L714
	movl	28(%esp), %ecx
	movl	124(%ecx), %edx
	testl	%edx, %edx
	movl	108(%ecx), %eax
	je	.L715
	orl	16(%edx), %eax
.L715:
	testl	$1048576, %eax
	je	.L714
	movb	$23, 68(%esp)
	movl	4(%esi), %eax
	testl	$32, %ebp
	movl	%eax, 76(%esp)
	je	.L717
	movl	24(%esp), %edi
	movl	%edi, 80(%esp)
	jmp	.L718
.L717:
	movl	$0, 80(%esp)
.L718:
	testl	$64, %ebp
	je	.L719
	movb	(%esp), %al
	movb	%al, 69(%esp)
	jmp	.L720
.L719:
	movb	$0, 69(%esp)
.L720:
	movw	22(%esp), %dx
	movw	%dx, 84(%esp)
	movl	20(%esp), %ecx
	movl	12(%esp), %eax
	movw	10(%esp), %dx
	movw	14(%esp), %di
	movw	%cx, 86(%esp)
	movw	%dx, 92(%esp)
	movw	%di, 88(%esp)
	movw	%ax, 90(%esp)
	movw	%bp, 94(%esp)
	movl	28(%esp), %ecx
	movl	4(%ecx), %eax
	movl	%eax, 72(%esp)
	pushl	132(%esp)
	pushl	$1048576
	pushl	$1
	leal	80(%esp), %eax
	pushl	%eax
	pushl	%ecx
	call	MaybeDeliverEventsToClient
	addl	$20, %esp
	xorl	%edx, %edx
	decl	%eax
	je	.L678
.L714:
	cmpl	$2, 4(%esp)
	jne	.L734
	movw	14(%esp), %di
	cmpw	12(%esi), %di
	jne	.L724
	movl	12(%esp), %eax
	cmpw	14(%esi), %ax
	je	.L762
.L724:
	movl	124(%esi), %edx
	testl	%edx, %edx
	movl	$1, %ebx
	movl	108(%esi), %eax
	je	.L726
	orl	16(%edx), %eax
.L726:
	testl	$262144, %eax
	je	.L725
	movb	$25, 36(%esp)
	movl	4(%esi), %eax
	movw	14(%esp), %dx
	movl	12(%esp), %ecx
	movl	%eax, 40(%esp)
	movw	%dx, 44(%esp)
	movw	%cx, 46(%esp)
	pushl	132(%esp)
	pushl	$262144
	pushl	$1
	leal	48(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	MaybeDeliverEventsToClient
	addl	$20, %esp
	decl	%eax
	jne	.L725
	movw	12(%esi), %di
	movw	14(%esi), %ax
	movw	%di, 14(%esp)
	movw	%ax, 12(%esp)
	xorl	%ebx, %ebx
.L725:
	testl	%ebx, %ebx
	jne	.L722
.L762:
	testl	$3, %ebp
	movl	$1, 4(%esp)
	jne	.L734
	testl	$80, %ebp
	movl	$0, 4(%esp)
	jne	.L734
	jmp	.L761
.L722:
	cmpl	$2, 4(%esp)
	je	.L735
.L734:
	testl	$1, %ebp
	je	.L736
	movw	18(%esp), %dx
	cmpw	%dx, 22(%esp)
	jne	.L735
.L736:
	testl	$2, %ebp
	je	.L737
	movl	16(%esp), %ecx
	cmpw	%cx, 20(%esp)
	jne	.L735
.L737:
	testl	$16, %ebp
	je	.L738
	movw	10(%esp), %di
	cmpw	104(%esi), %di
	jne	.L735
.L738:
	testl	$64, %ebp
	je	.L761
	movl	32(%esp), %eax
	cmpl	%eax, 32(%esi)
	je	.L761
.L735:
	movl	124(%esi), %edx
	testl	%edx, %edx
	movl	108(%esi), %eax
	je	.L743
	orl	16(%edx), %eax
.L743:
	testl	$131072, %eax
	jne	.L742
	movl	28(%esp), %edx
	movl	108(%edx), %eax
	movl	124(%edx), %edx
	testl	%edx, %edx
	je	.L745
	orl	16(%edx), %eax
.L745:
	testl	$524288, %eax
	je	.L741
.L742:
	movb	$22, 68(%esp)
	movl	4(%esi), %eax
	movl	%eax, 76(%esp)
	movl	32(%esp), %eax
	testl	%eax, %eax
	je	.L747
	movl	4(%eax), %eax
	movl	%eax, 80(%esp)
	jmp	.L748
.L747:
	movl	$0, 80(%esp)
.L748:
	movw	22(%esp), %di
	movw	%di, 84(%esp)
	movl	20(%esp), %eax
	movw	14(%esp), %dx
	movl	12(%esp), %ecx
	movw	10(%esp), %di
	movw	%ax, 86(%esp)
	movw	%dx, 88(%esp)
	movw	%cx, 90(%esp)
	movw	%di, 92(%esp)
	movzbl	130(%esi), %eax
	andl	$1, %eax
	movb	%al, 94(%esp)
	pushl	$0
	pushl	$1
	leal	76(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	DeliverEvents
	addl	$16, %esp
.L741:
	testl	$16, %ebp
	je	.L749
	cmpl	$0, 4(%esp)
	jne	.L750
	movw	10(%esp), %ax
	movl	$1, 4(%esp)
	movw	%ax, 104(%esi)
	jmp	.L765
.L750:
	cmpl	$1, 4(%esp)
	jne	.L752
	movswl	18(%esp),%edx
	movzwl	104(%esi), %ebx
	movswl	22(%esp),%eax
	movzwl	10(%esp), %ecx
	addl	%ebx, %edx
	addl	%ecx, %eax
	cmpl	%eax, %edx
	jne	.L752
	movswl	16(%esp),%edx
	movswl	20(%esp),%eax
	addl	%ebx, %edx
	addl	%ecx, %eax
	cmpl	%eax, %edx
	jne	.L752
	movl	$3, 4(%esp)
	movl	16(%esi), %eax
	pushl	%ecx
	pushl	%esi
	call	*412(%eax)
	popl	%edi
	popl	%eax
	jmp	.L758
.L752:
	movw	10(%esp), %dx
	movw	%dx, 104(%esi)
.L749:
	cmpl	$1, 4(%esp)
	jne	.L754
.L765:
	xorl	%eax, %eax
	testl	$16, %ebp
	sete	%al
	sall	%eax
	movl	16(%esi), %edx
	pushl	%eax
	pushl	36(%esp)
	movswl	28(%esp),%eax
	pushl	%eax
	movswl	34(%esp),%eax
	pushl	%eax
	pushl	%esi
	call	*388(%edx)
	addl	$20, %esp
	jmp	.L757
.L754:
	cmpl	$2, 4(%esp)
	jne	.L758
	movl	16(%esi), %edx
	pushl	32(%esp)
	movzwl	16(%esp), %eax
	pushl	%eax
	movzwl	22(%esp), %eax
	pushl	%eax
	movswl	32(%esp),%eax
	pushl	%eax
	movswl	38(%esp),%eax
	pushl	%eax
	pushl	%esi
	call	*392(%edx)
	addl	$24, %esp
	jmp	.L757
.L767:
	movl	24(%esp), %edi
	movl	132(%esp), %ecx
	movl	%eax, %edx
	movl	%edi, 24(%ecx)
	jmp	.L678
.L768:
	movl	$8, %edx
	jmp	.L678
.L758:
	andl	$64, %ebp
	je	.L757
	pushl	$0
	pushl	36(%esp)
	pushl	%esi
	call	ReflectStackChange
	addl	$12, %esp
.L757:
	cmpl	$0, 4(%esp)
	je	.L761
	pushl	%esi
	call	CheckCursorConfinement
	popl	%ebx
.L761:
	xorl	%edx, %edx
.L678:
	addl	$100, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	ConfigureWindow, .-ConfigureWindow
	.align 4
.globl CirculateWindow
	.type	CirculateWindow, @function
CirculateWindow:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	60(%esp), %edi
	pushl	%edi
	call	RealChildHead
	testl	%eax, %eax
	movl	%eax, %esi
	popl	%ecx
	je	.L772
	movl	32(%eax), %ebp
	jmp	.L773
.L772:
	movl	40(%edi), %ebp
.L773:
	cmpl	$0, 64(%esp)
	movl	%ebp, %ebx
	jne	.L783
	movl	44(%edi), %ebx
	jmp	.L775
.L780:
	movl	36(%ebx), %ebx
.L775:
	cmpl	%esi, %ebx
	je	.L771
	testb	$8, 130(%ebx)
	je	.L780
	movl	%esp, %eax
	pushl	%eax
	pushl	%ebx
	call	WindowExtents
	popl	%ecx
	popl	%edx
	pushl	%eax
	pushl	%esi
	pushl	%ebx
	call	AnyWindowOverlapsMe
	addl	$12, %esp
	testl	%eax, %eax
	je	.L780
	jmp	.L782
.L788:
	movl	32(%ebx), %ebx
.L783:
	testl	%ebx, %ebx
	je	.L771
	testb	$8, 130(%ebx)
	je	.L788
	movl	%esp, %eax
	pushl	%eax
	pushl	%ebx
	call	WindowExtents
	popl	%esi
	popl	%edx
	pushl	%eax
	pushl	%ebx
	call	IOverlapAnyWindow
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	je	.L788
.L782:
	movl	4(%ebx), %eax
	movl	%eax, 16(%esp)
	movl	4(%edi), %eax
	cmpl	$0, 64(%esp)
	setne	24(%esp)
	movl	%eax, 20(%esp)
	movl	%eax, 12(%esp)
	movl	124(%edi), %edx
	testl	%edx, %edx
	movl	108(%edi), %eax
	je	.L793
	orl	16(%edx), %eax
.L793:
	testl	$1048576, %eax
	je	.L792
	movb	$27, 8(%esp)
	pushl	68(%esp)
	pushl	$1048576
	pushl	$1
	leal	20(%esp), %eax
	pushl	%eax
	pushl	%edi
	call	MaybeDeliverEventsToClient
	addl	$20, %esp
	decl	%eax
	je	.L771
.L792:
	movb	$26, 8(%esp)
	pushl	$0
	pushl	$1
	leal	16(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	DeliverEvents
	pushl	$1
	cmpl	$0, 84(%esp)
	movl	%ebp, %eax
	je	.L799
	xorl	%eax, %eax
.L799:
	pushl	%eax
	pushl	%ebx
	call	ReflectStackChange
	addl	$28, %esp
.L771:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	xorl	%eax, %eax
	popl	%ebp
	ret
	.size	CirculateWindow, .-CirculateWindow
	.align 4
	.type	CompareWIDs, @function
CompareWIDs:
	movl	8(%esp), %eax
	movl	(%eax), %edx
	movl	4(%esp), %eax
	cmpl	%edx, 4(%eax)
	setne	%al
	movzbl	%al, %eax
	ret
	.size	CompareWIDs, .-CompareWIDs
	.align 4
.globl ReparentWindow
	.type	ReparentWindow, @function
ReparentWindow:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	60(%esp), %ebx
	movb	130(%ebx), %al
	shrb	$3, %al
	movl	64(%esp), %edi
	movl	%eax, %edx
	movzwl	104(%ebx), %eax
	movl	%eax, (%esp)
	andl	$1, %edx
	leal	4(%edi), %eax
	movl	%edx, 4(%esp)
	movl	16(%ebx), %ebp
	pushl	%eax
	pushl	$CompareWIDs
	pushl	%ebx
	call	TraverseTree
	addl	$12, %esp
	testl	%eax, %eax
	movl	$8, %edx
	je	.L803
	pushl	%ebx
	call	MakeWindowOptional
	testl	%eax, %eax
	popl	%ecx
	movl	$11, %edx
	je	.L803
	cmpl	$0, 4(%esp)
	je	.L806
	pushl	$0
	pushl	%ebx
	call	UnmapWindow
	popl	%eax
	popl	%edx
.L806:
	movb	$21, 8(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 16(%esp)
	movl	4(%edi), %eax
	movl	%eax, 20(%esp)
	movl	68(%esp), %edx
	movl	72(%esp), %eax
	movw	%dx, 24(%esp)
	movw	%ax, 26(%esp)
	movzbl	130(%ebx), %eax
	andl	$1, %eax
	movb	%al, 28(%esp)
	pushl	%edi
	pushl	$1
	leal	16(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	DeliverEvents
	movl	28(%ebx), %esi
	addl	$16, %esp
	cmpl	%ebx, 40(%esi)
	jne	.L807
	movl	32(%ebx), %eax
	movl	%eax, 40(%esi)
.L807:
	cmpl	%ebx, 44(%esi)
	jne	.L808
	movl	36(%ebx), %eax
	movl	%eax, 44(%esi)
.L808:
	movl	32(%ebx), %edx
	testl	%edx, %edx
	je	.L809
	movl	36(%ebx), %eax
	movl	%eax, 36(%edx)
.L809:
	movl	36(%ebx), %eax
	testl	%eax, %eax
	je	.L810
	movl	%edx, 32(%eax)
.L810:
	movl	%edi, 28(%ebx)
	pushl	%edi
	call	RealChildHead
	movl	%eax, %edx
	testl	%edx, %edx
	popl	%eax
	je	.L811
	movl	32(%edx), %eax
	movl	%eax, 32(%ebx)
	movl	32(%edx), %eax
	testl	%eax, %eax
	je	.L812
	movl	%ebx, 36(%eax)
	jmp	.L813
.L812:
	movl	%ebx, 44(%edi)
.L813:
	movl	%ebx, 32(%edx)
	movl	%edx, 36(%ebx)
	jmp	.L814
.L811:
	movl	40(%edi), %eax
	testl	%eax, %eax
	movl	%eax, 32(%ebx)
	movl	$0, 36(%ebx)
	je	.L815
	movl	%ebx, 36(%eax)
	jmp	.L816
.L815:
	movl	%ebx, 44(%edi)
.L816:
	movl	%ebx, 40(%edi)
.L814:
	movl	68(%esp), %eax
	movl	72(%esp), %edx
	addl	(%esp), %eax
	addl	(%esp), %edx
	movw	%ax, 100(%ebx)
	movw	%dx, 102(%ebx)
	addw	8(%edi), %ax
	addw	10(%edi), %dx
	movw	%ax, 8(%ebx)
	movw	%dx, 10(%ebx)
	pushl	%ebx
	call	SetWinSize
	pushl	%ebx
	call	SetBorderSize
	popl	%ecx
	cmpl	$0, 404(%ebp)
	popl	%edi
	je	.L817
	pushl	%esi
	pushl	%ebx
	call	*404(%ebp)
	popl	%eax
	popl	%edx
.L817:
	movswl	10(%ebx),%eax
	pushl	%eax
	movswl	8(%ebx),%eax
	pushl	%eax
	pushl	%ebx
	call	*140(%ebp)
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	%ebx
	call	ResizeChildrenWinSize
	addl	$32, %esp
	pushl	%ebx
	call	CheckWindowOptionalNeed
	popl	%ebp
	cmpl	$0, 4(%esp)
	je	.L818
	pushl	76(%esp)
	pushl	%ebx
	call	MapWindow
	popl	%esi
	popl	%edi
.L818:
	pushl	%ebx
	call	RecalculateDeliverableEvents
	xorl	%edx, %edx
	popl	%ebx
.L803:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	ReparentWindow, .-ReparentWindow
	.align 4
	.type	RealizeTree, @function
RealizeTree:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp), %esi
	movl	16(%esi), %eax
	movl	148(%eax), %edi
	movl	%esi, %ebx
.L834:
	movb	130(%ebx), %al
	testb	$8, %al
	je	.L823
	orl	$16, %eax
	testb	$64, 128(%ebx)
	movb	%al, 130(%ebx)
	je	.L824
	incl	deltaSaveUndersViewable
.L824:
	cmpb	$1, 1(%ebx)
	sete	%dl
	sall	$5, %edx
	andl	$-33, %eax
	orl	%edx, %eax
	movb	%al, 130(%ebx)
	pushl	%ebx
	call	*%edi
	popl	%eax
	movl	40(%ebx), %eax
	testl	%eax, %eax
	je	.L823
	movl	%eax, %ebx
	jmp	.L834
.L823:
	cmpl	$0, 32(%ebx)
	jne	.L827
	cmpl	%esi, %ebx
	je	.L819
.L830:
	movl	28(%ebx), %ebx
	cmpl	$0, 32(%ebx)
	jne	.L827
	cmpl	%esi, %ebx
	jne	.L830
	jmp	.L819
.L827:
	cmpl	%esi, %ebx
	je	.L819
	movl	32(%ebx), %ebx
	jmp	.L834
.L819:
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	RealizeTree, .-RealizeTree
	.align 4
.globl DisableMapUnmapEvents
	.type	DisableMapUnmapEvents, @function
DisableMapUnmapEvents:
	movl	4(%esp), %eax
	movl	%eax, windowDisableMapUnmapEvents
	ret
	.size	DisableMapUnmapEvents, .-DisableMapUnmapEvents
	.align 4
.globl EnableMapUnmapEvents
	.type	EnableMapUnmapEvents, @function
EnableMapUnmapEvents:
	movl	$0, windowDisableMapUnmapEvents
	ret
	.size	EnableMapUnmapEvents, .-EnableMapUnmapEvents
	.align 4
	.type	MapUnmapEventsEnabled, @function
MapUnmapEventsEnabled:
	movl	windowDisableMapUnmapEvents, %eax
	cmpl	%eax, 4(%esp)
	setne	%al
	movzbl	%al, %eax
	ret
	.size	MapUnmapEventsEnabled, .-MapUnmapEventsEnabled
	.align 4
.globl MapWindow
	.type	MapWindow, @function
MapWindow:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$52, %esp
	movl	72(%esp), %esi
	movb	130(%esi), %al
	xorl	%ebp, %ebp
	testb	$8, %al
	jne	.L838
	movl	28(%esi), %ebx
	testl	%ebx, %ebx
	movl	16(%esi), %edi
	je	.L841
	testb	$1, %al
	jne	.L842
	movl	124(%ebx), %edx
	testl	%edx, %edx
	movl	108(%ebx), %eax
	je	.L843
	orl	16(%edx), %eax
.L843:
	testl	$1048576, %eax
	je	.L842
	movb	$20, 20(%esp)
	movl	4(%esi), %eax
	movl	%eax, 28(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 24(%esp)
	pushl	76(%esp)
	pushl	$1048576
	pushl	$1
	leal	32(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	MaybeDeliverEventsToClient
	addl	$20, %esp
	decl	%eax
	je	.L838
.L842:
	movl	124(%esi), %edx
	orb	$8, 130(%esi)
	testl	%edx, %edx
	movl	108(%esi), %eax
	je	.L848
	orl	16(%edx), %eax
.L848:
	testl	$131072, %eax
	jne	.L847
	movl	124(%ebx), %edx
	testl	%edx, %edx
	movl	108(%ebx), %eax
	je	.L850
	orl	16(%edx), %eax
.L850:
	testl	$524288, %eax
	je	.L846
.L847:
	pushl	%esi
	call	MapUnmapEventsEnabled
	testl	%eax, %eax
	popl	%edx
	je	.L846
	movb	$19, 20(%esp)
	movl	4(%esi), %eax
	movl	%eax, 28(%esp)
	movzbl	130(%esi), %eax
	andl	$1, %eax
	movb	%al, 32(%esp)
	pushl	$0
	pushl	$1
	leal	28(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	DeliverEvents
	addl	$16, %esp
.L846:
	testb	$16, 130(%ebx)
	je	.L838
	pushl	%esi
	call	RealizeTree
	testb	$32, 130(%esi)
	popl	%eax
	je	.L853
	movl	%esp, %eax
	pushl	%eax
	pushl	%esi
	pushl	%esi
	call	*376(%edi)
	movl	%eax, %ebx
	movl	16(%esi), %eax
	addl	$12, %esp
	cmpb	$64, 37(%eax)
	jne	.L854
	pushl	32(%esi)
	pushl	4(%esp)
	call	*380(%edi)
	popl	%ecx
	movl	%eax, %ebp
	popl	%eax
.L854:
	testl	%ebx, %ebx
	je	.L855
	pushl	$4
	pushl	4(%esp)
	movl	8(%esp), %eax
	pushl	28(%eax)
	call	*156(%edi)
	movl	12(%esp), %eax
	pushl	28(%eax)
	call	*400(%edi)
	addl	$16, %esp
.L855:
	testl	%ebp, %ebp
	je	.L856
	pushl	32(%esi)
	pushl	4(%esp)
	call	*384(%edi)
	popl	%eax
	popl	%edx
.L856:
	testl	%ebx, %ebx
	je	.L853
	cmpl	$0, 160(%edi)
	je	.L853
	pushl	$4
	pushl	4(%esp)
	movl	8(%esp), %eax
	pushl	28(%eax)
	call	*160(%edi)
	addl	$12, %esp
.L853:
	call	WindowsRestructured
	jmp	.L838
.L841:
	movb	%al, %dl
	orl	$24, %edx
	cmpb	$1, 1(%esi)
	sete	%al
	sall	$5, %eax
	andl	$-33, %edx
	orl	%eax, %edx
	movb	%dl, 130(%esi)
	pushl	%esi
	call	*148(%edi)
	cmpl	$0, 184(%edi)
	popl	%eax
	je	.L859
	pushl	$0
	pushl	$0
	pushl	%esi
	call	*184(%edi)
	addl	$12, %esp
.L859:
	cmpl	$0, 160(%edi)
	je	.L860
	pushl	$4
	pushl	%esi
	pushl	$0
	call	*160(%edi)
	addl	$12, %esp
.L860:
	movl	miEmptyBox, %eax
	movl	%eax, 4(%esp)
	movl	miEmptyBox+4, %edx
	leal	48(%esi), %eax
	movl	%edx, 8(%esp)
	movl	$miEmptyData, 12(%esp)
	pushl	%eax
	leal	8(%esp), %ebx
	pushl	%ebx
	call	miRegionCopy
	pushl	$0
	pushl	%ebx
	pushl	%esi
	call	*164(%edi)
	addl	$20, %esp
	movl	12(%esp), %eax
	testl	%eax, %eax
	je	.L838
	cmpl	$0, (%eax)
	je	.L838
	pushl	%eax
	call	Xfree
	movl	$0, 16(%esp)
	popl	%eax
.L838:
	addl	$52, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	xorl	%eax, %eax
	popl	%ebp
	ret
	.size	MapWindow, .-MapWindow
	.align 4
.globl MapSubwindows
	.type	MapSubwindows, @function
MapSubwindows:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$52, %esp
	movl	72(%esp), %ebp
	movl	124(%ebp), %eax
	movl	108(%ebp), %edx
	testl	%eax, %eax
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, (%esp)
	movl	16(%ebp), %edi
	movl	%edx, %ecx
	je	.L904
	movl	16(%eax), %ecx
	orl	%edx, %ecx
.L904:
	andl	$1048576, %ecx
	testl	%eax, %eax
	movl	%ecx, 8(%esp)
	movl	%edx, %esi
	je	.L905
	movl	%edx, %esi
	orl	16(%eax), %esi
.L905:
	movl	40(%ebp), %ebx
	andl	$524288, %esi
	testl	%ebx, %ebx
	movl	$0, 4(%esp)
	je	.L862
.L882:
	movb	130(%ebx), %al
	testb	$8, %al
	jne	.L869
	cmpl	$0, 8(%esp)
	je	.L872
	testb	$1, %al
	jne	.L872
	movb	$20, 20(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 28(%esp)
	movl	4(%ebp), %eax
	movl	%eax, 24(%esp)
	pushl	76(%esp)
	pushl	$1048576
	pushl	$1
	leal	32(%esp), %eax
	pushl	%eax
	pushl	%ebp
	call	MaybeDeliverEventsToClient
	addl	$20, %esp
	decl	%eax
	je	.L869
.L872:
	orb	$8, 130(%ebx)
	testl	%esi, %esi
	jne	.L875
	movl	124(%ebx), %edx
	testl	%edx, %edx
	movl	108(%ebx), %eax
	je	.L876
	orl	16(%edx), %eax
.L876:
	testl	$131072, %eax
	je	.L874
.L875:
	movb	$19, 20(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 28(%esp)
	movzbl	130(%ebx), %eax
	andl	$1, %eax
	movb	%al, 32(%esp)
	pushl	$0
	pushl	$1
	leal	28(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	DeliverEvents
	addl	$16, %esp
.L874:
	cmpl	$0, 16(%esp)
	jne	.L878
	movl	%ebx, 16(%esp)
.L878:
	testb	$16, 130(%ebp)
	je	.L869
	pushl	%ebx
	call	RealizeTree
	testb	$32, 130(%ebx)
	popl	%eax
	je	.L869
	pushl	$0
	pushl	%ebx
	pushl	%ebx
	call	*376(%edi)
	orl	%eax, 16(%esp)
	movl	16(%ebx), %eax
	addl	$12, %esp
	cmpb	$64, 37(%eax)
	jne	.L869
	movl	$1, (%esp)
.L869:
	movl	32(%ebx), %ebx
	testl	%ebx, %ebx
	jne	.L882
	cmpl	$0, 16(%esp)
	je	.L862
	pushl	%ebp
	call	*396(%edi)
	movl	%eax, %esi
	cmpl	%ebp, 28(%esi)
	popl	%eax
	je	.L884
	pushl	$0
	pushl	%esi
	pushl	%esi
	call	*376(%edi)
	orl	%eax, 16(%esp)
	movl	%esi, 28(%esp)
	addl	$12, %esp
.L884:
	cmpl	$0, 4(%esp)
	je	.L885
	cmpl	%ebp, 28(%esi)
	je	.L886
	cmpl	$0, (%esp)
	jne	.L888
	movl	16(%esi), %eax
	cmpb	$64, 37(%eax)
	jne	.L889
.L888:
	pushl	%esi
	pushl	%esi
	call	*380(%edi)
	movl	%eax, 8(%esp)
	popl	%ecx
	popl	%ebx
	jmp	.L889
.L886:
	cmpl	$0, (%esp)
	je	.L889
	movl	40(%ebp), %ebx
	testl	%ebx, %ebx
	movl	$0, (%esp)
	je	.L889
.L897:
	movl	16(%ebx), %eax
	cmpb	$64, 37(%eax)
	jne	.L893
	pushl	32(%ebx)
	pushl	%ebx
	call	*380(%edi)
	popl	%ebp
	popl	%edx
	orl	%eax, (%esp)
	je	.L893
	cmpl	$0, 12(%esp)
	jne	.L893
	movl	%ebx, 12(%esp)
.L893:
	movl	32(%ebx), %ebx
	testl	%ebx, %ebx
	jne	.L897
.L889:
	pushl	$4
	pushl	20(%esp)
	pushl	28(%esi)
	call	*156(%edi)
	pushl	28(%esi)
	call	*400(%edi)
	addl	$16, %esp
.L885:
	cmpl	$0, (%esp)
	je	.L898
	movl	12(%esp), %eax
	pushl	32(%eax)
	pushl	%esi
	call	*384(%edi)
	popl	%ecx
	popl	%ebx
.L898:
	cmpl	$0, 4(%esp)
	je	.L899
	cmpl	$0, 160(%edi)
	je	.L899
	pushl	$4
	pushl	20(%esp)
	pushl	28(%esi)
	call	*160(%edi)
	addl	$12, %esp
.L899:
	call	WindowsRestructured
.L862:
	addl	$52, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	MapSubwindows, .-MapSubwindows
	.align 4
	.type	UnrealizeTree, @function
UnrealizeTree:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %esi
	movl	16(%esi), %eax
	movl	152(%eax), %ebp
	movl	416(%eax), %edi
	movl	%esi, %ebx
.L925:
	movb	130(%ebx), %al
	testb	$16, %al
	je	.L910
	andl	$-17, %eax
	orl	$6, %eax
	movb	%al, 130(%ebx)
	pushl	%ebx
	call	*%ebp
	pushl	%esi
	call	MapUnmapEventsEnabled
	testl	%eax, %eax
	popl	%ecx
	popl	%edx
	je	.L911
	pushl	$0
	pushl	%ebx
	call	DeleteWindowFromAnyEvents
	popl	%eax
	popl	%edx
.L911:
	movb	130(%ebx), %al
	testb	$32, %al
	je	.L912
	testb	$64, 128(%ebx)
	je	.L913
	decl	deltaSaveUndersViewable
.L913:
	andl	$-33, %eax
	movb	%al, 130(%ebx)
	pushl	24(%esp)
	pushl	%esi
	pushl	%ebx
	call	*%edi
	movl	globalSerialNumber, %eax
	incl	%eax
	addl	$12, %esp
	cmpl	$268435456, %eax
	movl	%eax, globalSerialNumber
	jbe	.L915
	movl	$1, globalSerialNumber
	movl	$1, %eax
.L915:
	movl	%eax, 20(%ebx)
.L912:
	movl	40(%ebx), %eax
	testl	%eax, %eax
	je	.L910
	movl	%eax, %ebx
	jmp	.L925
.L910:
	cmpl	$0, 32(%ebx)
	jne	.L918
	cmpl	%esi, %ebx
	je	.L906
.L921:
	movl	28(%ebx), %ebx
	cmpl	$0, 32(%ebx)
	jne	.L918
	cmpl	%esi, %ebx
	jne	.L921
	jmp	.L906
.L918:
	cmpl	%esi, %ebx
	je	.L906
	movl	32(%ebx), %ebx
	jmp	.L925
.L906:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	UnrealizeTree, .-UnrealizeTree
	.align 4
.globl UnmapWindow
	.type	UnmapWindow, @function
UnmapWindow:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	60(%esp), %ebx
	movb	130(%ebx), %al
	movb	%al, %dl
	shrb	$4, %dl
	movl	%edx, %ecx
	movb	%al, %dl
	shrb	$5, %dl
	movl	$1, %ebp
	andl	$1, %ecx
	andl	%edx, %ebp
	testb	$8, %al
	movl	64(%esp), %edi
	movl	%ecx, (%esp)
	movl	16(%ebx), %esi
	movl	%ebx, 4(%esp)
	je	.L926
	movl	28(%ebx), %ecx
	testl	%ecx, %ecx
	je	.L926
	movl	124(%ebx), %edx
	testl	%edx, %edx
	movl	108(%ebx), %eax
	je	.L931
	orl	16(%edx), %eax
.L931:
	testl	$131072, %eax
	jne	.L930
	movl	124(%ecx), %edx
	testl	%edx, %edx
	movl	108(%ecx), %eax
	je	.L933
	orl	16(%edx), %eax
.L933:
	testl	$524288, %eax
	je	.L929
.L930:
	pushl	%ebx
	call	MapUnmapEventsEnabled
	testl	%eax, %eax
	popl	%ecx
	je	.L929
	movb	$18, 8(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 16(%esp)
	movl	%edi, %eax
	movb	%al, 20(%esp)
	pushl	$0
	pushl	$1
	leal	16(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	DeliverEvents
	addl	$16, %esp
.L929:
	testl	%ebp, %ebp
	je	.L935
	testl	%edi, %edi
	jne	.L935
	leal	4(%esp), %eax
	movl	$1, 72(%ebx)
	pushl	%eax
	pushl	32(%ebx)
	pushl	%ebx
	call	*376(%esi)
	movl	16(%esp), %eax
	pushl	28(%eax)
	call	*372(%esi)
	addl	$16, %esp
.L935:
	andb	$-9, 130(%ebx)
	cmpl	$0, (%esp)
	je	.L936
	pushl	%edi
	pushl	%ebx
	call	UnrealizeTree
	popl	%eax
	popl	%edx
.L936:
	testl	%ebp, %ebp
	je	.L937
	testl	%edi, %edi
	jne	.L938
	pushl	$3
	pushl	%ebx
	movl	12(%esp), %eax
	pushl	28(%eax)
	call	*156(%esi)
	movl	16(%esp), %eax
	pushl	28(%eax)
	call	*400(%esi)
	addl	$16, %esp
.L938:
	movl	16(%ebx), %eax
	cmpb	$64, 37(%eax)
	jne	.L939
	pushl	32(%ebx)
	pushl	8(%esp)
	call	*380(%esi)
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	je	.L939
	pushl	32(%ebx)
	pushl	8(%esp)
	call	*384(%esi)
	popl	%ecx
	popl	%ebp
.L939:
	andb	$127, 128(%ebx)
	testl	%edi, %edi
	jne	.L937
	cmpl	$0, 160(%esi)
	je	.L937
	pushl	$3
	pushl	%ebx
	movl	12(%esp), %eax
	pushl	28(%eax)
	call	*160(%esi)
	addl	$12, %esp
.L937:
	cmpl	$0, (%esp)
	je	.L926
	testl	%edi, %edi
	jne	.L926
	call	WindowsRestructured
.L926:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	xorl	%eax, %eax
	popl	%ebp
	ret
	.size	UnmapWindow, .-UnmapWindow
	.align 4
.globl UnmapSubwindows
	.type	UnmapSubwindows, @function
UnmapSubwindows:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$52, %esp
	movl	72(%esp), %edi
	movb	130(%edi), %al
	shrb	$4, %al
	movl	%eax, %edx
	andl	$1, %edx
	shrb	%al
	movl	%edx, 12(%esp)
	movl	%eax, %edx
	andl	$1, %edx
	xorl	%ebp, %ebp
	cmpl	$0, 40(%edi)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	16(%edi), %esi
	je	.L943
	movl	124(%edi), %eax
	testl	%eax, %eax
	movl	108(%edi), %edx
	je	.L945
	orl	16(%eax), %edx
.L945:
	andl	$524288, %edx
	movl	%edx, (%esp)
	pushl	%edi
	call	RealChildHead
	movl	%eax, 20(%esp)
	popl	%ebx
	cmpl	$0, 8(%esp)
	je	.L947
	pushl	%edi
	call	*396(%esi)
	movl	%eax, %ebp
	popl	%ecx
.L947:
	movl	44(%edi), %ebx
	cmpl	16(%esp), %ebx
	je	.L974
.L960:
	testb	$8, 130(%ebx)
	je	.L950
	cmpl	$0, (%esp)
	jne	.L954
	movl	124(%ebx), %edx
	testl	%edx, %edx
	movl	108(%ebx), %eax
	je	.L955
	orl	16(%edx), %eax
.L955:
	testl	$131072, %eax
	je	.L953
.L954:
	movb	$18, 20(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 28(%esp)
	movb	$0, 32(%esp)
	pushl	$0
	pushl	$1
	leal	28(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	DeliverEvents
	addl	$16, %esp
.L953:
	testb	$32, 130(%ebx)
	je	.L957
	movl	$1, 72(%ebx)
	movl	$1, 4(%esp)
.L957:
	movb	130(%ebx), %al
	andl	$-9, %eax
	testb	$16, %al
	movb	%al, 130(%ebx)
	je	.L958
	pushl	$0
	pushl	%ebx
	call	UnrealizeTree
	popl	%eax
	popl	%edx
.L958:
	cmpl	$0, 8(%esp)
	je	.L950
	andb	$127, 128(%ebx)
.L950:
	movl	36(%ebx), %ebx
	cmpl	16(%esp), %ebx
	jne	.L960
.L974:
	cmpl	$0, 8(%esp)
	je	.L961
	cmpl	$0, 4(%esp)
	je	.L962
	cmpl	%edi, 28(%ebp)
	jne	.L963
	pushl	%edi
	call	*372(%esi)
	popl	%eax
	jmp	.L964
.L963:
	pushl	$0
	pushl	%ebp
	pushl	%edi
	call	*376(%esi)
	pushl	28(%ebp)
	call	*372(%esi)
	addl	$16, %esp
	cmpl	28(%ebp), %edi
	movl	%edi, %ebx
	je	.L976
.L968:
	pushl	%ebx
	call	*372(%esi)
	movl	28(%ebx), %ebx
	cmpl	28(%ebp), %ebx
	popl	%eax
	jne	.L968
.L976:
	movl	40(%edi), %eax
	movl	%eax, 16(%esp)
.L964:
	pushl	$3
	pushl	20(%esp)
	pushl	28(%ebp)
	call	*156(%esi)
	pushl	28(%ebp)
	call	*400(%esi)
	addl	$16, %esp
.L962:
	movl	16(%edi), %eax
	cmpb	$64, 37(%eax)
	jne	.L969
	pushl	%ebp
	pushl	%ebp
	call	*380(%esi)
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	je	.L969
	pushl	%ebp
	pushl	%ebp
	call	*384(%esi)
	popl	%ebx
	popl	%edi
.L969:
	cmpl	$0, 4(%esp)
	je	.L961
	cmpl	$0, 160(%esi)
	je	.L961
	pushl	$3
	pushl	20(%esp)
	pushl	28(%ebp)
	call	*160(%esi)
	addl	$12, %esp
.L961:
	cmpl	$0, 12(%esp)
	je	.L943
	call	WindowsRestructured
.L943:
	addl	$52, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	UnmapSubwindows, .-UnmapSubwindows
	.align 4
.globl HandleSaveSet
	.type	HandleSaveSet, @function
HandleSaveSet:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %esi
	xorl	%ebp, %ebp
	cmpl	48(%esi), %ebp
	jge	.L992
.L990:
	movl	44(%esi), %eax
	movl	(%eax,%ebp,4), %ebx
	movl	28(%ebx), %ecx
	testl	%ecx, %ecx
	movl	%ecx, %edi
	je	.L980
	movl	4(%ecx), %eax
	andl	$534773760, %eax
	shrl	$21, %eax
	movl	clients, %edx
	cmpl	%esi, (%edx,%eax,4)
	jne	.L983
.L986:
	movl	28(%ecx), %ecx
	testl	%ecx, %ecx
	je	.L980
	movl	4(%ecx), %eax
	andl	$534773760, %eax
	shrl	$21, %eax
	cmpl	%esi, (%edx,%eax,4)
	je	.L986
.L983:
	testl	%ecx, %ecx
	je	.L980
	cmpl	%edi, %ecx
	je	.L988
	pushl	%esi
	movzwl	104(%ebx), %eax
	movswl	10(%ebx),%edx
	subl	%eax, %edx
	movswl	10(%ecx),%eax
	subl	%eax, %edx
	pushl	%edx
	movzwl	104(%ebx), %eax
	movswl	8(%ebx),%edx
	subl	%eax, %edx
	movswl	8(%ecx),%eax
	subl	%eax, %edx
	pushl	%edx
	pushl	%ecx
	pushl	%ebx
	call	ReparentWindow
	movb	130(%ebx), %dl
	movb	%dl, %al
	andl	$24, %eax
	addl	$20, %esp
	cmpb	$8, %al
	jne	.L988
	andl	$-9, %edx
	movb	%dl, 130(%ebx)
.L988:
	pushl	%esi
	pushl	%ebx
	call	MapWindow
	popl	%edi
	popl	%eax
.L980:
	incl	%ebp
	cmpl	48(%esi), %ebp
	jl	.L990
.L992:
	pushl	44(%esi)
	call	Xfree
	movl	$0, 48(%esi)
	movl	$0, 44(%esi)
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	HandleSaveSet, .-HandleSaveSet
	.align 4
.globl PointInWindowIsVisible
	.type	PointInWindowIsVisible, @function
PointInWindowIsVisible:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	pushl	%ebx
	movl	28(%esp), %edi
	testb	$16, 130(%edi)
	movl	32(%esp), %esi
	movl	36(%esp), %ebx
	je	.L996
	movl	%esp, %ebp
	pushl	%ebp
	pushl	%ebx
	pushl	%esi
	leal	60(%edi), %eax
	pushl	%eax
	call	miPointInRegion
	addl	$16, %esp
	testl	%eax, %eax
	je	.L996
	movl	124(%edi), %edx
	testl	%edx, %edx
	je	.L997
	cmpl	$0, 48(%edx)
	je	.L997
	pushl	%ebp
	movswl	10(%edi),%eax
	subl	%eax, %ebx
	pushl	%ebx
	movswl	8(%edi),%eax
	subl	%eax, %esi
	pushl	%esi
	pushl	48(%edx)
	call	miPointInRegion
	addl	$16, %esp
	testl	%eax, %eax
	je	.L996
.L997:
	movl	$1, %eax
	jmp	.L994
.L996:
	xorl	%eax, %eax
.L994:
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	PointInWindowIsVisible, .-PointInWindowIsVisible
	.align 4
.globl NotClippedByChildren
	.type	NotClippedByChildren, @function
NotClippedByChildren:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %ebx
	pushl	$1
	pushl	$0
	call	miRegionCreate
	movl	%eax, %esi
	cmpl	$0, 28(%ebx)
	popl	%eax
	popl	%edx
	jne	.L1002
	cmpl	$0, screenIsSaved
	jne	.L1002
	movl	16(%ebx), %eax
	movl	(%eax), %eax
	sall	$4, %eax
	cmpl	$0, savedScreenInfo(%eax)
	jne	.L1001
.L1002:
	leal	76(%ebx), %eax
	pushl	%eax
	leal	60(%ebx), %eax
	pushl	%eax
	pushl	%esi
	call	miIntersect
	addl	$12, %esp
.L1001:
	popl	%ebx
	movl	%esi, %eax
	popl	%esi
	ret
	.size	NotClippedByChildren, .-NotClippedByChildren
	.align 4
.globl SendVisibilityNotify
	.type	SendVisibilityNotify, @function
SendVisibilityNotify:
	subl	$32, %esp
	movl	36(%esp), %ecx
	movb	130(%ecx), %dl
	shrb	%dl
	movb	$15, (%esp)
	movl	4(%ecx), %eax
	andl	$3, %edx
	movl	%eax, 4(%esp)
	movb	%dl, 8(%esp)
	pushl	$0
	pushl	$1
	leal	8(%esp), %eax
	pushl	%eax
	pushl	%ecx
	call	DeliverEvents
	addl	$48, %esp
	ret
	.size	SendVisibilityNotify, .-SendVisibilityNotify
	.align 4
.globl dixSaveScreens
	.type	dixSaveScreens, @function
dixSaveScreens:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%edi
	pushl	%edi
	cmpl	$2, 32(%esp)
	jne	.L1005
	call	UpdateCurrentTimeIf
	movl	currentTime, %eax
	movl	%eax, lastDeviceEventTime
	xorl	%eax, %eax
	cmpl	$0, 36(%esp)
	sete	%al
	movl	currentTime+4, %edx
	movl	%edx, lastDeviceEventTime+4
	movl	%eax, 4(%esp)
	movl	%eax, (%esp)
	jmp	.L1008
.L1005:
	movl	32(%esp), %eax
	cmpl	screenIsSaved, %eax
	movl	%eax, 4(%esp)
	movl	%eax, (%esp)
	jne	.L1008
	movl	$3, (%esp)
.L1008:
	xorl	%ebp, %ebp
	movl	screenInfo+48, %eax
	cmpl	%eax, %ebp
	jge	.L1049
.L1015:
	incl	%ebp
	cmpl	%eax, %ebp
	jl	.L1015
	xorl	%ebp, %ebp
	cmpl	screenInfo+48, %ebp
	jge	.L1049
.L1044:
	cmpl	$2, 32(%esp)
	jne	.L1020
	pushl	$2
	movl	screenInfo+52(,%ebp,4), %eax
	pushl	%eax
	call	*112(%eax)
	popl	%ebx
	popl	%esi
.L1020:
	movl	%ebp, %ebx
	sall	$4, %ebx
	movl	savedScreenInfo+12(%ebx), %edx
	testl	%edx, %edx
	je	.L1021
	xorl	%eax, %eax
	cmpl	$2, 32(%esp)
	sete	%al
	pushl	%eax
	pushl	4(%esp)
	pushl	screenInfo+52(,%ebp,4)
	call	*%edx
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L1018
.L1021:
	movl	(%esp), %eax
	cmpl	screenIsSaved, %eax
	je	.L1018
	cmpl	$1, %eax
	je	.L1025
	cmpl	$1, %eax
	jg	.L1043
	testl	%eax, %eax
	je	.L1035
	jmp	.L1018
.L1043:
	cmpl	$3, (%esp)
	je	.L1029
	jmp	.L1018
.L1025:
	cmpb	$0, savedScreenInfo+8(%ebx)
	jne	.L1026
	movl	screenInfo+52(,%ebp,4), %eax
	pushl	4(%esp)
	jmp	.L1051
.L1026:
	cmpl	$0, savedScreenInfo(%ebx)
	je	.L1018
	pushl	$0
	pushl	savedScreenInfo+4(%ebx)
	movl	$0, savedScreenInfo(%ebx)
	call	FreeResource
	jmp	.L1050
.L1029:
	movb	savedScreenInfo+8(%ebx), %al
	cmpb	$2, %al
	jne	.L1030
	cmpl	$0, logoScreenSaver
	movl	savedScreenInfo(%ebx), %edi
	movl	$1, screenIsSaved
	je	.L1031
	movl	16(%edi), %eax
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	%edi
	call	*180(%eax)
	addl	$24, %esp
.L1031:
	movl	16(%edi), %esi
	pushl	$2
	pushl	32(%edi)
	call	rand
	movl	$32, %ebx
	cltd
	idivl	%ebx
	negl	%edx
	movswl	%dx,%edx
	pushl	%edx
	call	rand
	cltd
	idivl	%ebx
	negl	%edx
	movswl	%dx,%edx
	pushl	%edx
	pushl	%edi
	call	*388(%esi)
	addl	$20, %esp
	cmpl	$0, logoScreenSaver
	je	.L1032
	pushl	%edi
	call	DrawLogo
	popl	%ecx
.L1032:
	movl	$0, screenIsSaved
	jmp	.L1018
.L1030:
	testb	%al, %al
	jne	.L1018
	movl	screenInfo+52(,%ebp,4), %eax
	pushl	$3
.L1051:
	pushl	%eax
	call	*112(%eax)
.L1050:
	popl	%eax
	popl	%edx
	jmp	.L1018
.L1035:
	cmpl	$0, ScreenSaverBlanking
	je	.L1036
	pushl	4(%esp)
	movl	screenInfo+52(,%ebp,4), %eax
	pushl	%eax
	call	*112(%eax)
	testl	%eax, %eax
	popl	%esi
	popl	%edi
	je	.L1037
	movb	$0, savedScreenInfo+8(%ebx)
	jmp	.L1018
.L1037:
	cmpl	$0, ScreenSaverAllowExposures
	je	.L1039
	pushl	$3
	pushl	%ebp
	call	TileScreenSaver
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	je	.L1036
	movb	$3, savedScreenInfo+8(%ebx)
	jmp	.L1018
.L1036:
	cmpl	$0, ScreenSaverAllowExposures
	je	.L1039
	pushl	$2
	pushl	%ebp
	call	TileScreenSaver
	testl	%eax, %eax
	popl	%esi
	popl	%edi
	je	.L1039
	movl	%ebp, %eax
	sall	$4, %eax
	movb	$2, savedScreenInfo+8(%eax)
	jmp	.L1018
.L1039:
	movl	%ebp, %eax
	sall	$4, %eax
	movb	$1, savedScreenInfo+8(%eax)
.L1018:
	incl	%ebp
	cmpl	screenInfo+48, %ebp
	jl	.L1044
.L1049:
	movl	4(%esp), %eax
	cmpl	$0, 36(%esp)
	movl	%eax, screenIsSaved
	jne	.L1045
	call	SetScreenSaverTimer
.L1045:
	popl	%ecx
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	xorl	%eax, %eax
	popl	%ebp
	ret
	.size	dixSaveScreens, .-dixSaveScreens
	.align 4
.globl SaveScreens
	.type	SaveScreens, @function
SaveScreens:
	pushl	8(%esp)
	pushl	8(%esp)
	pushl	serverClient
	call	dixSaveScreens
	addl	$12, %esp
	ret
	.size	SaveScreens, .-SaveScreens
	.align 4
	.type	TileScreenSaver, @function
TileScreenSaver:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	xorl	%ebp, %ebp
	xorl	%edi, %edi
	cmpl	$2, 60(%esp)
	movl	$0, (%esp)
	je	.L1055
	cmpl	$3, 60(%esp)
	je	.L1061
	jmp	.L1054
.L1055:
	movl	WindowTable, %eax
	movl	56(%esp), %ecx
	movl	(%eax,%ecx,4), %edx
	movzbl	128(%edx), %eax
	andl	$3, %eax
	cmpl	$2, %eax
	je	.L1057
	cmpl	$3, %eax
	je	.L1058
	jmp	.L1054
.L1057:
	movl	112(%edx), %eax
	jmp	.L1085
.L1058:
	movl	$1, %edi
	movl	$1, %ebp
	movl	$0, 20(%esp)
	jmp	.L1054
.L1061:
	movl	WindowTable, %eax
	movl	56(%esp), %edx
	movl	(%eax,%edx,4), %eax
	movl	16(%eax), %eax
	movl	44(%eax), %eax
.L1085:
	movl	%eax, 20(%esp)
	movl	$1, %edi
	movl	$2, %ebp
.L1054:
	movl	$1, 20(%esp,%edi,4)
	movw	$16, 12(%esp)
	movw	$16, 14(%esp)
	movw	$8, 16(%esp)
	movw	$8, 18(%esp)
	pushl	$64
	call	Xalloc
	pushl	$64
	movl	%eax, %ebx
	call	Xalloc
	orl	$512, %ebp
	incl	%edi
	movl	%eax, %esi
	testl	%ebx, %ebx
	popl	%eax
	popl	%edx
	je	.L1065
	xorl	%eax, %eax
	testl	%esi, %esi
	jne	.L1071
.L1065:
	pushl	%ebx
	call	Xfree
	pushl	%esi
	call	Xfree
	movl	$0, 16(%esp)
	jmp	.L1086
.L1071:
	movb	$0, (%eax,%esi)
	movb	$0, (%eax,%ebx)
	incl	%eax
	cmpl	$63, %eax
	jle	.L1071
	pushl	$0
	pushl	serverClient
	leal	16(%esp), %eax
	pushl	%eax
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	leal	48(%esp), %eax
	pushl	%eax
	pushl	$0
	pushl	%esi
	pushl	%ebx
	call	AllocARGBCursor
	movl	%eax, 56(%esp)
	addl	$52, %esp
	cmpl	$0, 8(%esp)
	je	.L1072
	pushl	$0
	call	FakeClientID
	movl	%eax, 4(%esp)
	pushl	12(%esp)
	pushl	$5
	pushl	12(%esp)
	call	AddResource
	addl	$16, %esp
	testl	%eax, %eax
	je	.L1073
	movl	(%esp), %ecx
	orl	$16384, %ebp
	movl	%ecx, 20(%esp,%edi,4)
	jmp	.L1066
.L1073:
	movl	$0, 8(%esp)
	jmp	.L1066
.L1072:
	pushl	%ebx
	call	Xfree
	pushl	%esi
	call	Xfree
.L1086:
	popl	%ecx
	popl	%ebx
.L1066:
	leal	4(%esp), %eax
	movl	56(%esp), %edi
	pushl	%eax
	movl	60(%esp), %ecx
	movl	WindowTable, %eax
	movl	(%eax,%ecx,4), %edx
	movl	124(%edx), %eax
	sall	$4, %edi
	testl	%eax, %eax
	jne	.L1087
	pushl	%edx
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%edx
.L1087:
	movl	(%eax), %eax
	pushl	%eax
	pushl	serverClient
	pushl	$0
	leal	36(%esp), %eax
	pushl	%eax
	pushl	%ebp
	pushl	$1
	pushl	$0
	movl	88(%esp), %eax
	movl	screenInfo+52(,%eax,4), %edx
	movzwl	10(%edx), %eax
	addl	$32, %eax
	pushl	%eax
	movzwl	8(%edx), %eax
	addl	$32, %eax
	pushl	%eax
	pushl	$-32
	pushl	$-32
	movl	104(%esp), %edx
	movl	WindowTable, %eax
	movl	%edx, %esi
	pushl	(%eax,%edx,4)
	sall	$4, %esi
	pushl	savedScreenInfo+4(%esi)
	call	CreateWindow
	addl	$56, %esp
	cmpl	$0, 8(%esp)
	movl	%eax, %ebx
	movl	%eax, savedScreenInfo(%edi)
	je	.L1078
	pushl	$0
	pushl	4(%esp)
	call	FreeResource
	popl	%ecx
	popl	%edi
.L1078:
	xorl	%edx, %edx
	testl	%ebx, %ebx
	je	.L1053
	pushl	savedScreenInfo(%esi)
	pushl	$1073741825
	pushl	4(%ebx)
	call	AddResource
	addl	$12, %esp
	xorl	%edx, %edx
	testl	%eax, %eax
	je	.L1053
	andl	$1, %ebp
	je	.L1081
	pushl	%ebx
	call	MakeRootTile
	movl	16(%ebx), %eax
	pushl	$1
	pushl	%ebx
	call	*144(%eax)
	addl	$12, %esp
.L1081:
	pushl	serverClient
	pushl	%ebx
	call	MapWindow
	popl	%eax
	popl	%edx
	cmpl	$2, 60(%esp)
	jne	.L1082
	cmpl	$0, logoScreenSaver
	je	.L1082
	pushl	%ebx
	call	DrawLogo
	popl	%ebp
.L1082:
	movl	$1, %edx
.L1053:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	TileScreenSaver, .-TileScreenSaver
	.align 4
.globl FindWindowWithOptional
	.type	FindWindowWithOptional, @function
FindWindowWithOptional:
	movl	4(%esp), %eax
.L1089:
	movl	28(%eax), %eax
	cmpl	$0, 124(%eax)
	je	.L1089
	ret
	.size	FindWindowWithOptional, .-FindWindowWithOptional
	.align 4
.globl CheckWindowOptionalNeed
	.type	CheckWindowOptionalNeed, @function
CheckWindowOptionalNeed:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %esi
	cmpl	$0, 28(%esi)
	je	.L1093
	movw	130(%esi), %ax
	shrw	$6, %ax
	andl	$7, %eax
	movl	124(%esi), %ebx
	movl	DontPropagateMasks(,%eax,4), %eax
	cmpl	%eax, 12(%ebx)
	jne	.L1093
	cmpl	$0, 16(%ebx)
	jne	.L1093
	cmpl	$0, 20(%ebx)
	jne	.L1093
	cmpl	$0, 24(%ebx)
	jne	.L1093
	cmpl	$0, 28(%ebx)
	jne	.L1093
	cmpl	$-1, 32(%ebx)
	jne	.L1093
	cmpl	$0, 36(%ebx)
	jne	.L1093
	cmpl	$0, 40(%ebx)
	jne	.L1093
	cmpl	$0, 44(%ebx)
	jne	.L1093
	cmpl	$0, 48(%ebx)
	jne	.L1093
	cmpl	$0, 52(%ebx)
	jne	.L1093
	pushl	%esi
	call	FindWindowWithOptional
	movl	124(%eax), %edx
	movl	(%edx), %eax
	cmpl	%eax, (%ebx)
	popl	%ecx
	jne	.L1093
	movl	4(%ebx), %eax
	testl	%eax, %eax
	je	.L1107
	cmpl	4(%edx), %eax
	jne	.L1093
	movl	28(%esi), %eax
	testb	$8, 128(%eax)
	jne	.L1093
.L1107:
	movl	8(%edx), %eax
	cmpl	%eax, 8(%ebx)
	jne	.L1093
	movl	%esi, 12(%esp)
	popl	%ebx
	popl	%esi
	jmp	DisposeWindowOptional
.L1093:
	popl	%ebx
	popl	%esi
	ret
	.size	CheckWindowOptionalNeed, .-CheckWindowOptionalNeed
	.align 4
.globl MakeWindowOptional
	.type	MakeWindowOptional, @function
MakeWindowOptional:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %esi
	cmpl	$0, 124(%esi)
	jne	.L1115
	pushl	$56
	call	Xalloc
	movl	%eax, %ebx
	popl	%eax
	xorl	%eax, %eax
	testl	%ebx, %ebx
	je	.L1110
	movw	130(%esi), %ax
	shrw	$6, %ax
	andl	$7, %eax
	movl	DontPropagateMasks(,%eax,4), %eax
	movl	%eax, 12(%ebx)
	movl	$0, 16(%ebx)
	movl	$0, 20(%ebx)
	movl	$0, 24(%ebx)
	movl	$0, 28(%ebx)
	movl	$-1, 32(%ebx)
	movl	$0, 36(%ebx)
	movl	$0, 40(%ebx)
	movl	$0, 44(%ebx)
	movl	$0, 48(%ebx)
	movl	$0, 52(%ebx)
	pushl	%esi
	call	FindWindowWithOptional
	movl	124(%eax), %edx
	movl	(%edx), %eax
	movl	%eax, (%ebx)
	testb	$8, 128(%esi)
	popl	%eax
	jne	.L1113
	movl	4(%edx), %eax
	incl	16(%eax)
	movl	%eax, 4(%ebx)
	jmp	.L1114
.L1113:
	movl	$0, 4(%ebx)
.L1114:
	movl	8(%edx), %eax
	movl	%eax, 8(%ebx)
	movl	%ebx, 124(%esi)
.L1115:
	movl	$1, %eax
.L1110:
	popl	%ebx
	popl	%esi
	ret
	.size	MakeWindowOptional, .-MakeWindowOptional
	.align 4
	.type	DrawLogo, @function
DrawLogo:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$100, %esp
	movl	120(%esp), %eax
	movl	16(%eax), %ebx
	movswl	100(%eax),%edx
	movswl	102(%eax),%ecx
	negl	%edx
	movswl	8(%ebx),%eax
	negl	%ecx
	movl	%edx, 40(%esp)
	movl	%ecx, 36(%esp)
	movl	%eax, 32(%esp)
	movswl	10(%ebx),%esi
	pushl	%ebx
	movzbl	18(%ebx), %eax
	pushl	%eax
	call	GetScratchGC
	movl	%eax, %edi
	testl	%edi, %edi
	popl	%eax
	popl	%edx
	je	.L1116
	call	rand
	movl	$100, %edx
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	cmpl	$17, %edx
	jg	.L1118
	movl	40(%ebx), %eax
	jmp	.L1132
.L1118:
	movl	44(%ebx), %eax
.L1132:
	movl	%eax, 52(%esp)
	movl	120(%esp), %edx
	movzbl	128(%edx), %eax
	andl	$3, %eax
	cmpl	$2, %eax
	jne	.L1120
	pushl	$6
	cmpb	$2, 1(%edx)
	je	.L1121
	movl	124(%edx), %eax
	testl	%eax, %eax
	jne	.L1133
	pushl	124(%esp)
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%ebp
.L1133:
	movl	8(%eax), %eax
	jmp	.L1122
.L1121:
	xorl	%eax, %eax
.L1122:
	pushl	%eax
	call	LookupIDByType
	movl	%eax, %edx
	testl	%edx, %edx
	popl	%eax
	popl	%ecx
	je	.L1120
	movl	52(%esp), %eax
	movl	%eax, 60(%esp)
	movl	120(%esp), %ecx
	movl	112(%ecx), %eax
	movl	%eax, 64(%esp)
	leal	68(%esp), %eax
	pushl	%eax
	leal	64(%esp), %eax
	pushl	%eax
	pushl	$2
	pushl	%edx
	call	QueryColors
	addl	$16, %esp
	movl	76(%esp), %eax
	cmpw	%ax, 68(%esp)
	jne	.L1120
	movw	78(%esp), %ax
	cmpw	%ax, 70(%esp)
	jne	.L1120
	movl	80(%esp), %eax
	cmpw	%ax, 72(%esp)
	jne	.L1120
	movl	44(%ebx), %eax
	cmpl	%eax, 52(%esp)
	jne	.L1126
	movl	40(%ebx), %eax
.L1126:
	movl	%eax, 52(%esp)
.L1120:
	movl	$0, 56(%esp)
	movl	120(%esp), %ebx
	movzbl	128(%ebx), %eax
	andl	$3, %eax
	cmpl	$2, %eax
	jne	.L1128
	movl	112(%ebx), %eax
	movl	%eax, 44(%esp)
	movl	$0, 48(%esp)
	movl	$260, 20(%esp)
	jmp	.L1129
.L1128:
	leal	44(%esp), %eax
	movl	$0, 44(%esp)
	movl	$0, 48(%esp)
	pushl	%eax
	pushl	$0
	pushl	$12288
	pushl	%edi
	pushl	$0
	call	dixChangeGC
	movl	$1, 64(%esp)
	movl	140(%esp), %edx
	movl	112(%edx), %eax
	movl	%eax, 68(%esp)
	movl	$1280, 40(%esp)
	addl	$20, %esp
.L1129:
	movl	32(%esp), %ebp
	cmpl	%ebp, %esi
	jae	.L1130
	movl	%esi, %ebp
.L1130:
	call	rand
	leal	-32(%ebp), %edx
	movl	%edx, %ecx
	xorl	%edx, %edx
	divl	%ecx
	leal	32(%edx), %ebp
	andl	$-2, %ebp
	call	rand
	subl	%ebp, 32(%esp)
	xorl	%edx, %edx
	divl	32(%esp)
	addl	%edx, 40(%esp)
	subl	%ebp, %esi
	call	rand
	xorl	%edx, %edx
	divl	%esi
	addl	%edx, 36(%esp)
	movl	$11, %edx
	movl	%edx, %ecx
	movl	%ebp, %eax
	xorl	%edx, %edx
	divl	%ecx
	testl	%eax, %eax
	movl	%eax, 28(%esp)
	jg	.L1131
	movl	$1, 28(%esp)
.L1131:
	movl	28(%esp), %ecx
	addl	$3, %ecx
	movl	%ecx, %eax
	movl	$4, %edx
	movl	%edx, %ebx
	cltd
	movl	40(%esp), %ecx
	idivl	%ebx
	movl	28(%esp), %edx
	leal	(%eax,%edx,2), %edx
	addl	%ebp, %ecx
	movl	36(%esp), %ebx
	movl	%edx, 24(%esp)
	movw	%cx, 14(%esp)
	movw	%cx, 84(%esp)
	subw	%dx, %cx
	movl	40(%esp), %edx
	movw	%bx, 86(%esp)
	movw	%cx, 12(%esp)
	movw	%cx, 88(%esp)
	movw	%bx, 90(%esp)
	movl	%ebx, %ecx
	movl	%edx, %ebx
	addl	24(%esp), %ebx
	movl	%eax, 16(%esp)
	addl	%ebp, %ecx
	leal	52(%esp), %eax
	movw	%cx, 10(%esp)
	movw	%cx, 94(%esp)
	movw	%cx, 98(%esp)
	movw	%dx, 92(%esp)
	movw	%bx, 8(%esp)
	movw	%bx, 96(%esp)
	pushl	%eax
	pushl	$0
	pushl	$260
	pushl	%edi
	pushl	$0
	call	dixChangeGC
	pushl	%edi
	pushl	144(%esp)
	call	ValidateGC
	leal	112(%esp), %edx
	movl	72(%edi), %eax
	pushl	%edx
	pushl	$4
	pushl	$0
	pushl	$2
	pushl	%edi
	pushl	168(%esp)
	call	*40(%eax)
	movl	76(%esp), %eax
	movl	$2, %edx
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	movl	%eax, 56(%esp)
	movw	62(%esp), %bx
	movl	92(%esp), %eax
	addl	56(%esp), %eax
	movw	%bx, 138(%esp)
	movl	%ebp, %ebx
	movw	%ax, 136(%esp)
	shrl	%ebx
	movl	92(%esp), %esi
	movl	76(%esp), %eax
	addl	%ebx, %esi
	subw	56(%esp), %ax
	movw	%ax, 54(%esp)
	movl	%esi, %eax
	addl	88(%esp), %ebx
	movw	62(%esp), %cx
	addw	54(%esp), %ax
	movl	60(%esp), %edx
	movw	%cx, 150(%esp)
	movw	%dx, 148(%esp)
	movw	%si, 140(%esp)
	movw	%bx, 142(%esp)
	movw	%ax, 144(%esp)
	movw	%bx, 146(%esp)
	addl	$52, %esp
	leal	44(%esp), %eax
	pushl	%eax
	pushl	$0
	pushl	28(%esp)
	pushl	%edi
	pushl	$0
	call	dixChangeGC
	pushl	%edi
	pushl	144(%esp)
	call	ValidateGC
	leal	112(%esp), %edx
	movl	72(%edi), %eax
	pushl	%edx
	pushl	$4
	pushl	$0
	pushl	$2
	pushl	%edi
	pushl	168(%esp)
	call	*40(%eax)
	movw	66(%esp), %ax
	movl	88(%esp), %ecx
	subw	56(%esp), %ax
	movw	%si, 140(%esp)
	movw	%bx, 142(%esp)
	subw	54(%esp), %si
	movw	%bx, 146(%esp)
	movl	64(%esp), %ebx
	movw	%cx, 138(%esp)
	movw	%cx, 150(%esp)
	movw	%ax, 136(%esp)
	movw	%bx, 148(%esp)
	movw	%si, 144(%esp)
	addl	$52, %esp
	pushl	%edi
	pushl	124(%esp)
	call	ValidateGC
	leal	92(%esp), %edx
	movl	72(%edi), %eax
	pushl	%edx
	pushl	$4
	pushl	$0
	pushl	$2
	pushl	%edi
	pushl	148(%esp)
	call	*40(%eax)
	movl	72(%esp), %ecx
	movl	%ebp, %edx
	shrl	$2, %edx
	movl	%ecx, %eax
	addl	%edx, %eax
	movw	%cx, 116(%esp)
	movw	46(%esp), %cx
	movl	68(%esp), %ebx
	movw	%ax, 120(%esp)
	movl	%ecx, %eax
	subw	%dx, %ax
	movw	%bx, 118(%esp)
	movw	%bx, 122(%esp)
	movw	42(%esp), %bx
	movw	%cx, 124(%esp)
	movw	%bx, 126(%esp)
	movw	%ax, 128(%esp)
	movw	%bx, 130(%esp)
	addl	$32, %esp
	leal	52(%esp), %eax
	pushl	%eax
	pushl	$0
	pushl	$260
	pushl	%edi
	pushl	$0
	call	dixChangeGC
	pushl	%edi
	pushl	144(%esp)
	call	ValidateGC
	leal	112(%esp), %edx
	movl	72(%edi), %eax
	pushl	%edx
	pushl	$4
	pushl	$0
	pushl	$2
	pushl	%edi
	pushl	168(%esp)
	call	*40(%eax)
	movw	66(%esp), %ax
	subw	80(%esp), %ax
	movw	%ax, 136(%esp)
	movl	80(%esp), %eax
	addl	68(%esp), %eax
	subw	%ax, 66(%esp)
	movl	92(%esp), %eax
	addl	80(%esp), %eax
	movw	62(%esp), %dx
	movl	88(%esp), %ecx
	movw	66(%esp), %bx
	movw	%ax, 144(%esp)
	addl	68(%esp), %eax
	movw	%dx, 146(%esp)
	movw	%dx, 150(%esp)
	movw	%cx, 138(%esp)
	movw	%bx, 140(%esp)
	movw	%cx, 142(%esp)
	movw	%ax, 148(%esp)
	addl	$52, %esp
	leal	44(%esp), %ecx
	pushl	%ecx
	pushl	$0
	pushl	28(%esp)
	pushl	%edi
	pushl	$0
	call	dixChangeGC
	pushl	%edi
	pushl	144(%esp)
	leal	112(%esp), %ebx
	call	ValidateGC
	movl	72(%edi), %eax
	pushl	%ebx
	pushl	$4
	pushl	$0
	pushl	$2
	pushl	%edi
	pushl	168(%esp)
	call	*40(%eax)
	addl	$52, %esp
	pushl	%edi
	call	FreeScratchGC
	popl	%eax
.L1116:
	addl	$100, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	DrawLogo, .-DrawLogo
	.comm	savedScreenInfo,256,32
	.local	windowDisableMapUnmapEvents
	.comm	windowDisableMapUnmapEvents,4,4
	.ident	"GCC: (GNU) 3.3.2"
