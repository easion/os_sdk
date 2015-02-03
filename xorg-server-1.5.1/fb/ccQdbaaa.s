	.file	"fbbltone.c"
.globl fb8Lane
	.data
	.type	fb8Lane, @object
	.size	fb8Lane, 16
fb8Lane:
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	12
	.byte	13
	.byte	14
	.byte	15
.globl fb16Lane
	.type	fb16Lane, @object
	.size	fb16Lane, 16
fb16Lane:
	.byte	0
	.byte	3
	.byte	12
	.byte	15
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.globl fb32Lane
	.type	fb32Lane, @object
	.size	fb32Lane, 16
fb32Lane:
	.byte	0
	.byte	15
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.globl fbLaneTable
	.align 32
	.type	fbLaneTable, @object
	.size	fbLaneTable, 132
fbLaneTable:
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	fb8Lane
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	fb16Lane
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	fb32Lane
	.text
	.align 4
.globl fbBltOne
	.type	fbBltOne, @function
fbBltOne:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$112, %esp
	movl	136(%esp), %eax
	movl	140(%esp), %edx
	movl	148(%esp), %ecx
	movl	%eax, 108(%esp)
	movl	156(%esp), %eax
	movl	%eax, 96(%esp)
	movl	%edx, 104(%esp)
	movl	168(%esp), %eax
	movl	160(%esp), %edx
	movl	%ecx, 100(%esp)
	movl	164(%esp), %ecx
	movl	%edx, 92(%esp)
	movl	%ecx, 88(%esp)
	movl	%eax, 84(%esp)
	movl	172(%esp), %edx
	movl	176(%esp), %ecx
	movl	180(%esp), %eax
	cmpl	$24, 96(%esp)
	movl	132(%esp), %ebp
	movl	144(%esp), %esi
	movl	152(%esp), %ebx
	movl	%edx, 80(%esp)
	movl	%ecx, 76(%esp)
	movl	%eax, 72(%esp)
	movl	$0, 44(%esp)
	movl	$0, 24(%esp)
	jne	.L2
	movl	$24, 156(%esp)
	addl	$112, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	fbBltOne24
.L2:
	movl	88(%esp), %eax
	imull	108(%esp), %eax
	leal	(%ebp,%eax,4), %eax
	movl	$32, %ecx
	movl	%eax, 64(%esp)
	movl	%ecx, %eax
	cltd
	idivl	96(%esp)
	movl	%eax, 8(%esp)
	movl	%ecx, %eax
	cltd
	idivl	8(%esp)
	cmpl	$0, 76(%esp)
	movl	%eax, 4(%esp)
	movl	$0, 32(%esp)
	movl	$0, 28(%esp)
	jne	.L3
	cmpl	$0, 84(%esp)
	jne	.L3
	movl	$1, 32(%esp)
	jmp	.L4
.L3:
	cmpl	$-1, 76(%esp)
	jne	.L4
	cmpl	$0, 72(%esp)
	jne	.L4
	movl	$1, 28(%esp)
.L4:
	movl	104(%esp), %eax
	sarl	$5, %eax
	leal	(%ebp,%eax,4), %ebp
	movl	%ebx, %eax
	sarl	$5, %eax
	andl	$31, %ebx
	movl	92(%esp), %edi
	leal	(%esi,%eax,4), %esi
	leal	(%edi,%ebx), %eax
	negl	%eax
	movl	%eax, %ecx
	andl	$31, 104(%esp)
	andl	$31, %ecx
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 48(%esp)
	je	.L7
	movl	$-1, 48(%esp)
	shrl	%cl, 48(%esp)
.L7:
	cmpl	$0, 48(%esp)
	je	.L8
	cmpl	$0, 32(%esp)
	je	.L9
	movl	92(%esp), %edx
	leal	(%edx,%ebx), %eax
	testb	$7, %al
	jne	.L9
	andl	$31, %eax
	sarl	$3, %eax
	movl	%eax, 12(%esp)
	jmp	.L8
.L9:
	movl	$16, 12(%esp)
.L8:
	movl	%ebx, %ecx
	andl	$31, %ecx
	movl	$0, 52(%esp)
	je	.L12
	movl	$-1, 52(%esp)
	sall	%cl, 52(%esp)
.L12:
	cmpl	$0, 52(%esp)
	je	.L13
	cmpl	$0, 32(%esp)
	je	.L14
	testb	$7, %bl
	jne	.L14
	movl	%ebx, %ecx
	andl	$31, %ecx
	sarl	$3, %ecx
	movl	%ecx, 16(%esp)
	jmp	.L15
.L14:
	movl	$16, 16(%esp)
.L15:
	movl	%ebx, %eax
	andl	$31, %eax
	movl	92(%esp), %edx
	leal	-32(%eax,%edx), %edi
	testl	%edi, %edi
	jns	.L13
	cmpl	$16, 16(%esp)
	je	.L17
	cmpl	$16, 12(%esp)
	jne	.L18
	movl	$16, 16(%esp)
	jmp	.L17
.L18:
	cmpl	$0, 12(%esp)
	je	.L17
	movl	16(%esp), %ecx
	subl	%ecx, 12(%esp)
	movl	12(%esp), %eax
	sall	$2, %eax
	orl	%eax, %ecx
	movl	%ecx, 16(%esp)
	movl	$0, 12(%esp)
.L17:
	movl	48(%esp), %eax
	xorl	%edi, %edi
	andl	%eax, 52(%esp)
	movl	$0, 48(%esp)
.L13:
	movl	%ebx, %eax
	cltd
	idivl	96(%esp)
	sarl	$5, %edi
	cmpl	%eax, 104(%esp)
	movl	%eax, (%esp)
	jl	.L21
	movl	104(%esp), %edx
	subl	%eax, %edx
	movl	$32, 56(%esp)
	subl	%edx, 56(%esp)
	movl	%edx, 60(%esp)
	jmp	.L22
.L21:
	movl	(%esp), %ecx
	subl	104(%esp), %ecx
	movl	$32, 60(%esp)
	movl	%ecx, 56(%esp)
	subl	%ecx, 60(%esp)
.L22:
	cmpl	$8, 8(%esp)
	movl	$0, 68(%esp)
	jg	.L23
	movl	8(%esp), %eax
	movl	fbStippleTable(,%eax,4), %eax
	movl	%eax, 68(%esp)
.L23:
	cmpl	$0, 28(%esp)
	movl	$0, 20(%esp)
	je	.L24
	cmpl	$0, 84(%esp)
	jne	.L24
	cmpl	$7, 96(%esp)
	jle	.L24
	movl	96(%esp), %edx
	movl	fbLaneTable(,%edx,4), %edx
	movl	%edx, 20(%esp)
.L24:
	cmpl	$0, 52(%esp)
	movl	%edi, 36(%esp)
	je	.L25
	incl	36(%esp)
.L25:
	movl	36(%esp), %ecx
	movl	4(%esp), %eax
	leal	-1(%eax,%ecx), %ebx
	movl	%ebx, %eax
	cltd
	idivl	4(%esp)
	movl	(%esp), %edx
	subl	%ecx, 100(%esp)
	cmpl	%edx, 104(%esp)
	movl	%eax, %ecx
	jle	.L26
	incl	%ecx
.L26:
	cmpl	$0, 48(%esp)
	je	.L27
	movl	36(%esp), %eax
	cltd
	idivl	4(%esp)
	xorl	%eax, %eax
	testl	%edx, %edx
	sete	%al
	testl	%eax, %eax
	movl	%eax, 24(%esp)
	je	.L27
	incl	%ecx
.L27:
	decl	88(%esp)
	subl	%ecx, 108(%esp)
	cmpl	$-1, 88(%esp)
	je	.L125
.L123:
	movl	36(%esp), %ebx
	movl	4(%esp), %edi
	cmpl	%ebx, %edi
	jle	.L32
	movl	%ebx, %edi
.L32:
	movl	(%esp), %edx
	cmpl	%edx, 104(%esp)
	movl	$0, 40(%esp)
	jle	.L33
	movl	(%ebp), %ecx
	movl	%ecx, 40(%esp)
	addl	$4, %ebp
.L33:
	testl	%edi, %edi
	je	.L34
	cmpl	$0, 60(%esp)
	je	.L35
	xorl	%edx, %edx
	cmpl	64(%esp), %ebp
	jae	.L37
	movl	(%ebp), %edx
	addl	$4, %ebp
.L37:
	movl	40(%esp), %eax
	movb	60(%esp), %cl
	shrl	%cl, %eax
	movl	%eax, 44(%esp)
	movb	56(%esp), %cl
	movl	%edx, %eax
	sall	%cl, %eax
	orl	%eax, 44(%esp)
	movl	%edx, 40(%esp)
	jmp	.L38
.L35:
	cmpl	64(%esp), %ebp
	movl	$0, 44(%esp)
	jae	.L38
	movl	(%ebp), %eax
	movl	%eax, 44(%esp)
	addl	$4, %ebp
.L38:
	cmpl	$0, 52(%esp)
	je	.L130
	movb	8(%esp), %cl
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	andl	44(%esp), %eax
	movl	68(%esp), %edx
	cmpl	$0, 20(%esp)
	movl	(%edx,%eax,4), %ecx
	je	.L42
	pushl	$1
	pushl	84(%esp)
	andl	60(%esp), %ecx
	pushl	%ecx
	pushl	%esi
	call	fbTransparentSpan
	addl	$16, %esp
	jmp	.L43
.L42:
	testl	%ecx, %ecx
	jne	.L45
	cmpl	$0, 28(%esp)
	jne	.L43
.L45:
	movl	%ecx, %ebx
	movl	80(%esp), %edx
	notl	%ebx
	movl	72(%esp), %eax
	andl	%ebx, %eax
	andl	%ecx, %edx
	orl	%eax, %edx
	movl	16(%esp), %eax
	decl	%eax
	cmpl	$8, %eax
	ja	.L53
	jmp	*.L54(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L54:
	.long	.L50
	.long	.L51
	.long	.L52
	.long	.L53
	.long	.L47
	.long	.L49
	.long	.L53
	.long	.L53
	.long	.L48
	.text
.L47:
	shrl	$8, %edx
	movb	%dl, 1(%esi)
	jmp	.L43
.L48:
	shrl	$8, %edx
	movb	%dl, 1(%esi)
	shrl	$8, %edx
	jmp	.L131
.L49:
	shrl	$16, %edx
.L131:
	movb	%dl, 2(%esi)
	jmp	.L43
.L50:
	movl	%edx, %eax
	shrl	$8, %eax
	movb	%al, 1(%esi)
.L51:
	shrl	$16, %edx
	movw	%dx, 2(%esi)
	jmp	.L43
.L52:
	shrl	$24, %edx
	movb	%dl, 3(%esi)
	jmp	.L43
.L53:
	andl	84(%esp), %ecx
	andl	76(%esp), %ebx
	movl	52(%esp), %eax
	orl	%ebx, %ecx
	notl	%eax
	orl	%eax, %ecx
	andl	(%esi), %ecx
	andl	52(%esp), %edx
	xorl	%edx, %ecx
	movl	%ecx, (%esi)
.L43:
	movb	8(%esp), %cl
	movl	36(%esp), %ebx
	shrl	%cl, 44(%esp)
	addl	$4, %esi
	decl	%edi
	decl	%ebx
.L130:
	subl	%edi, %ebx
	cmpl	$0, 32(%esp)
	je	.L58
	decl	%edi
	cmpl	$-1, %edi
	je	.L63
.L62:
	movb	8(%esp), %cl
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	andl	44(%esp), %eax
	movl	68(%esp), %edx
	movl	(%edx,%eax,4), %ecx
	movl	80(%esp), %eax
	andl	%ecx, %eax
	notl	%ecx
	andl	72(%esp), %ecx
	orl	%ecx, %eax
	decl	%edi
	movb	8(%esp), %cl
	movl	%eax, (%esi)
	shrl	%cl, 44(%esp)
	addl	$4, %esi
	cmpl	$-1, %edi
	jne	.L62
	jmp	.L63
.L58:
	cmpl	$0, 20(%esp)
	je	.L64
	cmpl	$0, 44(%esp)
	je	.L66
	testl	%edi, %edi
	je	.L66
.L88:
	movl	$1, %eax
	movb	8(%esp), %cl
	sall	%cl, %eax
	decl	%eax
	andl	44(%esp), %eax
	movl	20(%esp), %edx
	movzbl	(%eax,%edx), %eax
	cmpl	$15, %eax
	ja	.L69
	jmp	*.L86(,%eax,4)
	.section	.rodata
	.align 4
	.align 4
.L86:
	.long	.L69
	.long	.L71
	.long	.L72
	.long	.L73
	.long	.L133
	.long	.L75
	.long	.L76
	.long	.L77
	.long	.L132
	.long	.L79
	.long	.L80
	.long	.L81
	.long	.L82
	.long	.L83
	.long	.L84
	.long	.L85
	.text
.L71:
	movb	80(%esp), %cl
	movb	%cl, (%esi)
	jmp	.L69
.L72:
	movb	80(%esp), %al
	movb	%al, 1(%esi)
	jmp	.L69
.L73:
	movl	80(%esp), %edx
	movw	%dx, (%esi)
	jmp	.L69
.L75:
	movb	80(%esp), %al
	movb	%al, (%esi)
	movb	80(%esp), %dl
	movb	%dl, 2(%esi)
	jmp	.L69
.L76:
	movb	80(%esp), %cl
	movb	%cl, 1(%esi)
	movb	80(%esp), %al
	movb	%al, 2(%esi)
	jmp	.L69
.L77:
	movl	80(%esp), %edx
	movw	%dx, (%esi)
.L133:
	movb	80(%esp), %cl
	movb	%cl, 2(%esi)
	jmp	.L69
.L79:
	movb	80(%esp), %dl
	movb	%dl, (%esi)
	movb	80(%esp), %cl
	movb	%cl, 3(%esi)
	jmp	.L69
.L80:
	movb	80(%esp), %al
	movb	%al, 1(%esi)
	movb	80(%esp), %dl
	movb	%dl, 3(%esi)
	jmp	.L69
.L81:
	movl	80(%esp), %ecx
	movw	%cx, (%esi)
.L132:
	movb	80(%esp), %al
	movb	%al, 3(%esi)
	jmp	.L69
.L82:
	movl	80(%esp), %edx
	movw	%dx, 2(%esi)
	jmp	.L69
.L83:
	movb	80(%esp), %cl
	movb	%cl, (%esi)
	movl	80(%esp), %eax
	movw	%ax, 2(%esi)
	jmp	.L69
.L84:
	movb	80(%esp), %dl
	movb	%dl, 1(%esi)
	movl	80(%esp), %ecx
	movw	%cx, 2(%esi)
	jmp	.L69
.L85:
	movl	80(%esp), %eax
	movl	%eax, (%esi)
.L69:
	movb	8(%esp), %cl
	shrl	%cl, 44(%esp)
	addl	$4, %esi
	decl	%edi
	cmpl	$0, 44(%esp)
	je	.L66
	testl	%edi, %edi
	jne	.L88
.L66:
	leal	(%esi,%edi,4), %esi
	jmp	.L63
.L64:
	decl	%edi
	cmpl	$-1, %edi
	je	.L63
.L95:
	movl	$1, %eax
	movb	8(%esp), %cl
	sall	%cl, %eax
	decl	%eax
	andl	44(%esp), %eax
	jne	.L94
	cmpl	$0, 28(%esp)
	jne	.L93
.L94:
	movl	68(%esp), %edx
	movl	(%edx,%eax,4), %ecx
	movl	(%esi), %eax
	movl	84(%esp), %edx
	andl	%eax, %edx
	xorl	80(%esp), %edx
	andl	76(%esp), %eax
	andl	%ecx, %edx
	xorl	72(%esp), %eax
	notl	%ecx
	andl	%ecx, %eax
	orl	%eax, %edx
	movl	%edx, (%esi)
.L93:
	movb	8(%esp), %cl
	decl	%edi
	addl	$4, %esi
	shrl	%cl, 44(%esp)
	cmpl	$-1, %edi
	jne	.L95
.L63:
	testl	%ebx, %ebx
	je	.L34
	cmpl	$0, 60(%esp)
	je	.L97
	xorl	%edx, %edx
	cmpl	64(%esp), %ebp
	jae	.L99
	movl	(%ebp), %edx
	addl	$4, %ebp
.L99:
	movl	40(%esp), %eax
	movb	60(%esp), %cl
	shrl	%cl, %eax
	movl	%eax, 44(%esp)
	movb	56(%esp), %cl
	movl	%edx, %eax
	sall	%cl, %eax
	orl	%eax, 44(%esp)
	movl	%edx, 40(%esp)
	jmp	.L100
.L97:
	cmpl	64(%esp), %ebp
	movl	$0, 44(%esp)
	jae	.L100
	movl	(%ebp), %eax
	movl	%eax, 44(%esp)
	addl	$4, %ebp
.L100:
	movl	4(%esp), %edi
	cmpl	%ebx, %edi
	jle	.L130
	movl	%ebx, %edi
	jmp	.L130
.L34:
	cmpl	$0, 48(%esp)
	je	.L104
	cmpl	$0, 24(%esp)
	je	.L105
	cmpl	$0, 60(%esp)
	je	.L106
	xorl	%edx, %edx
	cmpl	64(%esp), %ebp
	jae	.L108
	movl	(%ebp), %edx
	addl	$4, %ebp
.L108:
	movb	60(%esp), %cl
	movl	40(%esp), %eax
	shrl	%cl, %eax
	movb	56(%esp), %cl
	sall	%cl, %edx
	orl	%edx, %eax
	movl	%eax, 44(%esp)
	jmp	.L105
.L106:
	cmpl	64(%esp), %ebp
	movl	$0, 44(%esp)
	jae	.L105
	movl	(%ebp), %eax
	movl	%eax, 44(%esp)
	addl	$4, %ebp
.L105:
	movb	8(%esp), %cl
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	andl	44(%esp), %eax
	movl	68(%esp), %edx
	cmpl	$0, 20(%esp)
	movl	(%edx,%eax,4), %ecx
	je	.L112
	pushl	$1
	pushl	84(%esp)
	andl	56(%esp), %ecx
	pushl	%ecx
	pushl	%esi
	call	fbTransparentSpan
	addl	$16, %esp
	jmp	.L104
.L112:
	testl	%ecx, %ecx
	jne	.L115
	cmpl	$0, 28(%esp)
	jne	.L104
.L115:
	movl	%ecx, %ebx
	movl	80(%esp), %edx
	notl	%ebx
	movl	72(%esp), %eax
	andl	%ecx, %edx
	andl	%ebx, %eax
	orl	%eax, %edx
	cmpl	$2, 12(%esp)
	je	.L118
	cmpl	$2, 12(%esp)
	jg	.L122
	cmpl	$1, 12(%esp)
	je	.L117
	jmp	.L120
.L122:
	cmpl	$3, 12(%esp)
	je	.L119
	jmp	.L120
.L117:
	movb	%dl, (%esi)
	jmp	.L104
.L118:
	movw	%dx, (%esi)
	jmp	.L104
.L119:
	movw	%dx, (%esi)
	shrl	$16, %edx
	movb	%dl, 2(%esi)
	jmp	.L104
.L120:
	andl	84(%esp), %ecx
	andl	76(%esp), %ebx
	movl	48(%esp), %eax
	orl	%ebx, %ecx
	notl	%eax
	orl	%eax, %ecx
	andl	(%esi), %ecx
	andl	48(%esp), %edx
	xorl	%edx, %ecx
	movl	%ecx, (%esi)
.L104:
	decl	88(%esp)
	movl	100(%esp), %ecx
	movl	108(%esp), %eax
	cmpl	$-1, 88(%esp)
	leal	(%esi,%ecx,4), %esi
	leal	(%ebp,%eax,4), %ebp
	jne	.L123
.L125:
	addl	$112, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	fbBltOne, .-fbBltOne
.globl fbStipple24Bits
	.section	.rodata
	.align 32
	.type	fbStipple24Bits, @object
	.size	fbStipple24Bits, 48
fbStipple24Bits:
	.long	0
	.long	16777215
	.long	-16777216
	.long	-1
	.long	0
	.long	255
	.long	-256
	.long	-1
	.long	0
	.long	65535
	.long	-65536
	.long	-1
	.text
	.align 4
.globl fbBltOne24
	.type	fbBltOne24, @function
fbBltOne24:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	112(%esp), %eax
	movl	80(%esp), %edx
	imull	84(%esp), %eax
	leal	(%edx,%eax,4), %eax
	movl	%eax, 48(%esp)
	movl	88(%esp), %eax
	sarl	$5, %eax
	movl	100(%esp), %esi
	leal	(%edx,%eax,4), %edx
	movl	%esi, %eax
	sarl	$5, %eax
	sall	$2, %eax
	movl	92(%esp), %ecx
	addl	%ecx, %eax
	andl	$31, %esi
	movl	%eax, 56(%esp)
	movl	%esi, %eax
	movl	108(%esp), %ebx
	movl	$24, %ecx
	movl	%edx, 80(%esp)
	cltd
	idivl	%ecx
	leal	(%ebx,%esi), %eax
	negl	%eax
	movl	%eax, %ecx
	andl	$31, 88(%esp)
	andl	$31, %ecx
	movl	%edx, 12(%esp)
	movl	%ebx, 36(%esp)
	movl	$0, 40(%esp)
	je	.L136
	movl	$-1, 40(%esp)
	shrl	%cl, 40(%esp)
.L136:
	movl	%esi, %ecx
	andl	$31, %ecx
	movl	$0, 44(%esp)
	je	.L138
	movl	$-1, 44(%esp)
	sall	%cl, 44(%esp)
.L138:
	cmpl	$0, 44(%esp)
	je	.L139
	movl	%esi, %eax
	andl	$31, %eax
	leal	-32(%eax,%ebx), %ebx
	testl	%ebx, %ebx
	movl	%ebx, 36(%esp)
	jns	.L139
	movl	40(%esp), %ecx
	movl	$0, 36(%esp)
	andl	%ecx, 44(%esp)
	movl	$0, 40(%esp)
.L139:
	leal	23(%esi), %eax
	movl	$24, %edx
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	movl	$2, 20(%esp)
	sarl	$5, 36(%esp)
	subl	%eax, 20(%esp)
	cmpl	$0, 44(%esp)
	movl	36(%esp), %eax
	je	.L141
	incl	%eax
.L141:
	subl	%eax, 96(%esp)
	cmpl	$0, 124(%esp)
	jne	.L142
	cmpl	$0, 116(%esp)
	jne	.L142
	decl	112(%esp)
	cmpl	$-1, 112(%esp)
	je	.L134
.L172:
	movl	80(%esp), %edx
	movl	84(%esp), %ecx
	leal	(%edx,%ecx,4), %ecx
	movl	12(%esp), %eax
	movl	%eax, 16(%esp)
	movl	%ecx, 80(%esp)
	movl	(%edx), %eax
	movb	88(%esp), %cl
	shrl	%cl, %eax
	movl	$32, 24(%esp)
	movl	%eax, 28(%esp)
	movl	88(%esp), %eax
	subl	%eax, 24(%esp)
	movl	%edx, 52(%esp)
	movl	24(%esp), %ecx
	movl	20(%esp), %edx
	addl	$4, 52(%esp)
	cmpl	%ecx, %edx
	jg	.L146
	movl	$1, %eax
	movb	20(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edi
	andl	28(%esp), %edi
	jmp	.L147
.L146:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edi
	movl	48(%esp), %eax
	andl	28(%esp), %edi
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L149
	movl	52(%esp), %edx
	movl	(%edx), %edx
	movl	%edx, 28(%esp)
	addl	$4, 52(%esp)
.L149:
	movl	20(%esp), %edx
	subl	24(%esp), %edx
	movb	%dl, %cl
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edi
	movl	$32, 24(%esp)
.L147:
	movb	%dl, %cl
	shrl	%cl, 28(%esp)
	movl	$2, %ecx
	subl	20(%esp), %ecx
	sall	%cl, %edi
	subl	%edx, 24(%esp)
	cmpl	$0, 44(%esp)
	movl	%edi, 8(%esp)
	je	.L150
	movl	12(%esp), %eax
	sarl	$3, %eax
	leal	(%edi,%eax,4), %eax
	movl	44(%esp), %esi
	movl	$24, %ebx
	subl	12(%esp), %ebx
	movl	fbStipple24Bits(,%eax,4), %ebp
	movl	120(%esp), %edi
	movl	56(%esp), %eax
	movb	12(%esp), %cl
	notl	%esi
	andl	(%eax), %esi
	sall	%cl, %edi
	movl	120(%esp), %eax
	movb	%bl, %cl
	shrl	%cl, %eax
	movl	128(%esp), %edx
	movb	12(%esp), %cl
	orl	%eax, %edi
	sall	%cl, %edx
	movl	128(%esp), %eax
	movb	%bl, %cl
	shrl	%cl, %eax
	andl	%ebp, %edi
	orl	%eax, %edx
	notl	%ebp
	andl	%ebp, %edx
	orl	%edx, %edi
	andl	44(%esp), %edi
	orl	%edi, %esi
	movl	56(%esp), %eax
	movl	%esi, (%eax)
	xorl	%ebx, %ebx
	addl	$4, %eax
	cmpl	$8, 12(%esp)
	sete	%bl
	incl	%ebx
	cmpl	24(%esp), %ebx
	movl	%eax, 56(%esp)
	movl	%ebx, %esi
	jg	.L153
	movl	$1, %eax
	movb	%bl, %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	andl	28(%esp), %edx
	jmp	.L154
.L153:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	movl	48(%esp), %eax
	andl	28(%esp), %edx
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L156
	movl	52(%esp), %ecx
	movl	(%ecx), %ecx
	movl	%ecx, 28(%esp)
	addl	$4, 52(%esp)
.L156:
	movl	%ebx, %esi
	subl	24(%esp), %esi
	movl	%esi, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edx
	movl	$32, 24(%esp)
.L154:
	movl	%esi, %ecx
	shrl	%cl, 28(%esp)
	movl	8(%esp), %edi
	movb	%bl, %cl
	shrl	%cl, %edi
	movl	$2, %ecx
	subl	%ebx, %ecx
	sall	%cl, %edx
	subl	%esi, 24(%esp)
	orl	%edx, %edi
	cmpl	$0, 12(%esp)
	movl	$16, %ecx
	je	.L158
	movl	12(%esp), %ecx
	subl	$8, %ecx
.L158:
	movl	%ecx, 16(%esp)
.L150:
	movl	36(%esp), %eax
	decl	%eax
	movl	%eax, 32(%esp)
	incl	%eax
	je	.L242
.L170:
	movl	16(%esp), %eax
	sarl	$3, %eax
	movl	$24, %esi
	subl	16(%esp), %esi
	leal	(%edi,%eax,4), %eax
	movl	120(%esp), %ebx
	movb	16(%esp), %cl
	movl	fbStipple24Bits(,%eax,4), %ebp
	sall	%cl, %ebx
	movl	120(%esp), %eax
	movl	%esi, %ecx
	shrl	%cl, %eax
	movl	128(%esp), %edx
	movb	16(%esp), %cl
	orl	%eax, %ebx
	sall	%cl, %edx
	movl	128(%esp), %eax
	movl	%esi, %ecx
	shrl	%cl, %eax
	andl	%ebp, %ebx
	orl	%eax, %edx
	notl	%ebp
	andl	%ebp, %edx
	orl	%edx, %ebx
	movl	56(%esp), %eax
	movl	%ebx, (%eax)
	addl	$4, %eax
	xorl	%ebx, %ebx
	cmpl	$8, 16(%esp)
	sete	%bl
	incl	%ebx
	cmpl	24(%esp), %ebx
	movl	%eax, 56(%esp)
	movl	%ebx, %esi
	jg	.L164
	movl	$1, %eax
	movb	%bl, %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	andl	28(%esp), %edx
	jmp	.L165
.L164:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	movl	48(%esp), %eax
	andl	28(%esp), %edx
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L167
	movl	52(%esp), %ecx
	movl	(%ecx), %ecx
	movl	%ecx, 28(%esp)
	addl	$4, 52(%esp)
.L167:
	movl	%ebx, %esi
	subl	24(%esp), %esi
	movl	%esi, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edx
	movl	$32, 24(%esp)
.L165:
	movl	%esi, %ecx
	shrl	%cl, 28(%esp)
	movb	%bl, %cl
	shrl	%cl, %edi
	movl	$2, %ecx
	subl	%ebx, %ecx
	sall	%cl, %edx
	subl	%esi, 24(%esp)
	orl	%edx, %edi
	cmpl	$0, 16(%esp)
	movl	$16, %ecx
	je	.L169
	movl	16(%esp), %ecx
	subl	$8, %ecx
.L169:
	decl	32(%esp)
	cmpl	$-1, 32(%esp)
	movl	%ecx, 16(%esp)
	jne	.L170
.L242:
	cmpl	$0, 40(%esp)
	je	.L171
	movl	16(%esp), %eax
	sarl	$3, %eax
	leal	(%edi,%eax,4), %eax
	movl	40(%esp), %esi
	movl	$24, %ebx
	movl	fbStipple24Bits(,%eax,4), %ebp
	movl	120(%esp), %edi
	movl	56(%esp), %eax
	movb	16(%esp), %cl
	subl	16(%esp), %ebx
	notl	%esi
	andl	(%eax), %esi
	sall	%cl, %edi
	movl	120(%esp), %eax
	movb	%bl, %cl
	shrl	%cl, %eax
	movl	128(%esp), %edx
	movb	16(%esp), %cl
	orl	%eax, %edi
	sall	%cl, %edx
	movl	128(%esp), %eax
	movb	%bl, %cl
	shrl	%cl, %eax
	andl	%ebp, %edi
	orl	%eax, %edx
	notl	%ebp
	andl	%ebp, %edx
	orl	%edx, %edi
	andl	40(%esp), %edi
	orl	%edi, %esi
	movl	56(%esp), %eax
	movl	%esi, (%eax)
.L171:
	movl	56(%esp), %ecx
	movl	96(%esp), %edx
	decl	112(%esp)
	leal	(%ecx,%edx,4), %ecx
	cmpl	$-1, 112(%esp)
	movl	%ecx, 56(%esp)
	jne	.L172
	jmp	.L134
.L142:
	cmpl	$-1, 124(%esp)
	jne	.L174
	cmpl	$0, 128(%esp)
	jne	.L174
	cmpl	$0, 116(%esp)
	jne	.L174
	decl	112(%esp)
	cmpl	$-1, 112(%esp)
	je	.L134
.L207:
	movl	80(%esp), %edx
	movl	84(%esp), %ecx
	leal	(%edx,%ecx,4), %ecx
	movl	12(%esp), %eax
	movl	%eax, 16(%esp)
	movl	%ecx, 80(%esp)
	movl	(%edx), %eax
	movb	88(%esp), %cl
	shrl	%cl, %eax
	movl	$32, 24(%esp)
	movl	%eax, 28(%esp)
	movl	88(%esp), %eax
	subl	%eax, 24(%esp)
	movl	%edx, 52(%esp)
	movl	24(%esp), %ecx
	movl	20(%esp), %edx
	addl	$4, 52(%esp)
	cmpl	%ecx, %edx
	jg	.L178
	movl	$1, %eax
	movb	20(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edi
	andl	28(%esp), %edi
	jmp	.L179
.L178:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edi
	movl	48(%esp), %eax
	andl	28(%esp), %edi
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L181
	movl	52(%esp), %edx
	movl	(%edx), %edx
	movl	%edx, 28(%esp)
	addl	$4, 52(%esp)
.L181:
	movl	20(%esp), %edx
	subl	24(%esp), %edx
	movb	%dl, %cl
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edi
	movl	$32, 24(%esp)
.L179:
	movb	%dl, %cl
	shrl	%cl, 28(%esp)
	movl	$2, %ecx
	subl	20(%esp), %ecx
	movl	%edi, %esi
	sall	%cl, %esi
	subl	%edx, 24(%esp)
	cmpl	$0, 44(%esp)
	movl	%esi, %edi
	je	.L182
	testl	%esi, %esi
	je	.L183
	movl	12(%esp), %eax
	sarl	$3, %eax
	leal	(%esi,%eax,4), %eax
	movl	44(%esp), %ebp
	andl	fbStipple24Bits(,%eax,4), %ebp
	movl	120(%esp), %edx
	movb	12(%esp), %cl
	movl	%ebp, %ebx
	movl	56(%esp), %eax
	sall	%cl, %edx
	notl	%ebx
	movl	$24, %ecx
	andl	(%eax), %ebx
	subl	12(%esp), %ecx
	movl	120(%esp), %eax
	shrl	%cl, %eax
	orl	%eax, %edx
	andl	%ebp, %edx
	orl	%edx, %ebx
	movl	56(%esp), %eax
	movl	%ebx, (%eax)
.L183:
	xorl	%ebx, %ebx
	addl	$4, 56(%esp)
	cmpl	$8, 12(%esp)
	sete	%bl
	incl	%ebx
	cmpl	24(%esp), %ebx
	movl	%ebx, %edi
	jg	.L186
	movl	$1, %eax
	movb	%bl, %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	andl	28(%esp), %edx
	jmp	.L187
.L186:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	movl	48(%esp), %eax
	andl	28(%esp), %edx
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L189
	movl	52(%esp), %ecx
	movl	(%ecx), %ecx
	movl	%ecx, 28(%esp)
	addl	$4, 52(%esp)
.L189:
	movl	%ebx, %edi
	subl	24(%esp), %edi
	movl	%edi, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edx
	movl	$32, 24(%esp)
.L187:
	movl	%edi, %ecx
	shrl	%cl, 28(%esp)
	subl	%edi, 24(%esp)
	movb	%bl, %cl
	movl	%esi, %edi
	shrl	%cl, %edi
	movl	$2, %ecx
	subl	%ebx, %ecx
	sall	%cl, %edx
	orl	%edx, %edi
	cmpl	$0, 12(%esp)
	movl	$16, %ecx
	je	.L191
	movl	12(%esp), %ecx
	subl	$8, %ecx
.L191:
	movl	%ecx, 16(%esp)
.L182:
	movl	36(%esp), %eax
	decl	%eax
	movl	%eax, 32(%esp)
	incl	%eax
	je	.L246
.L204:
	testl	%edi, %edi
	je	.L195
	movl	16(%esp), %eax
	sarl	$3, %eax
	leal	(%edi,%eax,4), %eax
	movl	fbStipple24Bits(,%eax,4), %ebp
	movl	%ebp, %ebx
	movl	56(%esp), %edx
	notl	%ebx
	andl	(%edx), %ebx
	movb	16(%esp), %cl
	movl	120(%esp), %edx
	sall	%cl, %edx
	movl	$24, %ecx
	movl	120(%esp), %eax
	subl	16(%esp), %ecx
	shrl	%cl, %eax
	orl	%eax, %edx
	andl	%ebp, %edx
	orl	%edx, %ebx
	movl	56(%esp), %eax
	movl	%ebx, (%eax)
.L195:
	xorl	%ebx, %ebx
	addl	$4, 56(%esp)
	cmpl	$8, 16(%esp)
	sete	%bl
	incl	%ebx
	cmpl	24(%esp), %ebx
	movl	%ebx, %esi
	jg	.L198
	movl	$1, %eax
	movb	%bl, %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	andl	28(%esp), %edx
	jmp	.L199
.L198:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	movl	48(%esp), %eax
	andl	28(%esp), %edx
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L201
	movl	52(%esp), %ecx
	movl	(%ecx), %ecx
	movl	%ecx, 28(%esp)
	addl	$4, 52(%esp)
.L201:
	movl	%ebx, %esi
	subl	24(%esp), %esi
	movl	%esi, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edx
	movl	$32, 24(%esp)
.L199:
	movl	%esi, %ecx
	shrl	%cl, 28(%esp)
	movb	%bl, %cl
	shrl	%cl, %edi
	movl	$2, %ecx
	subl	%ebx, %ecx
	sall	%cl, %edx
	subl	%esi, 24(%esp)
	orl	%edx, %edi
	cmpl	$0, 16(%esp)
	movl	$16, %ecx
	je	.L203
	movl	16(%esp), %ecx
	subl	$8, %ecx
.L203:
	decl	32(%esp)
	cmpl	$-1, 32(%esp)
	movl	%ecx, 16(%esp)
	jne	.L204
.L246:
	cmpl	$0, 40(%esp)
	je	.L205
	testl	%edi, %edi
	je	.L205
	movl	16(%esp), %eax
	sarl	$3, %eax
	leal	(%edi,%eax,4), %eax
	movl	40(%esp), %ebp
	andl	fbStipple24Bits(,%eax,4), %ebp
	movl	120(%esp), %edx
	movb	16(%esp), %cl
	movl	%ebp, %ebx
	movl	56(%esp), %eax
	sall	%cl, %edx
	notl	%ebx
	movl	$24, %ecx
	andl	(%eax), %ebx
	subl	16(%esp), %ecx
	movl	120(%esp), %eax
	shrl	%cl, %eax
	orl	%eax, %edx
	andl	%ebp, %edx
	orl	%edx, %ebx
	movl	56(%esp), %eax
	movl	%ebx, (%eax)
.L205:
	movl	56(%esp), %ecx
	movl	96(%esp), %edx
	decl	112(%esp)
	leal	(%ecx,%edx,4), %ecx
	cmpl	$-1, 112(%esp)
	movl	%ecx, 56(%esp)
	jne	.L207
	jmp	.L134
.L174:
	decl	112(%esp)
	cmpl	$-1, 112(%esp)
	je	.L134
.L238:
	movl	80(%esp), %edx
	movl	84(%esp), %ecx
	leal	(%edx,%ecx,4), %ecx
	movl	12(%esp), %eax
	movl	%eax, 16(%esp)
	movl	%ecx, 80(%esp)
	movl	(%edx), %eax
	movb	88(%esp), %cl
	shrl	%cl, %eax
	movl	$32, 24(%esp)
	movl	%eax, 28(%esp)
	movl	88(%esp), %eax
	subl	%eax, 24(%esp)
	movl	%edx, 52(%esp)
	movl	24(%esp), %ecx
	movl	20(%esp), %edx
	addl	$4, 52(%esp)
	cmpl	%ecx, %edx
	jg	.L212
	movl	$1, %eax
	movb	20(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edi
	andl	28(%esp), %edi
	jmp	.L213
.L212:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edi
	movl	48(%esp), %eax
	andl	28(%esp), %edi
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L215
	movl	52(%esp), %edx
	movl	(%edx), %edx
	movl	%edx, 28(%esp)
	addl	$4, 52(%esp)
.L215:
	movl	20(%esp), %edx
	subl	24(%esp), %edx
	movb	%dl, %cl
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edi
	movl	$32, 24(%esp)
.L213:
	movb	%dl, %cl
	shrl	%cl, 28(%esp)
	movl	$2, %ecx
	subl	20(%esp), %ecx
	sall	%cl, %edi
	subl	%edx, 24(%esp)
	cmpl	$0, 44(%esp)
	movl	%edi, 4(%esp)
	je	.L216
	movl	12(%esp), %eax
	sarl	$3, %eax
	movl	$24, %esi
	subl	12(%esp), %esi
	leal	(%edi,%eax,4), %eax
	movl	116(%esp), %ebx
	movb	12(%esp), %cl
	movl	fbStipple24Bits(,%eax,4), %ebp
	sall	%cl, %ebx
	movl	116(%esp), %eax
	movl	%esi, %ecx
	shrl	%cl, %eax
	movl	44(%esp), %edi
	orl	%eax, %ebx
	notl	%edi
	movl	56(%esp), %eax
	movl	(%eax), %eax
	orl	%edi, %ebx
	movl	%eax, (%esp)
	andl	%eax, %ebx
	movb	12(%esp), %cl
	movl	120(%esp), %eax
	sall	%cl, %eax
	movl	120(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	andl	44(%esp), %eax
	xorl	%eax, %ebx
	movb	12(%esp), %cl
	movl	124(%esp), %eax
	sall	%cl, %eax
	movl	124(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	orl	%edi, %eax
	andl	%eax, (%esp)
	movb	12(%esp), %cl
	movl	128(%esp), %eax
	sall	%cl, %eax
	movl	128(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	andl	44(%esp), %eax
	xorl	%eax, (%esp)
	andl	%ebp, %ebx
	notl	%ebp
	andl	%ebp, (%esp)
	orl	(%esp), %ebx
	movl	56(%esp), %eax
	movl	%ebx, (%eax)
	addl	$4, %eax
	xorl	%ebx, %ebx
	cmpl	$8, 12(%esp)
	sete	%bl
	incl	%ebx
	cmpl	24(%esp), %ebx
	movl	%eax, 56(%esp)
	movl	%ebx, %esi
	jg	.L219
	movl	$1, %eax
	movb	%bl, %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	andl	28(%esp), %edx
	jmp	.L220
.L219:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	movl	48(%esp), %eax
	andl	28(%esp), %edx
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L222
	movl	52(%esp), %ecx
	movl	(%ecx), %ecx
	movl	%ecx, 28(%esp)
	addl	$4, 52(%esp)
.L222:
	movl	%ebx, %esi
	subl	24(%esp), %esi
	movl	%esi, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edx
	movl	$32, 24(%esp)
.L220:
	movl	%esi, %ecx
	shrl	%cl, 28(%esp)
	movl	4(%esp), %edi
	movb	%bl, %cl
	shrl	%cl, %edi
	movl	$2, %ecx
	subl	%ebx, %ecx
	sall	%cl, %edx
	subl	%esi, 24(%esp)
	orl	%edx, %edi
	cmpl	$0, 12(%esp)
	movl	$16, %ecx
	je	.L224
	movl	12(%esp), %ecx
	subl	$8, %ecx
.L224:
	movl	%ecx, 16(%esp)
.L216:
	movl	36(%esp), %eax
	decl	%eax
	movl	%eax, 32(%esp)
	incl	%eax
	je	.L249
.L236:
	movl	16(%esp), %eax
	sarl	$3, %eax
	movl	$24, %esi
	subl	16(%esp), %esi
	leal	(%edi,%eax,4), %eax
	movl	116(%esp), %ebx
	movb	16(%esp), %cl
	movl	fbStipple24Bits(,%eax,4), %ebp
	sall	%cl, %ebx
	movl	116(%esp), %eax
	movl	%esi, %ecx
	shrl	%cl, %eax
	orl	%eax, %ebx
	movl	56(%esp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	andl	%eax, %ebx
	movb	16(%esp), %cl
	movl	120(%esp), %eax
	sall	%cl, %eax
	movl	120(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	xorl	%eax, %ebx
	movb	16(%esp), %cl
	movl	124(%esp), %eax
	sall	%cl, %eax
	movl	124(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	andl	%eax, (%esp)
	movb	16(%esp), %cl
	movl	128(%esp), %eax
	sall	%cl, %eax
	movl	128(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	xorl	%eax, (%esp)
	andl	%ebp, %ebx
	notl	%ebp
	andl	%ebp, (%esp)
	orl	(%esp), %ebx
	movl	56(%esp), %eax
	movl	%ebx, (%eax)
	addl	$4, %eax
	xorl	%ebx, %ebx
	cmpl	$8, 16(%esp)
	sete	%bl
	incl	%ebx
	cmpl	24(%esp), %ebx
	movl	%eax, 56(%esp)
	movl	%ebx, %esi
	jg	.L230
	movl	$1, %eax
	movb	%bl, %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	andl	28(%esp), %edx
	jmp	.L231
.L230:
	movl	$1, %eax
	movb	24(%esp), %cl
	sall	%cl, %eax
	leal	-1(%eax), %edx
	movl	48(%esp), %eax
	andl	28(%esp), %edx
	cmpl	%eax, 52(%esp)
	movl	$0, 28(%esp)
	jae	.L233
	movl	52(%esp), %ecx
	movl	(%ecx), %ecx
	movl	%ecx, 28(%esp)
	addl	$4, 52(%esp)
.L233:
	movl	%ebx, %esi
	subl	24(%esp), %esi
	movl	%esi, %ecx
	movl	$1, %eax
	sall	%cl, %eax
	decl	%eax
	movb	24(%esp), %cl
	andl	28(%esp), %eax
	sall	%cl, %eax
	orl	%eax, %edx
	movl	$32, 24(%esp)
.L231:
	movl	%esi, %ecx
	shrl	%cl, 28(%esp)
	movb	%bl, %cl
	shrl	%cl, %edi
	movl	$2, %ecx
	subl	%ebx, %ecx
	sall	%cl, %edx
	subl	%esi, 24(%esp)
	orl	%edx, %edi
	cmpl	$0, 16(%esp)
	movl	$16, %ecx
	je	.L235
	movl	16(%esp), %ecx
	subl	$8, %ecx
.L235:
	decl	32(%esp)
	cmpl	$-1, 32(%esp)
	movl	%ecx, 16(%esp)
	jne	.L236
.L249:
	cmpl	$0, 40(%esp)
	je	.L237
	movl	16(%esp), %eax
	sarl	$3, %eax
	movl	$24, %esi
	subl	16(%esp), %esi
	leal	(%edi,%eax,4), %eax
	movl	116(%esp), %ebx
	movb	16(%esp), %cl
	movl	fbStipple24Bits(,%eax,4), %ebp
	sall	%cl, %ebx
	movl	116(%esp), %eax
	movl	%esi, %ecx
	shrl	%cl, %eax
	movl	40(%esp), %edi
	orl	%eax, %ebx
	notl	%edi
	movl	56(%esp), %eax
	movl	(%eax), %eax
	orl	%edi, %ebx
	movl	%eax, (%esp)
	andl	%eax, %ebx
	movb	16(%esp), %cl
	movl	120(%esp), %eax
	sall	%cl, %eax
	movl	120(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	andl	40(%esp), %eax
	xorl	%eax, %ebx
	movb	16(%esp), %cl
	movl	124(%esp), %eax
	sall	%cl, %eax
	movl	124(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	orl	%edi, %eax
	andl	%eax, (%esp)
	movb	16(%esp), %cl
	movl	128(%esp), %eax
	sall	%cl, %eax
	movl	128(%esp), %edx
	movl	%esi, %ecx
	shrl	%cl, %edx
	orl	%edx, %eax
	andl	40(%esp), %eax
	xorl	%eax, (%esp)
	andl	%ebp, %ebx
	notl	%ebp
	andl	%ebp, (%esp)
	orl	(%esp), %ebx
	movl	56(%esp), %eax
	movl	%ebx, (%eax)
.L237:
	movl	56(%esp), %ecx
	movl	96(%esp), %edx
	decl	112(%esp)
	leal	(%ecx,%edx,4), %ecx
	cmpl	$-1, 112(%esp)
	movl	%ecx, 56(%esp)
	jne	.L238
.L134:
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	fbBltOne24, .-fbBltOne24
	.align 4
.globl fbBltPlane
	.type	fbBltPlane, @function
fbBltPlane:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	88(%esp), %edx
	testl	%edx, %edx
	movl	68(%esp), %esi
	movl	84(%esp), %edi
	movl	$0, 24(%esp)
	je	.L250
	movl	%esi, %eax
	movl	60(%esp), %ecx
	sarl	$5, %eax
	leal	(%ecx,%eax,4), %ecx
	movl	%edi, %eax
	movl	%ecx, 60(%esp)
	sarl	$5, %eax
	movl	76(%esp), %ecx
	leal	(%ecx,%eax,4), %ecx
	movl	%edx, %eax
	cltd
	idivl	72(%esp)
	movl	%ecx, 76(%esp)
	movl	%eax, (%esp)
	pushl	72(%esp)
	pushl	116(%esp)
	call	fbReplicatePixel
	movl	%eax, 44(%esp)
	popl	%eax
	popl	%edx
	andl	$31, %esi
	andl	$31, %edi
	cmpl	$24, 72(%esp)
	jne	.L252
	movl	%esi, %eax
	cltd
	idivl	72(%esp)
	leal	24(%esi), %eax
	cmpl	$32, %eax
	movl	$24, %ebp
	movl	%edx, 4(%esp)
	jle	.L253
	movl	$32, %ebp
	subl	%esi, %ebp
.L253:
	movb	4(%esp), %cl
	movl	36(%esp), %eax
	sall	%cl, %eax
	movl	72(%esp), %ecx
	movl	%eax, 28(%esp)
	subl	4(%esp), %ecx
	movl	36(%esp), %eax
	shrl	%cl, %eax
	orl	%eax, 28(%esp)
	movl	%esi, %ecx
	orl	$-1, %eax
	andl	$31, %ecx
	movl	%eax, %ebx
	sall	%cl, %ebx
	leal	(%ebp,%esi), %ecx
	negl	%ecx
	andl	$31, %ecx
	shrl	%cl, %eax
	andl	%eax, %ebx
	andl	%ebx, 28(%esp)
	jmp	.L254
.L252:
	orl	$-1, %ebx
	movl	%esi, %ecx
	andl	$31, %ecx
	movl	%ebx, %edx
	sall	%cl, %edx
	movl	$32, %eax
	movl	72(%esp), %ecx
	movl	%edx, 28(%esp)
	leal	(%ecx,%esi), %edx
	movl	%eax, %ecx
	subl	%edx, %ecx
	subl	72(%esp), %eax
	andl	$31, %ecx
	movl	%ebx, %edx
	andl	$31, %eax
	shrl	%cl, %edx
	movl	%ebx, 24(%esp)
	movb	%al, %cl
	andl	%edx, 28(%esp)
	shrl	%cl, 24(%esp)
	movl	36(%esp), %edx
	movl	$0, 4(%esp)
	andl	%edx, 28(%esp)
	andl	%edx, 24(%esp)
.L254:
	orl	$-1, %eax
	movl	%edi, %ecx
	andl	$31, %ecx
	movl	%eax, %edx
	sall	%cl, %edx
	movl	$31, %ecx
	subl	%edi, %ecx
	andl	$31, %ecx
	shrl	%cl, %eax
	decl	92(%esp)
	andl	%eax, %edx
	cmpl	$-1, 92(%esp)
	movl	%edx, 12(%esp)
	je	.L250
.L270:
	movl	76(%esp), %ebp
	movl	60(%esp), %esi
	movl	80(%esp), %ecx
	movl	64(%esp), %eax
	leal	(%ebp,%ecx,4), %ecx
	leal	(%esi,%eax,4), %eax
	movl	28(%esp), %edx
	cmpl	$24, 72(%esp)
	movl	%ecx, 76(%esp)
	movl	%eax, 60(%esp)
	movl	%edx, 32(%esp)
	jne	.L258
	movb	4(%esp), %cl
	movl	36(%esp), %eax
	sall	%cl, %eax
	movl	72(%esp), %ecx
	movl	%eax, 24(%esp)
	subl	4(%esp), %ecx
	movl	36(%esp), %eax
	shrl	%cl, %eax
	orl	%eax, 24(%esp)
	andl	$16777215, 24(%esp)
.L258:
	movl	(%esp), %ecx
	decl	%ecx
	movl	(%esi), %edx
	xorl	%edi, %edi
	addl	$4, %esi
	movl	%ecx, 8(%esp)
	incl	%ecx
	movl	%edx, 20(%esp)
	movl	$0, 16(%esp)
	movl	12(%esp), %edx
	je	.L255
.L268:
	cmpl	$0, 32(%esp)
	jne	.L262
	movl	(%esi), %eax
	addl	$4, %esi
	cmpl	$24, 72(%esp)
	movl	%eax, 20(%esp)
	jne	.L263
	movl	24(%esp), %eax
	sall	$16, %eax
	shrl	$8, 24(%esp)
	orl	%eax, 24(%esp)
	andl	$16777215, 24(%esp)
.L263:
	movl	24(%esp), %ecx
	movl	%ecx, 32(%esp)
.L262:
	testl	%edx, %edx
	jne	.L264
	movl	%edi, %ebx
	notl	%ebx
	movl	96(%esp), %ecx
	movl	(%ebp), %edx
	orl	%ebx, %ecx
	movl	100(%esp), %eax
	andl	%edx, %ecx
	andl	%edi, %eax
	orl	104(%esp), %ebx
	andl	108(%esp), %edi
	xorl	%eax, %ecx
	andl	%ebx, %edx
	andl	16(%esp), %ecx
	xorl	%edi, %edx
	notl	16(%esp)
	andl	16(%esp), %edx
	orl	%edx, %ecx
	movl	%ecx, (%ebp)
	movl	$1, %edx
	addl	$4, %ebp
	xorl	%edi, %edi
	movl	$0, 16(%esp)
.L264:
	movl	32(%esp), %eax
	testl	%eax, 20(%esp)
	je	.L265
	orl	%edx, 16(%esp)
.L265:
	orl	%edx, %edi
	cmpl	$32, 72(%esp)
	jne	.L266
	movl	$0, 32(%esp)
	jmp	.L267
.L266:
	movb	72(%esp), %cl
	sall	%cl, 32(%esp)
.L267:
	decl	8(%esp)
	sall	%edx
	cmpl	$-1, 8(%esp)
	jne	.L268
	testl	%edi, %edi
	je	.L255
	movl	%edi, %ebx
	notl	%ebx
	movl	96(%esp), %ecx
	movl	(%ebp), %edx
	orl	%ebx, %ecx
	movl	100(%esp), %eax
	andl	%edx, %ecx
	andl	%edi, %eax
	orl	104(%esp), %ebx
	andl	108(%esp), %edi
	xorl	%eax, %ecx
	andl	%ebx, %edx
	andl	16(%esp), %ecx
	xorl	%edi, %edx
	notl	16(%esp)
	andl	16(%esp), %edx
	orl	%edx, %ecx
	movl	%ecx, (%ebp)
.L255:
	decl	92(%esp)
	cmpl	$-1, 92(%esp)
	jne	.L270
.L250:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	fbBltPlane, .-fbBltPlane
	.ident	"GCC: (GNU) 3.3.2"
