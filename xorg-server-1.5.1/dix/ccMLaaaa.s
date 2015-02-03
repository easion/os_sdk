	.file	"colormap.c"
	.text
	.align 4
.globl CreateColormap
	.type	CreateColormap, @function
CreateColormap:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	movl	32(%esp), %eax
	movswl	4(%eax),%edi
	testl	$1, %edi
	jne	.L2
	cmpl	$0, 40(%esp)
	je	.L2
	cmpl	$0, 44(%esp)
	movl	$8, %edx
	jne	.L1
.L2:
	movl	32(%esp), %edx
	movl	%edi, %ecx
	orl	$1, %ecx
	movswl	8(%edx),%esi
	imull	$20, %esi, %ebp
	cmpl	$5, %ecx
	leal	2048(%ebp), %eax
	movl	%ecx, (%esp)
	jne	.L3
	imull	$3, %eax, %eax
.L3:
	addl	$76, %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, %ebx
	testl	%ebx, %ebx
	popl	%eax
	movl	$11, %edx
	je	.L1
	leal	76(%ebx), %eax
	movl	%eax, 56(%ebx)
	addl	%ebp, %eax
	movl	%eax, 44(%ebx)
	addl	$1024, %eax
	movl	%eax, 32(%ebx)
	movl	24(%esp), %eax
	movl	%eax, 8(%ebx)
	movl	28(%esp), %edx
	cmpl	28(%edx), %eax
	movw	$0, 16(%ebx)
	jne	.L5
	movw	$1, 16(%ebx)
.L5:
	movl	28(%esp), %ecx
	movl	32(%esp), %eax
	cmpl	$5, (%esp)
	movl	%ecx, 12(%ebx)
	movl	%eax, (%ebx)
	movw	%di, 4(%ebx)
	jne	.L6
	movl	32(%esp), %edx
	movl	12(%edx), %eax
	movl	24(%edx), %ecx
	shrl	%cl, %eax
	leal	1(%eax), %esi
.L6:
	movl	%esi, 20(%ebx)
	pushl	%ebp
	pushl	$0
	pushl	56(%ebx)
	call	memset
	pushl	$1024
	pushl	$0
	pushl	32(%ebx)
	call	memset
	movl	44(%ebx), %edx
	leal	1020(%edx), %eax
	addl	$24, %esp
	cmpl	%edx, %eax
	jb	.L53
.L11:
	movl	$0, (%eax)
	subl	$4, %eax
	cmpl	%edx, %eax
	jae	.L11
.L53:
	cmpl	$1, 40(%esp)
	jne	.L12
	testl	$1, %edi
	je	.L13
	orw	$2, 16(%ebx)
.L13:
	imull	$20, %esi, %eax
	movl	56(%ebx), %edx
	leal	-20(%eax,%edx), %eax
	cmpl	%edx, %eax
	jb	.L55
.L18:
	movw	$-1, 12(%eax)
	subl	$20, %eax
	cmpl	%edx, %eax
	jae	.L18
.L55:
	leal	0(,%esi,4), %eax
	movl	$0, 20(%ebx)
	pushl	%eax
	call	Xalloc
	movl	%eax, %edx
	testl	%edx, %edx
	popl	%eax
	jne	.L19
	pushl	%ebx
	call	Xfree
	movl	$11, %edx
	popl	%eax
	jmp	.L1
.L19:
	movl	44(%ebx), %eax
	movl	44(%esp), %ecx
	movl	%edx, (%eax,%ecx,4)
	xorl	%eax, %eax
	cmpl	%esi, %eax
	jge	.L57
.L24:
	movl	%eax, (%edx,%eax,4)
	incl	%eax
	cmpl	%esi, %eax
	jl	.L24
.L57:
	movl	32(%ebx), %eax
	movl	44(%esp), %edx
	movl	%esi, (%eax,%edx,4)
.L12:
	orl	$1, %edi
	cmpl	$5, %edi
	jne	.L25
	movl	32(%esp), %ecx
	movl	16(%ecx), %eax
	movl	%ecx, %esi
	movl	28(%ecx), %ecx
	shrl	%cl, %eax
	incl	%eax
	movl	%eax, 24(%ebx)
	movl	32(%ebx), %eax
	addl	$1024, %eax
	movl	%eax, 60(%ebx)
	addl	%ebp, %eax
	leal	1024(%eax), %edx
	movl	32(%esi), %ecx
	movl	%eax, 48(%ebx)
	movl	%edx, 36(%ebx)
	addl	$2048, %eax
	movl	20(%esi), %edx
	shrl	%cl, %edx
	movl	%eax, 64(%ebx)
	addl	%ebp, %eax
	incl	%edx
	movl	%eax, 52(%ebx)
	addl	$1024, %eax
	movl	%edx, 28(%ebx)
	movl	%eax, 40(%ebx)
	pushl	%ebp
	pushl	$0
	pushl	60(%ebx)
	call	memset
	pushl	%ebp
	pushl	$0
	pushl	64(%ebx)
	call	memset
	pushl	$1024
	pushl	44(%ebx)
	pushl	48(%ebx)
	call	memmove
	addl	$36, %esp
	pushl	$1024
	pushl	44(%ebx)
	pushl	52(%ebx)
	call	memmove
	pushl	$1024
	pushl	$0
	pushl	36(%ebx)
	call	memset
	pushl	$1024
	pushl	$0
	pushl	40(%ebx)
	call	memset
	addl	$36, %esp
	cmpl	$1, 40(%esp)
	jne	.L25
	movl	24(%ebx), %esi
	imull	$20, %esi, %eax
	movl	60(%ebx), %edx
	leal	-20(%eax,%edx), %eax
	cmpl	%edx, %eax
	jb	.L59
.L31:
	movw	$-1, 12(%eax)
	subl	$20, %eax
	cmpl	%edx, %eax
	jae	.L31
.L59:
	leal	0(,%esi,4), %eax
	movl	$0, 24(%ebx)
	pushl	%eax
	call	Xalloc
	testl	%eax, %eax
	movl	%eax, %edx
	popl	%ebp
	jne	.L32
	movl	44(%esp), %edx
	movl	44(%ebx), %eax
	pushl	(%eax,%edx,4)
	call	Xfree
	pushl	%ebx
	call	Xfree
	jmp	.L66
.L32:
	movl	48(%ebx), %eax
	movl	44(%esp), %ecx
	movl	%edx, (%eax,%ecx,4)
	xorl	%eax, %eax
	cmpl	%esi, %eax
	jge	.L61
.L37:
	movl	%eax, (%edx,%eax,4)
	incl	%eax
	cmpl	%esi, %eax
	jl	.L37
.L61:
	movl	36(%ebx), %eax
	movl	44(%esp), %edx
	movl	%esi, (%eax,%edx,4)
	movl	28(%ebx), %esi
	imull	$20, %esi, %eax
	movl	64(%ebx), %edx
	leal	-20(%eax,%edx), %eax
	cmpl	%edx, %eax
	jb	.L63
.L42:
	movw	$-1, 12(%eax)
	subl	$20, %eax
	cmpl	%edx, %eax
	jae	.L42
.L63:
	leal	0(,%esi,4), %eax
	movl	$0, 28(%ebx)
	pushl	%eax
	call	Xalloc
	testl	%eax, %eax
	movl	%eax, %edx
	popl	%edi
	jne	.L43
	movl	44(%esp), %ecx
	movl	48(%ebx), %eax
	pushl	(%eax,%ecx,4)
	call	Xfree
	movl	48(%esp), %esi
	movl	44(%ebx), %eax
	pushl	(%eax,%esi,4)
	call	Xfree
	pushl	%ebx
	call	Xfree
	movl	$11, %edx
	addl	$12, %esp
	jmp	.L1
.L43:
	movl	52(%ebx), %eax
	movl	44(%esp), %ecx
	movl	%edx, (%eax,%ecx,4)
	xorl	%eax, %eax
	cmpl	%esi, %eax
	jge	.L65
.L48:
	movl	%eax, (%edx,%eax,4)
	incl	%eax
	cmpl	%esi, %eax
	jl	.L48
.L65:
	movl	40(%ebx), %eax
	movl	44(%esp), %edx
	movl	%esi, (%eax,%edx,4)
.L25:
	orw	$4, 16(%ebx)
	movl	$0, 72(%ebx)
	pushl	%ebx
	pushl	$6
	pushl	32(%esp)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	movl	$11, %edx
	je	.L1
	pushl	%ebx
	movl	32(%esp), %ecx
	call	*284(%ecx)
	testl	%eax, %eax
	popl	%esi
	jne	.L51
	pushl	$0
	pushl	28(%esp)
	call	FreeResource
.L66:
	popl	%ecx
	movl	$11, %edx
	popl	%ebx
	jmp	.L1
.L51:
	movl	36(%esp), %eax
	andw	$-5, 16(%ebx)
	movl	%ebx, (%eax)
	xorl	%edx, %edx
.L1:
	movl	%edx, %eax
	popl	%edx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	CreateColormap, .-CreateColormap
	.align 4
.globl FreeColormap
	.type	FreeColormap, @function
FreeColormap:
	pushl	%esi
	pushl	%ebx
	testl	$534773760, 16(%esp)
	movl	12(%esp), %esi
	je	.L68
	movl	12(%esi), %eax
	pushl	%esi
	call	*296(%eax)
	leal	20(%esp), %eax
	pushl	%eax
	pushl	$TellNoMap
	pushl	12(%esi)
	call	WalkTree
	addl	$16, %esp
.L68:
	movl	12(%esi), %eax
	pushl	%esi
	call	*288(%eax)
	cmpl	$0, 44(%esi)
	popl	%eax
	je	.L69
	xorl	%ebx, %ebx
.L74:
	movl	44(%esi), %eax
	pushl	(%eax,%ebx,4)
	incl	%ebx
	call	Xfree
	cmpl	$255, %ebx
	popl	%eax
	jle	.L74
.L69:
	movw	4(%esi), %ax
	cmpw	$3, %ax
	je	.L76
	decw	%ax
	jne	.L75
.L76:
	movl	(%esi), %eax
	movswl	8(%eax),%eax
	imull	$20, %eax, %eax
	movl	56(%esi), %edx
	leal	-20(%eax,%edx), %ebx
	cmpl	%edx, %ebx
	jb	.L75
.L85:
	cmpl	$0, 16(%ebx)
	je	.L79
	movl	(%ebx), %eax
	movw	2(%eax), %dx
	decl	%edx
	testw	%dx, %dx
	movw	%dx, 2(%eax)
	jne	.L82
	pushl	(%ebx)
	call	Xfree
	popl	%eax
.L82:
	movl	4(%ebx), %eax
	movw	2(%eax), %dx
	decl	%edx
	testw	%dx, %dx
	movw	%dx, 2(%eax)
	jne	.L83
	pushl	4(%ebx)
	call	Xfree
	popl	%eax
.L83:
	movl	8(%ebx), %eax
	movw	2(%eax), %dx
	decl	%edx
	testw	%dx, %dx
	movw	%dx, 2(%eax)
	jne	.L79
	pushl	8(%ebx)
	call	Xfree
	popl	%eax
.L79:
	subl	$20, %ebx
	cmpl	56(%esi), %ebx
	jae	.L85
.L75:
	movw	4(%esi), %ax
	orl	$1, %eax
	cmpw	$5, %ax
	jne	.L86
	xorl	%ebx, %ebx
.L91:
	movl	48(%esi), %eax
	pushl	(%eax,%ebx,4)
	call	Xfree
	movl	52(%esi), %eax
	pushl	(%eax,%ebx,4)
	incl	%ebx
	call	Xfree
	popl	%ecx
	cmpl	$255, %ebx
	popl	%eax
	jle	.L91
.L86:
	pushl	72(%esi)
	call	dixFreePrivates
	pushl	%esi
	call	Xfree
	popl	%eax
	popl	%edx
	popl	%ebx
	xorl	%eax, %eax
	popl	%esi
	ret
	.size	FreeColormap, .-FreeColormap
	.align 4
	.type	TellNoMap, @function
TellNoMap:
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	44(%esp), %esi
	movl	48(%esp), %eax
	cmpb	$2, 1(%esi)
	movl	(%eax), %ebx
	je	.L97
	movl	124(%esi), %eax
	testl	%eax, %eax
	jne	.L103
	pushl	%esi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%ecx
.L103:
	cmpl	%ebx, 8(%eax)
	jmp	.L102
.L97:
	testl	%ebx, %ebx
.L102:
	jne	.L96
	movb	$32, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	movl	$0, 8(%esp)
	movb	$1, 12(%esp)
	movb	$0, 13(%esp)
	pushl	$0
	pushl	$1
	leal	8(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	DeliverEvents
	movl	124(%esi), %eax
	addl	$16, %esp
	testl	%eax, %eax
	je	.L96
	movl	$0, 8(%eax)
	pushl	%esi
	call	CheckWindowOptionalNeed
	popl	%edx
.L96:
	addl	$32, %esp
	popl	%ebx
	movl	$1, %eax
	popl	%esi
	ret
	.size	TellNoMap, .-TellNoMap
	.align 4
.globl TellLostMap
	.type	TellLostMap, @function
TellLostMap:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	48(%esp), %esi
	movl	52(%esp), %edi
	cmpb	$2, 1(%esi)
	movl	(%edi), %ebx
	je	.L106
	movl	124(%esi), %eax
	testl	%eax, %eax
	jne	.L111
	pushl	%esi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%edx
.L111:
	cmpl	%ebx, 8(%eax)
	jmp	.L110
.L106:
	testl	%ebx, %ebx
.L110:
	jne	.L105
	movb	$32, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	movl	(%edi), %eax
	movl	%eax, 8(%esp)
	movb	$0, 12(%esp)
	movb	$0, 13(%esp)
	pushl	$0
	pushl	$1
	leal	8(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	DeliverEvents
	addl	$16, %esp
.L105:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	movl	$1, %eax
	popl	%edi
	ret
	.size	TellLostMap, .-TellLostMap
	.align 4
.globl TellGainedMap
	.type	TellGainedMap, @function
TellGainedMap:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	48(%esp), %esi
	movl	52(%esp), %edi
	cmpb	$2, 1(%esi)
	movl	(%edi), %ebx
	je	.L114
	movl	124(%esi), %eax
	testl	%eax, %eax
	jne	.L119
	pushl	%esi
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%ecx
.L119:
	cmpl	%ebx, 8(%eax)
	jmp	.L118
.L114:
	testl	%ebx, %ebx
.L118:
	jne	.L113
	movb	$32, (%esp)
	movl	4(%esi), %eax
	movl	%eax, 4(%esp)
	movl	(%edi), %eax
	movl	%eax, 8(%esp)
	movb	$0, 12(%esp)
	movb	$1, 13(%esp)
	pushl	$0
	pushl	$1
	leal	8(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	DeliverEvents
	addl	$16, %esp
.L113:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	movl	$1, %eax
	popl	%edi
	ret
	.size	TellGainedMap, .-TellGainedMap
	.align 4
.globl CopyColormapAndFree
	.type	CopyColormapAndFree, @function
CopyColormapAndFree:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%edi
	movl	28(%esp), %esi
	xorl	%ebx, %ebx
	testb	$2, 16(%esi)
	movl	32(%esp), %ebp
	movl	$0, (%esp)
	movl	12(%esi), %ecx
	movl	(%esi), %edx
	movl	8(%esi), %eax
	je	.L121
	andl	$534773760, %eax
	shrl	$21, %eax
	cmpl	%ebp, %eax
	jne	.L121
	movl	$1, %ebx
.L121:
	movswl	8(%edx),%edi
	pushl	%ebp
	pushl	%ebx
	leal	8(%esp), %eax
	pushl	%eax
	pushl	%edx
	pushl	%ecx
	pushl	44(%esp)
	call	CreateColormap
	addl	$24, %esp
	testl	%eax, %eax
	jne	.L120
	decl	%ebx
	jne	.L123
	imull	$20, %edi, %ebx
	pushl	%ebx
	pushl	56(%esi)
	movl	8(%esp), %eax
	pushl	56(%eax)
	call	memmove
	movl	12(%esp), %edx
	movw	4(%edx), %ax
	orl	$1, %eax
	addl	$12, %esp
	cmpw	$5, %ax
	jne	.L124
	pushl	%ebx
	pushl	60(%esi)
	pushl	60(%edx)
	call	memmove
	pushl	%ebx
	pushl	64(%esi)
	movl	20(%esp), %eax
	pushl	64(%eax)
	call	memmove
	addl	$24, %esp
.L124:
	andw	$-3, 16(%esi)
	pushl	%ebp
	pushl	%esi
	call	FreePixels
	pushl	8(%esp)
	call	UpdateColors
	xorl	%eax, %eax
	addl	$12, %esp
	jmp	.L120
.L123:
	pushl	(%esp)
	pushl	%esi
	pushl	%ebp
	pushl	$0
	call	CopyFree
	movl	16(%esp), %edx
	movw	4(%edx), %ax
	orl	$1, %eax
	addl	$16, %esp
	cmpw	$5, %ax
	jne	.L125
	pushl	%edx
	pushl	%esi
	pushl	%ebp
	pushl	$1
	call	CopyFree
	pushl	16(%esp)
	pushl	%esi
	pushl	%ebp
	pushl	$2
	call	CopyFree
	addl	$32, %esp
.L125:
	movl	(%esp), %eax
	testb	$1, 4(%eax)
	je	.L126
	pushl	%eax
	call	UpdateColors
	popl	%esi
.L126:
	xorl	%eax, %eax
.L120:
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	CopyColormapAndFree, .-CopyColormapAndFree
	.align 4
	.type	CopyFree, @function
CopyFree:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	cmpl	$1, 40(%esp)
	movl	44(%esp), %ebp
	je	.L131
	cmpl	$1, 40(%esp)
	jle	.L130
	cmpl	$2, 40(%esp)
	je	.L132
.L130:
	movl	48(%esp), %edx
	movl	44(%edx), %eax
	movl	(%eax,%ebp,4), %eax
	movl	%eax, 4(%esp)
	movl	32(%edx), %eax
	movl	56(%edx), %edx
	movl	%edx, 12(%esp)
	movl	52(%esp), %edx
	movl	(%eax,%ebp,4), %eax
	movl	56(%edx), %edx
	jmp	.L153
.L131:
	movl	48(%esp), %edx
	movl	48(%edx), %eax
	movl	(%eax,%ebp,4), %eax
	movl	%eax, 4(%esp)
	movl	36(%edx), %eax
	movl	60(%edx), %edx
	movl	%edx, 12(%esp)
	movl	52(%esp), %edx
	movl	(%eax,%ebp,4), %eax
	movl	60(%edx), %edx
	jmp	.L153
.L132:
	movl	48(%esp), %edx
	movl	52(%edx), %eax
	movl	(%eax,%ebp,4), %eax
	movl	%eax, 4(%esp)
	movl	40(%edx), %eax
	movl	64(%edx), %edx
	movl	%edx, 12(%esp)
	movl	52(%esp), %edx
	movl	(%eax,%ebp,4), %eax
	movl	64(%edx), %edx
.L153:
	movl	%edx, 8(%esp)
	movl	48(%esp), %edx
	testb	$1, 4(%edx)
	movl	$0, (%esp)
	je	.L135
	decl	%eax
	movl	%eax, 16(%esp)
	js	.L135
.L144:
	movl	4(%esp), %edx
	imull	$20, (%edx), %eax
	movl	8(%esp), %edx
	addl	%eax, %edx
	movl	12(%esp), %ebx
	addl	%eax, %ebx
	movw	12(%edx), %ax
	testw	%ax, %ax
	jle	.L140
	incl	%eax
	movw	%ax, 12(%edx)
	jmp	.L141
.L140:
	cld
	movl	$5, %ecx
	movl	%edx, %edi
	movl	%ebx, %esi
	rep
	movsl
	incl	(%esp)
	cmpw	$0, 12(%ebx)
	jle	.L142
	movw	$1, 12(%edx)
	jmp	.L141
.L142:
	movl	$0, 16(%ebx)
.L141:
	pushl	40(%esp)
	movl	8(%esp), %eax
	pushl	(%eax)
	pushl	56(%esp)
	call	FreeCell
	addl	$12, %esp
	addl	$4, 4(%esp)
	decl	16(%esp)
	jns	.L144
.L135:
	cmpl	$1, 40(%esp)
	je	.L147
	cmpl	$1, 40(%esp)
	jg	.L151
	cmpl	$0, 40(%esp)
	je	.L146
	jmp	.L127
.L151:
	cmpl	$2, 40(%esp)
	je	.L148
	jmp	.L127
.L146:
	movl	52(%esp), %edx
	movl	(%esp), %eax
	subl	%eax, 20(%edx)
	movl	48(%esp), %eax
	movl	44(%edx), %ecx
	movl	44(%eax), %edx
	movl	(%edx,%ebp,4), %eax
	movl	%eax, (%ecx,%ebp,4)
	movl	$0, (%edx,%ebp,4)
	movl	48(%esp), %eax
	movl	52(%esp), %edx
	movl	32(%edx), %ecx
	movl	32(%eax), %edx
	jmp	.L154
.L147:
	movl	52(%esp), %edx
	movl	(%esp), %eax
	subl	%eax, 24(%edx)
	movl	48(%esp), %eax
	movl	48(%edx), %ecx
	movl	48(%eax), %edx
	movl	(%edx,%ebp,4), %eax
	movl	%eax, (%ecx,%ebp,4)
	movl	$0, (%edx,%ebp,4)
	movl	48(%esp), %eax
	movl	52(%esp), %edx
	movl	36(%edx), %ecx
	movl	36(%eax), %edx
	jmp	.L154
.L148:
	movl	52(%esp), %edx
	movl	(%esp), %eax
	subl	%eax, 28(%edx)
	movl	48(%esp), %eax
	movl	52(%edx), %ecx
	movl	52(%eax), %edx
	movl	(%edx,%ebp,4), %eax
	movl	%eax, (%ecx,%ebp,4)
	movl	$0, (%edx,%ebp,4)
	movl	48(%esp), %eax
	movl	52(%esp), %edx
	movl	40(%edx), %ecx
	movl	40(%eax), %edx
.L154:
	movl	(%edx,%ebp,4), %eax
	movl	%eax, (%ecx,%ebp,4)
	movl	$0, (%edx,%ebp,4)
.L127:
	addl	$20, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	CopyFree, .-CopyFree
	.align 4
	.type	FreeCell, @function
FreeCell:
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %edx
	cmpl	$1, %edx
	movl	12(%esp), %ecx
	movl	16(%esp), %eax
	je	.L160
	cmpl	$1, %edx
	jle	.L159
	cmpl	$2, %edx
	je	.L161
.L159:
	imull	$20, %eax, %ebx
	addl	56(%ecx), %ebx
	leal	20(%ecx), %esi
	jmp	.L156
.L160:
	imull	$20, %eax, %ebx
	addl	60(%ecx), %ebx
	leal	24(%ecx), %esi
	jmp	.L156
.L161:
	imull	$20, %eax, %ebx
	addl	64(%ecx), %ebx
	leal	28(%ecx), %esi
.L156:
	movw	12(%ebx), %ax
	cmpw	$1, %ax
	jle	.L164
	decl	%eax
	movw	%ax, 12(%ebx)
	jmp	.L155
.L164:
	cmpl	$0, 16(%ebx)
	je	.L166
	movl	(%ebx), %eax
	movw	2(%eax), %dx
	decl	%edx
	testw	%dx, %dx
	movw	%dx, 2(%eax)
	jne	.L167
	pushl	(%ebx)
	call	Xfree
	popl	%eax
.L167:
	movl	4(%ebx), %eax
	movw	2(%eax), %dx
	decl	%edx
	testw	%dx, %dx
	movw	%dx, 2(%eax)
	jne	.L168
	pushl	4(%ebx)
	call	Xfree
	popl	%eax
.L168:
	movl	8(%ebx), %eax
	movw	2(%eax), %dx
	decl	%edx
	testw	%dx, %dx
	movw	%dx, 2(%eax)
	jne	.L169
	pushl	8(%ebx)
	call	Xfree
	popl	%eax
.L169:
	movl	$0, 16(%ebx)
.L166:
	movw	$0, 12(%ebx)
	incl	(%esi)
.L155:
	popl	%ebx
	popl	%esi
	ret
	.size	FreeCell, .-FreeCell
	.align 4
	.type	UpdateColors, @function
UpdateColors:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	36(%esp), %esi
	movl	(%esi), %ebp
	movswl	8(%ebp),%eax
	movl	%eax, 4(%esp)
	imull	$12, %eax, %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, 16(%esp)
	popl	%eax
	cmpl	$0, 12(%esp)
	je	.L170
	cmpw	$5, 4(%esi)
	movl	$0, 8(%esp)
	movl	12(%esp), %ebx
	jne	.L172
	xorl	%edi, %edi
	movl	4(%esp), %edx
	cmpl	%edx, %edi
	jge	.L179
.L178:
	movl	56(%esi), %ecx
	imull	$20, %edi, %edx
	cmpw	$0, 12(%ecx,%edx)
	movl	%ecx, (%esp)
	jne	.L177
	movl	60(%esi), %eax
	cmpw	$0, 12(%eax,%edx)
	jne	.L177
	movl	64(%esi), %eax
	cmpw	$0, 12(%eax,%edx)
	je	.L175
.L177:
	movl	24(%ebp), %ecx
	movl	%edi, %eax
	sall	%cl, %eax
	movl	%edi, %edx
	movl	28(%ebp), %ecx
	sall	%cl, %edx
	orl	%edx, %eax
	movl	32(%ebp), %ecx
	movl	%edi, %edx
	sall	%cl, %edx
	orl	%edx, %eax
	movl	%eax, (%ebx)
	imull	$20, %edi, %edx
	movl	(%esp), %ecx
	movw	(%ecx,%edx), %ax
	movw	%ax, 4(%ebx)
	movl	60(%esi), %eax
	movw	2(%eax,%edx), %ax
	movw	%ax, 6(%ebx)
	movl	64(%esi), %eax
	movw	4(%eax,%edx), %ax
	movb	$7, 10(%ebx)
	movw	%ax, 8(%ebx)
	incl	8(%esp)
	addl	$12, %ebx
.L175:
	incl	%edi
	cmpl	4(%esp), %edi
	jl	.L178
	jmp	.L179
.L172:
	movl	4(%esp), %eax
	xorl	%edi, %edi
	cmpl	%eax, 8(%esp)
	movl	56(%esi), %edx
	jge	.L188
.L187:
	cmpw	$0, 12(%edx)
	je	.L182
	cmpl	$0, 16(%edx)
	movl	%edi, (%ebx)
	je	.L185
	movl	(%edx), %eax
	movw	(%eax), %ax
	movw	%ax, 4(%ebx)
	movl	4(%edx), %eax
	movw	(%eax), %ax
	movw	%ax, 6(%ebx)
	movl	8(%edx), %eax
	movw	(%eax), %ax
	jmp	.L193
.L185:
	movw	(%edx), %ax
	movw	%ax, 4(%ebx)
	movw	2(%edx), %ax
	movw	%ax, 6(%ebx)
	movw	4(%edx), %ax
.L193:
	movb	$7, 10(%ebx)
	movw	%ax, 8(%ebx)
	incl	8(%esp)
	addl	$12, %ebx
.L182:
	incl	%edi
	addl	$20, %edx
	cmpl	4(%esp), %edi
	jl	.L187
.L179:
	cmpl	$0, 8(%esp)
	je	.L188
	movl	12(%esi), %eax
	pushl	12(%esp)
	pushl	12(%esp)
	pushl	%esi
	call	*304(%eax)
	addl	$12, %esp
.L188:
	movl	12(%esp), %edx
	movl	%edx, 36(%esp)
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	Xfree
.L170:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	UpdateColors, .-UpdateColors
	.align 4
.globl AllocColor
	.type	AllocColor, @function
AllocColor:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	movl	40(%esp), %ebp
	movl	(%ebp), %edi
	movl	12(%ebp), %eax
	pushl	%edi
	pushl	56(%esp)
	pushl	56(%esp)
	pushl	56(%esp)
	call	*308(%eax)
	movl	60(%esp), %edx
	movw	(%edx), %ax
	movw	%ax, 28(%esp)
	movl	64(%esp), %ecx
	movw	(%ecx), %ax
	movw	%ax, 30(%esp)
	movl	68(%esp), %ebx
	movw	(%ebx), %ax
	movw	%ax, 32(%esp)
	addl	$16, %esp
	testb	$4, 16(%ebp)
	movswl	4(%ebp),%eax
	movswl	8(%edi),%esi
	je	.L195
	orl	$1, %eax
.L195:
	cmpl	$5, %eax
	ja	.L196
	jmp	*.L215(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L215:
	.long	.L198
	.long	.L205
	.long	.L198
	.long	.L205
	.long	.L200
	.long	.L209
	.text
.L198:
	pushl	$3
	leal	16(%esp), %eax
	pushl	%eax
	pushl	%esi
	pushl	56(%ebp)
	call	FindBestPixel
	movl	72(%esp), %edx
	movl	%eax, 24(%esp)
	movl	56(%ebp), %ecx
	movl	%eax, (%edx)
	imull	$20, %eax, %eax
	movw	(%ecx,%eax), %dx
	movl	60(%esp), %ebx
	movw	%dx, (%ebx)
	movw	2(%ecx,%eax), %dx
	movl	64(%esp), %esi
	movw	%dx, (%esi)
	movw	4(%ecx,%eax), %ax
	movl	68(%esp), %edx
	movl	76(%esp), %ecx
	movw	%ax, (%edx)
	movl	32(%ebp), %eax
	movl	(%eax,%ecx,4), %ebx
	leal	4(,%ebx,4), %eax
	pushl	%eax
	movl	44(%ebp), %eax
	pushl	(%eax,%ecx,4)
	call	Xrealloc
	addl	$24, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	movl	$11, %ecx
	je	.L194
	movl	8(%esp), %eax
	movl	%eax, (%edx,%ebx,4)
	movl	44(%ebp), %eax
	movl	60(%esp), %ebx
	movl	%edx, (%eax,%ebx,4)
	movl	32(%ebp), %eax
	incl	(%eax,%ebx,4)
	jmp	.L196
.L200:
	pushl	$0
	leal	16(%esp), %esi
	pushl	%esi
	movl	24(%edi), %ecx
	movl	12(%edi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	56(%ebp)
	call	FindBestPixel
	movl	%eax, 24(%esp)
	pushl	$1
	leal	32(%esp), %eax
	pushl	%eax
	movl	28(%edi), %ecx
	movl	16(%edi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	60(%ebp)
	call	FindBestPixel
	movl	%eax, 36(%esp)
	addl	$32, %esp
	pushl	$2
	leal	16(%esp), %edx
	pushl	%edx
	movl	32(%edi), %ecx
	movl	20(%edi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	64(%ebp)
	call	FindBestPixel
	movl	24(%esp), %ebx
	movl	24(%edi), %ecx
	movl	%ebx, %edx
	movl	20(%esp), %esi
	sall	%cl, %edx
	movl	28(%edi), %ecx
	sall	%cl, %esi
	orl	%esi, %edx
	movl	32(%edi), %ecx
	movl	%eax, %esi
	sall	%cl, %esi
	orl	%esi, %edx
	movl	72(%esp), %ecx
	movl	%eax, 16(%esp)
	imull	$20, %ebx, %ebx
	movl	%edx, (%ecx)
	movl	56(%ebp), %edx
	movw	(%edx,%ebx), %dx
	movl	60(%esp), %ebx
	movw	%dx, (%ebx)
	imull	$20, 20(%esp), %esi
	movl	60(%ebp), %edx
	movw	2(%edx,%esi), %dx
	movl	64(%esp), %esi
	movw	%dx, (%esi)
	imull	$20, %eax, %eax
	movl	64(%ebp), %edx
	movw	4(%edx,%eax), %ax
	movl	68(%esp), %edx
	movl	76(%esp), %ecx
	movw	%ax, (%edx)
	movl	32(%ebp), %eax
	movl	(%eax,%ecx,4), %ebx
	leal	4(,%ebx,4), %eax
	pushl	%eax
	movl	44(%ebp), %eax
	pushl	(%eax,%ecx,4)
	call	Xrealloc
	addl	$24, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	movl	$11, %ecx
	je	.L194
	movl	8(%esp), %eax
	movl	%eax, (%edx,%ebx,4)
	movl	60(%esp), %ebx
	movl	44(%ebp), %eax
	movl	%edx, (%eax,%ebx,4)
	movl	36(%ebp), %eax
	movl	%ebx, %esi
	movl	(%eax,%ebx,4), %ebx
	leal	4(,%ebx,4), %eax
	pushl	%eax
	movl	48(%ebp), %eax
	pushl	(%eax,%esi,4)
	call	Xrealloc
	movl	%eax, %edx
	popl	%edi
	testl	%edx, %edx
	popl	%eax
	movl	$11, %ecx
	je	.L194
	movl	4(%esp), %eax
	movl	%eax, (%edx,%ebx,4)
	movl	48(%ebp), %eax
	movl	%edx, (%eax,%esi,4)
	movl	40(%ebp), %eax
	movl	(%eax,%esi,4), %ebx
	leal	4(,%ebx,4), %eax
	pushl	%eax
	movl	52(%ebp), %eax
	pushl	(%eax,%esi,4)
	call	Xrealloc
	movl	%eax, %edx
	testl	%edx, %edx
	popl	%eax
	popl	%ecx
	movl	$11, %ecx
	je	.L194
	movl	(%esp), %eax
	movl	%eax, (%edx,%ebx,4)
	movl	52(%ebp), %eax
	movl	%edx, (%eax,%esi,4)
	movl	32(%ebp), %eax
	incl	(%eax,%esi,4)
	movl	36(%ebp), %eax
	incl	(%eax,%esi,4)
	movl	40(%ebp), %eax
	incl	(%eax,%esi,4)
	jmp	.L196
.L205:
	movl	12(%ebp), %ecx
	movl	28(%ecx), %eax
	cmpl	%eax, 8(%ebp)
	je	.L206
	movl	(%ebp), %edx
	movl	24(%ecx), %eax
	cmpl	%eax, (%edx)
	jne	.L206
	pushl	$1
	pushl	$6
	pushl	28(%ecx)
	movl	72(%esp), %edx
	movl	clients, %eax
	pushl	(%eax,%edx,4)
	call	SecurityLookupIDByType
	movl	%eax, %edx
	movw	4(%eax), %ax
	addl	$16, %esp
	cmpw	%ax, 4(%ebp)
	jne	.L206
	pushl	$AllComp
	pushl	$3
	pushl	64(%esp)
	leal	24(%esp), %ecx
	pushl	%ecx
	pushl	%esi
	pushl	56(%edx)
	pushl	%edx
	call	FindColorInRootCmap
	addl	$28, %esp
.L206:
	pushl	$AllComp
	pushl	64(%esp)
	pushl	$3
	pushl	68(%esp)
	leal	28(%esp), %eax
	pushl	%eax
	pushl	%esi
	pushl	56(%ebp)
	pushl	%ebp
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	movl	$11, %ecx
	jne	.L194
	jmp	.L196
.L209:
	movl	12(%ebp), %ecx
	movl	28(%ecx), %eax
	cmpl	%eax, 8(%ebp)
	je	.L210
	movl	(%ebp), %edx
	movl	24(%ecx), %eax
	cmpl	%eax, (%edx)
	jne	.L210
	pushl	$1
	pushl	$6
	pushl	28(%ecx)
	movl	72(%esp), %ebx
	movl	clients, %eax
	pushl	(%eax,%ebx,4)
	call	SecurityLookupIDByType
	movl	%eax, %ebx
	movw	4(%eax), %ax
	addl	$16, %esp
	cmpw	%ax, 4(%ebp)
	jne	.L210
	movl	56(%esp), %edx
	movl	12(%edi), %eax
	andl	(%edx), %eax
	movl	24(%edi), %ecx
	shrl	%cl, %eax
	movl	%eax, 8(%esp)
	pushl	$RedComp
	pushl	$0
	leal	16(%esp), %eax
	pushl	%eax
	leal	24(%esp), %ecx
	pushl	%ecx
	pushl	%esi
	pushl	56(%ebx)
	pushl	%ebx
	call	FindColorInRootCmap
	movl	84(%esp), %edx
	movl	16(%edi), %eax
	andl	(%edx), %eax
	movl	28(%edi), %ecx
	shrl	%cl, %eax
	movl	%eax, 32(%esp)
	pushl	$GreenComp
	pushl	$1
	leal	40(%esp), %eax
	pushl	%eax
	leal	52(%esp), %ecx
	pushl	%ecx
	pushl	%esi
	pushl	60(%ebx)
	pushl	%ebx
	call	FindColorInRootCmap
	movl	20(%edi), %eax
	movl	112(%esp), %edx
	andl	(%edx), %eax
	movl	32(%edi), %ecx
	shrl	%cl, %eax
	movl	%eax, 56(%esp)
	addl	$56, %esp
	pushl	$BlueComp
	pushl	$2
	leal	8(%esp), %eax
	pushl	%eax
	leal	24(%esp), %ecx
	pushl	%ecx
	pushl	%esi
	pushl	64(%ebx)
	pushl	%ebx
	call	FindColorInRootCmap
	movl	32(%esp), %eax
	orl	36(%esp), %eax
	orl	28(%esp), %eax
	movl	84(%esp), %ebx
	movl	%eax, (%ebx)
	addl	$28, %esp
.L210:
	movl	56(%esp), %esi
	movl	12(%edi), %eax
	andl	(%esi), %eax
	movl	24(%edi), %ecx
	shrl	%cl, %eax
	movl	%eax, 8(%esp)
	pushl	$RedComp
	pushl	64(%esp)
	pushl	$0
	leal	20(%esp), %esi
	pushl	%esi
	leal	28(%esp), %ebx
	pushl	%ebx
	movl	24(%edi), %ecx
	movl	12(%edi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	56(%ebp)
	pushl	%ebp
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	movl	$11, %ecx
	jne	.L194
	movl	16(%edi), %eax
	movl	56(%esp), %edx
	andl	(%edx), %eax
	movl	28(%edi), %ecx
	shrl	%cl, %eax
	movl	%eax, 4(%esp)
	pushl	$GreenComp
	pushl	64(%esp)
	pushl	$1
	leal	16(%esp), %ecx
	pushl	%ecx
	pushl	%ebx
	movl	16(%edi), %eax
	movl	28(%edi), %ecx
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	60(%ebp)
	pushl	%ebp
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	je	.L213
	pushl	$0
	pushl	%esi
	pushl	$1
	pushl	$0
	pushl	76(%esp)
	pushl	%ebp
	call	FreeCo
	movl	$11, %ecx
	addl	$24, %esp
	jmp	.L194
.L213:
	movl	20(%edi), %eax
	movl	56(%esp), %edx
	andl	(%edx), %eax
	movl	32(%edi), %ecx
	shrl	%cl, %eax
	movl	%eax, (%esp)
	pushl	$BlueComp
	pushl	64(%esp)
	pushl	$2
	leal	12(%esp), %eax
	pushl	%eax
	pushl	%ebx
	movl	20(%edi), %eax
	movl	32(%edi), %ecx
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	64(%ebp)
	pushl	%ebp
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	je	.L214
	pushl	$0
	leal	8(%esp), %ecx
	pushl	%ecx
	pushl	$1
	pushl	$1
	pushl	76(%esp)
	pushl	%ebp
	call	FreeCo
	pushl	$0
	pushl	%esi
	pushl	$1
	pushl	$0
	pushl	100(%esp)
	pushl	%ebp
	call	FreeCo
	movl	$11, %ecx
	addl	$48, %esp
	jmp	.L194
.L214:
	movl	4(%esp), %eax
	orl	8(%esp), %eax
	orl	(%esp), %eax
	movl	56(%esp), %ebx
	movl	%eax, (%ebx)
.L196:
	movl	32(%ebp), %eax
	movl	60(%esp), %esi
	cmpl	$1, (%eax,%esi,4)
	jne	.L217
	movl	8(%ebp), %eax
	andl	$534773760, %eax
	shrl	$21, %eax
	cmpl	%esi, %eax
	je	.L217
	testb	$4, 16(%ebp)
	jne	.L217
	pushl	$8
	call	Xalloc
	movl	%eax, %ecx
	testl	%ecx, %ecx
	popl	%eax
	jne	.L218
	pushl	$0
	pushl	60(%esp)
	pushl	$1
	pushl	%esi
	pushl	%ebp
	call	FreeColors
	movl	$11, %ecx
	addl	$20, %esp
	jmp	.L194
.L218:
	movl	8(%ebp), %eax
	movl	%eax, (%ecx)
	movl	60(%esp), %eax
	movl	%eax, 4(%ecx)
	pushl	%ecx
	pushl	$7
	pushl	%eax
	call	FakeClientID
	movl	%eax, (%esp)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	movl	$11, %ecx
	je	.L194
.L217:
	xorl	%ecx, %ecx
.L194:
	addl	$20, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%ecx, %eax
	popl	%ebp
	ret
	.size	AllocColor, .-AllocColor
	.align 4
.globl FakeAllocColor
	.type	FakeAllocColor, @function
FakeAllocColor:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$24, %esp
	movl	48(%esp), %edx
	movw	4(%edx), %ax
	movw	%ax, 16(%esp)
	movw	6(%edx), %ax
	movl	44(%esp), %ebx
	movw	%ax, 18(%esp)
	movw	8(%edx), %ax
	movl	(%ebx), %esi
	movw	%ax, 20(%esp)
	movl	12(%ebx), %edx
	pushl	%esi
	leal	24(%esp), %eax
	pushl	%eax
	leal	26(%esp), %eax
	leal	24(%esp), %edi
	pushl	%eax
	pushl	%edi
	call	*308(%edx)
	movswl	4(%ebx),%eax
	addl	$16, %esp
	cmpl	$5, %eax
	movswl	8(%esi),%ebp
	ja	.L220
	jmp	*.L232(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L232:
	.long	.L226
	.long	.L223
	.long	.L226
	.long	.L223
	.long	.L231
	.long	.L227
	.text
.L223:
	movl	48(%esp), %eax
	movl	$0, 12(%esp)
	movl	$0, (%eax)
	pushl	$AllComp
	pushl	$-1
	pushl	$3
	leal	24(%esp), %eax
	pushl	%eax
	pushl	%edi
	pushl	%ebp
	pushl	56(%ebx)
	pushl	%ebx
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	jne	.L226
	movl	12(%esp), %eax
	jmp	.L235
.L226:
	pushl	$3
	leal	20(%esp), %eax
	pushl	%eax
	pushl	%ebp
	pushl	56(%ebx)
	call	FindBestPixel
	movl	64(%esp), %edx
	movl	%eax, (%edx)
	jmp	.L234
.L227:
	movl	48(%esp), %eax
	movl	(%eax), %edx
	movl	%edx, %eax
	andl	12(%esi), %eax
	movl	24(%esi), %ecx
	shrl	%cl, %eax
	movl	%eax, 8(%esp)
	movl	%edx, %eax
	andl	16(%esi), %eax
	movl	28(%esi), %ecx
	shrl	%cl, %eax
	movl	%eax, 4(%esp)
	andl	20(%esi), %edx
	movl	32(%esi), %ecx
	shrl	%cl, %edx
	movl	%edx, (%esp)
	pushl	$RedComp
	pushl	$-1
	pushl	$0
	leal	20(%esp), %eax
	pushl	%eax
	pushl	%edi
	movl	12(%esi), %eax
	movl	24(%esi), %ecx
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	56(%ebx)
	pushl	%ebx
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	je	.L228
	pushl	$0
	pushl	%edi
	movl	24(%esi), %ecx
	movl	12(%esi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	56(%ebx)
	call	FindBestPixel
	movl	24(%esi), %ecx
	sall	%cl, %eax
	movl	%eax, 24(%esp)
	addl	$16, %esp
.L228:
	pushl	$GreenComp
	pushl	$-1
	pushl	$1
	leal	16(%esp), %eax
	pushl	%eax
	leal	32(%esp), %edi
	pushl	%edi
	movl	16(%esi), %eax
	movl	28(%esi), %ecx
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	60(%ebx)
	pushl	%ebx
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	je	.L229
	pushl	$1
	pushl	%edi
	movl	28(%esi), %ecx
	movl	16(%esi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	60(%ebx)
	call	FindBestPixel
	movl	28(%esi), %ecx
	sall	%cl, %eax
	movl	%eax, 20(%esp)
	addl	$16, %esp
.L229:
	pushl	$BlueComp
	pushl	$-1
	pushl	$2
	leal	12(%esp), %eax
	pushl	%eax
	pushl	%edi
	movl	20(%esi), %eax
	movl	32(%esi), %ecx
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	64(%ebx)
	pushl	%ebx
	call	FindColor
	addl	$32, %esp
	testl	%eax, %eax
	je	.L230
	pushl	$2
	pushl	%edi
	movl	32(%esi), %ecx
	movl	20(%esi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	64(%ebx)
	call	FindBestPixel
	movl	32(%esi), %ecx
	sall	%cl, %eax
	movl	%eax, 16(%esp)
	addl	$16, %esp
.L230:
	movl	4(%esp), %eax
	orl	8(%esp), %eax
	orl	(%esp), %eax
.L235:
	movl	48(%esp), %edx
	movl	%eax, (%edx)
	jmp	.L220
.L231:
	pushl	$0
	pushl	%edi
	movl	24(%esi), %ecx
	movl	12(%esi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	56(%ebx)
	call	FindBestPixel
	movl	%eax, 24(%esp)
	pushl	$1
	pushl	%edi
	movl	28(%esi), %ecx
	movl	16(%esi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	60(%ebx)
	call	FindBestPixel
	movl	%eax, 36(%esp)
	addl	$32, %esp
	pushl	$2
	pushl	%edi
	movl	32(%esi), %ecx
	movl	20(%esi), %eax
	shrl	%cl, %eax
	incl	%eax
	pushl	%eax
	pushl	64(%ebx)
	call	FindBestPixel
	movl	24(%esp), %ebx
	movl	24(%esi), %ecx
	sall	%cl, %ebx
	movl	20(%esp), %edx
	movl	28(%esi), %ecx
	sall	%cl, %edx
	movl	32(%esi), %ecx
	movl	%eax, 16(%esp)
	orl	%edx, %ebx
	sall	%cl, %eax
	orl	%eax, %ebx
	movl	64(%esp), %eax
	movl	%ebx, (%eax)
.L234:
	addl	$16, %esp
.L220:
	addl	$24, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	FakeAllocColor, .-FakeAllocColor
	.align 4
.globl FakeFreeColor
	.type	FakeFreeColor, @function
FakeFreeColor:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp), %edi
	movswl	4(%edi),%eax
	cmpl	$3, %eax
	movl	20(%esp), %esi
	je	.L239
	cmpl	$3, %eax
	jg	.L247
	decl	%eax
	je	.L239
	jmp	.L236
.L247:
	cmpl	$5, %eax
	je	.L241
	jmp	.L236
.L239:
	movl	56(%edi), %eax
	jmp	.L249
.L241:
	movl	(%edi), %eax
	movl	%esi, %edx
	andl	12(%eax), %edx
	movl	24(%eax), %ecx
	movl	%esi, %ebx
	shrl	%cl, %edx
	andl	16(%eax), %ebx
	movl	28(%eax), %ecx
	andl	20(%eax), %esi
	shrl	%cl, %ebx
	movl	32(%eax), %ecx
	shrl	%cl, %esi
	imull	$20, %edx, %eax
	movl	56(%edi), %ecx
	cmpw	$-2, 12(%ecx,%eax)
	jne	.L242
	movw	$0, 12(%ecx,%eax)
.L242:
	movl	60(%edi), %edx
	imull	$20, %ebx, %eax
	cmpw	$-2, 12(%edx,%eax)
	jne	.L243
	movw	$0, 12(%edx,%eax)
.L243:
	movl	64(%edi), %eax
.L249:
	imull	$20, %esi, %edx
	cmpw	$-2, 12(%eax,%edx)
	jne	.L236
	movw	$0, 12(%eax,%edx)
.L236:
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	FakeFreeColor, .-FakeFreeColor
	.align 4
	.type	BigNumAdd, @function
BigNumAdd:
	pushl	%esi
	pushl	%ebx
	movl	16(%esp), %eax
	movl	12(%esp), %ebx
	movl	4(%eax), %edx
	addl	4(%ebx), %edx
	xorl	%ecx, %ecx
	cmpl	$16777215, %edx
	movl	20(%esp), %esi
	jbe	.L251
	subl	$16777216, %edx
	movl	$1, %ecx
.L251:
	movw	(%eax), %ax
	addw	(%ebx), %ax
	addl	%ecx, %eax
	movl	%edx, 4(%esi)
	movw	%ax, (%esi)
	popl	%ebx
	popl	%esi
	ret
	.size	BigNumAdd, .-BigNumAdd
	.align 4
	.type	FindBestPixel, @function
FindBestPixel:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	$0, (%esp)
	movl	56(%esp), %eax
	cmpl	%eax, (%esp)
	movw	$-1, 24(%esp)
	movl	$16777215, 28(%esp)
	movl	52(%esp), %edi
	movl	$0, 4(%esp)
	jae	.L269
.L267:
	xorl	%ebp, %ebp
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	cmpl	$1, 64(%esp)
	je	.L260
	cmpl	$1, 64(%esp)
	jg	.L264
	cmpl	$0, 64(%esp)
	je	.L259
	jmp	.L257
.L264:
	cmpl	$2, 64(%esp)
	je	.L261
	cmpl	$3, 64(%esp)
	jne	.L257
	movl	60(%esp), %edx
	movzwl	2(%edx), %eax
	movzwl	2(%edi), %ecx
	subl	%eax, %ecx
	movzwl	4(%edi), %ebp
	movzwl	4(%edx), %eax
	subl	%eax, %ebp
.L259:
	movl	60(%esp), %ebx
	movzwl	(%edi), %edx
	movzwl	(%ebx), %eax
	subl	%eax, %edx
	jmp	.L257
.L260:
	movl	60(%esp), %ebx
	movzwl	2(%edi), %ecx
	movzwl	2(%ebx), %eax
	subl	%eax, %ecx
	jmp	.L257
.L261:
	movl	60(%esp), %ebx
	movzwl	4(%edi), %ebp
	movzwl	4(%ebx), %eax
	subl	%eax, %ebp
.L257:
	imull	%edx, %edx
	movl	%edx, %eax
	andl	$16777215, %edx
	movl	%edx, 20(%esp)
	movl	%ecx, %edx
	imull	%ecx, %edx
	shrl	$24, %eax
	movw	%ax, 16(%esp)
	movl	%edx, %eax
	leal	16(%esp), %ebx
	shrl	$24, %eax
	andl	$16777215, %edx
	movw	%ax, 8(%esp)
	movl	%edx, 12(%esp)
	leal	8(%esp), %esi
	pushl	%ebx
	pushl	%esi
	pushl	%ebx
	call	BigNumAdd
	movl	%ebp, %edx
	imull	%ebp, %edx
	movl	%edx, %eax
	shrl	$24, %eax
	andl	$16777215, %edx
	movw	%ax, 20(%esp)
	movl	%edx, 24(%esp)
	pushl	%ebx
	pushl	%esi
	pushl	%ebx
	call	BigNumAdd
	movl	48(%esp), %edx
	movl	40(%esp), %eax
	addl	$24, %esp
	cmpw	%ax, %dx
	ja	.L266
	cmpw	%ax, %dx
	jne	.L255
	movl	20(%esp), %eax
	cmpl	%eax, 28(%esp)
	jbe	.L255
.L266:
	movl	4(%esp), %eax
	movl	%eax, (%esp)
	movl	20(%esp), %edx
	movl	16(%esp), %eax
	movl	%eax, 24(%esp)
	movl	%edx, 28(%esp)
.L255:
	incl	4(%esp)
	movl	56(%esp), %edx
	addl	$20, %edi
	cmpl	%edx, 4(%esp)
	jb	.L267
.L269:
	movl	(%esp), %eax
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	FindBestPixel, .-FindBestPixel
	.align 4
	.type	FindColorInRootCmap, @function
FindColorInRootCmap:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	36(%esp), %eax
	movl	28(%esp), %edx
	movl	(%eax), %ebx
	cmpl	%edx, %ebx
	movl	40(%esp), %ebp
	jb	.L271
	xorl	%ebx, %ebx
.L271:
	imull	$20, %ebx, %eax
	movl	24(%esp), %edi
	movl	%edx, %esi
	addl	%eax, %edi
	decl	%esi
	js	.L286
.L284:
	cmpw	$0, 12(%edi)
	jle	.L274
	pushl	32(%esp)
	pushl	%edi
	call	*52(%esp)
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	je	.L274
	cmpl	$1, %ebp
	je	.L279
	cmpl	$1, %ebp
	jg	.L283
	testl	%ebp, %ebp
	je	.L278
	jmp	.L277
.L283:
	cmpl	$2, %ebp
	je	.L280
	jmp	.L277
.L278:
	movl	20(%esp), %edx
	movl	(%edx), %eax
	movl	24(%eax), %ecx
	jmp	.L287
.L279:
	movl	20(%esp), %edx
	movl	(%edx), %eax
	movl	28(%eax), %ecx
	jmp	.L287
.L280:
	movl	20(%esp), %edx
	movl	(%edx), %eax
	movl	32(%eax), %ecx
.L287:
	sall	%cl, %ebx
.L277:
	movl	36(%esp), %eax
	movl	%ebx, (%eax)
.L274:
	addl	$20, %edi
	incl	%ebx
	decl	%esi
	jns	.L284
.L286:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	FindColorInRootCmap, .-FindColorInRootCmap
	.align 4
.globl FindColor
	.type	FindColor, @function
FindColor:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	68(%esp), %eax
	movl	(%eax), %ebx
	cmpl	60(%esp), %ebx
	movl	52(%esp), %esi
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	$0, 12(%esp)
	jb	.L289
	xorl	%ebx, %ebx
.L289:
	imull	$20, %ebx, %eax
	movl	56(%esp), %edi
	movl	60(%esp), %ebp
	addl	%eax, %edi
	decl	%ebp
	js	.L338
.L311:
	movw	12(%edi), %ax
	testw	%ax, %ax
	jle	.L294
	pushl	64(%esp)
	pushl	%edi
	call	*88(%esp)
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	je	.L306
	cmpl	$0, 76(%esp)
	js	.L296
	incw	12(%edi)
.L296:
	movl	68(%esp), %edx
	cmpl	$1, 72(%esp)
	movl	%ebx, (%edx)
	je	.L300
	cmpl	$1, 72(%esp)
	jg	.L304
	cmpl	$0, 72(%esp)
	je	.L298
	jmp	.L305
.L304:
	cmpl	$2, 72(%esp)
	je	.L301
	jmp	.L305
.L298:
	movl	(%esi), %eax
	movl	24(%eax), %ecx
	jmp	.L352
.L300:
	movl	(%esi), %eax
	movl	28(%eax), %ecx
	jmp	.L352
.L301:
	movl	(%esi), %eax
	movl	32(%eax), %ecx
.L352:
	movl	%ebx, %eax
	sall	%cl, %eax
	movl	68(%esp), %edx
	movl	%eax, (%edx)
	jmp	.L305
.L294:
	cmpl	$0, 12(%esp)
	jne	.L306
	testw	%ax, %ax
	jne	.L306
	testb	$4, 16(%esi)
	movl	%ebx, 8(%esp)
	movl	$1, 12(%esp)
	jne	.L312
.L306:
	incl	%ebx
	cmpl	60(%esp), %ebx
	jb	.L309
	movl	56(%esp), %edi
	xorl	%ebx, %ebx
	jmp	.L290
.L309:
	addl	$20, %edi
.L290:
	decl	%ebp
	jns	.L311
	cmpl	$0, 12(%esp)
	je	.L338
.L312:
	imull	$20, 8(%esp), %eax
	movl	56(%esp), %edi
	addl	%eax, %edi
	movl	$0, 16(%edi)
	cmpl	$0, 76(%esp)
	movl	$1, %eax
	jns	.L314
	movl	$-2, %eax
.L314:
	cmpl	$1, 72(%esp)
	movw	%ax, 12(%edi)
	je	.L320
	cmpl	$1, 72(%esp)
	jg	.L326
	cmpl	$0, 72(%esp)
	je	.L318
	jmp	.L315
.L326:
	cmpl	$2, 72(%esp)
	je	.L322
	cmpl	$3, 72(%esp)
	jne	.L315
	movl	64(%esp), %ecx
	movw	(%ecx), %ax
	movw	%ax, (%edi)
	movw	2(%ecx), %ax
	movw	%ax, 2(%edi)
	movw	4(%ecx), %ax
	movw	%ax, 4(%edi)
	movw	(%ecx), %ax
	movw	%ax, 20(%esp)
	movw	2(%ecx), %ax
	movw	%ax, 22(%esp)
	movw	4(%ecx), %ax
	cmpl	$0, 76(%esp)
	movw	%ax, 24(%esp)
	movb	$7, 26(%esp)
	js	.L317
	decl	20(%esi)
.L317:
	movl	8(%esp), %eax
	jmp	.L356
.L318:
	movl	64(%esp), %edx
	movw	(%edx), %ax
	movw	%ax, (%edi)
	movw	(%edx), %ax
	movw	%ax, 20(%esp)
	movl	60(%esi), %eax
	movw	2(%eax), %ax
	movw	%ax, 22(%esp)
	movl	64(%esi), %eax
	movw	4(%eax), %ax
	cmpl	$0, 76(%esp)
	movw	%ax, 24(%esp)
	movb	$1, 26(%esp)
	js	.L319
	decl	20(%esi)
.L319:
	movl	(%esi), %eax
	movl	24(%eax), %ecx
	jmp	.L351
.L320:
	movl	64(%esp), %edx
	movw	2(%edx), %ax
	movw	%ax, 2(%edi)
	movl	56(%esi), %eax
	movw	(%eax), %ax
	movw	%ax, 20(%esp)
	movw	2(%edx), %ax
	movw	%ax, 22(%esp)
	movl	64(%esi), %eax
	movw	4(%eax), %ax
	cmpl	$0, 76(%esp)
	movw	%ax, 24(%esp)
	movb	$2, 26(%esp)
	js	.L321
	decl	24(%esi)
.L321:
	movl	(%esi), %eax
	movl	28(%eax), %ecx
	jmp	.L351
.L322:
	movl	64(%esp), %edx
	movw	4(%edx), %ax
	movw	%ax, 4(%edi)
	movl	56(%esi), %eax
	movw	(%eax), %ax
	movw	%ax, 20(%esp)
	movl	60(%esi), %eax
	movw	2(%eax), %ax
	movw	%ax, 22(%esp)
	movw	4(%edx), %ax
	cmpl	$0, 76(%esp)
	movw	%ax, 24(%esp)
	movb	$4, 26(%esp)
	js	.L323
	decl	28(%esi)
.L323:
	movl	(%esi), %eax
	movl	32(%eax), %ecx
.L351:
	movl	8(%esp), %eax
	sall	%cl, %eax
.L356:
	movl	%eax, 16(%esp)
.L315:
	leal	16(%esp), %edx
	movl	12(%esi), %eax
	pushl	%edx
	pushl	$1
	pushl	%esi
	call	*304(%eax)
	movl	28(%esp), %eax
	movl	80(%esp), %edx
	movl	20(%esp), %ebx
	movl	%eax, (%edx)
	addl	$12, %esp
.L305:
	testb	$4, 16(%esi)
	jne	.L355
	cmpl	$-1, 76(%esp)
	je	.L355
	cmpl	$1, 72(%esp)
	je	.L332
	cmpl	$1, 72(%esp)
	jg	.L336
	cmpl	$0, 72(%esp)
	jmp	.L353
.L336:
	cmpl	$2, 72(%esp)
	je	.L333
	cmpl	$3, 72(%esp)
.L353:
	jne	.L329
	movl	32(%esi), %ecx
	movl	44(%esi), %eax
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	jmp	.L329
.L332:
	movl	36(%esi), %edx
	movl	48(%esi), %ecx
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	jmp	.L329
.L333:
	movl	40(%esi), %eax
	movl	52(%esi), %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
.L329:
	movl	76(%esp), %ecx
	movl	4(%esp), %eax
	movl	(%eax,%ecx,4), %ebp
	leal	4(,%ebp,4), %eax
	pushl	%eax
	movl	4(%esp), %edx
	pushl	(%edx,%ecx,4)
	call	Xrealloc
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L337
	decw	12(%edi)
	cmpl	$0, 16(%edi)
	jne	.L338
	cmpl	$1, 72(%esp)
	je	.L342
	cmpl	$1, 72(%esp)
	jg	.L346
	cmpl	$0, 72(%esp)
	jmp	.L354
.L346:
	cmpl	$2, 72(%esp)
	je	.L343
	cmpl	$3, 72(%esp)
.L354:
	jne	.L338
	incl	20(%esi)
	jmp	.L338
.L342:
	incl	24(%esi)
	jmp	.L338
.L343:
	incl	28(%esi)
.L338:
	movl	$11, %eax
	jmp	.L288
.L337:
	movl	76(%esp), %ecx
	movl	(%esp), %edx
	movl	%ebx, (%eax,%ebp,4)
	movl	%eax, (%edx,%ecx,4)
	movl	4(%esp), %eax
	incl	(%eax,%ecx,4)
.L355:
	xorl	%eax, %eax
.L288:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	FindColor, .-FindColor
	.align 4
	.type	AllComp, @function
AllComp:
	movl	8(%esp), %edx
	movl	4(%esp), %ecx
	movw	(%edx), %ax
	cmpw	%ax, (%ecx)
	jne	.L358
	movw	2(%edx), %ax
	cmpw	%ax, 2(%ecx)
	jne	.L358
	movw	4(%edx), %ax
	cmpw	%ax, 4(%ecx)
	jne	.L358
	movl	$1, %eax
	ret
.L358:
	xorl	%eax, %eax
	ret
	.size	AllComp, .-AllComp
	.align 4
	.type	RedComp, @function
RedComp:
	movl	8(%esp), %eax
	movw	(%eax), %dx
	movl	4(%esp), %eax
	cmpw	%dx, (%eax)
	sete	%al
	movzbl	%al, %eax
	ret
	.size	RedComp, .-RedComp
	.align 4
	.type	GreenComp, @function
GreenComp:
	movl	8(%esp), %eax
	movw	2(%eax), %dx
	movl	4(%esp), %eax
	cmpw	%dx, 2(%eax)
	sete	%al
	movzbl	%al, %eax
	ret
	.size	GreenComp, .-GreenComp
	.align 4
	.type	BlueComp, @function
BlueComp:
	movl	8(%esp), %eax
	movw	4(%eax), %dx
	movl	4(%esp), %eax
	cmpw	%dx, 4(%eax)
	sete	%al
	movzbl	%al, %eax
	ret
	.size	BlueComp, .-BlueComp
	.align 4
.globl QueryColors
	.type	QueryColors, @function
QueryColors:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	56(%esp), %eax
	movl	(%eax), %edi
	movw	4(%eax), %ax
	orl	$1, %eax
	movl	60(%esp), %esi
	cmpw	$5, %ax
	movl	64(%esp), %ebp
	movl	$0, 32(%esp)
	leal	-1(%esi), %esi
	jne	.L366
	movl	12(%edi), %ebx
	movl	24(%edi), %ecx
	movl	%ebx, %eax
	shrl	%cl, %eax
	incl	%eax
	movl	%eax, 28(%esp)
	movl	28(%edi), %eax
	movl	%eax, 8(%esp)
	movl	%ecx, 12(%esp)
	movl	16(%edi), %eax
	movb	8(%esp), %cl
	shrl	%cl, %eax
	incl	%eax
	movl	%eax, 24(%esp)
	movl	32(%edi), %eax
	movl	20(%edi), %edx
	movl	%eax, 4(%esp)
	orl	16(%edi), %ebx
	movl	%edx, %eax
	movb	4(%esp), %cl
	movl	%ebx, 16(%esp)
	shrl	%cl, %eax
	incl	%eax
	orl	%edx, 16(%esp)
	testl	%esi, %esi
	movl	%eax, 20(%esp)
	notl	16(%esp)
	movl	68(%esp), %ebx
	js	.L376
.L375:
	movl	(%ebp), %eax
	testl	%eax, 16(%esp)
	movl	%eax, (%esp)
	jne	.L390
	movl	(%esp), %edx
	andl	12(%edi), %edx
	movb	12(%esp), %cl
	shrl	%cl, %edx
	cmpl	28(%esp), %edx
	jae	.L389
	movl	56(%esp), %ecx
	imull	$20, %edx, %edx
	movl	56(%ecx), %eax
	movw	(%eax,%edx), %ax
	movl	(%esp), %edx
	andl	16(%edi), %edx
	movb	8(%esp), %cl
	shrl	%cl, %edx
	cmpl	24(%esp), %edx
	movw	%ax, (%ebx)
	jae	.L389
	movl	56(%esp), %ecx
	imull	$20, %edx, %edx
	movl	60(%ecx), %eax
	movw	2(%eax,%edx), %ax
	movl	(%esp), %edx
	andl	20(%edi), %edx
	movb	4(%esp), %cl
	shrl	%cl, %edx
	cmpl	20(%esp), %edx
	movw	%ax, 2(%ebx)
	jb	.L374
.L389:
	movl	(%esp), %eax
.L390:
	movl	%eax, clientErrorValue
	movl	$2, 32(%esp)
	jmp	.L369
.L374:
	movl	56(%esp), %ecx
	movl	64(%ecx), %eax
	imull	$20, %edx, %edx
	movw	4(%eax,%edx), %ax
	movw	%ax, 4(%ebx)
.L369:
	addl	$4, %ebp
	addl	$8, %ebx
	decl	%esi
	jns	.L375
	jmp	.L376
.L366:
	testl	%esi, %esi
	movl	68(%esp), %ebx
	js	.L376
.L385:
	movl	(%ebp), %eax
	movl	%eax, (%esp)
	movswl	8(%edi),%eax
	cmpl	%eax, (%esp)
	jb	.L381
	movl	(%esp), %edx
	movl	%edx, clientErrorValue
	movl	$2, 32(%esp)
	jmp	.L379
.L381:
	imull	$20, (%esp), %edx
	movl	56(%esp), %ecx
	addl	56(%ecx), %edx
	cmpl	$0, 16(%edx)
	je	.L383
	movl	(%edx), %eax
	movw	(%eax), %ax
	movw	%ax, (%ebx)
	movl	4(%edx), %eax
	movw	(%eax), %ax
	movw	%ax, 2(%ebx)
	movl	8(%edx), %eax
	movw	(%eax), %ax
	jmp	.L391
.L383:
	movw	(%edx), %ax
	movw	%ax, (%ebx)
	movw	2(%edx), %ax
	movw	%ax, 2(%ebx)
	movw	4(%edx), %ax
.L391:
	movw	%ax, 4(%ebx)
.L379:
	addl	$4, %ebp
	addl	$8, %ebx
	decl	%esi
	jns	.L385
.L376:
	movl	32(%esp), %eax
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	QueryColors, .-QueryColors
	.align 4
	.type	FreePixels, @function
FreePixels:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	movl	24(%esp), %ebp
	movswl	4(%ebp),%eax
	movl	%eax, (%esp)
	movl	28(%esp), %edx
	movl	44(%ebp), %eax
	testb	$1, (%esp)
	movl	(%eax,%edx,4), %edi
	je	.L393
	movl	32(%ebp), %eax
	movl	(%eax,%edx,4), %ebx
	decl	%ebx
	movl	%edi, %esi
	js	.L393
.L398:
	pushl	$0
	pushl	(%esi)
	pushl	%ebp
	call	FreeCell
	addl	$4, %esi
	addl	$12, %esp
	decl	%ebx
	jns	.L398
.L393:
	pushl	%edi
	call	Xfree
	movl	32(%esp), %edx
	movl	44(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	movl	32(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	movl	4(%esp), %eax
	orl	$1, %eax
	cmpl	$5, %eax
	popl	%ecx
	jne	.L392
	movl	48(%ebp), %eax
	testb	$1, (%esp)
	movl	(%eax,%edx,4), %edi
	je	.L400
	movl	36(%ebp), %eax
	movl	(%eax,%edx,4), %ebx
	decl	%ebx
	movl	%edi, %esi
	js	.L400
.L405:
	pushl	$1
	pushl	(%esi)
	pushl	%ebp
	call	FreeCell
	addl	$4, %esi
	addl	$12, %esp
	decl	%ebx
	jns	.L405
.L400:
	pushl	%edi
	call	Xfree
	movl	32(%esp), %edx
	movl	48(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	movl	36(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	movl	52(%ebp), %eax
	movl	(%eax,%edx,4), %edi
	popl	%eax
	testb	$1, (%esp)
	je	.L406
	movl	40(%ebp), %eax
	movl	(%eax,%edx,4), %ebx
	decl	%ebx
	movl	%edi, %esi
	js	.L406
.L411:
	pushl	$2
	pushl	(%esi)
	pushl	%ebp
	call	FreeCell
	addl	$4, %esi
	addl	$12, %esp
	decl	%ebx
	jns	.L411
.L406:
	pushl	%edi
	call	Xfree
	movl	32(%esp), %edx
	movl	52(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	movl	40(%ebp), %eax
	movl	$0, (%eax,%edx,4)
	popl	%esi
.L392:
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	FreePixels, .-FreePixels
	.align 4
.globl FreeClientPixels
	.type	FreeClientPixels, @function
FreeClientPixels:
	pushl	%ebx
	movl	8(%esp), %ebx
	pushl	$6
	pushl	(%ebx)
	call	LookupIDByType
	testl	%eax, %eax
	popl	%ecx
	popl	%edx
	je	.L416
	pushl	4(%ebx)
	pushl	%eax
	call	FreePixels
	popl	%eax
	popl	%edx
.L416:
	pushl	%ebx
	call	Xfree
	popl	%eax
	popl	%ebx
	xorl	%eax, %eax
	ret
	.size	FreeClientPixels, .-FreeClientPixels
	.align 4
.globl AllocColorCells
	.type	AllocColorCells, @function
AllocColorCells:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	68(%esp), %eax
	movw	4(%eax), %dx
	testb	$1, %dl
	movl	72(%esp), %ebp
	movl	76(%esp), %edi
	movl	80(%esp), %esi
	movl	$0, 24(%esp)
	movl	$11, %eax
	je	.L417
	movl	68(%esp), %ecx
	movl	32(%ecx), %ecx
	movl	64(%esp), %ebx
	cmpw	$5, %dx
	movl	(%ecx,%ebx,4), %ecx
	jne	.L419
	movl	68(%esp), %edx
	movl	36(%edx), %edx
	movl	68(%esp), %ebx
	movl	%edx, 4(%esp)
	movl	40(%ebx), %ebx
	movl	64(%esp), %edx
	movl	(%ebx,%edx,4), %eax
	movl	4(%esp), %ebx
	addl	(%ebx,%edx,4), %eax
	addl	%eax, %ecx
.L419:
	testl	%ecx, %ecx
	jne	.L420
	movl	68(%esp), %edx
	movl	8(%edx), %eax
	andl	$534773760, %eax
	shrl	$21, %eax
	cmpl	64(%esp), %eax
	je	.L420
	pushl	$8
	call	Xalloc
	movl	%eax, 28(%esp)
	popl	%ebx
	cmpl	$0, 24(%esp)
	movl	$11, %eax
	je	.L417
.L420:
	movl	68(%esp), %ecx
	cmpw	$5, 4(%ecx)
	leal	32(%esp), %edx
	jne	.L422
	leal	40(%esp), %eax
	pushl	%eax
	leal	40(%esp), %eax
	pushl	%eax
	pushl	%edx
	pushl	96(%esp)
	pushl	%esi
	pushl	%edi
	pushl	%edi
	pushl	%edi
	pushl	%ebp
	pushl	%ecx
	pushl	104(%esp)
	call	AllocDirect
	addl	$44, %esp
	testl	%eax, %eax
	movl	%eax, %ebp
	jne	.L452
	movl	%edi, %edx
	decl	%edx
	movl	$1, %esi
	movl	$1, %ebx
	movl	$1, %ecx
	js	.L441
	movl	32(%esp), %edi
	movl	%edi, 20(%esp)
	movl	36(%esp), %eax
	movl	40(%esp), %edi
	movl	%eax, 16(%esp)
	movl	%edi, 12(%esp)
.L440:
	movl	20(%esp), %eax
	testl	%ecx, %eax
	jne	.L459
.L431:
	sall	%ecx
	testl	%ecx, %eax
	je	.L431
.L459:
	movl	16(%esp), %eax
	testl	%ebx, %eax
	jne	.L461
.L435:
	sall	%ebx
	testl	%ebx, %eax
	je	.L435
.L461:
	movl	12(%esp), %eax
	testl	%esi, %eax
	jne	.L463
.L439:
	sall	%esi
	testl	%esi, %eax
	je	.L439
.L463:
	movl	%ecx, %eax
	orl	%ebx, %eax
	orl	%esi, %eax
	movl	88(%esp), %edi
	movl	%eax, (%edi)
	sall	%ecx
	addl	$4, %edi
	sall	%ebx
	sall	%esi
	decl	%edx
	movl	%edi, 88(%esp)
	jns	.L440
	jmp	.L441
.L422:
	leal	28(%esp), %eax
	pushl	%eax
	pushl	%edx
	pushl	92(%esp)
	pushl	%esi
	pushl	%edi
	pushl	%ebp
	pushl	92(%esp)
	pushl	92(%esp)
	call	AllocPseudo
	addl	$32, %esp
	testl	%eax, %eax
	movl	%eax, %ebp
	jne	.L452
	movl	%edi, %edx
	decl	%edx
	movl	$1, %ecx
	js	.L441
	movl	32(%esp), %ebx
.L451:
	testl	%ecx, %ebx
	movl	%ebx, %eax
	jne	.L466
.L450:
	sall	%ecx
	testl	%ecx, %eax
	je	.L450
.L466:
	movl	88(%esp), %eax
	movl	%ecx, (%eax)
	addl	$4, %eax
	sall	%ecx
	decl	%edx
	movl	%eax, 88(%esp)
	jns	.L451
.L441:
	testl	%ebp, %ebp
	jne	.L452
	cmpl	$0, 24(%esp)
	je	.L454
	movl	68(%esp), %edx
	movl	24(%esp), %ecx
	movl	8(%edx), %eax
	movl	64(%esp), %ebx
	movl	%eax, (%ecx)
	movl	%ebx, 4(%ecx)
	pushl	%ecx
	pushl	$7
	pushl	%ebx
	call	FakeClientID
	movl	%eax, (%esp)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L454
	movl	$11, %ebp
	jmp	.L454
.L452:
	cmpl	$0, 24(%esp)
	je	.L454
	pushl	24(%esp)
	call	Xfree
	popl	%ecx
.L454:
	movl	%ebp, %eax
.L417:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	AllocColorCells, .-AllocColorCells
	.align 4
.globl AllocColorPlanes
	.type	AllocColorPlanes, @function
AllocColorPlanes:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	36(%esp), %edi
	movswl	4(%edi),%ebx
	testb	$1, %bl
	movl	32(%esp), %ebp
	movl	56(%esp), %esi
	movl	$0, (%esp)
	movl	$11, %eax
	je	.L467
	movl	32(%edi), %eax
	cmpl	$5, %ebx
	movl	(%eax,%ebp,4), %ecx
	jne	.L469
	movl	40(%edi), %eax
	movl	36(%edi), %edx
	movl	(%eax,%ebp,4), %eax
	addl	(%edx,%ebp,4), %eax
	addl	%eax, %ecx
.L469:
	testl	%ecx, %ecx
	jne	.L470
	movl	8(%edi), %eax
	andl	$534773760, %eax
	shrl	$21, %eax
	cmpl	%ebp, %eax
	je	.L470
	pushl	$8
	call	Xalloc
	movl	%eax, 4(%esp)
	popl	%eax
	cmpl	$0, (%esp)
	movl	$11, %eax
	je	.L467
.L470:
	cmpl	$5, %ebx
	jne	.L472
	pushl	72(%esp)
	pushl	72(%esp)
	pushl	72(%esp)
	pushl	72(%esp)
	pushl	%esi
	pushl	72(%esp)
	pushl	72(%esp)
	pushl	72(%esp)
	pushl	72(%esp)
	pushl	%edi
	pushl	%ebp
	call	AllocDirect
	movl	%eax, %esi
	addl	$44, %esp
	jmp	.L473
.L472:
	leal	8(%esp), %eax
	pushl	%eax
	leal	8(%esp), %eax
	pushl	%eax
	pushl	68(%esp)
	pushl	%esi
	movl	60(%esp), %eax
	addl	64(%esp), %eax
	addl	68(%esp), %eax
	pushl	%eax
	pushl	60(%esp)
	pushl	%edi
	pushl	%ebp
	call	AllocPseudo
	addl	$32, %esp
	testl	%eax, %eax
	movl	%eax, %esi
	jne	.L503
	movl	72(%esp), %eax
	movl	$0, (%eax)
	movl	44(%esp), %eax
	movl	68(%esp), %edx
	movl	64(%esp), %ecx
	decl	%eax
	movl	$0, (%edx)
	movl	$0, (%ecx)
	movl	$1, %edx
	js	.L508
	movl	4(%esp), %ebx
.L483:
	testl	%edx, %ebx
	movl	%ebx, %ecx
	jne	.L510
.L482:
	sall	%edx
	testl	%edx, %ecx
	je	.L482
.L510:
	movl	64(%esp), %ecx
	orl	%edx, (%ecx)
	sall	%edx
	decl	%eax
	jns	.L483
.L508:
	movl	48(%esp), %eax
	decl	%eax
	js	.L512
	movl	4(%esp), %ebx
.L492:
	testl	%edx, %ebx
	movl	%ebx, %ecx
	jne	.L514
.L491:
	sall	%edx
	testl	%edx, %ecx
	je	.L491
.L514:
	movl	68(%esp), %ecx
	orl	%edx, (%ecx)
	sall	%edx
	decl	%eax
	jns	.L492
.L512:
	movl	52(%esp), %eax
	decl	%eax
	js	.L516
	movl	4(%esp), %ebx
.L501:
	testl	%edx, %ebx
	movl	%ebx, %ecx
	jne	.L518
.L500:
	sall	%edx
	testl	%edx, %ecx
	je	.L500
.L518:
	movl	72(%esp), %ecx
	orl	%edx, (%ecx)
	sall	%edx
	decl	%eax
	jns	.L501
.L516:
	pushl	8(%esp)
	movl	76(%esp), %eax
	pushl	(%eax)
	movl	76(%esp), %edx
	pushl	(%edx)
	movl	76(%esp), %ecx
	pushl	(%ecx)
	pushl	68(%esp)
	pushl	68(%esp)
	pushl	68(%esp)
	pushl	68(%esp)
	pushl	92(%esp)
	pushl	%edi
	call	AllocShared
	addl	$40, %esp
	testl	%eax, %eax
	jne	.L473
	pushl	4(%esp)
	pushl	64(%esp)
	pushl	48(%esp)
	pushl	%ebp
	pushl	%edi
	call	FreeColors
	movl	$11, %esi
	addl	$20, %esp
.L473:
	testl	%esi, %esi
	jne	.L503
	cmpl	$0, (%esp)
	je	.L505
	movl	(%esp), %edx
	movl	8(%edi), %eax
	movl	%eax, (%edx)
	movl	%ebp, 4(%edx)
	pushl	%edx
	pushl	$7
	pushl	%ebp
	call	FakeClientID
	movl	%eax, (%esp)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L505
	movl	$11, %esi
	jmp	.L505
.L503:
	cmpl	$0, (%esp)
	je	.L505
	pushl	(%esp)
	call	Xfree
	popl	%edi
.L505:
	movl	%esi, %eax
.L467:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	AllocColorPlanes, .-AllocColorPlanes
	.align 4
	.type	AllocDirect, @function
AllocDirect:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	76(%esp), %esi
	movl	%esi, %ecx
	movl	72(%esp), %eax
	sall	%cl, %eax
	movl	80(%esp), %edi
	movl	%edi, %ecx
	movl	%eax, 28(%esp)
	movl	72(%esp), %eax
	sall	%cl, %eax
	movl	%eax, 24(%esp)
	movb	84(%esp), %cl
	movl	72(%esp), %eax
	sall	%cl, %eax
	cmpl	$31, %esi
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, 20(%esp)
	jg	.L531
	cmpl	$31, %edi
	jg	.L531
	cmpl	$31, 84(%esp)
	jg	.L531
	movl	28(%esp), %edx
	movl	68(%esp), %ecx
	cmpl	20(%ecx), %edx
	jg	.L531
	movl	72(%esp), %eax
	cmpl	%eax, %edx
	jl	.L531
	movl	24(%esp), %edx
	cmpl	24(%ecx), %edx
	jg	.L531
	cmpl	%eax, %edx
	jl	.L531
	movl	20(%esp), %eax
	cmpl	28(%ecx), %eax
	jg	.L531
	movl	72(%esp), %edx
	cmpl	%edx, %eax
	jl	.L531
	movl	92(%esp), %ebx
	movl	72(%esp), %ecx
	leal	(%ebx,%ecx,4), %eax
	cmpl	%eax, %ebx
	jae	.L580
.L526:
	movl	$0, (%ebx)
	addl	$4, %ebx
	cmpl	%eax, %ebx
	jb	.L526
.L580:
	movl	28(%esp), %eax
	sall	$2, %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, 44(%esp)
	movl	28(%esp), %eax
	sall	$2, %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, 44(%esp)
	movl	28(%esp), %eax
	sall	$2, %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, 44(%esp)
	addl	$12, %esp
	cmpl	$0, 40(%esp)
	je	.L528
	cmpl	$0, 36(%esp)
	je	.L528
	cmpl	$0, 32(%esp)
	jne	.L527
	jmp	.L529
.L528:
	cmpl	$0, 32(%esp)
	je	.L529
	pushl	32(%esp)
	call	Xfree
	popl	%esi
.L529:
	cmpl	$0, 36(%esp)
	je	.L530
	pushl	36(%esp)
	call	Xfree
	popl	%ebx
.L530:
	cmpl	$0, 40(%esp)
	je	.L531
	pushl	40(%esp)
	call	Xfree
	popl	%ecx
.L531:
	movl	$11, %eax
	jmp	.L519
.L527:
	pushl	96(%esp)
	pushl	44(%esp)
	pushl	96(%esp)
	pushl	%esi
	pushl	88(%esp)
	movl	88(%esp), %eax
	pushl	56(%eax)
	pushl	%eax
	call	AllocCP
	pushl	128(%esp)
	pushl	68(%esp)
	pushl	124(%esp)
	pushl	%edi
	pushl	116(%esp)
	movl	116(%esp), %edx
	pushl	60(%edx)
	pushl	%edx
	movl	%eax, %ebx
	call	AllocCP
	addl	$56, %esp
	pushl	104(%esp)
	pushl	36(%esp)
	pushl	96(%esp)
	pushl	96(%esp)
	pushl	88(%esp)
	movl	88(%esp), %ecx
	pushl	64(%ecx)
	pushl	%ecx
	movl	%eax, %ebp
	call	AllocCP
	movl	%eax, 44(%esp)
	addl	$28, %esp
	testl	%ebx, %ebx
	je	.L538
	testl	%ebp, %ebp
	je	.L532
	cmpl	$0, 16(%esp)
	je	.L532
	movl	68(%esp), %edx
	movl	32(%edx), %eax
	movl	%esi, %ecx
	movl	72(%esp), %edx
	sall	%cl, %edx
	movl	64(%esp), %ecx
	addl	(%eax,%ecx,4), %edx
	sall	$2, %edx
	pushl	%edx
	movl	72(%esp), %edx
	movl	44(%edx), %eax
	pushl	(%eax,%ecx,4)
	call	Xrealloc
	movl	%eax, 20(%esp)
	popl	%eax
	popl	%edx
	cmpl	$0, 12(%esp)
	je	.L533
	movl	68(%esp), %ecx
	movl	44(%ecx), %eax
	movl	64(%esp), %edx
	movl	12(%esp), %ecx
	movl	%ecx, (%eax,%edx,4)
.L533:
	movl	68(%esp), %edx
	movl	36(%edx), %eax
	movl	%edi, %ecx
	movl	72(%esp), %edx
	sall	%cl, %edx
	movl	64(%esp), %ecx
	addl	(%eax,%ecx,4), %edx
	sall	$2, %edx
	pushl	%edx
	movl	72(%esp), %edx
	movl	48(%edx), %eax
	pushl	(%eax,%ecx,4)
	call	Xrealloc
	movl	%eax, 16(%esp)
	popl	%ecx
	popl	%esi
	cmpl	$0, 8(%esp)
	je	.L534
	movl	68(%esp), %ecx
	movl	48(%ecx), %eax
	movl	64(%esp), %edx
	movl	8(%esp), %ecx
	movl	%ecx, (%eax,%edx,4)
.L534:
	movl	68(%esp), %edx
	movl	40(%edx), %eax
	movb	84(%esp), %cl
	movl	72(%esp), %edx
	sall	%cl, %edx
	movl	64(%esp), %ecx
	addl	(%eax,%ecx,4), %edx
	sall	$2, %edx
	pushl	%edx
	movl	72(%esp), %edx
	movl	52(%edx), %eax
	pushl	(%eax,%ecx,4)
	call	Xrealloc
	movl	%eax, 12(%esp)
	popl	%eax
	popl	%edx
	cmpl	$0, 4(%esp)
	je	.L532
	movl	68(%esp), %ecx
	movl	52(%ecx), %eax
	movl	64(%esp), %edx
	movl	4(%esp), %ecx
	movl	%ecx, (%eax,%edx,4)
.L532:
	testl	%ebx, %ebx
	je	.L538
	testl	%ebp, %ebp
	je	.L537
	cmpl	$0, 16(%esp)
	je	.L537
	cmpl	$0, 12(%esp)
	je	.L537
	cmpl	$0, 8(%esp)
	je	.L537
	cmpl	$0, 4(%esp)
	jne	.L536
.L537:
	testl	%ebx, %ebx
	je	.L538
	movl	28(%esp), %edx
	decl	%edx
	movl	40(%esp), %edi
	js	.L538
	movl	68(%esp), %eax
	movl	56(%eax), %ecx
.L543:
	imull	$20, (%edi), %eax
	addl	$4, %edi
	decl	%edx
	movw	$0, 12(%ecx,%eax)
	jns	.L543
.L538:
	testl	%ebp, %ebp
	je	.L544
	movl	24(%esp), %edx
	decl	%edx
	movl	36(%esp), %edi
	js	.L544
	movl	68(%esp), %eax
	movl	60(%eax), %ecx
.L549:
	imull	$20, (%edi), %eax
	addl	$4, %edi
	decl	%edx
	movw	$0, 12(%ecx,%eax)
	jns	.L549
.L544:
	cmpl	$0, 16(%esp)
	je	.L550
	movl	20(%esp), %edx
	decl	%edx
	movl	32(%esp), %edi
	js	.L550
	movl	68(%esp), %eax
	movl	64(%eax), %ecx
.L555:
	imull	$20, (%edi), %eax
	addl	$4, %edi
	decl	%edx
	movw	$0, 12(%ecx,%eax)
	jns	.L555
.L550:
	pushl	32(%esp)
	call	Xfree
	pushl	40(%esp)
	call	Xfree
	pushl	48(%esp)
	call	Xfree
	movl	$11, %eax
	jmp	.L592
.L536:
	movl	68(%esp), %ecx
	movl	(%ecx), %edx
	movl	24(%edx), %ecx
	movl	96(%esp), %eax
	sall	%cl, (%eax)
	movl	28(%edx), %ecx
	movl	100(%esp), %eax
	sall	%cl, (%eax)
	movl	32(%edx), %ecx
	movl	104(%esp), %eax
	sall	%cl, (%eax)
	movl	68(%esp), %ecx
	movl	32(%ecx), %ebp
	movl	64(%esp), %ecx
	movl	(%ebp,%ecx,4), %eax
	movl	12(%esp), %ecx
	movl	40(%esp), %ebx
	leal	(%ecx,%eax,4), %edi
	movl	28(%esp), %eax
	leal	(%ebx,%eax,4), %eax
	cmpl	%eax, %ebx
	movl	92(%esp), %esi
	jae	.L585
.L561:
	movl	(%ebx), %eax
	movl	%eax, (%edi)
	movl	72(%esp), %ecx
	movl	40(%esp), %eax
	leal	(%eax,%ecx,4), %ecx
	addl	$4, %edi
	cmpl	%ecx, %ebx
	jae	.L558
	movl	(%ebx), %eax
	movl	24(%edx), %ecx
	sall	%cl, %eax
	orl	%eax, (%esi)
	addl	$4, %esi
.L558:
	movl	28(%esp), %eax
	movl	40(%esp), %ecx
	addl	$4, %ebx
	leal	(%ecx,%eax,4), %eax
	cmpl	%eax, %ebx
	jb	.L561
.L585:
	movl	64(%esp), %edx
	movl	28(%esp), %ecx
	addl	%ecx, (%ebp,%edx,4)
	movl	68(%esp), %eax
	subl	%ecx, 20(%eax)
	movl	36(%eax), %ebp
	movl	(%ebp,%edx,4), %eax
	movl	36(%esp), %ebx
	movl	8(%esp), %edx
	movl	24(%esp), %ecx
	leal	(%edx,%eax,4), %edi
	leal	(%ebx,%ecx,4), %eax
	cmpl	%eax, %ebx
	movl	92(%esp), %esi
	jae	.L587
.L567:
	movl	(%ebx), %eax
	movl	72(%esp), %edx
	movl	36(%esp), %ecx
	movl	%eax, (%edi)
	leal	(%ecx,%edx,4), %eax
	addl	$4, %edi
	cmpl	%eax, %ebx
	jae	.L564
	movl	68(%esp), %edx
	movl	(%edx), %eax
	movl	28(%eax), %ecx
	movl	(%ebx), %edx
	sall	%cl, %edx
	orl	%edx, (%esi)
	addl	$4, %esi
.L564:
	movl	24(%esp), %ecx
	movl	36(%esp), %edx
	addl	$4, %ebx
	leal	(%edx,%ecx,4), %eax
	cmpl	%eax, %ebx
	jb	.L567
.L587:
	movl	64(%esp), %ecx
	movl	24(%esp), %eax
	addl	%eax, (%ebp,%ecx,4)
	movl	68(%esp), %edx
	subl	%eax, 24(%edx)
	movl	40(%edx), %ebp
	movl	(%ebp,%ecx,4), %eax
	movl	32(%esp), %ebx
	movl	4(%esp), %ecx
	movl	20(%esp), %edx
	leal	(%ecx,%eax,4), %edi
	leal	(%ebx,%edx,4), %eax
	cmpl	%eax, %ebx
	movl	92(%esp), %esi
	jae	.L589
.L573:
	movl	(%ebx), %eax
	movl	72(%esp), %ecx
	movl	32(%esp), %edx
	movl	%eax, (%edi)
	leal	(%edx,%ecx,4), %eax
	addl	$4, %edi
	cmpl	%eax, %ebx
	jae	.L570
	movl	68(%esp), %ecx
	movl	(%ecx), %eax
	movl	(%ebx), %edx
	movl	32(%eax), %ecx
	sall	%cl, %edx
	orl	%edx, (%esi)
	addl	$4, %esi
.L570:
	movl	20(%esp), %edx
	movl	32(%esp), %ecx
	addl	$4, %ebx
	leal	(%ecx,%edx,4), %eax
	cmpl	%eax, %ebx
	jb	.L573
.L589:
	movl	20(%esp), %edx
	movl	64(%esp), %eax
	addl	%edx, (%ebp,%eax,4)
	movl	68(%esp), %ecx
	subl	%edx, 28(%ecx)
	movl	72(%esp), %edx
	movl	92(%esp), %esi
	sall	$2, %edx
	leal	(%edx,%esi), %eax
	cmpl	%eax, %esi
	jae	.L591
.L578:
	movl	92(%esp), %eax
	addl	$4, %esi
	addl	%edx, %eax
	cmpl	%eax, %esi
	jb	.L578
.L591:
	pushl	32(%esp)
	call	Xfree
	pushl	40(%esp)
	call	Xfree
	pushl	48(%esp)
	call	Xfree
	xorl	%eax, %eax
.L592:
	addl	$12, %esp
.L519:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	AllocDirect, .-AllocDirect
	.align 4
	.type	AllocPseudo, @function
AllocPseudo:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	44(%esp), %esi
	movl	40(%esp), %edi
	movl	%esi, %ecx
	sall	%cl, %edi
	cmpl	$31, %esi
	jg	.L613
	movl	36(%esp), %eax
	cmpl	20(%eax), %edi
	jg	.L613
	cmpl	40(%esp), %edi
	jl	.L613
	leal	0(,%edi,4), %ebp
	pushl	%ebp
	call	Xalloc
	movl	%eax, %ebx
	testl	%ebx, %ebx
	popl	%ecx
	movl	$11, %eax
	je	.L593
	pushl	56(%esp)
	pushl	%ebx
	pushl	56(%esp)
	pushl	%esi
	pushl	56(%esp)
	movl	56(%esp), %edx
	pushl	56(%edx)
	pushl	%edx
	call	AllocCP
	movl	%eax, 36(%esp)
	addl	$28, %esp
	cmpl	$0, 8(%esp)
	je	.L597
	movl	36(%esp), %ecx
	movl	32(%esp), %edx
	movl	32(%ecx), %eax
	movl	(%eax,%edx,4), %eax
	addl	%edi, %eax
	sall	$2, %eax
	pushl	%eax
	movl	44(%ecx), %eax
	pushl	(%eax,%edx,4)
	call	Xrealloc
	movl	%eax, %ecx
	popl	%eax
	popl	%edx
	leal	(%ebp,%ebx), %ebp
	testl	%ecx, %ecx
	movl	%ebp, 4(%esp)
	jne	.L598
	cmpl	%ebp, %ebx
	movl	%ebx, %edx
	jae	.L613
	movl	36(%esp), %eax
	movl	56(%eax), %ecx
.L603:
	imull	$20, (%edx), %eax
	movw	$0, 12(%ecx,%eax)
	addl	$4, %edx
	leal	(%ebx,%edi,4), %eax
	cmpl	%eax, %edx
	jb	.L603
.L613:
	movl	$11, %eax
	jmp	.L593
.L598:
	movl	36(%esp), %edx
	movl	44(%edx), %eax
	movl	32(%esp), %edx
	movl	%ecx, (%eax,%edx,4)
	movl	36(%esp), %eax
	movl	32(%eax), %ebp
	movl	(%ebp,%edx,4), %eax
	leal	(%ecx,%eax,4), %ecx
	movl	60(%esp), %eax
	movl	%ecx, (%eax)
	cmpl	4(%esp), %ebx
	movl	52(%esp), %esi
	movl	%ebx, %edx
	jae	.L615
.L609:
	movl	(%edx), %eax
	movl	%eax, (%ecx)
	movl	40(%esp), %eax
	leal	(%ebx,%eax,4), %eax
	addl	$4, %ecx
	cmpl	%eax, %edx
	jae	.L606
	movl	(%edx), %eax
	movl	%eax, (%esi)
	addl	$4, %esi
.L606:
	addl	$4, %edx
	leal	(%ebx,%edi,4), %eax
	cmpl	%eax, %edx
	jb	.L609
.L615:
	movl	32(%esp), %edx
	addl	%edi, (%ebp,%edx,4)
	movl	36(%esp), %ecx
	subl	%edi, 20(%ecx)
.L597:
	pushl	%ebx
	call	Xfree
	popl	%edi
	cmpl	$0, 8(%esp)
	movl	$11, %eax
	je	.L593
	xorl	%eax, %eax
.L593:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	AllocPseudo, .-AllocPseudo
	.align 4
	.type	AllocCP, @function
AllocCP:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	56(%esp), %eax
	movl	(%eax), %eax
	movswl	10(%eax),%edx
	cmpl	$0, 68(%esp)
	movl	64(%esp), %ebp
	movl	%eax, 12(%esp)
	movl	%edx, (%esp)
	jne	.L617
	xorl	%esi, %esi
	decl	%ebp
	movl	76(%esp), %edi
	movl	60(%esp), %eax
	js	.L694
.L625:
	cmpw	$0, 12(%eax)
	je	.L696
.L624:
	addl	$20, %eax
	incl	%esi
	cmpw	$0, 12(%eax)
	jne	.L624
.L696:
	movl	%esi, (%edi)
	addl	$4, %edi
	decl	%ebp
	movw	$-1, 12(%eax)
	movl	$0, 16(%eax)
	jns	.L625
.L694:
	movl	80(%esp), %ecx
	movl	$0, (%ecx)
	jmp	.L715
.L617:
	movl	(%esp), %edx
	xorl	%eax, %eax
	cmpl	%edx, 68(%esp)
	jg	.L616
	movl	$1, %eax
	movb	68(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %ebx
	movl	68(%esp), %eax
	subl	%eax, %edx
	movl	$1, 32(%esp)
	movl	%edx, (%esp)
	js	.L698
.L653:
	movl	12(%esp), %edx
	movswl	8(%edx),%edx
	subl	%ebx, %edx
	xorl	%esi, %esi
	cmpl	%edx, %esi
	movl	76(%esp), %edi
	movl	$0, 20(%esp)
	movl	%edx, 28(%esp)
	jae	.L700
.L652:
	leal	(%ebx,%esi), %eax
	movl	32(%esp), %ecx
	leal	(%ecx,%eax), %edx
	cmpl	%edx, %esi
	movl	%esi, 24(%esp)
	je	.L714
	imull	$20, %esi, %eax
	movl	60(%esp), %ecx
	cmpw	$0, 12(%ecx,%eax)
	jne	.L636
.L639:
	addl	32(%esp), %esi
	cmpl	%edx, %esi
	je	.L714
	imull	$20, %esi, %eax
	movl	60(%esp), %ecx
	cmpw	$0, 12(%ecx,%eax)
	je	.L639
.L636:
	cmpl	%edx, %esi
	jne	.L640
.L714:
	movl	24(%esp), %eax
	incl	20(%esp)
	movl	%eax, (%edi)
	addl	$4, %edi
	cmpl	%ebp, 20(%esp)
	jne	.L640
	decl	%ebp
	js	.L711
.L650:
	movl	76(%esp), %edx
	movl	(%edx,%ebp,4), %esi
	leal	(%ebx,%esi), %edx
.L649:
	imull	$20, %esi, %eax
	movl	60(%esp), %ecx
	cmpl	%edx, %esi
	movw	$-1, 12(%ecx,%eax)
	movl	$0, 16(%ecx,%eax)
	je	.L646
	addl	32(%esp), %esi
	movl	%esi, (%edi)
	addl	$4, %edi
	jmp	.L649
.L646:
	decl	%ebp
	jns	.L650
	jmp	.L711
.L640:
	movl	24(%esp), %esi
	incl	%esi
	testl	%ebx, %esi
	je	.L632
	addl	%ebx, %esi
.L632:
	cmpl	28(%esp), %esi
	jb	.L652
.L700:
	sall	%ebx
	sall	32(%esp)
	decl	(%esp)
	jns	.L653
.L698:
	movl	56(%esp), %edx
	movl	(%edx), %edx
	movswl	10(%edx),%ecx
	cmpl	$0, 72(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, (%esp)
	jne	.L705
	cmpl	$1, 68(%esp)
	je	.L705
	cmpl	$2, %ecx
	jle	.L705
	movl	68(%esp), %esi
	decl	%esi
	movl	$1, %edx
	movl	(%esp), %edi
	subl	68(%esp), %edi
	movl	%edx, %ebx
	movl	%esi, %ecx
	sall	%cl, %ebx
	leal	1(%edi), %eax
	movb	%al, %cl
	decl	%ebx
	sall	%cl, %ebx
	leal	-1(%edi), %ecx
	sall	%cl, %edx
	movl	$3, %eax
	movl	%esi, %ecx
	addl	%edx, %ebx
	sall	%cl, %eax
	movl	%ebx, 16(%esp)
	leal	-1(%eax), %ebx
	cmpl	16(%esp), %ebx
	ja	.L705
.L692:
	movl	%ebx, %esi
	shrl	%esi
	andl	$-613566757, %esi
	movl	%esi, %eax
	movl	%ebx, %edx
	subl	%esi, %edx
	shrl	%eax
	andl	$-613566757, %eax
	movl	%edx, %esi
	subl	%eax, %esi
	movl	%esi, %eax
	shrl	$3, %eax
	movl	$63, %edx
	leal	(%eax,%esi), %eax
	andl	$-954437177, %eax
	movl	%edx, %ecx
	xorl	%edx, %edx
	divl	%ecx
	cmpl	68(%esp), %edx
	jne	.L658
	movl	8(%esp), %eax
	movl	%ebx, %edx
	notl	%edx
	movswl	8(%eax),%eax
	subl	%ebx, %eax
	movl	%edx, 4(%esp)
	xorl	%esi, %esi
	incl	%edx
	andl	%ebx, %edx
	cmpl	%eax, %esi
	movl	76(%esp), %edi
	movl	$0, 20(%esp)
	movl	%eax, 28(%esp)
	movl	%edx, 32(%esp)
	jae	.L658
.L691:
	testl	%ebx, %esi
	jne	.L663
	imull	$20, %esi, %eax
	movl	60(%esp), %ecx
	xorl	%edx, %edx
	cmpw	$0, 12(%ecx,%eax)
	jne	.L667
.L674:
	cmpl	%ebx, %edx
	je	.L667
	addl	32(%esp), %edx
	movl	4(%esp), %ecx
	testl	%ecx, %edx
	je	.L709
.L673:
	movl	%edx, %eax
	andl	%ecx, %eax
	addl	%eax, %edx
	testl	%ecx, %edx
	jne	.L673
.L709:
	leal	(%edx,%esi), %eax
	imull	$20, %eax, %eax
	movl	60(%esp), %ecx
	cmpw	$0, 12(%ecx,%eax)
	je	.L674
.L667:
	cmpl	%ebx, %edx
	jb	.L663
	leal	(%ebx,%esi), %eax
	imull	$20, %eax, %eax
	movl	60(%esp), %edx
	cmpw	$0, 12(%edx,%eax)
	jne	.L663
	incl	20(%esp)
	movl	%esi, (%edi)
	addl	$4, %edi
	cmpl	%ebp, 20(%esp)
	jl	.L663
	decl	%ebp
	js	.L711
.L690:
	movl	76(%esp), %ecx
	movl	(%ecx,%ebp,4), %esi
	xorl	%edx, %edx
.L689:
	leal	(%edx,%esi), %eax
	imull	$20, %eax, %eax
	movl	60(%esp), %ecx
	cmpl	%ebx, %edx
	movw	$-1, 12(%ecx,%eax)
	movl	$0, 16(%ecx,%eax)
	je	.L682
	movl	%ebx, %ecx
	addl	32(%esp), %edx
	notl	%ecx
	testl	%ecx, %edx
	je	.L713
.L688:
	movl	%edx, %eax
	andl	%ecx, %eax
	addl	%eax, %edx
	testl	%ecx, %edx
	jne	.L688
.L713:
	leal	(%edx,%esi), %eax
	movl	%eax, (%edi)
	addl	$4, %edi
	jmp	.L689
.L682:
	decl	%ebp
	jns	.L690
.L711:
	movl	80(%esp), %eax
	movl	%ebx, (%eax)
.L715:
	movl	$1, %eax
	jmp	.L616
.L663:
	incl	%esi
	cmpl	28(%esp), %esi
	jb	.L691
.L658:
	incl	%ebx
	cmpl	16(%esp), %ebx
	jbe	.L692
.L705:
	xorl	%eax, %eax
.L616:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	AllocCP, .-AllocCP
	.align 4
	.type	AllocShared, @function
AllocShared:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	76(%esp), %ecx
	movl	72(%esp), %edi
	addl	80(%esp), %ecx
	addl	84(%esp), %ecx
	movl	%edi, %eax
	sall	%cl, %eax
	movl	%eax, 32(%esp)
	movb	76(%esp), %cl
	movl	%edi, %eax
	sall	%cl, %eax
	movl	%edi, %edx
	movb	80(%esp), %cl
	sall	%cl, %edx
	addl	%edx, %eax
	movb	84(%esp), %cl
	movl	%edi, %edx
	sall	%cl, %edx
	leal	(%edx,%eax), %esi
	leal	0(,%esi,4), %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, 16(%esp)
	popl	%eax
	xorl	%eax, %eax
	cmpl	$0, 12(%esp)
	je	.L716
	movl	%esi, %ebx
	movl	12(%esp), %eax
	decl	%ebx
	movl	%eax, 16(%esp)
	js	.L804
.L728:
	pushl	$4
	call	Xalloc
	movl	16(%esp), %edx
	movl	%eax, (%edx,%ebx,4)
	testl	%eax, %eax
	popl	%ebp
	jne	.L718
	incl	%ebx
	cmpl	%esi, %ebx
	jge	.L806
.L727:
	movl	12(%esp), %ecx
	pushl	(%ecx,%ebx,4)
	incl	%ebx
	call	Xfree
	cmpl	%esi, %ebx
	popl	%edi
	jl	.L727
.L806:
	xorl	%eax, %eax
	jmp	.L716
.L718:
	decl	%ebx
	jns	.L728
.L804:
	movl	68(%esp), %eax
	decl	%edi
	movl	%eax, 40(%esp)
	movl	%edi, 36(%esp)
	js	.L808
.L802:
	movl	92(%esp), %edx
	orl	96(%esp), %edx
	notl	%edx
	movl	40(%esp), %ecx
	movl	%edx, 28(%esp)
	andl	(%ecx), %edx
	cmpl	$0, 88(%esp)
	movl	%edx, 20(%esp)
	je	.L733
	movl	88(%esp), %eax
	notl	%eax
	movl	%eax, 8(%esp)
	movl	88(%esp), %edx
	incl	%eax
	andl	%edx, %eax
	xorl	%edi, %edi
	movl	%eax, 24(%esp)
.L824:
	movl	16(%esp), %ecx
	movl	(%ecx), %esi
	addl	$4, %ecx
	movl	%ecx, 16(%esp)
	movl	80(%esp), %ecx
	addl	84(%esp), %ecx
	movl	$1, %eax
	movl	32(%esp), %ebx
	sall	%cl, %eax
	decl	%ebx
	movw	%ax, 2(%esi)
	movl	100(%esp), %ecx
	js	.L810
.L742:
	movl	(%ecx), %ebp
	movl	28(%esp), %edx
	movl	20(%esp), %eax
	andl	%ebp, %edx
	orl	%edi, %eax
	cmpl	%eax, %edx
	jne	.L739
	movl	64(%esp), %eax
	movl	56(%eax), %edx
	imull	$20, %ebp, %eax
	movl	$1, 16(%edx,%eax)
	movl	%esi, (%edx,%eax)
.L739:
	addl	$4, %ecx
	decl	%ebx
	jns	.L742
.L810:
	cmpl	88(%esp), %edi
	je	.L749
	addl	24(%esp), %edi
	movl	8(%esp), %edx
	testl	%edx, %edi
	je	.L824
.L747:
	movl	%edi, %eax
	andl	%edx, %eax
	addl	%eax, %edi
	testl	%edx, %edi
	jne	.L747
	jmp	.L824
.L733:
	movl	80(%esp), %ecx
	movl	16(%esp), %edx
	addl	84(%esp), %ecx
	movl	$1, %eax
	movl	32(%esp), %ebx
	sall	%cl, %eax
	movl	(%edx), %esi
	addl	$4, %edx
	decl	%ebx
	movl	%edx, 16(%esp)
	movw	%ax, 2(%esi)
	movl	100(%esp), %ecx
	js	.L749
.L755:
	movl	(%ecx), %edi
	movl	28(%esp), %eax
	andl	%edi, %eax
	cmpl	20(%esp), %eax
	jne	.L752
	movl	64(%esp), %eax
	movl	56(%eax), %edx
	imull	$20, %edi, %eax
	movl	$1, 16(%edx,%eax)
	movl	%esi, (%edx,%eax)
.L752:
	addl	$4, %ecx
	decl	%ebx
	jns	.L755
.L749:
	movl	88(%esp), %edx
	orl	96(%esp), %edx
	notl	%edx
	movl	40(%esp), %ecx
	movl	%edx, 28(%esp)
	andl	(%ecx), %edx
	cmpl	$0, 92(%esp)
	movl	%edx, 20(%esp)
	je	.L756
	movl	92(%esp), %eax
	notl	%eax
	movl	%eax, 4(%esp)
	movl	92(%esp), %edx
	incl	%eax
	andl	%edx, %eax
	xorl	%edi, %edi
	movl	%eax, 24(%esp)
.L825:
	movl	16(%esp), %ecx
	movl	(%ecx), %esi
	addl	$4, %ecx
	movl	%ecx, 16(%esp)
	movl	76(%esp), %ecx
	addl	84(%esp), %ecx
	movl	$1, %eax
	movl	32(%esp), %ebx
	sall	%cl, %eax
	decl	%ebx
	movw	%ax, 2(%esi)
	movl	100(%esp), %ecx
	js	.L815
.L765:
	movl	(%ecx), %ebp
	movl	28(%esp), %edx
	movl	20(%esp), %eax
	andl	%ebp, %edx
	orl	%edi, %eax
	cmpl	%eax, %edx
	jne	.L762
	movl	64(%esp), %eax
	movl	56(%eax), %edx
	imull	$20, %ebp, %eax
	movl	%esi, 4(%edx,%eax)
.L762:
	addl	$4, %ecx
	decl	%ebx
	jns	.L765
.L815:
	cmpl	92(%esp), %edi
	je	.L772
	addl	24(%esp), %edi
	movl	4(%esp), %edx
	testl	%edx, %edi
	je	.L825
.L770:
	movl	%edi, %eax
	andl	%edx, %eax
	addl	%eax, %edi
	testl	%edx, %edi
	jne	.L770
	jmp	.L825
.L756:
	movl	80(%esp), %ecx
	movl	16(%esp), %edx
	addl	84(%esp), %ecx
	movl	$1, %eax
	movl	32(%esp), %ebx
	sall	%cl, %eax
	movl	(%edx), %esi
	addl	$4, %edx
	decl	%ebx
	movl	%edx, 16(%esp)
	movw	%ax, 2(%esi)
	movl	100(%esp), %ecx
	js	.L772
.L778:
	movl	(%ecx), %edi
	movl	28(%esp), %eax
	andl	%edi, %eax
	cmpl	20(%esp), %eax
	jne	.L775
	movl	64(%esp), %eax
	movl	56(%eax), %edx
	imull	$20, %edi, %eax
	movl	%esi, 4(%edx,%eax)
.L775:
	addl	$4, %ecx
	decl	%ebx
	jns	.L778
.L772:
	movl	88(%esp), %edx
	orl	92(%esp), %edx
	notl	%edx
	movl	40(%esp), %ecx
	movl	%edx, 28(%esp)
	andl	(%ecx), %edx
	cmpl	$0, 96(%esp)
	movl	%edx, 20(%esp)
	je	.L779
	movl	96(%esp), %eax
	notl	%eax
	movl	%eax, (%esp)
	movl	96(%esp), %edx
	incl	%eax
	andl	%edx, %eax
	xorl	%edi, %edi
	movl	%eax, 24(%esp)
.L826:
	movl	16(%esp), %ecx
	movl	(%ecx), %esi
	addl	$4, %ecx
	movl	%ecx, 16(%esp)
	movl	76(%esp), %ecx
	addl	80(%esp), %ecx
	movl	$1, %eax
	movl	32(%esp), %ebx
	sall	%cl, %eax
	decl	%ebx
	movw	%ax, 2(%esi)
	movl	100(%esp), %ecx
	js	.L820
.L788:
	movl	(%ecx), %ebp
	movl	28(%esp), %edx
	movl	20(%esp), %eax
	andl	%ebp, %edx
	orl	%edi, %eax
	cmpl	%eax, %edx
	jne	.L785
	movl	64(%esp), %eax
	movl	56(%eax), %edx
	imull	$20, %ebp, %eax
	movl	%esi, 8(%edx,%eax)
.L785:
	addl	$4, %ecx
	decl	%ebx
	jns	.L788
.L820:
	cmpl	96(%esp), %edi
	je	.L731
	addl	24(%esp), %edi
	movl	(%esp), %edx
	testl	%edx, %edi
	je	.L826
.L793:
	movl	%edi, %eax
	andl	%edx, %eax
	addl	%eax, %edi
	testl	%edx, %edi
	jne	.L793
	jmp	.L826
.L779:
	movl	80(%esp), %ecx
	movl	16(%esp), %edx
	addl	84(%esp), %ecx
	movl	$1, %eax
	movl	32(%esp), %ebx
	sall	%cl, %eax
	movl	(%edx), %esi
	addl	$4, %edx
	decl	%ebx
	movl	%edx, 16(%esp)
	movw	%ax, 2(%esi)
	movl	100(%esp), %ecx
	js	.L731
.L801:
	movl	(%ecx), %edi
	movl	28(%esp), %eax
	andl	%edi, %eax
	cmpl	20(%esp), %eax
	jne	.L798
	movl	64(%esp), %eax
	movl	56(%eax), %edx
	imull	$20, %edi, %eax
	movl	%esi, 8(%edx,%eax)
.L798:
	addl	$4, %ecx
	decl	%ebx
	jns	.L801
.L731:
	addl	$4, 40(%esp)
	decl	36(%esp)
	jns	.L802
.L808:
	pushl	12(%esp)
	call	Xfree
	movl	$1, %eax
	popl	%ebx
.L716:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	AllocShared, .-AllocShared
	.align 4
.globl FreeColors
	.type	FreeColors, @function
FreeColors:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %ebp
	testb	$2, 16(%ebp)
	movl	36(%esp), %ebx
	movswl	4(%ebp),%eax
	je	.L828
	movl	$10, %eax
	jmp	.L827
.L828:
	orl	$1, %eax
	cmpl	$5, %eax
	movl	(%ebp), %edx
	jne	.L829
	movl	12(%edx), %eax
	movl	%eax, %esi
	orl	16(%edx), %esi
	andl	%ebx, %eax
	orl	20(%edx), %esi
	pushl	%eax
	pushl	36(%esp)
	pushl	36(%esp)
	pushl	$0
	pushl	40(%esp)
	pushl	%ebp
	call	FreeCo
	movl	%eax, %edi
	movl	%ebx, %edx
	movl	(%ebp), %eax
	andl	16(%eax), %edx
	pushl	%edx
	pushl	60(%esp)
	pushl	60(%esp)
	pushl	$1
	pushl	64(%esp)
	pushl	%ebp
	call	FreeCo
	andl	%ebx, %esi
	addl	$48, %esp
	testl	%eax, %eax
	je	.L830
	movl	%eax, %edi
.L830:
	movl	(%ebp), %eax
	movl	%ebx, %edx
	andl	20(%eax), %edx
	pushl	%edx
	pushl	36(%esp)
	pushl	36(%esp)
	pushl	$2
	pushl	40(%esp)
	pushl	%ebp
	call	FreeCo
	addl	$24, %esp
	testl	%eax, %eax
	je	.L832
	movl	%eax, %edi
	jmp	.L832
.L829:
	movswl	10(%edx),%ecx
	movl	$1, %eax
	sall	%cl, %eax
	leal	-1(%eax), %esi
	andl	%ebx, %esi
	pushl	%esi
	pushl	36(%esp)
	pushl	36(%esp)
	pushl	$3
	pushl	40(%esp)
	pushl	%ebp
	call	FreeCo
	movl	%eax, %edi
	addl	$24, %esp
.L832:
	cmpl	%esi, %ebx
	je	.L833
	cmpl	$0, 28(%esp)
	je	.L833
	movl	32(%esp), %eax
	orl	(%eax), %ebx
	movl	%ebx, clientErrorValue
	movl	$2, %edi
.L833:
	movl	%edi, %eax
.L827:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	FreeColors, .-FreeColors
	.align 4
	.type	FreeCo, @function
FreeCo:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	xorl	%eax, %eax
	cmpl	$0, 72(%esp)
	movl	$0, 12(%esp)
	je	.L834
	movl	80(%esp), %eax
	notl	%eax
	movl	%eax, (%esp)
	movl	80(%esp), %edx
	incl	%eax
	andl	%edx, %eax
	cmpl	$1, 68(%esp)
	movl	$0, 32(%esp)
	movl	$0, 16(%esp)
	movl	%eax, 28(%esp)
	je	.L838
	cmpl	$1, 68(%esp)
	jg	.L843
	cmpl	$0, 68(%esp)
	je	.L837
	jmp	.L841
.L843:
	cmpl	$2, 68(%esp)
	je	.L839
	jmp	.L841
.L837:
	movl	60(%esp), %ecx
	movl	(%ecx), %eax
	movl	12(%eax), %edx
	movl	%edx, %edi
	orl	16(%eax), %edi
	orl	20(%eax), %edi
	movl	24(%eax), %eax
	movl	%eax, 8(%esp)
	movb	8(%esp), %cl
	movl	%edx, %eax
	shrl	%cl, %eax
	movl	%edx, 24(%esp)
	incl	%eax
	notl	%edi
	movl	60(%esp), %edx
	jmp	.L899
.L838:
	movl	60(%esp), %edx
	movl	(%edx), %eax
	movl	16(%eax), %ecx
	movl	%ecx, %edi
	orl	12(%eax), %edi
	orl	20(%eax), %edi
	movl	28(%eax), %eax
	movl	%eax, 8(%esp)
	movl	%ecx, 24(%esp)
	movl	%ecx, %eax
	movb	8(%esp), %cl
	shrl	%cl, %eax
	incl	%eax
	movl	%eax, 4(%esp)
	movl	48(%edx), %eax
	movl	64(%esp), %edx
	movl	(%eax,%edx,4), %eax
	movl	60(%esp), %ecx
	movl	%eax, 36(%esp)
	notl	%edi
	movl	36(%ecx), %eax
	jmp	.L896
.L839:
	movl	60(%esp), %edx
	movl	(%edx), %eax
	movl	16(%eax), %edi
	movl	20(%eax), %ecx
	orl	12(%eax), %edi
	movl	32(%eax), %eax
	movl	%eax, 8(%esp)
	orl	%ecx, %edi
	movl	%ecx, %eax
	movl	%ecx, 24(%esp)
	movb	8(%esp), %cl
	shrl	%cl, %eax
	incl	%eax
	movl	%eax, 4(%esp)
	movl	52(%edx), %eax
	movl	64(%esp), %edx
	movl	(%eax,%edx,4), %eax
	movl	60(%esp), %ecx
	movl	%eax, 36(%esp)
	notl	%edi
	movl	40(%ecx), %eax
.L896:
	movl	(%eax,%edx,4), %ebp
	jmp	.L894
.L841:
	movl	60(%esp), %edx
	movl	(%edx), %eax
	movswl	8(%eax),%eax
	movl	$-1, 24(%esp)
	xorl	%edi, %edi
	movl	$0, 8(%esp)
.L899:
	movl	%eax, 4(%esp)
	movl	64(%esp), %ecx
	movl	44(%edx), %eax
	movl	(%eax,%ecx,4), %eax
	movl	%eax, 36(%esp)
	movl	32(%edx), %eax
	movl	(%eax,%ecx,4), %ebp
.L894:
	movl	72(%esp), %eax
	decl	%eax
	movl	76(%esp), %esi
	movl	%eax, 20(%esp)
	js	.L888
.L862:
	movl	(%esi), %eax
	movl	32(%esp), %ebx
	orl	%eax, %ebx
	movl	24(%esp), %edx
	andl	%ebx, %edx
	movb	8(%esp), %cl
	shrl	%cl, %edx
	cmpl	4(%esp), %edx
	jae	.L852
	testl	%edi, %eax
	je	.L851
.L852:
	movl	%ebx, clientErrorValue
	movl	$2, 12(%esp)
	jmp	.L849
.L851:
	movl	%ebp, %eax
	decl	%eax
	movl	36(%esp), %ebx
	js	.L859
	cmpl	%edx, (%ebx)
	je	.L854
.L858:
	addl	$4, %ebx
	decl	%eax
	js	.L859
	cmpl	%edx, (%ebx)
	jne	.L858
.L854:
	testl	%eax, %eax
	js	.L859
	movl	60(%esp), %eax
	testb	$1, 4(%eax)
	je	.L860
	pushl	68(%esp)
	pushl	%edx
	pushl	%eax
	call	FreeCell
	addl	$12, %esp
.L860:
	incl	16(%esp)
	movl	$-1, (%ebx)
	jmp	.L849
.L859:
	movl	$10, 12(%esp)
.L849:
	addl	$4, %esi
	decl	20(%esp)
	jns	.L862
.L888:
	movl	80(%esp), %edx
	cmpl	%edx, 32(%esp)
	je	.L845
	movl	28(%esp), %ecx
	addl	%ecx, 32(%esp)
	movl	(%esp), %edx
	testl	%edx, 32(%esp)
	je	.L894
.L867:
	movl	32(%esp), %eax
	andl	%edx, %eax
	addl	%eax, 32(%esp)
	testl	%edx, 32(%esp)
	jne	.L867
	jmp	.L894
.L845:
	cmpl	$0, 16(%esp)
	je	.L869
	movl	%ebp, %edi
	subl	16(%esp), %edi
	je	.L870
	xorl	%eax, %eax
	movl	36(%esp), %ebx
	cmpl	%edi, %eax
	movl	%ebx, %esi
	jge	.L893
.L876:
	movl	(%ebx), %edx
	cmpl	$-1, %edx
	je	.L873
	movl	%edx, (%esi)
	incl	%eax
	addl	$4, %esi
.L873:
	addl	$4, %ebx
	cmpl	%edi, %eax
	jl	.L876
.L893:
	leal	0(,%edi,4), %eax
	pushl	%eax
	pushl	40(%esp)
	call	Xrealloc
	movl	%eax, %esi
	testl	%esi, %esi
	popl	%eax
	popl	%edx
	je	.L877
	movl	%esi, 36(%esp)
.L877:
	movl	%edi, %ebp
	jmp	.L878
.L870:
	pushl	36(%esp)
	call	Xfree
	xorl	%ebp, %ebp
	movl	$0, 40(%esp)
	popl	%eax
.L878:
	cmpl	$1, 68(%esp)
	je	.L882
	cmpl	$1, 68(%esp)
	jg	.L886
	cmpl	$0, 68(%esp)
	jmp	.L897
.L886:
	cmpl	$2, 68(%esp)
	je	.L883
	cmpl	$3, 68(%esp)
.L897:
	jne	.L869
	movl	60(%esp), %edx
	movl	44(%edx), %eax
	movl	64(%esp), %ecx
	movl	36(%esp), %edx
	movl	%edx, (%eax,%ecx,4)
	movl	60(%esp), %ecx
	movl	32(%ecx), %eax
	jmp	.L898
.L882:
	movl	60(%esp), %ecx
	movl	48(%ecx), %eax
	movl	64(%esp), %edx
	movl	36(%esp), %ecx
	movl	%ecx, (%eax,%edx,4)
	movl	60(%esp), %edx
	movl	36(%edx), %eax
	movl	64(%esp), %ecx
	movl	%ebp, (%eax,%ecx,4)
	jmp	.L869
.L883:
	movl	60(%esp), %edx
	movl	52(%edx), %eax
	movl	64(%esp), %ecx
	movl	36(%esp), %edx
	movl	%edx, (%eax,%ecx,4)
	movl	60(%esp), %ecx
	movl	40(%ecx), %eax
.L898:
	movl	64(%esp), %edx
	movl	%ebp, (%eax,%edx,4)
.L869:
	movl	12(%esp), %eax
.L834:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	FreeCo, .-FreeCo
	.align 4
.globl StoreColors
	.type	StoreColors, @function
StoreColors:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$68, %esp
	movl	88(%esp), %edx
	movswl	4(%edx),%eax
	testb	$1, %al
	movl	$0, 12(%esp)
	jne	.L901
	testb	$4, 16(%edx)
	jne	.L901
	movl	$10, %eax
	jmp	.L900
.L901:
	orl	$1, %eax
	movl	88(%esp), %ecx
	cmpl	$5, %eax
	movl	(%ecx), %ebp
	movl	$0, 16(%esp)
	jne	.L902
	movl	12(%ebp), %esi
	movl	24(%ebp), %ecx
	movl	%esi, %eax
	shrl	%cl, %eax
	incl	%eax
	movl	16(%ebp), %ebx
	movl	28(%ebp), %ecx
	movl	%eax, 8(%esp)
	movl	%ebx, %eax
	shrl	%cl, %eax
	incl	%eax
	movl	20(%ebp), %edx
	movl	%eax, 4(%esp)
	movl	32(%ebp), %ecx
	movl	%edx, %eax
	orl	%ebx, %esi
	shrl	%cl, %eax
	movl	92(%esp), %ebx
	incl	%eax
	orl	%edx, %esi
	cmpl	%ebx, 16(%esp)
	movl	%eax, (%esp)
	notl	%esi
	movl	96(%esp), %edi
	movl	$0, 32(%esp)
	jge	.L930
.L929:
	movl	88(%esp), %eax
	movl	12(%eax), %edx
	pushl	(%eax)
	leal	8(%edi), %eax
	pushl	%eax
	leal	6(%edi), %eax
	pushl	%eax
	leal	4(%edi), %eax
	pushl	%eax
	call	*308(%edx)
	movl	(%edi), %eax
	addl	$16, %esp
	testl	%esi, %eax
	movl	$1, %ebx
	je	.L907
	movl	$2, 12(%esp)
	jmp	.L985
.L907:
	andl	12(%ebp), %eax
	movl	24(%ebp), %ecx
	shrl	%cl, %eax
	cmpl	8(%esp), %eax
	jb	.L908
	movl	$2, 12(%esp)
	jmp	.L983
.L908:
	movl	88(%esp), %edx
	movl	56(%edx), %ecx
	imull	$20, %eax, %edx
	cmpw	$-1, 12(%ecx,%edx)
	je	.L910
	movl	$10, 12(%esp)
.L983:
	xorl	%ebx, %ebx
	jmp	.L909
.L910:
	testb	$1, 10(%edi)
	je	.L912
	movw	4(%edi), %ax
	movw	%ax, (%ecx,%edx)
	jmp	.L909
.L912:
	movw	(%ecx,%edx), %ax
	movw	%ax, 4(%edi)
.L909:
	movl	16(%ebp), %eax
	andl	(%edi), %eax
	movl	28(%ebp), %ecx
	shrl	%cl, %eax
	cmpl	4(%esp), %eax
	jb	.L914
	movl	$2, 12(%esp)
	jmp	.L984
.L914:
	movl	88(%esp), %edx
	movl	60(%edx), %ecx
	imull	$20, %eax, %edx
	cmpw	$-1, 12(%ecx,%edx)
	je	.L916
	movl	$10, 12(%esp)
.L984:
	xorl	%ebx, %ebx
	jmp	.L915
.L916:
	testb	$2, 10(%edi)
	je	.L918
	movw	6(%edi), %ax
	movw	%ax, 2(%ecx,%edx)
	jmp	.L915
.L918:
	movw	2(%ecx,%edx), %ax
	movw	%ax, 6(%edi)
.L915:
	movl	20(%ebp), %eax
	andl	(%edi), %eax
	movl	32(%ebp), %ecx
	shrl	%cl, %eax
	cmpl	(%esp), %eax
	jb	.L920
	movl	$2, 12(%esp)
	jmp	.L926
.L920:
	movl	88(%esp), %edx
	movl	64(%edx), %ecx
	imull	$20, %eax, %edx
	cmpw	$-1, 12(%ecx,%edx)
	je	.L922
	movl	$10, 12(%esp)
	jmp	.L926
.L922:
	testb	$4, 10(%edi)
	je	.L924
	movw	8(%edi), %ax
	movw	%ax, 4(%ecx,%edx)
	jmp	.L921
.L924:
	movw	4(%ecx,%edx), %ax
	movw	%ax, 8(%edi)
.L921:
	testl	%ebx, %ebx
	je	.L926
	movl	32(%esp), %ecx
	cmpl	%ecx, 16(%esp)
	je	.L927
	imull	$12, 32(%esp), %edx
	movl	96(%esp), %ebx
	movl	(%ebx,%edx), %eax
	imull	$12, 16(%esp), %ecx
	movl	%eax, (%ebx,%ecx)
	movl	4(%ebx,%edx), %eax
	movl	%eax, 4(%ebx,%ecx)
	movl	8(%ebx,%edx), %eax
	movl	%eax, 8(%ebx,%ecx)
.L927:
	incl	16(%esp)
	jmp	.L905
.L926:
	movl	(%edi), %eax
.L985:
	movl	%eax, clientErrorValue
.L905:
	incl	32(%esp)
	movl	92(%esp), %eax
	addl	$12, %edi
	cmpl	%eax, 32(%esp)
	jl	.L929
	jmp	.L930
.L902:
	movl	92(%esp), %edx
	cmpl	%edx, 16(%esp)
	movl	96(%esp), %edi
	movl	$0, 32(%esp)
	jge	.L974
.L973:
	movswl	8(%ebp),%eax
	movl	(%edi), %ecx
	cmpl	%eax, %ecx
	movl	$1, %ebx
	jb	.L935
	movl	%ecx, clientErrorValue
	movl	$2, 12(%esp)
	jmp	.L933
.L935:
	movl	88(%esp), %esi
	movl	56(%esi), %edx
	imull	$20, %ecx, %eax
	cmpw	$-1, 12(%edx,%eax)
	je	.L982
	movl	$10, 12(%esp)
	jmp	.L933
.L982:
	movl	32(%esp), %eax
	cmpl	%eax, 16(%esp)
	je	.L939
	movl	96(%esp), %esi
	imull	$12, %eax, %edx
	movl	(%esi,%edx), %eax
	imull	$12, 16(%esp), %ecx
	movl	%eax, (%esi,%ecx)
	movl	4(%esi,%edx), %eax
	movl	%eax, 4(%esi,%ecx)
	movl	8(%esi,%edx), %eax
	movl	%eax, 8(%esi,%ecx)
.L939:
	movl	88(%esp), %eax
	incl	16(%esp)
	movl	12(%eax), %edx
	pushl	(%eax)
	leal	8(%edi), %eax
	pushl	%eax
	leal	6(%edi), %eax
	pushl	%eax
	leal	4(%edi), %eax
	pushl	%eax
	call	*308(%edx)
	imull	$20, (%edi), %esi
	movl	104(%esp), %edx
	addl	56(%edx), %esi
	addl	$16, %esp
	testb	$1, 10(%edi)
	movl	16(%esi), %eax
	je	.L941
	testl	%eax, %eax
	movw	4(%edi), %dx
	je	.L942
	movl	(%esi), %eax
	movw	%dx, (%eax)
	movl	(%esi), %eax
	cmpw	$1, 2(%eax)
	jle	.L945
	xorl	%ebx, %ebx
	jmp	.L945
.L942:
	movw	%dx, (%esi)
	jmp	.L945
.L941:
	testl	%eax, %eax
	je	.L946
	movl	(%esi), %eax
	movw	(%eax), %ax
	jmp	.L986
.L946:
	movw	(%esi), %ax
.L986:
	movw	%ax, 4(%edi)
.L945:
	testb	$2, 10(%edi)
	movl	16(%esi), %eax
	je	.L948
	testl	%eax, %eax
	movw	6(%edi), %dx
	je	.L949
	movl	4(%esi), %eax
	movw	%dx, (%eax)
	movl	4(%esi), %eax
	cmpw	$1, 2(%eax)
	jle	.L952
	xorl	%ebx, %ebx
	jmp	.L952
.L949:
	movw	%dx, 2(%esi)
	jmp	.L952
.L948:
	testl	%eax, %eax
	je	.L953
	movl	4(%esi), %eax
	movw	(%eax), %ax
	jmp	.L987
.L953:
	movw	2(%esi), %ax
.L987:
	movw	%ax, 6(%edi)
.L952:
	testb	$4, 10(%edi)
	movl	16(%esi), %eax
	je	.L955
	testl	%eax, %eax
	movw	8(%edi), %dx
	je	.L956
	movl	8(%esi), %eax
	movw	%dx, (%eax)
	movl	8(%esi), %eax
	cmpw	$1, 2(%eax)
	jle	.L959
	jmp	.L980
.L956:
	movw	%dx, 4(%esi)
	jmp	.L959
.L955:
	testl	%eax, %eax
	je	.L960
	movl	8(%esi), %eax
	movw	(%eax), %ax
	jmp	.L988
.L960:
	movw	4(%esi), %ax
.L988:
	movw	%ax, 8(%edi)
.L959:
	testl	%ebx, %ebx
	jne	.L933
.L980:
	movl	(%esi), %ecx
	movl	%ecx, 44(%esp)
	movl	4(%esi), %ebx
	movl	%ebx, 40(%esp)
	movl	8(%esi), %eax
	movl	%eax, 36(%esp)
	movzbl	10(%edi), %eax
	movl	%eax, %edx
	movl	%eax, %ecx
	andl	$4, %eax
	andl	$1, %edx
	movl	88(%esp), %ebx
	movl	%eax, 20(%esp)
	movswl	8(%ebp),%eax
	imull	$20, %eax, %eax
	movl	%edx, 28(%esp)
	movl	56(%ebx), %edx
	leal	(%eax,%edx), %eax
	andl	$2, %ecx
	cmpl	%eax, %edx
	movl	%ecx, 24(%esp)
	movl	%eax, 48(%esp)
	movl	%edx, %ebx
	jae	.L933
.L972:
	cmpl	$0, 16(%ebx)
	je	.L965
	cmpl	%esi, %ebx
	je	.L965
	cmpl	$0, 28(%esp)
	movb	$0, 62(%esp)
	je	.L968
	movl	44(%esp), %eax
	cmpl	%eax, (%ebx)
	jne	.L968
	movb	$1, 62(%esp)
.L968:
	cmpl	$0, 24(%esp)
	je	.L969
	movl	40(%esp), %edx
	cmpl	%edx, 4(%ebx)
	jne	.L969
	orb	$2, 62(%esp)
.L969:
	cmpl	$0, 20(%esp)
	je	.L970
	movl	36(%esp), %ecx
	cmpl	%ecx, 8(%ebx)
	jne	.L970
	orb	$4, 62(%esp)
.L970:
	cmpb	$0, 62(%esp)
	je	.L965
	movl	88(%esp), %edx
	movl	%ebx, %eax
	subl	56(%edx), %eax
	sarl	$2, %eax
	imull	$-858993459, %eax, %eax
	movl	%eax, 52(%esp)
	movl	(%ebx), %eax
	movw	(%eax), %ax
	movw	%ax, 56(%esp)
	movl	4(%ebx), %eax
	movw	(%eax), %ax
	movw	%ax, 58(%esp)
	movl	8(%ebx), %eax
	movw	(%eax), %ax
	movw	%ax, 60(%esp)
	leal	52(%esp), %eax
	movl	%edx, %ecx
	movl	12(%edx), %edx
	pushl	%eax
	pushl	$1
	pushl	%ecx
	call	*304(%edx)
	addl	$12, %esp
.L965:
	addl	$20, %ebx
	cmpl	48(%esp), %ebx
	jb	.L972
.L933:
	incl	32(%esp)
	movl	92(%esp), %ebx
	addl	$12, %edi
	cmpl	%ebx, 32(%esp)
	jl	.L973
.L930:
	cmpl	$0, 16(%esp)
	je	.L974
	movl	88(%esp), %esi
	movl	12(%esi), %eax
	pushl	96(%esp)
	pushl	20(%esp)
	pushl	%esi
	call	*304(%eax)
	addl	$12, %esp
.L974:
	movl	12(%esp), %eax
.L900:
	addl	$68, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	StoreColors, .-StoreColors
	.align 4
.globl IsMapInstalled
	.type	IsMapInstalled, @function
IsMapInstalled:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	20(%esp), %esi
	movl	16(%esi), %eax
	movswl	34(%eax),%eax
	sall	$2, %eax
	movl	16(%esp), %edi
	pushl	%eax
	call	Xalloc
	movl	%eax, %ebx
	popl	%eax
	xorl	%eax, %eax
	testl	%ebx, %ebx
	je	.L989
	jmp	.L990
.L998:
	movl	$1, %esi
	jmp	.L992
.L990:
	movl	16(%esi), %eax
	pushl	%ebx
	pushl	%eax
	call	*300(%eax)
	xorl	%esi, %esi
	xorl	%edx, %edx
	popl	%ecx
	cmpl	%eax, %esi
	popl	%ecx
	jge	.L992
.L996:
	cmpl	%edi, (%ebx,%edx,4)
	je	.L998
	incl	%edx
	cmpl	%eax, %edx
	jl	.L996
.L992:
	pushl	%ebx
	call	Xfree
	movl	%esi, %eax
	popl	%ecx
.L989:
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	IsMapInstalled, .-IsMapInstalled
	.ident	"GCC: (GNU) 3.3.2"
