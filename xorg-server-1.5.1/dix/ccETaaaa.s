	.file	"dispatch.c"
	.local	grabState
	.comm	grabState,4,4
.globl ServerGrabCallback
	.section	.bss
	.align 4
	.type	ServerGrabCallback, @object
	.size	ServerGrabCallback, 4
ServerGrabCallback:
	.zero	4
.globl dispatchException
	.type	dispatchException, @object
	.size	dispatchException, 1
dispatchException:
	.zero	1
	.text
	.align 4
.globl SetInputCheck
	.type	SetInputCheck, @function
SetInputCheck:
	movl	4(%esp), %eax
	movl	%eax, checkForInput
	movl	8(%esp), %eax
	movl	%eax, checkForInput+4
	ret
	.size	SetInputCheck, .-SetInputCheck
	.align 4
.globl UpdateCurrentTime
	.type	UpdateCurrentTime, @function
UpdateCurrentTime:
	pushl	%esi
	pushl	%ebx
	movl	currentTime, %ebx
	call	GetTimeInMillis
	cmpl	%eax, currentTime+4
	movl	%eax, %esi
	jbe	.L3
	incl	%ebx
.L3:
	movl	checkForInput+4, %eax
	movl	(%eax), %edx
	movl	checkForInput, %eax
	cmpl	%edx, (%eax)
	je	.L4
	call	ProcessInputEvents
.L4:
	pushl	currentTime+4
	pushl	currentTime
	pushl	%esi
	pushl	%ebx
	call	CompareTimeStamps
	addl	$16, %esp
	decl	%eax
	jne	.L2
	movl	%ebx, currentTime
	movl	%esi, currentTime+4
.L2:
	popl	%ebx
	popl	%esi
	ret
	.size	UpdateCurrentTime, .-UpdateCurrentTime
	.align 4
.globl UpdateCurrentTimeIf
	.type	UpdateCurrentTimeIf, @function
UpdateCurrentTimeIf:
	pushl	%esi
	pushl	%ebx
	movl	currentTime, %ebx
	call	GetTimeInMillis
	cmpl	%eax, currentTime+4
	movl	%eax, %esi
	jbe	.L7
	incl	%ebx
.L7:
	movl	checkForInput+4, %eax
	movl	(%eax), %edx
	movl	checkForInput, %eax
	cmpl	%edx, (%eax)
	jne	.L6
	movl	%ebx, currentTime
	movl	%esi, currentTime+4
.L6:
	popl	%ebx
	popl	%esi
	ret
	.size	UpdateCurrentTimeIf, .-UpdateCurrentTimeIf
.globl SmartScheduleDisable
	.section	.bss
	.align 4
	.type	SmartScheduleDisable, @object
	.size	SmartScheduleDisable, 4
SmartScheduleDisable:
	.zero	4
.globl SmartScheduleSlice
	.data
	.align 4
	.type	SmartScheduleSlice, @object
	.size	SmartScheduleSlice, 4
SmartScheduleSlice:
	.long	20
.globl SmartScheduleInterval
	.align 4
	.type	SmartScheduleInterval, @object
	.size	SmartScheduleInterval, 4
SmartScheduleInterval:
	.long	20
.globl SmartScheduleMaxSlice
	.align 4
	.type	SmartScheduleMaxSlice, @object
	.size	SmartScheduleMaxSlice, 4
SmartScheduleMaxSlice:
	.long	200
	.text
	.align 4
	.type	SmartScheduleClient, @function
SmartScheduleClient:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	SmartScheduleSlice, %eax
	sall	%eax
	movl	%eax, 4(%esp)
	xorl	%esi, %esi
	movl	40(%esp), %eax
	cmpl	%eax, %esi
	movl	$0, 12(%esp)
	movl	SmartScheduleTime, %ebx
	movl	$-2147483647, %edi
	movl	$0, 8(%esp)
	jge	.L24
	movl	clients, %ecx
	movl	%ecx, (%esp)
.L18:
	movl	36(%esp), %eax
	movl	(%eax,%esi,4), %ebp
	movl	(%esp), %ecx
	movl	(%ecx,%ebp,4), %edx
	movl	%ebx, %eax
	subl	160(%edx), %eax
	cmpl	4(%esp), %eax
	jl	.L14
	movl	148(%edx), %eax
	testl	%eax, %eax
	jns	.L14
	incl	%eax
	movl	%eax, 148(%edx)
.L14:
	movl	148(%edx), %ecx
	movl	(%edx), %eax
	subl	SmartLastIndex+80(,%ecx,4), %eax
	andl	$255, %eax
	cmpl	%edi, %ecx
	movl	%ebx, 160(%edx)
	jg	.L17
	cmpl	%edi, %ecx
	jne	.L12
	cmpl	8(%esp), %eax
	jle	.L12
.L17:
	movl	%ecx, %edi
	movl	%eax, 8(%esp)
	movl	%ebp, 12(%esp)
.L12:
	incl	%esi
	cmpl	40(%esp), %esi
	jl	.L18
.L24:
	movl	clients, %eax
	movl	12(%esp), %ecx
	movl	(%eax,%ecx,4), %edx
	movl	(%edx), %eax
	cmpl	%edx, SmartLastClient
	movl	%eax, SmartLastIndex+80(,%edi,4)
	je	.L19
	movl	%ebx, 152(%edx)
	movl	%edx, SmartLastClient
.L19:
	cmpl	$1, 40(%esp)
	jne	.L20
	subl	152(%edx), %ebx
	cmpl	$1000, %ebx
	jle	.L22
	movl	SmartScheduleSlice, %eax
	cmpl	SmartScheduleMaxSlice, %eax
	jge	.L22
	addl	SmartScheduleInterval, %eax
	jmp	.L25
.L20:
	movl	SmartScheduleInterval, %eax
.L25:
	movl	%eax, SmartScheduleSlice
.L22:
	movl	12(%esp), %eax
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	SmartScheduleClient, .-SmartScheduleClient
	.align 4
.globl Dispatch
	.type	Dispatch, @function
Dispatch:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	movl	MaxClients, %eax
	pushl	%ebx
	sall	$2, %eax
	pushl	%eax
	movl	$1, nextFreeClientID
	movl	$0, nClients
	call	Xalloc
	testl	%eax, %eax
	movl	%eax, %edi
	popl	%ebx
	je	.L26
	movb	dispatchException, %al
	testb	%al, %al
	jne	.L59
.L56:
	movl	checkForInput+4, %eax
	movl	(%eax), %edx
	movl	checkForInput, %eax
	cmpl	%edx, (%eax)
	je	.L31
	call	ProcessInputEvents
	call	FlushIfCriticalOutputPending
.L31:
	pushl	%edi
	call	WaitForSomething
	testl	%eax, %eax
	movl	%eax, %esi
	popl	%ecx
	je	.L32
	cmpl	$0, SmartScheduleDisable
	jne	.L32
	pushl	%eax
	pushl	%edi
	call	SmartScheduleClient
	movl	%eax, (%edi)
	popl	%eax
	movl	$1, %esi
	popl	%edx
.L32:
	movb	dispatchException, %al
	testb	%al, %al
	jne	.L34
	decl	%esi
	js	.L34
.L55:
	movl	(%edi,%esi,4), %edx
	movl	clients, %eax
	movl	(%eax,%edx,4), %ebx
	testl	%ebx, %ebx
	je	.L33
	cmpl	$2, grabState
	jne	.L38
	movl	$1, grabState
	jmp	.L34
.L38:
	movb	$0, isItTimeToYield
	movb	isItTimeToYield, %al
	testb	%al, %al
	movl	SmartScheduleTime, %ebp
	jne	.L40
.L53:
	movl	checkForInput+4, %eax
	movl	(%eax), %edx
	movl	checkForInput, %eax
	cmpl	%edx, (%eax)
	je	.L42
	call	ProcessInputEvents
.L42:
	call	FlushIfCriticalOutputPending
	cmpl	$0, SmartScheduleDisable
	jne	.L43
	movl	SmartScheduleTime, %eax
	subl	%ebp, %eax
	cmpl	SmartScheduleSlice, %eax
	jl	.L43
	movl	148(%ebx), %eax
	cmpl	$-20, %eax
	jle	.L40
	decl	%eax
	movl	%eax, 148(%ebx)
	jmp	.L40
.L43:
	pushl	%ebx
	call	ReadRequestFromClient
	movl	%eax, %edx
	testl	%edx, %edx
	popl	%eax
	jg	.L45
	testl	%edx, %edx
	jns	.L40
.L64:
	pushl	%ebx
	call	CloseDownClient
	popl	%ebx
	jmp	.L40
.L45:
	movl	maxBigRequestSize, %eax
	sall	$2, %eax
	incl	28(%ebx)
	cmpl	%eax, %edx
	jle	.L47
	movl	$16, %edx
	jmp	.L62
.L47:
	movl	8(%ebx), %eax
	movzbl	(%eax), %edx
	movl	116(%ebx), %eax
	pushl	%ebx
	call	*(%eax,%edx,4)
	testl	%eax, %eax
	movl	%eax, %edx
	popl	%ecx
	je	.L39
.L62:
	cmpl	$0, 40(%ebx)
	jne	.L64
	pushl	%edx
	pushl	24(%ebx)
	pushl	%ebx
	call	MinorOpcodeOfRequest
	movzwl	%ax, %eax
	movl	%eax, (%esp)
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%eax
	pushl	%ebx
	call	SendErrorToClient
	addl	$20, %esp
	jmp	.L40
.L39:
	movb	isItTimeToYield, %al
	testb	%al, %al
	je	.L53
.L40:
	call	FlushAllOutput
	movl	(%edi,%esi,4), %edx
	movl	clients, %eax
	movl	(%eax,%edx,4), %ebx
	testl	%ebx, %ebx
	je	.L33
	movl	SmartScheduleTime, %eax
	movl	%eax, 156(%ebx)
.L33:
	movb	dispatchException, %al
	testb	%al, %al
	jne	.L34
	decl	%esi
	jns	.L55
.L34:
	movb	dispatchException, %al
	andl	$-5, %eax
	movb	%al, dispatchException
	movb	dispatchException, %al
	testb	%al, %al
	je	.L56
.L59:
	call	KillAllClients
	pushl	%edi
	call	Xfree
	movb	dispatchException, %al
	andl	$-2, %eax
	movb	%al, dispatchException
	popl	%eax
.L26:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	Dispatch, .-Dispatch
	.align 4
.globl ProcBadRequest
	.type	ProcBadRequest, @function
ProcBadRequest:
	movl	$1, %eax
	ret
	.size	ProcBadRequest, .-ProcBadRequest
	.align 4
.globl ProcCreateWindow
	.type	ProcCreateWindow, @function
ProcCreateWindow:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	pushl	%ebx
	movl	28(%esp), %edi
	cmpl	$7, 120(%edi)
	movl	8(%edi), %esi
	ja	.L67
	movl	$16, %edx
	jmp	.L66
.L67:
	pushl	%edi
	pushl	4(%esi)
	call	LegalNewID
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L68
	movl	4(%esi), %eax
	movl	$14, %edx
	movl	%eax, 24(%edi)
	jmp	.L66
.L68:
	pushl	$4096
	pushl	%edi
	pushl	8(%esi)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	movl	%eax, 16(%esp)
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L66
	movl	120(%edi), %ebx
	pushl	28(%esi)
	call	Ones
	subl	$8, %ebx
	cmpl	%ebx, %eax
	popl	%ebp
	movl	$16, %edx
	jne	.L66
	cmpw	$0, 16(%esi)
	je	.L72
	cmpw	$0, 18(%esi)
	jne	.L71
.L72:
	movl	$2, %edx
	movl	$0, 24(%edi)
	jmp	.L66
.L71:
	movl	%esp, %eax
	pushl	%eax
	pushl	24(%esi)
	pushl	%edi
	movzbl	1(%esi), %eax
	pushl	%eax
	leal	32(%esi), %eax
	pushl	%eax
	pushl	28(%esi)
	movzwl	22(%esi), %eax
	pushl	%eax
	movzwl	20(%esi), %eax
	pushl	%eax
	movzwl	18(%esi), %eax
	pushl	%eax
	movzwl	16(%esi), %eax
	pushl	%eax
	movswl	14(%esi),%eax
	pushl	%eax
	movswl	12(%esi),%eax
	pushl	%eax
	pushl	52(%esp)
	pushl	4(%esi)
	call	CreateWindow
	addl	$56, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	je	.L73
	movl	108(%eax), %ebp
	movl	$0, 108(%eax)
	pushl	%eax
	pushl	$1073741825
	pushl	4(%esi)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	movl	$11, %edx
	je	.L66
	movl	%ebp, 108(%ebx)
.L73:
	movl	40(%edi), %eax
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L66
	movl	(%esp), %edx
.L66:
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	ProcCreateWindow, .-ProcCreateWindow
	.align 4
.globl ProcChangeWindowAttributes
	.type	ProcChangeWindowAttributes, @function
ProcChangeWindowAttributes:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	20(%esp), %edi
	xorl	%edx, %edx
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L78
	movl	$16, %edx
	jmp	.L77
.L78:
	movl	8(%esi), %eax
	testb	$8, %ah
	je	.L79
	movl	$8388608, %edx
.L79:
	testl	$-2049, %eax
	je	.L80
	orl	$32, %edx
.L80:
	pushl	%edx
	pushl	%edi
	pushl	4(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L77
	movl	120(%edi), %ebx
	pushl	8(%esi)
	call	Ones
	subl	$3, %ebx
	cmpl	%eax, %ebx
	popl	%edx
	movl	$16, %edx
	jne	.L77
	pushl	%edi
	leal	12(%esi), %eax
	pushl	%eax
	pushl	8(%esi)
	pushl	12(%esp)
	call	ChangeWindowAttributes
	movl	%eax, %ecx
	movl	40(%edi), %eax
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L77
	movl	%ecx, %edx
.L77:
	popl	%esi
	popl	%ebx
	popl	%esi
	movl	%edx, %eax
	popl	%edi
	ret
	.size	ProcChangeWindowAttributes, .-ProcChangeWindowAttributes
	.align 4
.globl ProcGetWindowAttributes
	.type	ProcGetWindowAttributes, @function
ProcGetWindowAttributes:
	pushl	%esi
	pushl	%ebx
	subl	$52, %esp
	movl	64(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L86
	movl	$16, %eax
	jmp	.L85
.L86:
	pushl	$16
	pushl	%ebx
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L85
	leal	4(%esp), %esi
	pushl	%esi
	pushl	%ebx
	pushl	8(%esp)
	call	GetWindowAttributes
	addl	$12, %esp
	cmpl	$0, 16(%ebx)
	je	.L88
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%esi
	pushl	$44
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L90
.L88:
	pushl	%esi
	pushl	$44
	pushl	%ebx
	call	WriteToClient
.L90:
	addl	$12, %esp
	movl	40(%ebx), %eax
.L85:
	addl	$52, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	ProcGetWindowAttributes, .-ProcGetWindowAttributes
	.align 4
.globl ProcDestroyWindow
	.type	ProcDestroyWindow, @function
ProcDestroyWindow:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	movl	20(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %esi
	je	.L92
	movl	$16, %eax
	jmp	.L91
.L92:
	pushl	$4
	pushl	%ebx
	pushl	4(%esi)
	leal	12(%esp), %edi
	pushl	%edi
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L91
	movl	(%esp), %eax
	cmpl	$0, 28(%eax)
	je	.L94
	pushl	$8192
	pushl	%ebx
	movl	28(%eax), %eax
	pushl	4(%eax)
	pushl	%edi
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L91
	pushl	$0
	pushl	4(%esi)
	call	FreeResource
	popl	%esi
	popl	%edi
.L94:
	movl	40(%ebx), %eax
.L91:
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcDestroyWindow, .-ProcDestroyWindow
	.align 4
.globl ProcDestroySubwindows
	.type	ProcDestroySubwindows, @function
ProcDestroySubwindows:
	pushl	%ebx
	pushl	%eax
	movl	12(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L97
	movl	$16, %eax
	jmp	.L96
.L97:
	pushl	$8192
	pushl	%ebx
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L96
	pushl	%ebx
	pushl	4(%esp)
	call	DestroySubwindows
	popl	%ecx
	movl	40(%ebx), %eax
	popl	%ebx
.L96:
	popl	%edx
	popl	%ebx
	ret
	.size	ProcDestroySubwindows, .-ProcDestroySubwindows
	.align 4
.globl ProcChangeSaveSet
	.type	ProcChangeSaveSet, @function
ProcChangeSaveSet:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	16(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %esi
	je	.L100
	movl	$16, %eax
	jmp	.L99
.L100:
	pushl	$33554432
	pushl	%ebx
	pushl	4(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L99
	movl	(%esp), %edx
	movl	4(%edx), %eax
	andl	$534773760, %eax
	cmpl	%eax, 4(%ebx)
	jne	.L102
	movl	$8, %eax
	jmp	.L99
.L102:
	movb	1(%esi), %al
	cmpb	$1, %al
	ja	.L103
	pushl	$1
	pushl	$0
	movzbl	1(%esi), %eax
	pushl	%eax
	pushl	%edx
	pushl	%ebx
	call	AlterSaveSetForClient
	movl	%eax, %edx
	movl	40(%ebx), %eax
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L99
	movl	%edx, %eax
	jmp	.L99
.L103:
	movzbl	%al, %eax
	movl	%eax, 24(%ebx)
	movl	$2, %eax
.L99:
	popl	%edx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcChangeSaveSet, .-ProcChangeSaveSet
	.align 4
.globl ProcReparentWindow
	.type	ProcReparentWindow, @function
ProcReparentWindow:
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	pushl	%eax
	movl	20(%esp), %esi
	cmpl	$4, 120(%esi)
	movl	8(%esi), %ebx
	je	.L108
	movl	$16, %eax
	jmp	.L107
.L108:
	pushl	$33554432
	pushl	%esi
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L107
	pushl	$4096
	pushl	%esi
	pushl	8(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L107
	movl	(%esp), %ecx
	movl	4(%esp), %edx
	movl	16(%ecx), %eax
	cmpl	%eax, 16(%edx)
	jne	.L111
	movzbl	128(%edx), %eax
	andl	$3, %eax
	decl	%eax
	jne	.L112
	movb	2(%edx), %al
	cmpb	%al, 2(%ecx)
	jne	.L111
.L112:
	cmpb	$2, 1(%edx)
	je	.L113
	cmpb	$2, 1(%ecx)
	je	.L111
.L113:
	pushl	%esi
	movswl	14(%ebx),%eax
	pushl	%eax
	movswl	12(%ebx),%eax
	pushl	%eax
	pushl	12(%esp)
	pushl	20(%esp)
	call	ReparentWindow
	movl	%eax, %edx
	movl	40(%esi), %eax
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L107
	movl	%edx, %eax
	jmp	.L107
.L111:
	movl	$8, %eax
.L107:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcReparentWindow, .-ProcReparentWindow
	.align 4
.globl ProcMapWindow
	.type	ProcMapWindow, @function
ProcMapWindow:
	pushl	%ebx
	pushl	%eax
	movl	12(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L118
	movl	$16, %eax
	jmp	.L117
.L118:
	pushl	$32768
	pushl	%ebx
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L117
	pushl	%ebx
	pushl	4(%esp)
	call	MapWindow
	popl	%ecx
	movl	40(%ebx), %eax
	popl	%ebx
.L117:
	popl	%edx
	popl	%ebx
	ret
	.size	ProcMapWindow, .-ProcMapWindow
	.align 4
.globl ProcMapSubwindows
	.type	ProcMapSubwindows, @function
ProcMapSubwindows:
	pushl	%ebx
	pushl	%eax
	movl	12(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L121
	movl	$16, %eax
	jmp	.L120
.L121:
	pushl	$2048
	pushl	%ebx
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L120
	pushl	%ebx
	pushl	4(%esp)
	call	MapSubwindows
	popl	%ecx
	movl	40(%ebx), %eax
	popl	%ebx
.L120:
	popl	%edx
	popl	%ebx
	ret
	.size	ProcMapSubwindows, .-ProcMapSubwindows
	.align 4
.globl ProcUnmapWindow
	.type	ProcUnmapWindow, @function
ProcUnmapWindow:
	pushl	%ebx
	pushl	%eax
	movl	12(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L124
	movl	$16, %eax
	jmp	.L123
.L124:
	pushl	$16384
	pushl	%ebx
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L123
	pushl	$0
	pushl	4(%esp)
	call	UnmapWindow
	popl	%ecx
	movl	40(%ebx), %eax
	popl	%ebx
.L123:
	popl	%edx
	popl	%ebx
	ret
	.size	ProcUnmapWindow, .-ProcUnmapWindow
	.align 4
.globl ProcUnmapSubwindows
	.type	ProcUnmapSubwindows, @function
ProcUnmapSubwindows:
	pushl	%ebx
	pushl	%ebx
	movl	12(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L127
	movl	$16, %eax
	jmp	.L126
.L127:
	pushl	$2048
	pushl	%ebx
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L126
	pushl	(%esp)
	call	UnmapSubwindows
	movl	40(%ebx), %eax
	popl	%ecx
.L126:
	popl	%edx
	popl	%ebx
	ret
	.size	ProcUnmapSubwindows, .-ProcUnmapSubwindows
	.align 4
.globl ProcConfigureWindow
	.type	ProcConfigureWindow, @function
ProcConfigureWindow:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	20(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L130
	movl	$16, %edx
	jmp	.L129
.L130:
	pushl	$33554464
	pushl	%edi
	pushl	4(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L129
	movzwl	8(%esi), %eax
	movl	120(%edi), %ebx
	pushl	%eax
	call	Ones
	subl	$3, %ebx
	cmpl	%ebx, %eax
	popl	%edx
	movl	$16, %edx
	jne	.L129
	pushl	%edi
	leal	12(%esi), %eax
	pushl	%eax
	movzwl	8(%esi), %eax
	pushl	%eax
	pushl	12(%esp)
	call	ConfigureWindow
	movl	%eax, %ecx
	movl	40(%edi), %eax
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L129
	movl	%ecx, %edx
.L129:
	popl	%esi
	popl	%ebx
	popl	%esi
	movl	%edx, %eax
	popl	%edi
	ret
	.size	ProcConfigureWindow, .-ProcConfigureWindow
	.align 4
.globl ProcCirculateWindow
	.type	ProcCirculateWindow, @function
ProcCirculateWindow:
	pushl	%esi
	pushl	%ebx
	pushl	%esi
	movl	16(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	je	.L136
	movl	$16, %eax
	jmp	.L135
.L136:
	movb	1(%ebx), %al
	cmpb	$1, %al
	jbe	.L137
	movzbl	%al, %eax
	movl	%eax, 24(%esi)
	movl	$2, %eax
	jmp	.L135
.L137:
	pushl	$33554432
	pushl	%esi
	pushl	4(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L135
	pushl	%esi
	movzbl	1(%ebx), %eax
	pushl	%eax
	pushl	8(%esp)
	call	CirculateWindow
	movl	40(%esi), %eax
	addl	$12, %esp
.L135:
	popl	%ebx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcCirculateWindow, .-ProcCirculateWindow
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"dispatch.c"
.LC1:
	.string	"%s: got line %d\n"
	.text
	.align 4
	.type	GetGeometry, @function
GetGeometry:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	movl	20(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	24(%esp), %ebx
	movl	8(%esi), %edi
	je	.L140
	movl	$16, %eax
	jmp	.L139
.L140:
	pushl	$16
	pushl	$-1
	pushl	%esi
	pushl	4(%edi)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L139
	movb	$1, (%ebx)
	movl	(%esp), %ecx
	movw	28(%esi), %ax
	movw	%ax, 2(%ebx)
	movl	16(%ecx), %eax
	movl	(%eax), %edx
	movl	WindowTable, %eax
	movl	$0, 4(%ebx)
	movl	(%eax,%edx,4), %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%ebx)
	movb	2(%ecx), %al
	movb	%al, 1(%ebx)
	movw	12(%ecx), %ax
	movw	%ax, 16(%ebx)
	movw	14(%ecx), %ax
	movw	%ax, 18(%ebx)
	movb	(%ecx), %al
	cmpb	$2, %al
	je	.L143
	testb	%al, %al
	jne	.L142
	movl	4(%ecx), %eax
	cmpl	%eax, 4(%edi)
	jne	.L142
.L143:
	movw	100(%ecx), %ax
	subw	104(%ecx), %ax
	movw	%ax, 12(%ebx)
	movw	102(%ecx), %ax
	subw	104(%ecx), %ax
	movw	%ax, 14(%ebx)
	movw	104(%ecx), %ax
	movw	%ax, 20(%ebx)
	jmp	.L144
.L142:
	movw	$0, 20(%ebx)
	movw	$0, 14(%ebx)
	movw	$0, 12(%ebx)
.L144:
	pushl	$833
	pushl	$.LC0
	pushl	$.LC1
	call	printf
	xorl	%eax, %eax
	addl	$12, %esp
.L139:
	popl	%edi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	GetGeometry, .-GetGeometry
	.align 4
.globl ProcGetGeometry
	.type	ProcGetGeometry, @function
ProcGetGeometry:
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	44(%esp), %ebx
	pushl	$845
	pushl	$.LC0
	pushl	$.LC1
	leal	12(%esp), %esi
	call	printf
	pushl	%esi
	pushl	%ebx
	call	GetGeometry
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L145
	pushl	$850
	pushl	$.LC0
	pushl	$.LC1
	call	printf
	addl	$12, %esp
	cmpl	$0, 16(%ebx)
	je	.L147
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%esi
	pushl	$32
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L149
.L147:
	pushl	%esi
	pushl	$32
	pushl	%ebx
	call	WriteToClient
.L149:
	addl	$12, %esp
	movl	40(%ebx), %eax
.L145:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	ProcGetGeometry, .-ProcGetGeometry
	.align 4
.globl ProcQueryTree
	.type	ProcQueryTree, @function
ProcQueryTree:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	60(%esp), %edi
	xorl	%ebp, %ebp
	cmpl	$2, 120(%edi)
	movl	$0, (%esp)
	movl	8(%edi), %eax
	je	.L151
	movl	$16, %eax
	jmp	.L150
.L151:
	pushl	$2048
	pushl	%edi
	pushl	4(%eax)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L150
	movb	$1, 8(%esp)
	movl	4(%esp), %ecx
	movl	16(%ecx), %eax
	movl	(%eax), %edx
	movl	WindowTable, %eax
	movl	(%eax,%edx,4), %eax
	movl	4(%eax), %eax
	movl	%eax, 16(%esp)
	movw	28(%edi), %ax
	movw	%ax, 10(%esp)
	movl	28(%ecx), %eax
	testl	%eax, %eax
	je	.L153
	movl	4(%eax), %eax
	movl	%eax, 20(%esp)
	jmp	.L154
.L153:
	movl	$0, 20(%esp)
.L154:
	pushl	4(%esp)
	call	RealChildHead
	movl	%eax, %ebx
	movl	8(%esp), %eax
	movl	44(%eax), %edx
	cmpl	%ebx, %edx
	popl	%eax
	je	.L160
.L159:
	movl	36(%edx), %edx
	incl	%ebp
	cmpl	%ebx, %edx
	jne	.L159
	testl	%ebp, %ebp
	je	.L160
	leal	0(,%ebp,4), %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, 4(%esp)
	popl	%eax
	xorl	%esi, %esi
	cmpl	$0, (%esp)
	movl	$11, %eax
	je	.L150
	movl	4(%esp), %eax
	movl	44(%eax), %edx
	cmpl	%ebx, %edx
	je	.L160
.L166:
	movl	4(%edx), %eax
	movl	(%esp), %ecx
	movl	36(%edx), %edx
	movl	%eax, (%ecx,%esi,4)
	incl	%esi
	cmpl	%ebx, %edx
	jne	.L166
.L160:
	movl	%ebp, %eax
	andl	$1073741823, %eax
	cmpl	$0, 16(%edi)
	movw	%bp, 24(%esp)
	movl	%eax, 12(%esp)
	leal	8(%esp), %edx
	je	.L167
	movl	8(%edi), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%edi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L176
.L167:
	pushl	%edx
	pushl	$32
	pushl	%edi
	call	WriteToClient
.L176:
	addl	$12, %esp
	testl	%ebp, %ebp
	je	.L169
	cmpl	$0, 16(%edi)
	movl	$Swap32Write, 20(%edi)
	je	.L170
	pushl	(%esp)
	leal	0(,%ebp,4), %eax
	pushl	%eax
	pushl	%edi
	call	Swap32Write
	jmp	.L177
.L170:
	pushl	(%esp)
	leal	0(,%ebp,4), %eax
	pushl	%eax
	pushl	%edi
	call	WriteToClient
.L177:
	addl	$12, %esp
	pushl	(%esp)
	call	Xfree
	popl	%eax
.L169:
	movl	40(%edi), %eax
.L150:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcQueryTree, .-ProcQueryTree
	.align 4
.globl ProcInternAtom
	.type	ProcInternAtom, @function
ProcInternAtom:
	pushl	%ebx
	subl	$32, %esp
	movl	40(%esp), %ebx
	movl	120(%ebx), %edx
	cmpl	$1, %edx
	movl	8(%ebx), %ecx
	jbe	.L180
	movzwl	4(%ecx), %eax
	addl	$11, %eax
	shrl	$2, %eax
	cmpl	%edx, %eax
	je	.L179
.L180:
	movl	$16, %eax
	jmp	.L178
.L179:
	movb	1(%ecx), %dl
	cmpb	$1, %dl
	jbe	.L181
	movzbl	%dl, %eax
	movl	%eax, 24(%ebx)
	movl	$2, %eax
	jmp	.L178
.L181:
	testb	%dl, %dl
	sete	%dl
	movzbl	%dl, %edx
	pushl	%edx
	movzwl	4(%ecx), %edx
	pushl	%edx
	leal	8(%ecx), %eax
	pushl	%eax
	call	MakeAtom
	movl	%eax, %edx
	addl	$12, %esp
	cmpl	$-536870912, %edx
	movl	$11, %eax
	je	.L178
	movb	$1, (%esp)
	movw	28(%ebx), %ax
	cmpl	$0, 16(%ebx)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movw	%ax, 2(%esp)
	movl	%esp, %edx
	je	.L183
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L186
.L183:
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	WriteToClient
.L186:
	addl	$12, %esp
	movl	40(%ebx), %eax
.L178:
	addl	$32, %esp
	popl	%ebx
	ret
	.size	ProcInternAtom, .-ProcInternAtom
	.align 4
.globl ProcGetAtomName
	.type	ProcGetAtomName, @function
ProcGetAtomName:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	48(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %esi
	je	.L188
	movl	$16, %eax
	jmp	.L187
.L188:
	pushl	4(%esi)
	call	NameForAtom
	testl	%eax, %eax
	movl	%eax, %edi
	popl	%ecx
	je	.L189
	pushl	%eax
	call	strlen
	movl	%eax, %esi
	popl	%edx
	leal	3(%eax), %eax
	sarl	$2, %eax
	movb	$1, (%esp)
	movl	%eax, 4(%esp)
	cmpl	$0, 16(%ebx)
	movw	28(%ebx), %ax
	movw	%ax, 2(%esp)
	movw	%si, 8(%esp)
	movl	%esp, %edx
	je	.L190
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L193
.L190:
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	WriteToClient
.L193:
	addl	$12, %esp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	call	WriteToClient
	movl	40(%ebx), %eax
	addl	$12, %esp
	jmp	.L187
.L189:
	movl	4(%esi), %eax
	movl	%eax, 24(%ebx)
	movl	$5, %eax
.L187:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcGetAtomName, .-ProcGetAtomName
	.align 4
.globl ProcGrabServer
	.type	ProcGrabServer, @function
ProcGrabServer:
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	pushl	%eax
	movl	20(%esp), %ebx
	movl	120(%ebx), %esi
	cmpl	$1, %esi
	movl	$16, %eax
	jne	.L194
	cmpl	$0, grabState
	je	.L196
	cmpl	grabClient, %ebx
	je	.L196
	pushl	%ebx
	call	ResetCurrentRequest
	movl	(%ebx), %ecx
	movl	%ecx, %eax
	andl	$31, %ecx
	decl	28(%ebx)
	sarl	$5, %eax
	sall	%cl, %esi
	pushl	%ebx
	orl	%esi, grabWaiters(,%eax,4)
	call	IgnoreClient
	movl	40(%ebx), %eax
	popl	%ebx
	popl	%esi
	jmp	.L194
.L196:
	pushl	%ebx
	call	OnlyListenToOneClient
	testl	%eax, %eax
	popl	%ecx
	jne	.L194
	cmpl	$0, ServerGrabCallback
	movl	$2, grabState
	movl	%ebx, grabClient
	je	.L198
	movl	%esp, %eax
	movl	%ebx, (%esp)
	movl	$0, 4(%esp)
	pushl	%eax
	pushl	$ServerGrabCallback
	call	CallCallbacks
	popl	%eax
	popl	%edx
.L198:
	movl	40(%ebx), %eax
.L194:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcGrabServer, .-ProcGrabServer
	.align 4
	.type	UngrabServer, @function
UngrabServer:
	pushl	%ebx
	pushl	%eax
	pushl	%eax
	movl	$8, %ebx
	movl	$0, grabState
	call	ListenToAllClients
.L200:
	decl	%ebx
	js	.L206
	cmpl	$0, grabWaiters(,%ebx,4)
	je	.L200
	sall	$5, %ebx
	movl	%ebx, %eax
	sarl	$5, %eax
	testb	$1, grabWaiters(,%eax,4)
	jne	.L213
.L210:
	incl	%ebx
	movl	%ebx, %ecx
	andl	$31, %ecx
	movl	%ebx, %edx
	movl	$1, %eax
	sarl	$5, %edx
	sall	%cl, %eax
	testl	%eax, grabWaiters(,%edx,4)
	je	.L210
.L213:
	movl	%ebx, %ecx
	andl	$31, %ecx
	movl	%ebx, %edx
	movl	$-2, %eax
	roll	%cl, %eax
	sarl	$5, %edx
	andl	%eax, grabWaiters(,%edx,4)
	movl	clients, %eax
	pushl	(%eax,%ebx,4)
	call	AttendClient
	popl	%eax
.L206:
	cmpl	$0, ServerGrabCallback
	je	.L199
	movl	16(%esp), %eax
	movl	%eax, (%esp)
	movl	%esp, %eax
	movl	$1, 4(%esp)
	pushl	%eax
	pushl	$ServerGrabCallback
	call	CallCallbacks
	popl	%ecx
	popl	%ebx
.L199:
	popl	%eax
	popl	%edx
	popl	%ebx
	ret
	.size	UngrabServer, .-UngrabServer
	.align 4
.globl ProcUngrabServer
	.type	ProcUngrabServer, @function
ProcUngrabServer:
	pushl	%ebx
	movl	8(%esp), %ebx
	cmpl	$1, 120(%ebx)
	je	.L215
	movl	$16, %eax
	jmp	.L214
.L215:
	pushl	%ebx
	call	UngrabServer
	movl	40(%ebx), %eax
	popl	%edx
.L214:
	popl	%ebx
	ret
	.size	ProcUngrabServer, .-ProcUngrabServer
	.align 4
.globl ProcTranslateCoords
	.type	ProcTranslateCoords, @function
ProcTranslateCoords:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$48, %esp
	movl	68(%esp), %eax
	cmpl	$4, 120(%eax)
	movl	8(%eax), %ebx
	je	.L217
	movl	$16, %eax
	jmp	.L216
.L217:
	pushl	$16
	pushl	72(%esp)
	pushl	4(%ebx)
	leal	24(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L216
	pushl	$16
	pushl	72(%esp)
	pushl	8(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L216
	movb	$1, 16(%esp)
	movl	68(%esp), %edx
	movw	28(%edx), %ax
	movl	8(%esp), %ecx
	movw	%ax, 18(%esp)
	movl	12(%esp), %edx
	movl	16(%ecx), %eax
	cmpl	%eax, 16(%edx)
	movl	$0, 20(%esp)
	movl	%ecx, 4(%esp)
	je	.L220
	movb	$0, 17(%esp)
	movl	$0, 24(%esp)
	movw	$0, 30(%esp)
	movw	$0, 28(%esp)
	jmp	.L221
.L220:
	movb	$1, 17(%esp)
	movw	12(%ebx), %di
	movw	14(%ebx), %bp
	addw	8(%edx), %di
	addw	10(%edx), %bp
	movl	4(%esp), %edx
	movl	40(%edx), %eax
	testl	%eax, %eax
	movl	$0, 24(%esp)
	movl	%eax, 12(%esp)
	je	.L231
	movl	%eax, %edx
.L227:
	movl	%edx, (%esp)
	testb	$8, 130(%edx)
	je	.L225
	movswl	8(%edx),%ebx
	movzwl	104(%edx), %ecx
	movl	%ebx, %eax
	movswl	%di,%esi
	subl	%ecx, %eax
	cmpl	%eax, %esi
	jl	.L225
	movzwl	12(%edx), %eax
	leal	(%eax,%ebx), %eax
	addl	%ecx, %eax
	cmpl	%eax, %esi
	jge	.L225
	movswl	10(%edx),%ebx
	movl	%ebx, %eax
	movswl	%bp,%esi
	subl	%ecx, %eax
	cmpl	%eax, %esi
	jl	.L225
	movzwl	14(%edx), %eax
	leal	(%eax,%ebx), %eax
	addl	%ecx, %eax
	cmpl	%eax, %esi
	jge	.L225
	movl	4(%edx), %eax
	xorl	%edx, %edx
	movl	%eax, 24(%esp)
	jmp	.L222
.L225:
	movl	(%esp), %ecx
	movl	32(%ecx), %edx
.L222:
	testl	%edx, %edx
	jne	.L227
	movl	$0, 12(%esp)
.L231:
	movl	4(%esp), %eax
	subw	8(%eax), %di
	movw	%di, 28(%esp)
	subw	10(%eax), %bp
	movw	%bp, 30(%esp)
.L221:
	movl	68(%esp), %edx
	cmpl	$0, 16(%edx)
	leal	16(%esp), %edx
	je	.L228
	movl	68(%esp), %ecx
	movl	8(%ecx), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%ecx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L233
.L228:
	pushl	%edx
	pushl	$32
	pushl	76(%esp)
	call	WriteToClient
.L233:
	addl	$12, %esp
	movl	68(%esp), %edx
	movl	40(%edx), %eax
.L216:
	addl	$48, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcTranslateCoords, .-ProcTranslateCoords
	.align 4
.globl ProcOpenFont
	.type	ProcOpenFont, @function
ProcOpenFont:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %esi
	movl	120(%esi), %edx
	cmpl	$2, %edx
	movl	8(%esi), %ebx
	jbe	.L236
	movzwl	8(%ebx), %eax
	addl	$15, %eax
	shrl	$2, %eax
	cmpl	%edx, %eax
	je	.L235
.L236:
	movl	$16, %eax
	jmp	.L234
.L235:
	movl	4(%ebx), %eax
	movl	%eax, 24(%esi)
	pushl	%esi
	pushl	4(%ebx)
	call	LegalNewID
	testl	%eax, %eax
	popl	%ecx
	popl	%edx
	jne	.L237
	movl	4(%ebx), %eax
	movl	%eax, 24(%esi)
	movl	$14, %eax
	jmp	.L234
.L237:
	leal	12(%ebx), %eax
	pushl	%eax
	movzwl	8(%ebx), %eax
	pushl	%eax
	pushl	$0
	pushl	4(%ebx)
	pushl	%esi
	call	OpenFont
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L234
	movl	40(%esi), %eax
.L234:
	popl	%ebx
	popl	%esi
	ret
	.size	ProcOpenFont, .-ProcOpenFont
	.align 4
.globl ProcCloseFont
	.type	ProcCloseFont, @function
ProcCloseFont:
	pushl	%esi
	pushl	%ebx
	movl	12(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	je	.L241
	movl	$16, %eax
	jmp	.L240
.L241:
	pushl	$4
	pushl	$4
	pushl	4(%ebx)
	pushl	%esi
	call	SecurityLookupIDByType
	addl	$16, %esp
	testl	%eax, %eax
	je	.L242
	pushl	$0
	pushl	4(%ebx)
	call	FreeResource
	popl	%ecx
	movl	40(%esi), %eax
	popl	%ebx
	jmp	.L240
.L242:
	movl	4(%ebx), %eax
	movl	%eax, 24(%esi)
	movl	$7, %eax
.L240:
	popl	%ebx
	popl	%esi
	ret
	.size	ProcCloseFont, .-ProcCloseFont
	.align 4
.globl ProcQueryFont
	.type	ProcQueryFont, @function
ProcQueryFont:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	pushl	%eax
	movl	28(%esp), %eax
	cmpl	$2, 120(%eax)
	movl	8(%eax), %ebx
	je	.L245
	movl	$16, %eax
	jmp	.L244
.L245:
	movl	28(%esp), %edx
	movl	4(%ebx), %eax
	movl	%eax, 24(%edx)
	pushl	$16
	pushl	%edx
	pushl	$4
	pushl	4(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	cmpl	$2, %eax
	movl	%eax, %edx
	jne	.L246
	pushl	$16
	pushl	32(%esp)
	pushl	$3
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L257
	movl	(%esp), %eax
	movl	44(%eax), %eax
	movl	%eax, 4(%esp)
.L246:
	testl	%edx, %edx
	je	.L248
.L257:
	cmpl	$2, %edx
	movl	%edx, %eax
	jne	.L244
	movl	$7, %eax
	jmp	.L244
.L248:
	movl	4(%esp), %ecx
	leal	56(%ecx), %edx
	leal	44(%ecx), %ebx
	movw	2(%edx), %ax
	cmpw	%ax, 2(%ebx)
	jne	.L253
	movw	56(%ecx), %ax
	cmpw	%ax, 44(%ecx)
	jne	.L253
	movw	8(%edx), %ax
	cmpw	%ax, 8(%ebx)
	jne	.L253
	movw	6(%edx), %ax
	cmpw	%ax, 6(%ebx)
	jne	.L253
	movw	4(%edx), %ax
	cmpw	%ax, 4(%ebx)
	je	.L251
.L253:
	movzwl	4(%ecx), %edx
	movzwl	6(%ecx), %eax
	subl	%edx, %eax
	leal	1(%eax), %esi
	movzwl	8(%ecx), %edx
	movzwl	10(%ecx), %eax
	subl	%edx, %eax
	incl	%eax
	imull	%eax, %esi
	jmp	.L252
.L251:
	xorl	%esi, %esi
.L252:
	movl	4(%esp), %eax
	movl	72(%eax), %edx
	imull	$12, %esi, %eax
	leal	(%eax,%edx,8), %ebp
	leal	60(%ebp), %edi
	pushl	%edi
	call	Xalloc
	movl	%eax, %ebx
	testl	%ebx, %ebx
	popl	%eax
	movl	$11, %eax
	je	.L244
	movb	$1, (%ebx)
	leal	28(%ebp), %eax
	movl	28(%esp), %edx
	shrl	$2, %eax
	movl	%eax, 4(%ebx)
	movw	28(%edx), %ax
	movw	%ax, 2(%ebx)
	pushl	%esi
	pushl	%ebx
	pushl	12(%esp)
	call	QueryFont
	addl	$12, %esp
	movl	28(%esp), %eax
	cmpl	$0, 16(%eax)
	je	.L255
	movl	%eax, %edx
	movl	8(%eax), %eax
	movzbl	(%eax), %eax
	pushl	%ebx
	pushl	%edi
	pushl	%edx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L258
.L255:
	pushl	%ebx
	pushl	%edi
	pushl	36(%esp)
	call	WriteToClient
.L258:
	addl	$12, %esp
	pushl	%ebx
	call	Xfree
	movl	32(%esp), %edx
	movl	40(%edx), %eax
	popl	%ebp
.L244:
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcQueryFont, .-ProcQueryFont
	.align 4
.globl ProcQueryTextExtents
	.type	ProcQueryTextExtents, @function
ProcQueryTextExtents:
	pushl	%esi
	pushl	%ebx
	subl	$72, %esp
	movl	84(%esp), %esi
	cmpl	$1, 120(%esi)
	movl	8(%esi), %ebx
	ja	.L260
	movl	$16, %ecx
	jmp	.L259
.L260:
	movl	4(%ebx), %eax
	movl	%eax, 24(%esi)
	pushl	$16
	pushl	%esi
	pushl	$4
	pushl	4(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	cmpl	$2, %eax
	movl	%eax, %edx
	jne	.L261
	pushl	$16
	pushl	%esi
	pushl	$3
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L271
	movl	(%esp), %eax
	movl	44(%eax), %eax
	movl	%eax, 4(%esp)
.L261:
	testl	%edx, %edx
	je	.L263
.L271:
	cmpl	$2, %edx
	movl	%edx, %eax
	jne	.L265
	movl	$7, %eax
.L265:
	movl	%eax, %ecx
	jmp	.L259
.L263:
	movl	120(%esi), %edx
	subl	$2, %edx
	sall	%edx
	cmpb	$0, 1(%ebx)
	je	.L266
	testl	%edx, %edx
	movl	$16, %ecx
	je	.L259
	decl	%edx
.L266:
	leal	8(%esp), %eax
	pushl	%eax
	leal	8(%ebx), %eax
	pushl	%eax
	pushl	%edx
	pushl	16(%esp)
	call	QueryTextExtents
	addl	$16, %esp
	testl	%eax, %eax
	movl	$11, %ecx
	je	.L259
	movb	$1, 40(%esp)
	movw	28(%esi), %ax
	movw	%ax, 42(%esp)
	movb	8(%esp), %al
	movb	%al, 41(%esp)
	movl	12(%esp), %eax
	movw	%ax, 48(%esp)
	movl	16(%esp), %eax
	movw	%ax, 50(%esp)
	movl	20(%esp), %eax
	movw	%ax, 52(%esp)
	movl	24(%esp), %eax
	movw	%ax, 54(%esp)
	movl	28(%esp), %eax
	movl	%eax, 56(%esp)
	movl	32(%esp), %eax
	movl	%eax, 60(%esp)
	cmpl	$0, 16(%esi)
	movl	36(%esp), %eax
	movl	$0, 44(%esp)
	movl	%eax, 64(%esp)
	leal	40(%esp), %edx
	je	.L269
	movl	8(%esi), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%esi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L272
.L269:
	pushl	%edx
	pushl	$32
	pushl	%esi
	call	WriteToClient
.L272:
	addl	$12, %esp
	movl	40(%esi), %ecx
.L259:
	addl	$72, %esp
	popl	%ebx
	movl	%ecx, %eax
	popl	%esi
	ret
	.size	ProcQueryTextExtents, .-ProcQueryTextExtents
	.align 4
.globl ProcListFonts
	.type	ProcListFonts, @function
ProcListFonts:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	120(%ebx), %ecx
	cmpl	$1, %ecx
	movl	8(%ebx), %edx
	jbe	.L275
	movzwl	6(%edx), %eax
	addl	$11, %eax
	shrl	$2, %eax
	cmpl	%ecx, %eax
	je	.L274
.L275:
	movl	$16, %eax
	jmp	.L273
.L274:
	movzwl	4(%edx), %eax
	pushl	%eax
	movzwl	6(%edx), %eax
	pushl	%eax
	leal	8(%edx), %eax
	pushl	%eax
	pushl	%ebx
	call	ListFonts
	addl	$16, %esp
.L273:
	popl	%ebx
	ret
	.size	ProcListFonts, .-ProcListFonts
	.align 4
.globl ProcListFontsWithInfo
	.type	ProcListFontsWithInfo, @function
ProcListFontsWithInfo:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	120(%ebx), %ecx
	cmpl	$1, %ecx
	movl	8(%ebx), %edx
	jbe	.L278
	movzwl	6(%edx), %eax
	addl	$11, %eax
	shrl	$2, %eax
	cmpl	%ecx, %eax
	je	.L277
.L278:
	movl	$16, %eax
	jmp	.L276
.L277:
	movzwl	4(%edx), %eax
	pushl	%eax
	leal	8(%edx), %eax
	pushl	%eax
	movzwl	6(%edx), %eax
	pushl	%eax
	pushl	%ebx
	call	StartListFontsWithInfo
	addl	$16, %esp
.L276:
	popl	%ebx
	ret
	.size	ProcListFontsWithInfo, .-ProcListFontsWithInfo
	.align 4
.globl dixDestroyPixmap
	.type	dixDestroyPixmap, @function
dixDestroyPixmap:
	movl	4(%esp), %eax
	movl	16(%eax), %edx
	pushl	%eax
	call	*196(%edx)
	popl	%edx
	ret
	.size	dixDestroyPixmap, .-dixDestroyPixmap
	.align 4
.globl ProcCreatePixmap
	.type	ProcCreatePixmap, @function
ProcCreatePixmap:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	28(%esp), %ebp
	cmpl	$4, 120(%ebp)
	movl	8(%ebp), %ebx
	je	.L281
	movl	$16, %eax
	jmp	.L280
.L281:
	movl	4(%ebx), %eax
	movl	%eax, 24(%ebp)
	pushl	%ebp
	pushl	4(%ebx)
	call	LegalNewID
	testl	%eax, %eax
	popl	%edi
	popl	%edx
	jne	.L282
	movl	4(%ebx), %eax
	movl	%eax, 24(%ebp)
	movl	$14, %eax
	jmp	.L280
.L282:
	pushl	$16
	pushl	$-1
	pushl	%ebp
	pushl	8(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %ecx
	jne	.L280
	movw	12(%ebx), %dx
	testw	%dx, %dx
	je	.L285
	movw	14(%ebx), %ax
	testw	%ax, %ax
	jne	.L284
.L285:
	movl	$0, 24(%ebp)
	jmp	.L303
.L284:
	testw	%dx, %dx
	js	.L296
	testw	%ax, %ax
	js	.L296
	movb	1(%ebx), %al
	movb	%al, 3(%esp)
	decb	%al
	je	.L294
	movl	4(%esp), %eax
	movl	16(%eax), %eax
	movw	16(%eax), %di
	movl	20(%eax), %edx
	movswl	%di,%eax
	xorl	%esi, %esi
	cmpl	%eax, %ecx
	jge	.L302
.L295:
	movb	3(%esp), %al
	cmpb	%al, (%edx)
	je	.L294
	incl	%esi
	movswl	%di,%eax
	addl	$8, %edx
	cmpl	%eax, %esi
	jl	.L295
.L302:
	movzbl	1(%ebx), %eax
	movl	%eax, 24(%ebp)
.L303:
	movl	$2, %eax
	jmp	.L280
.L294:
	movl	4(%esp), %edx
	movl	16(%edx), %ecx
	pushl	$0
	movzbl	1(%ebx), %eax
	pushl	%eax
	movzwl	14(%ebx), %eax
	pushl	%eax
	movzwl	12(%ebx), %eax
	pushl	%eax
	pushl	16(%edx)
	call	*192(%ecx)
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %esi
	je	.L296
	movl	globalSerialNumber, %eax
	incl	%eax
	cmpl	$268435456, %eax
	movl	%eax, globalSerialNumber
	jbe	.L298
	movl	$1, globalSerialNumber
	movl	$1, %eax
.L298:
	movl	%eax, 20(%esi)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esi)
	pushl	%esi
	pushl	$1073741826
	pushl	4(%ebx)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	je	.L300
	movl	40(%ebp), %eax
	jmp	.L280
.L300:
	movl	4(%esp), %eax
	movl	16(%eax), %eax
	pushl	%esi
	call	*196(%eax)
	popl	%esi
.L296:
	movl	$11, %eax
.L280:
	popl	%ecx
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcCreatePixmap, .-ProcCreatePixmap
	.align 4
.globl ProcFreePixmap
	.type	ProcFreePixmap, @function
ProcFreePixmap:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	16(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	je	.L305
	movl	$16, %eax
	jmp	.L304
.L305:
	pushl	$4
	pushl	%esi
	pushl	$1073741826
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L306
	pushl	$0
	pushl	4(%ebx)
	call	FreeResource
	movl	40(%esi), %eax
	popl	%esi
	popl	%edx
	jmp	.L304
.L306:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L304
	movl	$4, %eax
.L304:
	popl	%ebx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcFreePixmap, .-ProcFreePixmap
	.align 4
.globl ProcCreateGC
	.type	ProcCreateGC, @function
ProcCreateGC:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%esi
	pushl	%esi
	movl	24(%esp), %edi
	cmpl	$3, 120(%edi)
	movl	8(%edi), %esi
	ja	.L311
	movl	$16, %edx
	jmp	.L310
.L311:
	movl	4(%esi), %eax
	movl	%eax, 24(%edi)
	pushl	%edi
	pushl	4(%esi)
	call	LegalNewID
	testl	%eax, %eax
	popl	%ecx
	popl	%ebx
	jne	.L312
	movl	4(%esi), %eax
	movl	$14, %edx
	movl	%eax, 24(%edi)
	jmp	.L310
.L312:
	pushl	$16
	pushl	$0
	pushl	%edi
	pushl	8(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L310
	movl	120(%edi), %ebx
	pushl	12(%esi)
	call	Ones
	subl	$4, %ebx
	cmpl	%eax, %ebx
	popl	%edx
	movl	$16, %edx
	jne	.L310
	pushl	%edi
	pushl	4(%esi)
	leal	8(%esp), %eax
	pushl	%eax
	leal	16(%esi), %eax
	pushl	%eax
	pushl	12(%esi)
	pushl	24(%esp)
	call	CreateGC
	addl	$24, %esp
	movl	%eax, %ecx
	movl	(%esp), %eax
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L310
	pushl	%ecx
	pushl	$3
	pushl	4(%esi)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	movl	$11, %edx
	je	.L310
	movl	40(%edi), %edx
.L310:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	movl	%edx, %eax
	popl	%edi
	ret
	.size	ProcCreateGC, .-ProcCreateGC
	.align 4
.globl ProcChangeGC
	.type	ProcChangeGC, @function
ProcChangeGC:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	20(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L318
	movl	$16, %edx
	jmp	.L317
.L318:
	pushl	$32
	pushl	%edi
	pushl	4(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L317
	movl	120(%edi), %ebx
	pushl	8(%esi)
	call	Ones
	subl	$3, %ebx
	cmpl	%eax, %ebx
	popl	%edx
	movl	$16, %edx
	jne	.L317
	pushl	$0
	leal	12(%esi), %eax
	pushl	%eax
	pushl	8(%esi)
	pushl	12(%esp)
	pushl	%edi
	call	dixChangeGC
	movl	%eax, %ecx
	movl	40(%edi), %eax
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L317
	movl	clientErrorValue, %eax
	movl	%eax, 24(%edi)
	movl	%ecx, %edx
.L317:
	popl	%edi
	popl	%ebx
	popl	%esi
	movl	%edx, %eax
	popl	%edi
	ret
	.size	ProcChangeGC, .-ProcChangeGC
	.align 4
.globl ProcCopyGC
	.type	ProcCopyGC, @function
ProcCopyGC:
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	pushl	%eax
	movl	20(%esp), %esi
	cmpl	$4, 120(%esi)
	movl	8(%esi), %ebx
	je	.L324
	movl	$16, %eax
	jmp	.L323
.L324:
	pushl	$16
	pushl	%esi
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L323
	pushl	$32
	pushl	%esi
	pushl	8(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L323
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movl	(%ecx), %eax
	cmpl	%eax, (%edx)
	jne	.L328
	movb	4(%ecx), %al
	cmpb	%al, 4(%edx)
	je	.L327
.L328:
	movl	$8, %eax
	jmp	.L323
.L327:
	pushl	12(%ebx)
	pushl	%edx
	pushl	%ecx
	call	CopyGC
	movl	%eax, %edx
	movl	40(%esi), %eax
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L323
	movl	clientErrorValue, %eax
	movl	%eax, 24(%esi)
	movl	%edx, %eax
.L323:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcCopyGC, .-ProcCopyGC
	.align 4
.globl ProcSetDashes
	.type	ProcSetDashes, @function
ProcSetDashes:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	16(%esp), %esi
	movl	120(%esi), %ecx
	cmpl	$2, %ecx
	movl	8(%esi), %ebx
	jbe	.L333
	movw	10(%ebx), %dx
	movzwl	%dx, %eax
	addl	$15, %eax
	shrl	$2, %eax
	cmpl	%ecx, %eax
	je	.L332
.L333:
	movl	$16, %eax
	jmp	.L331
.L332:
	testw	%dx, %dx
	jne	.L334
	movl	$2, %eax
	movl	$0, 24(%esi)
	jmp	.L331
.L334:
	pushl	$32
	pushl	%esi
	pushl	4(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L331
	leal	12(%ebx), %eax
	pushl	%eax
	movzwl	10(%ebx), %eax
	pushl	%eax
	movzwl	8(%ebx), %eax
	pushl	%eax
	pushl	12(%esp)
	call	SetDashes
	movl	%eax, %edx
	movl	40(%esi), %eax
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L331
	movl	clientErrorValue, %eax
	movl	%eax, 24(%esi)
	movl	%edx, %eax
.L331:
	popl	%edx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcSetDashes, .-ProcSetDashes
	.align 4
.globl ProcSetClipRectangles
	.type	ProcSetClipRectangles, @function
ProcSetClipRectangles:
	pushl	%esi
	pushl	%ebx
	pushl	%esi
	movl	16(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	ja	.L339
	movl	$16, %eax
	jmp	.L338
.L339:
	movb	1(%ebx), %al
	cmpb	$3, %al
	jbe	.L340
	movzbl	%al, %eax
	movl	%eax, 24(%esi)
	movl	$2, %eax
	jmp	.L338
.L340:
	pushl	$32
	pushl	%esi
	pushl	4(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L338
	movl	120(%esi), %eax
	leal	-12(,%eax,4), %edx
	testb	$4, %dl
	movl	$16, %eax
	jne	.L338
	movzbl	1(%ebx), %eax
	pushl	%eax
	leal	12(%ebx), %eax
	pushl	%eax
	sarl	$3, %edx
	pushl	%edx
	movswl	10(%ebx),%eax
	pushl	%eax
	movswl	8(%ebx),%eax
	pushl	%eax
	pushl	20(%esp)
	call	SetClipRects
	movl	%eax, %edx
	movl	40(%esi), %eax
	addl	$24, %esp
	testl	%eax, %eax
	jne	.L338
	movl	%edx, %eax
.L338:
	popl	%ebx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcSetClipRectangles, .-ProcSetClipRectangles
	.align 4
.globl ProcFreeGC
	.type	ProcFreeGC, @function
ProcFreeGC:
	pushl	%esi
	pushl	%ebx
	pushl	%esi
	movl	16(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %esi
	je	.L346
	movl	$16, %eax
	jmp	.L345
.L346:
	pushl	$4
	pushl	%ebx
	pushl	4(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L345
	pushl	$0
	pushl	4(%esi)
	call	FreeResource
	popl	%ecx
	movl	40(%ebx), %eax
	popl	%ebx
.L345:
	popl	%edx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcFreeGC, .-ProcFreeGC
	.align 4
.globl ProcClearToBackground
	.type	ProcClearToBackground, @function
ProcClearToBackground:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	16(%esp), %esi
	cmpl	$4, 120(%esi)
	movl	8(%esi), %ebx
	je	.L349
	movl	$16, %eax
	jmp	.L348
.L349:
	pushl	$2
	pushl	%esi
	pushl	4(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L348
	movl	(%esp), %ecx
	cmpb	$2, 1(%ecx)
	jne	.L351
	movl	4(%ebx), %eax
	movl	%eax, 24(%esi)
	movl	$8, %eax
	jmp	.L348
.L351:
	movb	1(%ebx), %al
	cmpb	$1, %al
	jbe	.L352
	movzbl	%al, %eax
	movl	%eax, 24(%esi)
	movl	$2, %eax
	jmp	.L348
.L352:
	movzbl	%al, %eax
	movl	16(%ecx), %edx
	pushl	%eax
	movzwl	14(%ebx), %eax
	pushl	%eax
	movzwl	12(%ebx), %eax
	pushl	%eax
	movswl	10(%ebx),%eax
	pushl	%eax
	movswl	8(%ebx),%eax
	pushl	%eax
	pushl	%ecx
	call	*180(%edx)
	movl	40(%esi), %eax
	addl	$24, %esp
.L348:
	popl	%edx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcClearToBackground, .-ProcClearToBackground
	.align 4
.globl ProcCopyArea
	.type	ProcCopyArea, @function
ProcCopyArea:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	28(%esp), %edi
	cmpl	$7, 120(%edi)
	movl	8(%edi), %ebx
	je	.L354
	movl	$16, %eax
	jmp	.L353
.L354:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	8(%ebx)
	leal	24(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L353
	pushl	$16777216
	pushl	%edi
	pushl	12(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L353
	movl	8(%esp), %ecx
	movl	4(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L367
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	jne	.L367
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L359
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%esi
	popl	%eax
.L359:
	movl	4(%ebx), %eax
	cmpl	%eax, 8(%ebx)
	je	.L360
	pushl	$1
	pushl	$0
	pushl	%edi
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L353
	movl	(%esp), %edx
	movl	8(%esp), %ecx
	movl	16(%edx), %eax
	cmpl	%eax, 16(%ecx)
	jne	.L363
	movb	2(%edx), %al
	cmpb	%al, 2(%ecx)
	je	.L364
.L363:
	movl	8(%ebx), %eax
	movl	%eax, 24(%edi)
.L367:
	movl	$8, %eax
	jmp	.L353
.L360:
	movl	8(%esp), %eax
	movl	%eax, (%esp)
.L364:
	movl	4(%esp), %edx
	movswl	22(%ebx),%eax
	movl	72(%edx), %ecx
	pushl	%eax
	movswl	20(%ebx),%eax
	pushl	%eax
	movzwl	26(%ebx), %eax
	pushl	%eax
	movzwl	24(%ebx), %eax
	pushl	%eax
	movswl	18(%ebx),%eax
	pushl	%eax
	movswl	16(%ebx),%eax
	pushl	%eax
	pushl	%edx
	pushl	36(%esp)
	pushl	32(%esp)
	call	*12(%ecx)
	addl	$36, %esp
	movl	%eax, %esi
	movl	4(%esp), %eax
	testb	$8, 17(%eax)
	je	.L365
	movl	8(%esp), %eax
	movl	16(%eax), %eax
	pushl	$0
	pushl	$62
	pushl	8(%ebx)
	pushl	%esi
	pushl	%edi
	call	*316(%eax)
	addl	$20, %esp
	testl	%esi, %esi
	je	.L365
	pushl	%esi
	call	miRegionDestroy
	popl	%ebx
.L365:
	movl	40(%edi), %eax
.L353:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcCopyArea, .-ProcCopyArea
	.align 4
.globl ProcCopyPlane
	.type	ProcCopyPlane, @function
ProcCopyPlane:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	32(%esp), %ebp
	cmpl	$8, 120(%ebp)
	movl	8(%ebp), %esi
	je	.L369
	movl	$16, %eax
	jmp	.L368
.L369:
	pushl	$2
	pushl	$-1
	pushl	%ebp
	pushl	8(%esi)
	leal	24(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L368
	pushl	$16777216
	pushl	%ebp
	pushl	12(%esi)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L368
	movl	8(%esp), %ecx
	movl	4(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L383
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	jne	.L383
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L374
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L374:
	movl	4(%esi), %eax
	cmpl	%eax, 8(%esi)
	je	.L375
	pushl	$1
	pushl	$0
	pushl	%ebp
	pushl	4(%esi)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L368
	movl	(%esp), %eax
	movl	16(%eax), %edx
	movl	8(%esp), %eax
	cmpl	%edx, 16(%eax)
	je	.L378
	movl	8(%esi), %eax
	movl	%eax, 24(%ebp)
.L383:
	movl	$8, %eax
	jmp	.L368
.L375:
	movl	8(%esp), %eax
	movl	%eax, (%esp)
.L378:
	movl	28(%esi), %ebx
	testl	%ebx, %ebx
	je	.L380
	leal	-1(%ebx), %eax
	testl	%eax, %ebx
	jne	.L380
	movl	(%esp), %edi
	movzbl	2(%edi), %ecx
	decl	%ecx
	movl	$1, %eax
	sall	%cl, %eax
	cmpl	%eax, %ebx
	jbe	.L379
.L380:
	movl	$2, %eax
	movl	%ebx, 24(%ebp)
	jmp	.L368
.L379:
	movl	4(%esp), %edx
	movl	72(%edx), %ecx
	pushl	%ebx
	movswl	22(%esi),%eax
	pushl	%eax
	movswl	20(%esi),%eax
	pushl	%eax
	movzwl	26(%esi), %eax
	pushl	%eax
	movzwl	24(%esi), %eax
	pushl	%eax
	movswl	18(%esi),%eax
	pushl	%eax
	movswl	16(%esi),%eax
	pushl	%eax
	pushl	%edx
	pushl	40(%esp)
	pushl	%edi
	call	*16(%ecx)
	addl	$40, %esp
	movl	%eax, %ebx
	movl	4(%esp), %eax
	testb	$8, 17(%eax)
	je	.L381
	movl	8(%esp), %eax
	movl	16(%eax), %eax
	pushl	$0
	pushl	$63
	pushl	8(%esi)
	pushl	%ebx
	pushl	%ebp
	call	*316(%eax)
	addl	$20, %esp
	testl	%ebx, %ebx
	je	.L381
	pushl	%ebx
	call	miRegionDestroy
	popl	%eax
.L381:
	movl	40(%ebp), %eax
.L368:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcCopyPlane, .-ProcCopyPlane
	.align 4
.globl ProcPolyPoint
	.type	ProcPolyPoint, @function
ProcPolyPoint:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L385
	movl	$16, %eax
	jmp	.L384
.L385:
	movb	1(%esi), %al
	cmpb	$1, %al
	jbe	.L386
	movzbl	%al, %eax
	movl	%eax, 24(%edi)
	movl	$2, %eax
	jmp	.L384
.L386:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L384
	pushl	$16777216
	pushl	%edi
	pushl	8(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L384
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L390
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L389
.L390:
	movl	$8, %eax
	jmp	.L384
.L389:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L391
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L391:
	movl	120(%edi), %eax
	leal	-12(,%eax,4), %eax
	movl	%eax, %ebx
	shrl	$2, %ebx
	je	.L392
	movl	(%esp), %edx
	leal	12(%esi), %eax
	movl	72(%edx), %ecx
	pushl	%eax
	pushl	%ebx
	movzbl	1(%esi), %eax
	pushl	%eax
	pushl	%edx
	pushl	20(%esp)
	call	*20(%ecx)
	addl	$20, %esp
.L392:
	movl	40(%edi), %eax
.L384:
	popl	%ecx
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPolyPoint, .-ProcPolyPoint
	.align 4
.globl ProcPolyLine
	.type	ProcPolyLine, @function
ProcPolyLine:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L394
	movl	$16, %eax
	jmp	.L393
.L394:
	movb	1(%esi), %al
	cmpb	$1, %al
	jbe	.L395
	movzbl	%al, %eax
	movl	%eax, 24(%edi)
	movl	$2, %eax
	jmp	.L393
.L395:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L393
	pushl	$16777216
	pushl	%edi
	pushl	8(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L393
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L399
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L398
.L399:
	movl	$8, %eax
	jmp	.L393
.L398:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L400
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L400:
	movl	120(%edi), %eax
	leal	-12(,%eax,4), %ebx
	shrl	$2, %ebx
	cmpl	$1, %ebx
	jle	.L401
	movl	(%esp), %edx
	leal	12(%esi), %eax
	movl	72(%edx), %ecx
	pushl	%eax
	pushl	%ebx
	movzbl	1(%esi), %eax
	pushl	%eax
	pushl	%edx
	pushl	20(%esp)
	call	*24(%ecx)
	addl	$20, %esp
.L401:
	movl	40(%edi), %eax
.L393:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPolyLine, .-ProcPolyLine
	.align 4
.globl ProcPolySegment
	.type	ProcPolySegment, @function
ProcPolySegment:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L403
	movl	$16, %eax
	jmp	.L402
.L403:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L402
	pushl	$16777216
	pushl	%edi
	pushl	8(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L402
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L407
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L406
.L407:
	movl	$8, %eax
	jmp	.L402
.L406:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L408
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L408:
	movl	120(%edi), %eax
	leal	-12(,%eax,4), %ebx
	testb	$4, %bl
	movl	$16, %eax
	jne	.L402
	sarl	$3, %ebx
	je	.L410
	movl	(%esp), %eax
	leal	12(%esi), %edx
	movl	72(%eax), %ecx
	pushl	%edx
	pushl	%ebx
	pushl	%eax
	pushl	16(%esp)
	call	*28(%ecx)
	addl	$16, %esp
.L410:
	movl	40(%edi), %eax
.L402:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPolySegment, .-ProcPolySegment
	.align 4
.globl ProcPolyRectangle
	.type	ProcPolyRectangle, @function
ProcPolyRectangle:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L412
	movl	$16, %eax
	jmp	.L411
.L412:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L411
	pushl	$16777216
	pushl	%edi
	pushl	8(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L411
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L416
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L415
.L416:
	movl	$8, %eax
	jmp	.L411
.L415:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L417
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L417:
	movl	120(%edi), %eax
	leal	-12(,%eax,4), %ebx
	testb	$4, %bl
	movl	$16, %eax
	jne	.L411
	sarl	$3, %ebx
	je	.L419
	movl	(%esp), %eax
	leal	12(%esi), %edx
	movl	72(%eax), %ecx
	pushl	%edx
	pushl	%ebx
	pushl	%eax
	pushl	16(%esp)
	call	*32(%ecx)
	addl	$16, %esp
.L419:
	movl	40(%edi), %eax
.L411:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPolyRectangle, .-ProcPolyRectangle
	.align 4
.globl ProcPolyArc
	.type	ProcPolyArc, @function
ProcPolyArc:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L421
	movl	$16, %eax
	jmp	.L420
.L421:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L420
	pushl	$16777216
	pushl	%edi
	pushl	8(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L420
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L425
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L424
.L425:
	movl	$8, %eax
	jmp	.L420
.L424:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L426
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L426:
	movl	$12, %edx
	movl	120(%edi), %eax
	movl	%edx, %ecx
	leal	-12(,%eax,4), %eax
	xorl	%edx, %edx
	divl	%ecx
	testl	%edx, %edx
	movl	%eax, %ebx
	movl	$16, %eax
	jne	.L420
	testl	%ebx, %ebx
	je	.L428
	movl	(%esp), %eax
	leal	12(%esi), %edx
	movl	72(%eax), %ecx
	pushl	%edx
	pushl	%ebx
	pushl	%eax
	pushl	16(%esp)
	call	*36(%ecx)
	addl	$16, %esp
.L428:
	movl	40(%edi), %eax
.L420:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPolyArc, .-ProcPolyArc
	.align 4
.globl ProcFillPoly
	.type	ProcFillPoly, @function
ProcFillPoly:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$3, 120(%edi)
	movl	8(%edi), %ebx
	ja	.L430
	movl	$16, %eax
	jmp	.L429
.L430:
	movb	12(%ebx), %al
	cmpb	$2, %al
	ja	.L439
	movb	13(%ebx), %al
	cmpb	$1, %al
	jbe	.L432
.L439:
	movzbl	%al, %eax
	movl	%eax, 24(%edi)
	movl	$2, %eax
	jmp	.L429
.L432:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L429
	pushl	$16777216
	pushl	%edi
	pushl	8(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L429
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L436
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L435
.L436:
	movl	$8, %eax
	jmp	.L429
.L435:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L437
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L437:
	movl	120(%edi), %eax
	leal	-16(,%eax,4), %eax
	movl	%eax, %esi
	shrl	$2, %esi
	je	.L438
	movl	(%esp), %edx
	leal	16(%ebx), %eax
	movl	72(%edx), %ecx
	pushl	%eax
	pushl	%esi
	movzbl	13(%ebx), %eax
	pushl	%eax
	movzbl	12(%ebx), %eax
	pushl	%eax
	pushl	%edx
	pushl	24(%esp)
	call	*40(%ecx)
	addl	$24, %esp
.L438:
	movl	40(%edi), %eax
.L429:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcFillPoly, .-ProcFillPoly
	.align 4
.globl ProcPolyFillRectangle
	.type	ProcPolyFillRectangle, @function
ProcPolyFillRectangle:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L441
	movl	$16, %eax
	jmp	.L440
.L441:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L440
	pushl	$16777216
	pushl	%edi
	pushl	8(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L440
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L445
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L444
.L445:
	movl	$8, %eax
	jmp	.L440
.L444:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L446
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L446:
	movl	120(%edi), %eax
	leal	-12(,%eax,4), %ebx
	testb	$4, %bl
	movl	$16, %eax
	jne	.L440
	sarl	$3, %ebx
	je	.L448
	movl	(%esp), %eax
	leal	12(%esi), %edx
	movl	72(%eax), %ecx
	pushl	%edx
	pushl	%ebx
	pushl	%eax
	pushl	16(%esp)
	call	*44(%ecx)
	addl	$16, %esp
.L448:
	movl	40(%edi), %eax
.L440:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPolyFillRectangle, .-ProcPolyFillRectangle
	.align 4
.globl ProcPolyFillArc
	.type	ProcPolyFillArc, @function
ProcPolyFillArc:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %esi
	ja	.L450
	movl	$16, %eax
	jmp	.L449
.L450:
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L449
	pushl	$16777216
	pushl	%edi
	pushl	8(%esi)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L449
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L454
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L453
.L454:
	movl	$8, %eax
	jmp	.L449
.L453:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L455
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L455:
	movl	$12, %edx
	movl	120(%edi), %eax
	movl	%edx, %ecx
	leal	-12(,%eax,4), %eax
	xorl	%edx, %edx
	divl	%ecx
	testl	%edx, %edx
	movl	%eax, %ebx
	movl	$16, %eax
	jne	.L449
	testl	%ebx, %ebx
	je	.L457
	movl	(%esp), %eax
	leal	12(%esi), %edx
	movl	72(%eax), %ecx
	pushl	%edx
	pushl	%ebx
	pushl	%eax
	pushl	16(%esp)
	call	*48(%ecx)
	addl	$16, %esp
.L457:
	movl	40(%edi), %eax
.L449:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPolyFillArc, .-ProcPolyFillArc
	.align 4
.globl ProcPutImage
	.type	ProcPutImage, @function
ProcPutImage:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	24(%esp), %edi
	cmpl	$5, 120(%edi)
	movl	8(%edi), %ebx
	jbe	.L481
	pushl	$2
	pushl	$-1
	pushl	%edi
	pushl	4(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L458
	pushl	$16777216
	pushl	%edi
	pushl	8(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L458
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L475
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	jne	.L475
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L464
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L464:
	movb	1(%ebx), %al
	testb	%al, %al
	jne	.L465
	cmpb	$1, 21(%ebx)
	jne	.L475
	movzbl	20(%ebx), %edx
	cmpl	screenInfo+8, %edx
	jae	.L475
	movzwl	12(%ebx), %eax
	leal	31(%edx,%eax), %eax
	sarl	$5, %eax
	leal	0(,%eax,4), %edx
	jmp	.L468
.L465:
	cmpb	$1, %al
	jne	.L469
	movl	4(%esp), %eax
	movb	2(%eax), %cl
	cmpb	21(%ebx), %cl
	jne	.L475
	movzbl	20(%ebx), %edx
	cmpl	screenInfo+8, %edx
	jae	.L475
	movzwl	12(%ebx), %eax
	leal	31(%edx,%eax), %eax
	sarl	$5, %eax
	leal	0(,%eax,4), %edx
	movzbl	%cl, %eax
	imull	%eax, %edx
	jmp	.L468
.L469:
	cmpb	$2, %al
	jne	.L473
	movl	4(%esp), %eax
	movb	2(%eax), %al
	cmpb	21(%ebx), %al
	jne	.L475
	cmpb	$0, 20(%ebx)
	je	.L474
.L475:
	movl	$8, %eax
	jmp	.L458
.L474:
	movzbl	%al, %eax
	imull	$24, %eax, %eax
	cmpl	$0, PixmapWidthPaddingInfo+12(%eax)
	movl	PixmapWidthPaddingInfo+8(%eax), %esi
	movw	12(%ebx), %dx
	je	.L476
	movzwl	%dx, %edx
	imull	PixmapWidthPaddingInfo+16(%eax), %edx
	addl	PixmapWidthPaddingInfo+16(%eax), %edx
	movl	%esi, %ecx
	sarl	%cl, %edx
	jmp	.L480
.L476:
	movzwl	%dx, %edx
	movl	PixmapWidthPaddingInfo+4(%eax), %ecx
	addl	PixmapWidthPaddingInfo(%eax), %edx
	sarl	%cl, %edx
	movl	%esi, %ecx
.L480:
	sall	%cl, %edx
	jmp	.L468
.L473:
	movzbl	%al, %eax
	movl	%eax, 24(%edi)
	movl	$2, %eax
	jmp	.L458
.L468:
	movzwl	14(%ebx), %eax
	imull	%eax, %edx
	leal	3(%edx), %eax
	shrl	$2, %eax
	addl	$6, %eax
	cmpl	120(%edi), %eax
	leal	24(%ebx), %esi
	je	.L479
.L481:
	movl	$16, %eax
	jmp	.L458
.L479:
	movl	(%esp), %edx
	movl	72(%edx), %ecx
	pushl	%esi
	movzbl	1(%ebx), %eax
	pushl	%eax
	movzbl	20(%ebx), %eax
	pushl	%eax
	movzwl	14(%ebx), %eax
	pushl	%eax
	movzwl	12(%ebx), %eax
	pushl	%eax
	movswl	18(%ebx),%eax
	pushl	%eax
	movswl	16(%ebx),%eax
	pushl	%eax
	movzbl	21(%ebx), %eax
	pushl	%eax
	pushl	%edx
	pushl	40(%esp)
	call	*8(%ecx)
	movl	40(%edi), %eax
	addl	$40, %esp
.L458:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcPutImage, .-ProcPutImage
	.align 4
	.type	DoGetImage, @function
DoGetImage:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$52, %esp
	movl	76(%esp), %eax
	decl	%eax
	cmpl	$1, %eax
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	jbe	.L483
	movl	72(%esp), %eax
	movl	76(%esp), %edx
	movl	%edx, 24(%eax)
	movl	$2, %eax
	jmp	.L482
.L483:
	pushl	$1
	pushl	$0
	pushl	80(%esp)
	pushl	92(%esp)
	leal	32(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L482
	movl	16(%esp), %ecx
	cmpb	$0, (%ecx)
	jne	.L485
	testb	$16, 130(%ecx)
	je	.L492
	movswl	8(%ecx),%eax
	addl	84(%esp), %eax
	js	.L492
	movl	92(%esp), %ebx
	leal	(%ebx,%eax), %edx
	movl	16(%ecx), %ebx
	movswl	8(%ebx),%eax
	cmpl	%eax, %edx
	jg	.L492
	movswl	10(%ecx),%eax
	addl	88(%esp), %eax
	js	.L492
	movl	96(%esp), %esi
	leal	(%esi,%eax), %edx
	movswl	10(%ebx),%eax
	cmpl	%eax, %edx
	jg	.L492
	movzwl	104(%ecx), %ebx
	movl	%ebx, %esi
	negl	%esi
	cmpl	%esi, 84(%esp)
	jl	.L492
	movl	84(%esp), %edx
	movzwl	12(%ecx), %eax
	addl	92(%esp), %edx
	leal	(%eax,%ebx), %eax
	cmpl	%eax, %edx
	jg	.L492
	cmpl	%esi, 88(%esp)
	jl	.L492
	movl	88(%esp), %edx
	movzwl	14(%ecx), %eax
	addl	96(%esp), %edx
	leal	(%eax,%ebx), %eax
	cmpl	%eax, %edx
	jg	.L492
	movl	124(%ecx), %eax
	testl	%eax, %eax
	jne	.L556
	pushl	%ecx
	call	FindWindowWithOptional
	movl	124(%eax), %eax
	popl	%ecx
.L556:
	movl	(%eax), %eax
	movl	%eax, 28(%esp)
	jmp	.L490
.L485:
	cmpl	$0, 84(%esp)
	js	.L492
	movl	84(%esp), %edx
	addl	92(%esp), %edx
	movzwl	12(%ecx), %eax
	cmpl	%eax, %edx
	jg	.L492
	cmpl	$0, 88(%esp)
	js	.L492
	movl	88(%esp), %edx
	addl	96(%esp), %edx
	movzwl	14(%ecx), %eax
	cmpl	%eax, %edx
	jle	.L491
.L492:
	movl	$8, %eax
	jmp	.L482
.L491:
	movl	$0, 28(%esp)
.L490:
	movb	$1, 20(%esp)
	movl	72(%esp), %edx
	movw	28(%edx), %ax
	movw	%ax, 22(%esp)
	movl	16(%esp), %edx
	movb	2(%edx), %al
	movb	%al, 21(%esp)
	cmpl	$2, 76(%esp)
	movb	2(%edx), %dl
	jne	.L493
	movzbl	%dl, %eax
	imull	$24, %eax, %eax
	cmpl	$0, PixmapWidthPaddingInfo+12(%eax)
	movl	PixmapWidthPaddingInfo+8(%eax), %edx
	je	.L494
	movl	92(%esp), %ecx
	imull	PixmapWidthPaddingInfo+16(%eax), %ecx
	movl	PixmapWidthPaddingInfo+16(%eax), %ebx
	addl	%ebx, %ecx
	movl	%ecx, 8(%esp)
	movb	%dl, %cl
	sarl	%cl, 8(%esp)
	sall	%cl, 8(%esp)
	jmp	.L495
.L494:
	movl	92(%esp), %ebx
	movl	PixmapWidthPaddingInfo+4(%eax), %ecx
	addl	PixmapWidthPaddingInfo(%eax), %ebx
	sarl	%cl, %ebx
	movb	%dl, %cl
	sall	%cl, %ebx
	movl	%ebx, 8(%esp)
.L495:
	movl	8(%esp), %eax
	imull	96(%esp), %eax
	jmp	.L496
.L493:
	movl	92(%esp), %eax
	movzbl	%dl, %ecx
	addl	$31, %eax
	movl	$1, 4(%esp)
	decl	%ecx
	sarl	$5, %eax
	sall	%cl, 4(%esp)
	sall	$2, %eax
	movl	%eax, 8(%esp)
	movl	%eax, %ebx
	movl	4(%esp), %eax
	decl	%eax
	orl	4(%esp), %eax
	andl	100(%esp), %eax
	imull	96(%esp), %ebx
	pushl	%eax
	call	Ones
	imull	%ebx, %eax
	popl	%edx
.L496:
	cmpl	$0, 104(%esp)
	movl	%eax, 24(%esp)
	je	.L497
	addl	$32, %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, %ebp
	testl	%ebp, %ebp
	popl	%eax
	movl	$11, %eax
	je	.L482
	cmpl	$0, 8(%esp)
	movl	$0, 12(%esp)
	je	.L500
	movl	96(%esp), %ebx
	movl	%ebx, 12(%esp)
.L500:
	movl	104(%esp), %esi
	movl	%ebp, (%esi)
	movl	%ebp, %edi
	leal	20(%esp), %esi
	cld
	movl	$8, %ecx
	rep
	movsl
	addl	$32, %ebp
	jmp	.L501
.L497:
	addl	$3, %eax
	shrl	$2, %eax
	cmpl	$0, 8(%esp)
	movl	%eax, 24(%esp)
	je	.L503
	cmpl	$0, 96(%esp)
	jne	.L502
.L503:
	movl	$0, 12(%esp)
	jmp	.L504
.L502:
	cmpl	$65535, 8(%esp)
	movl	$1, 12(%esp)
	jg	.L504
	movl	$65536, %edx
	movl	%edx, %eax
	cltd
	idivl	8(%esp)
	movl	96(%esp), %edx
	cmpl	%edx, %eax
	movl	%eax, 12(%esp)
	jle	.L504
	movl	%edx, 12(%esp)
.L504:
	movl	12(%esp), %eax
	movl	96(%esp), %ecx
	imull	8(%esp), %eax
	cmpl	%ecx, 12(%esp)
	jge	.L508
	cmpl	$1, 12(%esp)
	jle	.L510
	testb	$3, %al
	je	.L510
.L513:
	decl	12(%esp)
	subl	8(%esp), %eax
	cmpl	$1, 12(%esp)
	jle	.L510
	testb	$3, %al
	jne	.L513
.L510:
	testb	$3, %al
	je	.L508
.L517:
	addl	8(%esp), %eax
	incl	12(%esp)
	testb	$3, %al
	jne	.L517
.L508:
	pushl	%eax
	call	Xalloc
	movl	%eax, %ebp
	testl	%ebp, %ebp
	popl	%eax
	movl	$11, %eax
	je	.L482
	movl	72(%esp), %ebx
	cmpl	$0, 16(%ebx)
	leal	20(%esp), %edx
	je	.L519
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L557
.L519:
	pushl	%edx
	pushl	$32
	pushl	80(%esp)
	call	WriteToClient
.L557:
	addl	$12, %esp
.L501:
	movl	16(%esp), %eax
	cmpb	$0, (%eax)
	jne	.L521
	pushl	%eax
	call	NotClippedByChildren
	testl	%eax, %eax
	movl	%eax, 4(%esp)
	popl	%edi
	je	.L521
	movl	16(%esp), %eax
	movswl	10(%eax),%edx
	negl	%edx
	pushl	%edx
	movswl	8(%eax),%eax
	negl	%eax
	pushl	%eax
	pushl	8(%esp)
	call	miTranslateRegion
	addl	$12, %esp
.L521:
	cmpl	$0, 12(%esp)
	je	.L524
	cmpl	$2, 76(%esp)
	jne	.L525
	xorl	%esi, %esi
	cmpl	$0, 96(%esp)
	jle	.L524
.L532:
	movl	96(%esp), %ebx
	subl	%esi, %ebx
	cmpl	12(%esp), %ebx
	jle	.L529
	movl	12(%esp), %ebx
.L529:
	movl	16(%esp), %eax
	movl	16(%eax), %ecx
	pushl	%ebp
	pushl	104(%esp)
	pushl	84(%esp)
	pushl	%ebx
	pushl	108(%esp)
	movl	108(%esp), %edx
	addl	%esi, %edx
	pushl	%edx
	pushl	108(%esp)
	pushl	%eax
	call	*116(%ecx)
	addl	$32, %esp
	cmpl	$0, 104(%esp)
	jne	.L531
	pushl	%ebp
	movl	%ebx, %eax
	imull	12(%esp), %eax
	pushl	%eax
	pushl	80(%esp)
	call	WriteToClient
	addl	$12, %esp
.L531:
	addl	%ebx, %esi
	movl	96(%esp), %eax
	subl	%esi, %eax
	testl	%eax, %eax
	jg	.L532
	jmp	.L524
.L525:
	cmpl	$0, 4(%esp)
	je	.L524
.L547:
	movl	4(%esp), %esi
	testl	%esi, 100(%esp)
	je	.L536
	xorl	%esi, %esi
	cmpl	$0, 96(%esp)
	jle	.L536
.L546:
	movl	96(%esp), %ebx
	subl	%esi, %ebx
	cmpl	12(%esp), %ebx
	jle	.L542
	movl	12(%esp), %ebx
.L542:
	movl	16(%esp), %eax
	movl	16(%eax), %ecx
	pushl	%ebp
	pushl	8(%esp)
	pushl	84(%esp)
	pushl	%ebx
	pushl	108(%esp)
	movl	108(%esp), %edx
	addl	%esi, %edx
	pushl	%edx
	pushl	108(%esp)
	pushl	%eax
	call	*116(%ecx)
	addl	$32, %esp
	cmpl	$0, 104(%esp)
	je	.L544
	movl	8(%esp), %eax
	imull	%ebx, %eax
	addl	%eax, %ebp
	jmp	.L545
.L544:
	pushl	%ebp
	movl	%ebx, %eax
	imull	12(%esp), %eax
	pushl	%eax
	pushl	80(%esp)
	call	WriteToClient
	addl	$12, %esp
.L545:
	addl	%ebx, %esi
	movl	96(%esp), %eax
	subl	%esi, %eax
	testl	%eax, %eax
	jg	.L546
.L536:
	shrl	4(%esp)
	jne	.L547
.L524:
	cmpl	$0, (%esp)
	je	.L548
	pushl	(%esp)
	call	miRegionDestroy
	popl	%esi
.L548:
	cmpl	$0, 104(%esp)
	jne	.L549
	pushl	%ebp
	call	Xfree
	popl	%ebx
.L549:
	movl	72(%esp), %edx
	movl	40(%edx), %eax
.L482:
	addl	$52, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	DoGetImage, .-DoGetImage
	.align 4
.globl ProcGetImage
	.type	ProcGetImage, @function
ProcGetImage:
	movl	4(%esp), %ecx
	cmpl	$5, 120(%ecx)
	movl	8(%ecx), %edx
	je	.L559
	movl	$16, %eax
	ret
.L559:
	pushl	$0
	pushl	16(%edx)
	movzwl	14(%edx), %eax
	pushl	%eax
	movzwl	12(%edx), %eax
	pushl	%eax
	movswl	10(%edx),%eax
	pushl	%eax
	movswl	8(%edx),%eax
	pushl	%eax
	pushl	4(%edx)
	movzbl	1(%edx), %eax
	pushl	%eax
	pushl	%ecx
	call	DoGetImage
	addl	$36, %esp
	ret
	.size	ProcGetImage, .-ProcGetImage
	.align 4
.globl ProcPolyText
	.type	ProcPolyText, @function
ProcPolyText:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	20(%esp), %esi
	cmpl	$3, 120(%esi)
	movl	8(%esi), %ebx
	ja	.L561
	movl	$16, %eax
	jmp	.L560
.L561:
	pushl	$2
	pushl	$-1
	pushl	%esi
	pushl	4(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L560
	pushl	$16777216
	pushl	%esi
	pushl	8(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L560
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L565
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L564
.L565:
	movl	$8, %eax
	jmp	.L560
.L564:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L566
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L566:
	pushl	4(%ebx)
	movzbl	(%ebx), %eax
	pushl	%eax
	movswl	14(%ebx),%eax
	pushl	%eax
	movswl	12(%ebx),%eax
	pushl	%eax
	movl	120(%esi), %eax
	leal	(%ebx,%eax,4), %eax
	pushl	%eax
	leal	16(%ebx), %eax
	pushl	%eax
	pushl	24(%esp)
	pushl	32(%esp)
	pushl	%esi
	call	PolyText
	addl	$36, %esp
	testl	%eax, %eax
	jne	.L560
	movl	40(%esi), %eax
.L560:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcPolyText, .-ProcPolyText
	.align 4
.globl ProcImageText8
	.type	ProcImageText8, @function
ProcImageText8:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	20(%esp), %esi
	movl	120(%esi), %edx
	cmpl	$3, %edx
	movl	8(%esi), %ebx
	jbe	.L571
	movzbl	1(%ebx), %eax
	addl	$19, %eax
	shrl	$2, %eax
	cmpl	%edx, %eax
	je	.L570
.L571:
	movl	$16, %eax
	jmp	.L569
.L570:
	pushl	$2
	pushl	$-1
	pushl	%esi
	pushl	4(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L569
	pushl	$16777216
	pushl	%esi
	pushl	8(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L569
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L575
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L574
.L575:
	movl	$8, %eax
	jmp	.L569
.L574:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L576
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L576:
	pushl	4(%ebx)
	movzbl	(%ebx), %eax
	pushl	%eax
	movswl	14(%ebx),%eax
	pushl	%eax
	movswl	12(%ebx),%eax
	pushl	%eax
	leal	16(%ebx), %eax
	pushl	%eax
	movzbl	1(%ebx), %eax
	pushl	%eax
	pushl	24(%esp)
	pushl	32(%esp)
	pushl	%esi
	call	ImageText
	addl	$36, %esp
	testl	%eax, %eax
	jne	.L569
	movl	40(%esi), %eax
.L569:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcImageText8, .-ProcImageText8
	.align 4
.globl ProcImageText16
	.type	ProcImageText16, @function
ProcImageText16:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	20(%esp), %esi
	movl	120(%esi), %edx
	cmpl	$3, %edx
	movl	8(%esi), %ebx
	jbe	.L581
	movzbl	1(%ebx), %eax
	leal	19(%eax,%eax), %eax
	shrl	$2, %eax
	cmpl	%edx, %eax
	je	.L580
.L581:
	movl	$16, %eax
	jmp	.L579
.L580:
	pushl	$2
	pushl	$-1
	pushl	%esi
	pushl	4(%ebx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L579
	pushl	$16777216
	pushl	%esi
	pushl	8(%ebx)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupGC
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L579
	movl	4(%esp), %ecx
	movl	(%esp), %edx
	movb	2(%ecx), %al
	cmpb	%al, 4(%edx)
	jne	.L585
	movl	16(%ecx), %eax
	cmpl	%eax, (%edx)
	je	.L584
.L585:
	movl	$8, %eax
	jmp	.L579
.L584:
	movl	20(%ecx), %eax
	cmpl	%eax, 64(%edx)
	je	.L586
	pushl	%edx
	pushl	%ecx
	call	ValidateGC
	popl	%eax
	popl	%edx
.L586:
	pushl	4(%ebx)
	movzbl	(%ebx), %eax
	pushl	%eax
	movswl	14(%ebx),%eax
	pushl	%eax
	movswl	12(%ebx),%eax
	pushl	%eax
	leal	16(%ebx), %eax
	pushl	%eax
	movzbl	1(%ebx), %eax
	pushl	%eax
	pushl	24(%esp)
	pushl	32(%esp)
	pushl	%esi
	call	ImageText
	addl	$36, %esp
	testl	%eax, %eax
	jne	.L579
	movl	40(%esi), %eax
.L579:
	popl	%ebx
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcImageText16, .-ProcImageText16
	.align 4
.globl ProcCreateColormap
	.type	ProcCreateColormap, @function
ProcCreateColormap:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	32(%esp), %edi
	cmpl	$4, 120(%edi)
	movl	8(%edi), %esi
	je	.L590
	movl	$16, %eax
	jmp	.L589
.L590:
	movb	1(%esi), %al
	cmpb	$1, %al
	jbe	.L591
	movzbl	%al, %eax
	movl	%eax, 24(%edi)
	movl	$2, %eax
	jmp	.L589
.L591:
	movl	4(%esi), %eax
	movl	%eax, (%esp)
	pushl	%edi
	pushl	%eax
	call	LegalNewID
	testl	%eax, %eax
	popl	%ebx
	popl	%ebp
	jne	.L592
	movl	(%esp), %eax
	movl	%eax, 24(%edi)
	movl	$14, %eax
	jmp	.L589
.L592:
	pushl	$16
	pushl	%edi
	pushl	8(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L589
	jmp	.L593
.L604:
	movl	%edx, %eax
	jmp	.L589
.L593:
	movl	8(%esp), %eax
	movl	16(%eax), %ecx
	movw	96(%ecx), %bp
	xorl	%ebx, %ebx
	testw	%bp, %bp
	movl	100(%ecx), %edx
	jle	.L603
.L601:
	movl	12(%esi), %eax
	cmpl	%eax, (%edx)
	jne	.L596
	pushl	(%edi)
	movzbl	1(%esi), %eax
	pushl	%eax
	leal	12(%esp), %eax
	pushl	%eax
	pushl	%edx
	pushl	%ecx
	pushl	20(%esp)
	call	CreateColormap
	movl	40(%edi), %edx
	addl	$24, %esp
	testl	%edx, %edx
	je	.L589
	jmp	.L604
.L596:
	incl	%ebx
	movswl	%bp,%eax
	addl	$36, %edx
	cmpl	%eax, %ebx
	jl	.L601
.L603:
	movl	12(%esi), %eax
	movl	%eax, 24(%edi)
	movl	$8, %eax
.L589:
	addl	$12, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcCreateColormap, .-ProcCreateColormap
	.align 4
.globl ProcFreeColormap
	.type	ProcFreeColormap, @function
ProcFreeColormap:
	pushl	%esi
	pushl	%ebx
	pushl	%esi
	movl	16(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	je	.L606
	movl	$16, %eax
	jmp	.L605
.L606:
	pushl	$4
	pushl	%esi
	pushl	$6
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L607
	movl	(%esp), %eax
	testb	$1, 16(%eax)
	jne	.L608
	pushl	$0
	pushl	4(%ebx)
	call	FreeResource
	popl	%ecx
	popl	%ebx
.L608:
	movl	40(%esi), %eax
	jmp	.L605
.L607:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L605
	movl	$12, %eax
.L605:
	popl	%edx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcFreeColormap, .-ProcFreeColormap
	.align 4
.globl ProcCopyColormapAndFree
	.type	ProcCopyColormapAndFree, @function
ProcCopyColormapAndFree:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	movl	20(%esp), %ebx
	cmpl	$3, 120(%ebx)
	movl	8(%ebx), %edi
	je	.L613
	movl	$16, %eax
	jmp	.L612
.L613:
	movl	4(%edi), %esi
	pushl	%ebx
	pushl	%esi
	call	LegalNewID
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L614
	movl	$14, %eax
	movl	%esi, 24(%ebx)
	jmp	.L612
.L614:
	pushl	$8193
	pushl	%ebx
	pushl	$6
	pushl	8(%edi)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L615
	pushl	(%ebx)
	pushl	4(%esp)
	pushl	%esi
	call	CopyColormapAndFree
	movl	%eax, %edx
	movl	40(%ebx), %eax
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L612
	movl	%edx, %eax
	jmp	.L612
.L615:
	movl	8(%edi), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%ebx)
	movl	%edx, %eax
	jne	.L612
	movl	$12, %eax
.L612:
	popl	%edi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcCopyColormapAndFree, .-ProcCopyColormapAndFree
	.align 4
.globl ProcInstallColormap
	.type	ProcInstallColormap, @function
ProcInstallColormap:
	pushl	%esi
	pushl	%ebx
	pushl	%eax
	movl	16(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %esi
	je	.L622
	movl	$16, %eax
	jmp	.L621
.L622:
	pushl	$1048576
	pushl	%ebx
	pushl	$6
	pushl	4(%esi)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L624
	movl	(%esp), %eax
	movl	12(%eax), %edx
	pushl	%eax
	call	*292(%edx)
	movl	40(%ebx), %edx
	popl	%eax
.L624:
	movl	4(%esi), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%ebx)
	movl	%edx, %eax
	jne	.L621
	movl	$12, %eax
.L621:
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcInstallColormap, .-ProcInstallColormap
	.align 4
.globl ProcUninstallColormap
	.type	ProcUninstallColormap, @function
ProcUninstallColormap:
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	movl	16(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %esi
	je	.L629
	movl	$16, %eax
	jmp	.L628
.L629:
	pushl	$2097152
	pushl	%ebx
	pushl	$6
	pushl	4(%esi)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L631
	movl	(%esp), %edx
	movl	12(%edx), %ecx
	movl	28(%ecx), %eax
	cmpl	%eax, 8(%edx)
	je	.L633
	pushl	%edx
	call	*296(%ecx)
	popl	%ecx
.L633:
	movl	40(%ebx), %edx
.L631:
	movl	4(%esi), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%ebx)
	movl	%edx, %eax
	jne	.L628
	movl	$12, %eax
.L628:
	popl	%edx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcUninstallColormap, .-ProcUninstallColormap
	.align 4
.globl ProcListInstalledColormaps
	.type	ProcListInstalledColormaps, @function
ProcListInstalledColormaps:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	movl	20(%esp), %edi
	cmpl	$2, 120(%edi)
	movl	8(%edi), %eax
	je	.L637
	movl	$16, %eax
	jmp	.L636
.L637:
	pushl	$16
	pushl	%edi
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupWindow
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L636
	movl	(%esp), %eax
	movl	16(%eax), %eax
	movswl	34(%eax),%eax
	leal	32(,%eax,4), %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, %ebx
	testl	%ebx, %ebx
	popl	%ecx
	movl	$11, %eax
	je	.L636
	movb	$1, (%ebx)
	movw	28(%edi), %ax
	movl	(%esp), %edx
	movw	%ax, 2(%ebx)
	leal	32(%ebx), %eax
	movl	16(%edx), %ecx
	pushl	%eax
	pushl	16(%edx)
	call	*300(%ecx)
	movw	%ax, 8(%ebx)
	movl	%eax, 4(%ebx)
	movl	%eax, %esi
	cmpl	$0, 16(%edi)
	popl	%eax
	popl	%edx
	je	.L642
	movl	8(%edi), %eax
	movzbl	(%eax), %eax
	pushl	%ebx
	pushl	$32
	pushl	%edi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L646
.L642:
	pushl	%ebx
	pushl	$32
	pushl	%edi
	call	WriteToClient
.L646:
	addl	$12, %esp
	cmpl	$0, 16(%edi)
	movl	$Swap32Write, 20(%edi)
	leal	32(%ebx), %eax
	je	.L644
	pushl	%eax
	leal	0(,%esi,4), %eax
	pushl	%eax
	pushl	%edi
	call	Swap32Write
	jmp	.L647
.L644:
	pushl	%eax
	leal	0(,%esi,4), %eax
	pushl	%eax
	pushl	%edi
	call	WriteToClient
.L647:
	addl	$12, %esp
	pushl	%ebx
	call	Xfree
	movl	40(%edi), %eax
	popl	%edi
.L639:
.L636:
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcListInstalledColormaps, .-ProcListInstalledColormaps
	.align 4
.globl ProcAllocColor
	.type	ProcAllocColor, @function
ProcAllocColor:
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	48(%esp), %esi
	cmpl	$4, 120(%esi)
	movl	8(%esi), %ebx
	je	.L649
	movl	$16, %eax
	jmp	.L648
.L649:
	pushl	$4096
	pushl	%esi
	pushl	$6
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L650
	movb	$1, 4(%esp)
	movw	28(%esi), %ax
	movw	%ax, 6(%esp)
	movw	8(%ebx), %ax
	movw	%ax, 12(%esp)
	movw	10(%ebx), %ax
	movw	%ax, 14(%esp)
	movw	12(%ebx), %ax
	movw	%ax, 16(%esp)
	movl	$0, 8(%esp)
	movl	$0, 20(%esp)
	pushl	(%esi)
	leal	24(%esp), %eax
	leal	8(%esp), %ebx
	pushl	%eax
	leal	24(%esp), %eax
	pushl	%eax
	leal	26(%esp), %eax
	pushl	%eax
	leal	28(%esp), %eax
	pushl	%eax
	pushl	20(%esp)
	call	AllocColor
	addl	$24, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	je	.L651
	movl	40(%esi), %eax
	testl	%eax, %eax
	jne	.L648
	movl	%edx, %eax
	jmp	.L648
.L651:
	cmpl	$0, 16(%esi)
	je	.L654
	movl	8(%esi), %eax
	movzbl	(%eax), %eax
	pushl	%ebx
	pushl	$32
	pushl	%esi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L659
.L654:
	pushl	%ebx
	pushl	$32
	pushl	%esi
	call	WriteToClient
.L659:
	addl	$12, %esp
	movl	40(%esi), %eax
	jmp	.L648
.L650:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L648
	movl	$12, %eax
.L648:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	ProcAllocColor, .-ProcAllocColor
	.align 4
.globl ProcAllocNamedColor
	.type	ProcAllocNamedColor, @function
ProcAllocNamedColor:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	52(%esp), %esi
	movl	120(%esi), %edx
	cmpl	$2, %edx
	movl	8(%esi), %ebx
	jbe	.L662
	movzwl	8(%ebx), %eax
	addl	$15, %eax
	shrl	$2, %eax
	cmpl	%edx, %eax
	je	.L661
.L662:
	movl	$16, %ecx
	jmp	.L660
.L661:
	pushl	$4096
	pushl	%esi
	pushl	$6
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L663
	movb	$1, 4(%esp)
	movw	28(%esi), %ax
	movw	%ax, 6(%esp)
	leal	20(%esp), %eax
	movl	$0, 8(%esp)
	leal	4(%esp), %edi
	pushl	%eax
	leal	22(%esp), %eax
	pushl	%eax
	leal	24(%esp), %eax
	pushl	%eax
	movzwl	8(%ebx), %eax
	pushl	%eax
	leal	12(%ebx), %eax
	pushl	%eax
	movl	20(%esp), %eax
	movl	12(%eax), %eax
	pushl	(%eax)
	call	OsLookupColor
	addl	$24, %esp
	testl	%eax, %eax
	movl	$15, %ecx
	je	.L660
	movl	16(%esp), %eax
	movw	%ax, 22(%esp)
	movw	18(%esp), %ax
	movw	%ax, 24(%esp)
	movl	20(%esp), %eax
	movw	%ax, 26(%esp)
	movl	$0, 12(%esp)
	pushl	(%esi)
	leal	16(%esp), %eax
	pushl	%eax
	leal	34(%esp), %eax
	pushl	%eax
	leal	36(%esp), %eax
	pushl	%eax
	leal	38(%esp), %eax
	pushl	%eax
	pushl	20(%esp)
	call	AllocColor
	addl	$24, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	je	.L665
	movl	40(%esi), %eax
	testl	%eax, %eax
	movl	%eax, %ecx
	jne	.L660
	movl	%edx, %ecx
	jmp	.L660
.L665:
	cmpl	$0, 16(%esi)
	je	.L668
	movl	8(%esi), %eax
	movzbl	(%eax), %eax
	pushl	%edi
	pushl	$32
	pushl	%esi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L674
.L668:
	pushl	%edi
	pushl	$32
	pushl	%esi
	call	WriteToClient
.L674:
	addl	$12, %esp
	movl	40(%esi), %ecx
	jmp	.L660
.L663:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L673
	movl	$12, %eax
.L673:
	movl	%eax, %ecx
.L660:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	movl	%ecx, %eax
	popl	%edi
	ret
	.size	ProcAllocNamedColor, .-ProcAllocNamedColor
	.align 4
.globl ProcAllocColorCells
	.type	ProcAllocColorCells, @function
ProcAllocColorCells:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$48, %esp
	movl	68(%esp), %edi
	cmpl	$3, 120(%edi)
	movl	8(%edi), %ebp
	je	.L676
	movl	$16, %eax
	jmp	.L675
.L676:
	pushl	$4096
	pushl	%edi
	pushl	$6
	pushl	4(%ebp)
	leal	28(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	jne	.L677
	movzwl	8(%ebp), %eax
	testl	%eax, %eax
	movl	%eax, 8(%esp)
	jne	.L678
	movl	$0, 24(%edi)
	jmp	.L693
.L678:
	movb	1(%ebp), %al
	cmpb	$1, %al
	jbe	.L679
	movzbl	%al, %eax
	movl	%eax, 24(%edi)
.L693:
	movl	$2, %eax
	jmp	.L675
.L679:
	movzwl	10(%ebp), %edx
	movl	8(%esp), %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	pushl	%eax
	call	Xalloc
	movl	%eax, %esi
	testl	%esi, %esi
	popl	%eax
	movl	$11, %eax
	je	.L675
	movl	8(%esp), %edx
	leal	(%esi,%edx,4), %eax
	pushl	%eax
	pushl	%esi
	movzbl	1(%ebp), %eax
	pushl	%eax
	pushl	16(%esp)
	pushl	%edx
	pushl	32(%esp)
	pushl	(%edi)
	call	AllocColorCells
	addl	$28, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	je	.L681
	pushl	%esi
	call	Xfree
	movl	40(%edi), %eax
	testl	%eax, %eax
	popl	%ebp
	jne	.L675
	movl	%ebx, %eax
	jmp	.L675
.L681:
	movl	(%esp), %eax
	sarl	$2, %eax
	movb	$1, 16(%esp)
	movl	%eax, 20(%esp)
	movw	28(%edi), %ax
	movl	4(%esp), %edx
	movw	%ax, 18(%esp)
	cmpl	$0, 16(%edi)
	movl	8(%esp), %eax
	movw	%dx, 26(%esp)
	movw	%ax, 24(%esp)
	leal	16(%esp), %edx
	je	.L684
	movl	8(%edi), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%edi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L691
.L684:
	pushl	%edx
	pushl	$32
	pushl	%edi
	call	WriteToClient
.L691:
	addl	$12, %esp
	cmpl	$0, 16(%edi)
	movl	$Swap32Write, 20(%edi)
	je	.L686
	pushl	%esi
	pushl	4(%esp)
	pushl	%edi
	call	Swap32Write
	jmp	.L692
.L686:
	pushl	%esi
	pushl	4(%esp)
	pushl	%edi
	call	WriteToClient
.L692:
	addl	$12, %esp
	pushl	%esi
	call	Xfree
	movl	40(%edi), %eax
	popl	%esi
	jmp	.L675
.L677:
	movl	4(%ebp), %eax
	cmpl	$2, %ebx
	movl	%eax, 24(%edi)
	movl	%ebx, %eax
	jne	.L675
	movl	$12, %eax
.L675:
	addl	$48, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcAllocColorCells, .-ProcAllocColorCells
	.align 4
.globl ProcAllocColorPlanes
	.type	ProcAllocColorPlanes, @function
ProcAllocColorPlanes:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	60(%esp), %edi
	cmpl	$4, 120(%edi)
	movl	8(%edi), %esi
	je	.L695
	movl	$16, %eax
	jmp	.L694
.L695:
	pushl	$4096
	pushl	%edi
	pushl	$6
	pushl	4(%esi)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	jne	.L696
	movzwl	8(%esi), %ebx
	testl	%ebx, %ebx
	jne	.L697
	movl	$0, 24(%edi)
	jmp	.L712
.L697:
	movb	1(%esi), %al
	cmpb	$1, %al
	jbe	.L698
	movzbl	%al, %eax
	movl	%eax, 24(%edi)
.L712:
	movl	$2, %eax
	jmp	.L694
.L698:
	movb	$1, 8(%esp)
	movw	28(%edi), %ax
	movw	%ax, 10(%esp)
	leal	0(,%ebx,4), %eax
	movw	%bx, 16(%esp)
	movl	%eax, (%esp)
	pushl	%eax
	call	Xalloc
	movl	%eax, %ebp
	testl	%ebp, %ebp
	popl	%eax
	movl	$11, %eax
	je	.L694
	leal	28(%esp), %eax
	pushl	%eax
	leal	28(%esp), %eax
	pushl	%eax
	leal	28(%esp), %eax
	pushl	%eax
	pushl	%ebp
	movzbl	1(%esi), %eax
	pushl	%eax
	movzwl	14(%esi), %eax
	pushl	%eax
	movzwl	12(%esi), %eax
	pushl	%eax
	movzwl	10(%esi), %eax
	pushl	%eax
	pushl	%ebx
	pushl	40(%esp)
	pushl	(%edi)
	call	AllocColorPlanes
	addl	$44, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	je	.L700
	pushl	%ebp
	call	Xfree
	movl	40(%edi), %eax
	testl	%eax, %eax
	popl	%ecx
	jne	.L694
	movl	%ebx, %eax
	jmp	.L694
.L700:
	movl	(%esp), %eax
	sarl	$2, %eax
	cmpl	$0, 16(%edi)
	movl	%eax, 12(%esp)
	je	.L703
	movl	8(%edi), %eax
	leal	8(%esp), %edx
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%edi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L710
.L703:
	leal	8(%esp), %eax
	pushl	%eax
	pushl	$32
	pushl	%edi
	call	WriteToClient
.L710:
	addl	$12, %esp
	cmpl	$0, 16(%edi)
	movl	$Swap32Write, 20(%edi)
	je	.L705
	pushl	%ebp
	pushl	4(%esp)
	pushl	%edi
	call	Swap32Write
	jmp	.L711
.L705:
	pushl	%ebp
	pushl	4(%esp)
	pushl	%edi
	call	WriteToClient
.L711:
	addl	$12, %esp
	pushl	%ebp
	call	Xfree
	movl	40(%edi), %eax
	popl	%edx
	jmp	.L694
.L696:
	movl	4(%esi), %eax
	cmpl	$2, %ebx
	movl	%eax, 24(%edi)
	movl	%ebx, %eax
	jne	.L694
	movl	$12, %eax
.L694:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcAllocColorPlanes, .-ProcAllocColorPlanes
	.align 4
.globl ProcFreeColors
	.type	ProcFreeColors, @function
ProcFreeColors:
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	movl	16(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	ja	.L714
	movl	$16, %eax
	jmp	.L713
.L714:
	pushl	$8192
	pushl	%esi
	pushl	$6
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L715
	movl	(%esp), %ecx
	testb	$2, 16(%ecx)
	je	.L716
	movl	$10, %eax
	jmp	.L713
.L716:
	movl	120(%esi), %edx
	leal	12(%ebx), %eax
	pushl	8(%ebx)
	leal	-12(,%edx,4), %edx
	pushl	%eax
	shrl	$2, %edx
	pushl	%edx
	pushl	(%esi)
	pushl	%ecx
	call	FreeColors
	movl	%eax, %edx
	movl	40(%esi), %eax
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L713
	movl	clientErrorValue, %eax
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jmp	.L713
.L715:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L713
	movl	$12, %eax
.L713:
	popl	%edx
	popl	%ebx
	popl	%esi
	ret
	.size	ProcFreeColors, .-ProcFreeColors
	.align 4
.globl ProcStoreColors
	.type	ProcStoreColors, @function
ProcStoreColors:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%esi
	movl	20(%esp), %esi
	cmpl	$1, 120(%esi)
	movl	8(%esi), %ebx
	ja	.L723
	movl	$16, %eax
	jmp	.L722
.L723:
	pushl	$2
	pushl	%esi
	pushl	$6
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L724
	movl	$12, %edx
	movl	120(%esi), %eax
	movl	%edx, %edi
	leal	-8(,%eax,4), %eax
	xorl	%edx, %edx
	divl	%edi
	testl	%edx, %edx
	movl	%eax, %ecx
	movl	$16, %eax
	jne	.L722
	leal	8(%ebx), %eax
	pushl	%eax
	pushl	%ecx
	pushl	8(%esp)
	call	StoreColors
	movl	%eax, %edx
	movl	40(%esi), %eax
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L722
	movl	clientErrorValue, %eax
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jmp	.L722
.L724:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L722
	movl	$12, %eax
.L722:
	popl	%ebx
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcStoreColors, .-ProcStoreColors
	.align 4
.globl ProcStoreNamedColor
	.type	ProcStoreNamedColor, @function
ProcStoreNamedColor:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	movl	36(%esp), %esi
	movl	120(%esi), %edx
	cmpl	$3, %edx
	movl	8(%esi), %ebx
	jbe	.L733
	movzwl	12(%ebx), %eax
	addl	$19, %eax
	shrl	$2, %eax
	cmpl	%edx, %eax
	je	.L732
.L733:
	movl	$16, %ecx
	jmp	.L731
.L732:
	pushl	$2
	pushl	%esi
	pushl	$6
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L734
	leal	12(%esp), %eax
	leal	4(%esp), %edi
	pushl	%eax
	leal	14(%esp), %eax
	pushl	%eax
	leal	16(%esp), %eax
	pushl	%eax
	movzwl	12(%ebx), %eax
	pushl	%eax
	leal	16(%ebx), %eax
	pushl	%eax
	movl	20(%esp), %eax
	movl	12(%eax), %eax
	pushl	(%eax)
	call	OsLookupColor
	addl	$24, %esp
	testl	%eax, %eax
	movl	$15, %ecx
	je	.L731
	movb	1(%ebx), %al
	movb	%al, 14(%esp)
	movl	8(%ebx), %eax
	movl	%eax, 4(%esp)
	pushl	%edi
	pushl	$1
	pushl	8(%esp)
	call	StoreColors
	movl	%eax, %edx
	movl	40(%esi), %eax
	addl	$12, %esp
	testl	%eax, %eax
	movl	%eax, %ecx
	jne	.L731
	movl	%edx, %ecx
	jmp	.L731
.L734:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L740
	movl	$12, %eax
.L740:
	movl	%eax, %ecx
.L731:
	addl	$20, %esp
	popl	%ebx
	popl	%esi
	movl	%ecx, %eax
	popl	%edi
	ret
	.size	ProcStoreNamedColor, .-ProcStoreNamedColor
	.align 4
.globl ProcQueryColors
	.type	ProcQueryColors, @function
ProcQueryColors:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	60(%esp), %ebp
	movl	8(%ebp), %eax
	cmpl	$1, 120(%ebp)
	movl	%eax, (%esp)
	ja	.L742
	movl	$16, %eax
	jmp	.L741
.L742:
	pushl	$1
	pushl	%ebp
	pushl	$6
	movl	12(%esp), %edx
	pushl	4(%edx)
	leal	20(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	jne	.L743
	movl	120(%ebp), %eax
	leal	-8(,%eax,4), %esi
	shrl	$2, %esi
	leal	0(,%esi,8), %eax
	pushl	%eax
	call	Xalloc
	movl	%eax, %edi
	testl	%edi, %edi
	popl	%eax
	jne	.L744
	testl	%esi, %esi
	movl	$11, %eax
	jne	.L741
.L744:
	pushl	%edi
	movl	4(%esp), %eax
	addl	$8, %eax
	pushl	%eax
	pushl	%esi
	pushl	16(%esp)
	call	QueryColors
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %ebx
	je	.L745
	testl	%edi, %edi
	je	.L746
	pushl	%edi
	call	Xfree
	popl	%eax
.L746:
	movl	40(%ebp), %eax
	testl	%eax, %eax
	jne	.L741
	movl	clientErrorValue, %eax
	movl	%eax, 24(%ebp)
	movl	%ebx, %eax
	jmp	.L741
.L745:
	leal	0(,%esi,8), %eax
	shrl	$2, %eax
	movb	$1, 8(%esp)
	movl	%eax, 12(%esp)
	cmpl	$0, 16(%ebp)
	movl	28(%ebp), %eax
	movw	%ax, 10(%esp)
	movw	%si, 16(%esp)
	leal	8(%esp), %edx
	je	.L749
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%ebp
	call	*ReplySwapVector(,%eax,4)
	jmp	.L758
.L749:
	pushl	%edx
	pushl	$32
	pushl	%ebp
	call	WriteToClient
.L758:
	addl	$12, %esp
	testl	%esi, %esi
	je	.L751
	cmpl	$0, 16(%ebp)
	movl	$SQColorsExtend, 20(%ebp)
	je	.L752
	pushl	%edi
	leal	0(,%esi,8), %eax
	pushl	%eax
	pushl	%ebp
	call	SQColorsExtend
	jmp	.L759
.L752:
	pushl	%edi
	leal	0(,%esi,8), %eax
	pushl	%eax
	pushl	%ebp
	call	WriteToClient
.L759:
	addl	$12, %esp
.L751:
	testl	%edi, %edi
	je	.L754
	pushl	%edi
	call	Xfree
	popl	%edi
.L754:
	movl	40(%ebp), %eax
	jmp	.L741
.L743:
	movl	(%esp), %edx
	movl	4(%edx), %eax
	cmpl	$2, %ebx
	movl	%eax, 24(%ebp)
	movl	%ebx, %eax
	jne	.L741
	movl	$12, %eax
.L741:
	addl	$40, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ProcQueryColors, .-ProcQueryColors
	.align 4
.globl ProcLookupColor
	.type	ProcLookupColor, @function
ProcLookupColor:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	52(%esp), %esi
	movl	120(%esi), %edx
	cmpl	$2, %edx
	movl	8(%esi), %ebx
	jbe	.L762
	movzwl	8(%ebx), %eax
	addl	$15, %eax
	shrl	$2, %eax
	cmpl	%edx, %eax
	je	.L761
.L762:
	movl	$16, %edx
	jmp	.L760
.L761:
	pushl	$1
	pushl	%esi
	pushl	$6
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L763
	leal	16(%esp), %eax
	leal	4(%esp), %edi
	pushl	%eax
	leal	18(%esp), %eax
	pushl	%eax
	leal	20(%esp), %eax
	pushl	%eax
	movzwl	8(%ebx), %eax
	pushl	%eax
	leal	12(%ebx), %eax
	pushl	%eax
	movl	20(%esp), %eax
	movl	12(%eax), %eax
	pushl	(%eax)
	call	OsLookupColor
	addl	$24, %esp
	testl	%eax, %eax
	movl	$15, %edx
	je	.L760
	movb	$1, 4(%esp)
	movw	28(%esi), %ax
	movw	%ax, 6(%esp)
	movl	12(%esp), %eax
	movw	%ax, 18(%esp)
	movw	14(%esp), %ax
	movw	%ax, 20(%esp)
	movl	16(%esp), %eax
	movw	%ax, 22(%esp)
	movl	(%esp), %eax
	movl	$0, 8(%esp)
	movl	12(%eax), %edx
	pushl	(%eax)
	leal	26(%esp), %eax
	pushl	%eax
	leal	28(%esp), %eax
	pushl	%eax
	leal	30(%esp), %eax
	pushl	%eax
	call	*308(%edx)
	addl	$16, %esp
	cmpl	$0, 16(%esi)
	je	.L765
	movl	8(%esi), %eax
	movzbl	(%eax), %eax
	pushl	%edi
	pushl	$32
	pushl	%esi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L770
.L765:
	pushl	%edi
	pushl	$32
	pushl	%esi
	call	WriteToClient
.L770:
	addl	$12, %esp
	movl	40(%esi), %edx
	jmp	.L760
.L763:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L769
	movl	$12, %eax
.L769:
	movl	%eax, %edx
.L760:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	movl	%edx, %eax
	popl	%edi
	ret
	.size	ProcLookupColor, .-ProcLookupColor
	.align 4
.globl ProcCreateCursor
	.type	ProcCreateCursor, @function
ProcCreateCursor:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	52(%esp), %eax
	cmpl	$8, 120(%eax)
	movl	8(%eax), %esi
	je	.L772
	movl	$16, %edx
	jmp	.L771
.L772:
	pushl	52(%esp)
	pushl	4(%esi)
	call	LegalNewID
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L773
	movl	52(%esp), %edx
	movl	4(%esi), %eax
	movl	%eax, 24(%edx)
	movl	$14, %edx
	jmp	.L771
.L773:
	pushl	$1
	pushl	56(%esp)
	pushl	$1073741826
	pushl	8(%esi)
	leal	44(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	je	.L774
	movl	8(%esi), %eax
	jmp	.L799
.L774:
	pushl	$1
	pushl	56(%esp)
	pushl	$1073741826
	pushl	12(%esi)
	leal	40(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	je	.L777
	movl	12(%esi), %eax
	testl	%eax, %eax
	je	.L781
.L799:
	movl	52(%esp), %ecx
	cmpl	$2, %edx
	movl	%eax, 24(%ecx)
	movl	%edx, %eax
	jne	.L780
	movl	$4, %eax
.L780:
	movl	%eax, %edx
	jmp	.L771
.L777:
	movl	24(%esp), %ecx
	movl	28(%esp), %edx
	movl	12(%ecx), %eax
	cmpl	%eax, 12(%edx)
	jne	.L785
	cmpb	$1, 2(%edx)
	jne	.L785
	cmpb	$1, 2(%ecx)
	jne	.L785
.L781:
	movl	28(%esp), %eax
	movw	12(%eax), %dx
	cmpw	%dx, 28(%esi)
	movw	14(%eax), %ax
	movw	%dx, 6(%esp)
	movw	%ax, 4(%esp)
	ja	.L785
	cmpw	%ax, 30(%esi)
	jbe	.L784
.L785:
	movl	$8, %edx
	jmp	.L771
.L784:
	movzwl	6(%esp), %ecx
	movl	%ecx, %eax
	addl	$31, %eax
	sarl	$5, %eax
	movzwl	4(%esp), %edi
	leal	0(,%eax,4), %ebx
	imull	%edi, %ebx
	movl	%ecx, (%esp)
	pushl	%ebx
	call	Xalloc
	movl	%eax, 12(%esp)
	popl	%eax
	cmpl	$0, 8(%esp)
	movl	$11, %edx
	je	.L771
	pushl	%ebx
	call	Xalloc
	movl	%eax, %ebp
	testl	%ebp, %ebp
	popl	%eax
	jne	.L787
	pushl	8(%esp)
	call	Xfree
	movl	$11, %edx
	popl	%eax
	jmp	.L771
.L787:
	pushl	%ebx
	pushl	$0
	pushl	16(%esp)
	call	memset
	movl	40(%esp), %eax
	movl	16(%eax), %edx
	pushl	20(%esp)
	pushl	$1
	pushl	$1
	pushl	%edi
	pushl	28(%esp)
	pushl	$0
	pushl	$0
	pushl	%eax
	call	*116(%edx)
	addl	$44, %esp
	cmpl	$0, 24(%esp)
	jne	.L788
	decl	%ebx
	movl	%ebp, %eax
	js	.L793
.L792:
	movb	$-1, (%eax)
	incl	%eax
	decl	%ebx
	jns	.L792
	jmp	.L793
.L788:
	pushl	%ebx
	pushl	$0
	pushl	%ebp
	call	memset
	movl	36(%esp), %eax
	movl	16(%eax), %edx
	pushl	%ebp
	pushl	$1
	pushl	$1
	pushl	%edi
	pushl	28(%esp)
	pushl	$0
	pushl	$0
	pushl	%eax
	call	*116(%edx)
	addl	$44, %esp
.L793:
	movw	6(%esp), %ax
	movl	4(%esp), %edx
	movw	%dx, 18(%esp)
	movw	%ax, 16(%esp)
	movw	28(%esi), %ax
	movw	%ax, 20(%esp)
	movw	30(%esi), %ax
	movw	%ax, 22(%esp)
	pushl	4(%esi)
	pushl	56(%esp)
	leal	20(%esp), %eax
	pushl	%eax
	movzwl	26(%esi), %eax
	pushl	%eax
	movzwl	24(%esi), %eax
	pushl	%eax
	movzwl	22(%esi), %eax
	pushl	%eax
	movzwl	20(%esi), %eax
	pushl	%eax
	movzwl	18(%esi), %eax
	pushl	%eax
	movzwl	16(%esi), %eax
	pushl	%eax
	leal	52(%esp), %eax
	pushl	%eax
	pushl	$0
	pushl	%ebp
	pushl	56(%esp)
	call	AllocARGBCursor
	addl	$52, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L771
	pushl	12(%esp)
	pushl	$5
	pushl	4(%esi)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	movl	$11, %edx
	je	.L771
	movl	52(%esp), %ecx
	movl	40(%ecx), %edx
.L771:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	movl	%edx, %eax
	popl	%ebp
	ret
	.size	ProcCreateCursor, .-ProcCreateCursor
	.align 4
.globl ProcCreateGlyphCursor
	.type	ProcCreateGlyphCursor, @function
ProcCreateGlyphCursor:
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	movl	16(%esp), %esi
	cmpl	$8, 120(%esi)
	movl	8(%esi), %ebx
	je	.L801
	movl	$16, %edx
	jmp	.L800
.L801:
	pushl	%esi
	pushl	4(%ebx)
	call	LegalNewID
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L802
	movl	4(%ebx), %eax
	movl	$14, %edx
	movl	%eax, 24(%esi)
	jmp	.L800
.L802:
	pushl	4(%ebx)
	pushl	%esi
	leal	8(%esp), %eax
	pushl	%eax
	movzwl	30(%ebx), %eax
	pushl	%eax
	movzwl	28(%ebx), %eax
	pushl	%eax
	movzwl	26(%ebx), %eax
	pushl	%eax
	movzwl	24(%ebx), %eax
	pushl	%eax
	movzwl	22(%ebx), %eax
	pushl	%eax
	movzwl	20(%ebx), %eax
	pushl	%eax
	movzwl	18(%ebx), %eax
	pushl	%eax
	pushl	12(%ebx)
	movzwl	16(%ebx), %eax
	pushl	%eax
	pushl	8(%ebx)
	call	AllocGlyphCursor
	addl	$52, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L800
	pushl	(%esp)
	pushl	$5
	pushl	4(%ebx)
	call	AddResource
	addl	$12, %esp
	testl	%eax, %eax
	movl	$11, %edx
	je	.L800
	movl	40(%esi), %edx
.L800:
	popl	%ebx
	popl	%ebx
	movl	%edx, %eax
	popl	%esi
	ret
	.size	ProcCreateGlyphCursor, .-ProcCreateGlyphCursor
	.align 4
.globl ProcFreeCursor
	.type	ProcFreeCursor, @function
ProcFreeCursor:
	pushl	%esi
	pushl	%ebx
	pushl	%ebx
	movl	16(%esp), %esi
	cmpl	$2, 120(%esi)
	movl	8(%esi), %ebx
	je	.L806
	movl	$16, %eax
	jmp	.L805
.L806:
	pushl	$4
	pushl	%esi
	pushl	$5
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupResource
	addl	$20, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L807
	pushl	$0
	pushl	4(%ebx)
	call	FreeResource
	popl	%edx
	movl	40(%esi), %eax
	popl	%ecx
	jmp	.L805
.L807:
	movl	4(%ebx), %eax
	cmpl	$2, %edx
	movl	%eax, 24(%esi)
	movl	%edx, %eax
	jne	.L805
	movl	$6, %eax
.L805:
	popl	%esi
	popl	%ebx
	popl	%esi
	ret
	.size	ProcFreeCursor, .-ProcFreeCursor
	.align 4
.globl ProcQueryBestSize
	.type	ProcQueryBestSize, @function
ProcQueryBestSize:
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	48(%esp), %esi
	cmpl	$3, 120(%esi)
	movl	8(%esi), %ebx
	je	.L812
	movl	$16, %eax
	jmp	.L811
.L812:
	movb	1(%ebx), %al
	cmpb	$2, %al
	jbe	.L813
	movzbl	%al, %eax
	movl	%eax, 24(%esi)
	movl	$2, %eax
	jmp	.L811
.L813:
	pushl	$16
	pushl	$-1
	pushl	%esi
	pushl	4(%ebx)
	leal	16(%esp), %eax
	pushl	%eax
	call	dixLookupDrawable
	addl	$20, %esp
	testl	%eax, %eax
	jne	.L811
	cmpb	$0, 1(%ebx)
	je	.L815
	movl	(%esp), %eax
	cmpb	$2, (%eax)
	jne	.L815
	movl	$8, %eax
	jmp	.L811
.L815:
	movl	(%esp), %eax
	movl	16(%eax), %edx
	pushl	%edx
	leal	10(%ebx), %eax
	pushl	%eax
	leal	8(%ebx), %eax
	pushl	%eax
	movzbl	1(%ebx), %eax
	pushl	%eax
	call	*108(%edx)
	movb	$1, 20(%esp)
	movw	28(%esi), %ax
	movw	%ax, 22(%esp)
	movw	8(%ebx), %ax
	movw	%ax, 28(%esp)
	movw	10(%ebx), %ax
	movl	$0, 24(%esp)
	movw	%ax, 30(%esp)
	addl	$16, %esp
	cmpl	$0, 16(%esi)
	leal	4(%esp), %edx
	je	.L817
	movl	8(%esi), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%esi
	call	*ReplySwapVector(,%eax,4)
	jmp	.L819
.L817:
	pushl	%edx
	pushl	$32
	pushl	%esi
	call	WriteToClient
.L819:
	addl	$12, %esp
	movl	40(%esi), %eax
.L811:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	ProcQueryBestSize, .-ProcQueryBestSize
	.align 4
.globl ProcSetScreenSaver
	.type	ProcSetScreenSaver, @function
ProcSetScreenSaver:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp), %edi
	cmpl	$3, 120(%edi)
	movl	8(%edi), %eax
	je	.L821
	movl	$16, %eax
	jmp	.L820
.L821:
	xorl	%edx, %edx
	movl	screenInfo+48, %ecx
	cmpl	%ecx, %edx
	jge	.L841
.L827:
	incl	%edx
	cmpl	%ecx, %edx
	jl	.L827
.L841:
	movzbl	8(%eax), %edx
	cmpl	$2, %edx
	jbe	.L828
	movl	%edx, 24(%edi)
	jmp	.L845
.L828:
	movzbl	9(%eax), %ecx
	cmpl	$2, %ecx
	jbe	.L829
	movl	%ecx, 24(%edi)
	jmp	.L845
.L829:
	movw	4(%eax), %bx
	cmpw	$-1, %bx
	jge	.L830
	movswl	%bx,%eax
	jmp	.L844
.L830:
	movw	6(%eax), %si
	cmpw	$-1, %si
	jge	.L831
	movswl	%si,%eax
.L844:
	movl	%eax, 24(%edi)
.L845:
	movl	$2, %eax
	jmp	.L820
.L831:
	cmpl	$2, %edx
	jne	.L832
	movl	defaultScreenSaverBlanking, %eax
	movl	%eax, ScreenSaverBlanking
	jmp	.L833
.L832:
	movl	%edx, ScreenSaverBlanking
.L833:
	cmpl	$2, %ecx
	jne	.L834
	movl	defaultScreenSaverAllowExposures, %eax
	movl	%eax, ScreenSaverAllowExposures
	jmp	.L835
.L834:
	movl	%ecx, ScreenSaverAllowExposures
.L835:
	testw	%bx, %bx
	js	.L836
	movswl	%bx,%eax
	imull	$1000, %eax, %eax
	jmp	.L842
.L836:
	movl	defaultScreenSaverTime, %eax
.L842:
	testw	%si, %si
	movl	%eax, ScreenSaverTime
	js	.L838
	movswl	%si,%eax
	imull	$1000, %eax, %eax
	jmp	.L843
.L838:
	movl	defaultScreenSaverInterval, %eax
.L843:
	movl	%eax, ScreenSaverInterval
	call	SetScreenSaverTimer
	movl	40(%edi), %eax
.L820:
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcSetScreenSaver, .-ProcSetScreenSaver
	.align 4
.globl ProcGetScreenSaver
	.type	ProcGetScreenSaver, @function
ProcGetScreenSaver:
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	44(%esp), %ebx
	cmpl	$1, 120(%ebx)
	je	.L847
	movl	$16, %eax
	jmp	.L846
.L847:
	xorl	%eax, %eax
	movl	screenInfo+48, %edx
	cmpl	%edx, %eax
	jge	.L857
.L853:
	incl	%eax
	cmpl	%edx, %eax
	jl	.L853
.L857:
	movb	$1, (%esp)
	movw	28(%ebx), %ax
	movl	$1000, %esi
	xorl	%edx, %edx
	movw	%ax, 2(%esp)
	movl	ScreenSaverTime, %eax
	divl	%esi
	movw	%ax, 8(%esp)
	xorl	%edx, %edx
	movl	ScreenSaverInterval, %eax
	divl	%esi
	movw	%ax, 10(%esp)
	movb	ScreenSaverBlanking, %al
	movb	%al, 12(%esp)
	movb	ScreenSaverAllowExposures, %al
	movb	%al, 13(%esp)
	cmpl	$0, 16(%ebx)
	movl	$0, 4(%esp)
	movl	%esp, %edx
	je	.L854
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L858
.L854:
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	WriteToClient
.L858:
	addl	$12, %esp
	movl	40(%ebx), %eax
.L846:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	ProcGetScreenSaver, .-ProcGetScreenSaver
	.align 4
.globl ProcChangeHosts
	.type	ProcChangeHosts, @function
ProcChangeHosts:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	120(%ebx), %ecx
	cmpl	$1, %ecx
	movl	8(%ebx), %edx
	jbe	.L861
	movzwl	6(%edx), %eax
	addl	$11, %eax
	shrl	$2, %eax
	cmpl	%ecx, %eax
	je	.L860
.L861:
	movl	$16, %eax
	jmp	.L859
.L860:
	movb	1(%edx), %al
	testb	%al, %al
	jne	.L862
	leal	8(%edx), %eax
	pushl	%eax
	movzwl	6(%edx), %eax
	pushl	%eax
	movzbl	4(%edx), %eax
	pushl	%eax
	pushl	%ebx
	call	AddHost
	jmp	.L867
.L862:
	cmpb	$1, %al
	jne	.L864
	leal	8(%edx), %eax
	pushl	%eax
	movzwl	6(%edx), %eax
	pushl	%eax
	movzbl	4(%edx), %eax
	pushl	%eax
	pushl	%ebx
	call	RemoveHost
	jmp	.L867
.L864:
	movzbl	%al, %eax
	movl	%eax, 24(%ebx)
	movl	$2, %eax
	jmp	.L859
.L867:
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L859
	movl	40(%ebx), %eax
.L859:
	popl	%ebx
	ret
	.size	ProcChangeHosts, .-ProcChangeHosts
	.align 4
.globl ProcListHosts
	.type	ProcListHosts, @function
ProcListHosts:
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	56(%esp), %ebx
	cmpl	$1, 120(%ebx)
	je	.L869
	movl	$16, %eax
	jmp	.L868
.L869:
	leal	13(%esp), %eax
	leal	12(%esp), %esi
	pushl	%eax
	leal	12(%esp), %eax
	pushl	%eax
	leal	12(%esp), %eax
	pushl	%eax
	leal	12(%esp), %eax
	pushl	%eax
	call	GetHosts
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L868
	movb	$1, 12(%esp)
	movw	28(%ebx), %ax
	movw	%ax, 14(%esp)
	movl	4(%esp), %eax
	movw	%ax, 20(%esp)
	movl	8(%esp), %eax
	sarl	$2, %eax
	cmpl	$0, 16(%ebx)
	movl	%eax, 16(%esp)
	je	.L872
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%esi
	pushl	$32
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L877
.L872:
	pushl	%esi
	pushl	$32
	pushl	%ebx
	call	WriteToClient
.L877:
	addl	$12, %esp
	cmpl	$0, 4(%esp)
	je	.L874
	cmpl	$0, 16(%ebx)
	movl	$SLHostsExtend, 20(%ebx)
	je	.L875
	pushl	(%esp)
	pushl	12(%esp)
	pushl	%ebx
	call	SLHostsExtend
	jmp	.L878
.L875:
	pushl	(%esp)
	pushl	12(%esp)
	pushl	%ebx
	call	WriteToClient
.L878:
	addl	$12, %esp
.L874:
	pushl	(%esp)
	call	Xfree
	movl	40(%ebx), %eax
	popl	%esi
.L868:
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	ProcListHosts, .-ProcListHosts
	.align 4
.globl ProcChangeAccessControl
	.type	ProcChangeAccessControl, @function
ProcChangeAccessControl:
	pushl	%ebx
	movl	8(%esp), %ebx
	cmpl	$1, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L880
	movl	$16, %eax
	jmp	.L879
.L880:
	movb	1(%eax), %al
	cmpb	$1, %al
	jbe	.L881
	movzbl	%al, %eax
	movl	%eax, 24(%ebx)
	movl	$2, %eax
	jmp	.L879
.L881:
	decb	%al
	sete	%al
	movzbl	%al, %eax
	pushl	%eax
	pushl	%ebx
	call	ChangeAccessControl
	testl	%eax, %eax
	popl	%edx
	popl	%ecx
	jne	.L879
	movl	40(%ebx), %eax
.L879:
	popl	%ebx
	ret
	.size	ProcChangeAccessControl, .-ProcChangeAccessControl
	.align 4
	.type	CloseDownRetainedResources, @function
CloseDownRetainedResources:
	pushl	%ebx
	movl	$1, %ebx
	cmpl	currentMaxClients, %ebx
	jge	.L891
.L889:
	movl	clients, %eax
	movl	(%eax,%ebx,4), %eax
	testl	%eax, %eax
	je	.L886
	cmpl	$2, 32(%eax)
	jne	.L886
	cmpl	$0, 36(%eax)
	je	.L886
	pushl	%eax
	call	CloseDownClient
	popl	%eax
.L886:
	incl	%ebx
	cmpl	currentMaxClients, %ebx
	jl	.L889
.L891:
	popl	%ebx
	ret
	.size	CloseDownRetainedResources, .-CloseDownRetainedResources
	.align 4
.globl ProcKillClient
	.type	ProcKillClient, @function
ProcKillClient:
	pushl	%ebx
	pushl	%ebx
	movl	12(%esp), %ebx
	cmpl	$2, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L893
	movl	$16, %eax
	jmp	.L892
.L893:
	cmpl	$0, 4(%eax)
	jne	.L894
	call	CloseDownRetainedResources
	jmp	.L896
.L894:
	pushl	$4
	pushl	%ebx
	pushl	4(%eax)
	leal	12(%esp), %eax
	pushl	%eax
	call	dixLookupClient
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L892
	pushl	(%esp)
	call	CloseDownClient
	movb	isItTimeToYield, %al
	testb	%al, %al
	popl	%ecx
	jne	.L897
	cmpl	(%esp), %ebx
	jne	.L896
.L897:
	xorl	%eax, %eax
	movb	$1, isItTimeToYield
	jmp	.L892
.L896:
	movl	40(%ebx), %eax
.L892:
	popl	%edx
	popl	%ebx
	ret
	.size	ProcKillClient, .-ProcKillClient
	.align 4
.globl ProcSetFontPath
	.type	ProcSetFontPath, @function
ProcSetFontPath:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%edi
	movl	20(%esp), %edi
	movl	120(%edi), %edx
	cmpl	$1, %edx
	movl	8(%edi), %esi
	movl	$16, %eax
	jbe	.L899
	leal	-8(,%edx,4), %ecx
	movzwl	4(%esi), %edx
	decl	%edx
	leal	8(%esi), %ebx
	js	.L910
.L906:
	testl	%ecx, %ecx
	je	.L905
	movzbl	(%ebx), %eax
	incl	%eax
	cmpl	%eax, %ecx
	jae	.L904
.L905:
	movl	$16, %eax
	jmp	.L899
.L904:
	subl	%eax, %ecx
	addl	%eax, %ebx
	decl	%edx
	jns	.L906
.L910:
	cmpl	$3, %ecx
	movl	$16, %eax
	ja	.L899
	movl	%esp, %eax
	pushl	%eax
	leal	8(%esi), %eax
	pushl	%eax
	movzwl	4(%esi), %eax
	pushl	%eax
	pushl	%edi
	call	SetFontPath
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, %edx
	jne	.L908
	movl	(%esp), %eax
	movl	40(%edi), %edx
	movl	%eax, 24(%edi)
.L908:
	movl	%edx, %eax
.L899:
	popl	%esi
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcSetFontPath, .-ProcSetFontPath
	.align 4
.globl ProcGetFontPath
	.type	ProcGetFontPath, @function
ProcGetFontPath:
	pushl	%ebx
	subl	$44, %esp
	movl	52(%esp), %ebx
	cmpl	$1, 120(%ebx)
	je	.L912
	movl	$16, %eax
	jmp	.L911
.L912:
	leal	8(%esp), %eax
	pushl	%eax
	leal	8(%esp), %eax
	pushl	%eax
	leal	8(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	GetFontPath
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L911
	movb	$1, 12(%esp)
	movw	28(%ebx), %ax
	movw	%ax, 14(%esp)
	movl	(%esp), %eax
	addl	4(%esp), %eax
	addl	$3, %eax
	sarl	$2, %eax
	movl	%eax, 16(%esp)
	cmpl	$0, 16(%ebx)
	movl	(%esp), %eax
	movw	%ax, 20(%esp)
	leal	12(%esp), %edx
	je	.L914
	movl	8(%ebx), %eax
	movzbl	(%eax), %eax
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	*ReplySwapVector(,%eax,4)
	jmp	.L918
.L914:
	pushl	%edx
	pushl	$32
	pushl	%ebx
	call	WriteToClient
.L918:
	addl	$12, %esp
	movl	4(%esp), %eax
	testl	%eax, %eax
	jne	.L917
	cmpl	$0, (%esp)
	je	.L916
.L917:
	pushl	8(%esp)
	addl	4(%esp), %eax
	pushl	%eax
	pushl	%ebx
	call	WriteToClient
	addl	$12, %esp
.L916:
	movl	40(%ebx), %eax
.L911:
	addl	$44, %esp
	popl	%ebx
	ret
	.size	ProcGetFontPath, .-ProcGetFontPath
	.align 4
.globl ProcChangeCloseDownMode
	.type	ProcChangeCloseDownMode, @function
ProcChangeCloseDownMode:
	movl	4(%esp), %edx
	cmpl	$1, 120(%edx)
	movl	8(%edx), %eax
	je	.L920
	movl	$16, %eax
	ret
.L920:
	movb	1(%eax), %al
	cmpb	$2, %al
	ja	.L922
	movzbl	%al, %eax
	movl	%eax, 32(%edx)
	movl	40(%edx), %eax
	ret
.L922:
	movzbl	%al, %eax
	movl	%eax, 24(%edx)
	movl	$2, %eax
	ret
	.size	ProcChangeCloseDownMode, .-ProcChangeCloseDownMode
	.align 4
.globl ProcForceScreenSaver
	.type	ProcForceScreenSaver, @function
ProcForceScreenSaver:
	pushl	%ebx
	movl	8(%esp), %ebx
	cmpl	$1, 120(%ebx)
	movl	8(%ebx), %eax
	je	.L925
	movl	$16, %eax
	jmp	.L924
.L925:
	movb	1(%eax), %al
	cmpb	$1, %al
	jbe	.L926
	movzbl	%al, %eax
	movl	%eax, 24(%ebx)
	movl	$2, %eax
	jmp	.L924
.L926:
	movzbl	%al, %eax
	pushl	%eax
	pushl	$2
	pushl	%ebx
	call	dixSaveScreens
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L924
	movl	40(%ebx), %eax
.L924:
	popl	%ebx
	ret
	.size	ProcForceScreenSaver, .-ProcForceScreenSaver
	.align 4
.globl ProcNoOperation
	.type	ProcNoOperation, @function
ProcNoOperation:
	movl	4(%esp), %eax
	cmpl	$0, 120(%eax)
	jne	.L929
	movl	$16, %eax
	ret
.L929:
	movl	40(%eax), %eax
	ret
	.size	ProcNoOperation, .-ProcNoOperation
	.align 4
.globl InitProcVectors
	.type	InitProcVectors, @function
InitProcVectors:
	xorl	%eax, %eax
.L936:
	cmpl	$0, ProcVector(,%eax,4)
	jne	.L933
	movl	$ProcBadRequest, SwappedProcVector(,%eax,4)
	movl	$ProcBadRequest, ProcVector(,%eax,4)
	movl	$ReplyNotSwappd, ReplySwapVector(,%eax,4)
.L933:
	incl	%eax
	cmpl	$255, %eax
	jle	.L936
	movl	$35, %eax
.L941:
	movl	$NotImplemented, EventSwapVector(,%eax,4)
	incl	%eax
	cmpl	$127, %eax
	jle	.L941
	ret
	.size	InitProcVectors, .-InitProcVectors
.globl dispatchExceptionAtReset
	.data
	.type	dispatchExceptionAtReset, @object
	.size	dispatchExceptionAtReset, 1
dispatchExceptionAtReset:
	.byte	1
	.text
	.align 4
.globl CloseDownClient
	.type	CloseDownClient, @function
CloseDownClient:
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	movl	28(%esp), %ebx
	movl	36(%ebx), %eax
	xorl	%esi, %esi
	testl	%eax, %eax
	jne	.L948
	cmpl	$0, 32(%ebx)
	jne	.L947
.L948:
	movl	$1, %esi
.L947:
	testl	%eax, %eax
	jne	.L949
	cmpl	$0, grabState
	je	.L950
	cmpl	%ebx, grabClient
	jne	.L950
	pushl	%ebx
	call	UngrabServer
	popl	%eax
.L950:
	movl	(%ebx), %ecx
	movl	%ecx, %edx
	movl	$-2, %eax
	andl	$31, %ecx
	pushl	%ebx
	sarl	$5, %edx
	roll	%cl, %eax
	andl	%eax, grabWaiters(,%edx,4)
	call	DeleteClientFromAnySelections
	pushl	%ebx
	call	ReleaseActiveGrabs
	pushl	%ebx
	call	DeleteClientFontStuff
	addl	$12, %esp
	testl	%esi, %esi
	jne	.L951
	pushl	%ebx
	call	FreeClientNeverRetainResources
	movl	$3, 132(%ebx)
	cmpl	$0, ClientStateCallback
	popl	%eax
	je	.L951
	movl	%esp, %eax
	movl	%ebx, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	pushl	%eax
	pushl	$ClientStateCallback
	call	CallCallbacks
	popl	%ecx
	popl	%eax
.L951:
	movl	$1, 36(%ebx)
	pushl	%ebx
	call	ClientIsAsleep
	testl	%eax, %eax
	popl	%edx
	je	.L953
	pushl	%ebx
	call	ClientSignal
	popl	%eax
.L953:
	call	ProcessWorkQueueZombies
	pushl	%ebx
	call	CloseDownConnection
	cmpl	$1, 132(%ebx)
	popl	%eax
	jbe	.L949
	decl	nClients
.L949:
	testl	%esi, %esi
	je	.L946
	cmpl	$2, 132(%ebx)
	jne	.L956
	cmpl	$0, nClients
	jne	.L956
	movb	dispatchException, %al
	orb	dispatchExceptionAtReset, %al
	movb	%al, dispatchException
.L956:
	cmpl	$0, ClientStateCallback
	movl	$4, 132(%ebx)
	je	.L957
	movl	%esp, %eax
	movl	%ebx, (%esp)
	movl	$0, 4(%esp)
	movl	$0, 8(%esp)
	pushl	%eax
	pushl	$ClientStateCallback
	call	CallCallbacks
	popl	%esi
	popl	%eax
.L957:
	pushl	%ebx
	call	FreeClientResources
	movl	(%ebx), %edx
	cmpl	nextFreeClientID, %edx
	popl	%ecx
	jge	.L958
	movl	%edx, nextFreeClientID
.L958:
	movl	clients, %eax
	movl	$0, (%eax,%edx,4)
	pushl	136(%ebx)
	movl	$0, SmartLastClient
	call	dixFreePrivates
	pushl	%ebx
	call	Xfree
	popl	%eax
	popl	%edx
	movl	clients, %ecx
	movl	currentMaxClients, %edx
	cmpl	$0, -4(%ecx,%edx,4)
	jne	.L946
.L962:
	leal	-1(%edx), %eax
	cmpl	$0, -4(%ecx,%eax,4)
	movl	%eax, %edx
	je	.L962
	movl	%eax, currentMaxClients
.L946:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	ret
	.size	CloseDownClient, .-CloseDownClient
	.align 4
	.type	KillAllClients, @function
KillAllClients:
	pushl	%ebx
	movl	$1, %ebx
	cmpl	currentMaxClients, %ebx
	jge	.L973
.L971:
	movl	clients, %eax
	movl	(%eax,%ebx,4), %eax
	testl	%eax, %eax
	je	.L968
	movl	$0, 32(%eax)
	pushl	%eax
	call	CloseDownClient
	popl	%eax
.L968:
	incl	%ebx
	cmpl	currentMaxClients, %ebx
	jl	.L971
.L973:
	popl	%ebx
	ret
	.size	KillAllClients, .-KillAllClients
	.align 4
.globl InitClient
	.type	InitClient, @function
InitClient:
	movl	8(%esp), %ecx
	movl	%ecx, %eax
	movl	4(%esp), %edx
	sall	$21, %eax
	movl	%eax, 4(%edx)
	xorl	%eax, %eax
	testl	%ecx, %ecx
	sete	%al
	movl	%eax, 32(%edx)
	movl	12(%esp), %eax
	movl	%eax, 12(%edx)
	movl	SmartScheduleTime, %eax
	movl	%ecx, (%edx)
	movl	$0, 28(%edx)
	movl	$0, 36(%edx)
	movl	$0, 48(%edx)
	movl	$0, 44(%edx)
	movl	$0, 40(%edx)
	movl	$InitialVector, 116(%edx)
	movl	$0, 16(%edx)
	movl	$0, 124(%edx)
	movl	$0, 128(%edx)
	movl	$0, 132(%edx)
	movl	$0, 136(%edx)
	movl	$0, 140(%edx)
	movl	$0, 144(%edx)
	movl	$0, 148(%edx)
	movl	%eax, 152(%edx)
	movl	%eax, 156(%edx)
	movl	%eax, 160(%edx)
	ret
	.size	InitClient, .-InitClient
	.align 4
.globl NextAvailableClient
	.type	NextAvailableClient, @function
NextAvailableClient:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	movl	nextFreeClientID, %edi
	xorl	%eax, %eax
	cmpl	$256, %edi
	je	.L975
	pushl	$164
	movl	clients, %ebx
	call	Xalloc
	movl	%eax, %esi
	movl	%eax, (%ebx,%edi,4)
	popl	%eax
	xorl	%eax, %eax
	testl	%esi, %esi
	je	.L975
	pushl	36(%esp)
	pushl	%edi
	pushl	%esi
	call	InitClient
	pushl	%esi
	call	InitClientResources
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L978
	pushl	%esi
	call	Xfree
	xorl	%eax, %eax
	popl	%esi
	jmp	.L975
.L978:
	movb	$1, (%esp)
	movw	$4, 2(%esp)
	pushl	$4
	leal	4(%esp), %eax
	pushl	%eax
	pushl	%esi
	call	InsertFakeRequest
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L979
	pushl	%esi
	call	FreeClientResources
	pushl	%esi
	call	Xfree
	popl	%ecx
	xorl	%eax, %eax
	popl	%ebx
	jmp	.L975
.L979:
	cmpl	currentMaxClients, %edi
	jne	.L980
	leal	1(%edi), %eax
	movl	%eax, currentMaxClients
.L980:
	movl	nextFreeClientID, %edx
	cmpl	$255, %edx
	jg	.L982
	movl	clients, %ecx
	cmpl	$0, (%ecx,%edx,4)
	je	.L982
.L985:
	leal	1(%edx), %eax
	cmpl	$255, %eax
	jg	.L988
	cmpl	$0, (%ecx,%eax,4)
	movl	%eax, %edx
	jne	.L985
.L988:
	movl	%eax, nextFreeClientID
.L982:
	cmpl	$0, ClientStateCallback
	je	.L986
	leal	4(%esp), %eax
	movl	%esi, 4(%esp)
	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
	pushl	%eax
	pushl	$ClientStateCallback
	call	CallCallbacks
	popl	%eax
	popl	%edx
.L986:
	movl	%esi, %eax
.L975:
	addl	$20, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	NextAvailableClient, .-NextAvailableClient
	.align 4
.globl ProcInitialConnection
	.type	ProcInitialConnection, @function
ProcInitialConnection:
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	16(%esp), %edi
	movl	8(%edi), %ebx
	movb	4(%ebx), %al
	cmpb	$108, %al
	leal	4(%ebx), %esi
	je	.L990
	cmpb	$66, %al
	je	.L990
	orl	$-1, %eax
	movl	$-1, 40(%edi)
	jmp	.L989
.L990:
	cmpb	$66, (%esi)
	jne	.L991
	movl	$1, 16(%edi)
	pushl	%esi
	call	SwapConnClientPrefix
	popl	%ecx
.L991:
	movb	$2, (%ebx)
	movzwl	6(%esi), %edx
	movzwl	8(%esi), %eax
	addl	$3, %edx
	addl	$3, %eax
	shrl	$2, %edx
	shrl	$2, %eax
	addl	%eax, %edx
	addw	%dx, 2(%ebx)
	cmpl	$0, 16(%edi)
	je	.L994
	movsbl	2(%ebx),%edx
	movb	3(%ebx), %al
	movb	%al, 2(%ebx)
	movb	%dl, 3(%ebx)
.L994:
	pushl	%edi
	call	ResetCurrentRequest
	movl	40(%edi), %eax
	popl	%edx
.L989:
	popl	%ebx
	popl	%esi
	popl	%edi
	ret
	.size	ProcInitialConnection, .-ProcInitialConnection
	.align 4
	.type	SendConnSetup, @function
SendConnSetup:
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$36, %esp
	movl	60(%esp), %edi
	testl	%edi, %edi
	movl	56(%esp), %esi
	je	.L996
	movb	$0, 12(%esp)
	leal	12(%esp), %ebx
	pushl	%edi
	call	strlen
	popl	%edx
	movb	%al, 13(%esp)
	movzbl	%al, %eax
	addl	$3, %eax
	shrl	$2, %eax
	cmpl	$0, 16(%esi)
	movw	%ax, 18(%esp)
	movw	$11, 14(%esp)
	movw	$0, 16(%esp)
	je	.L997
	pushl	%ebx
	pushl	%esi
	call	WriteSConnSetupPrefix
	popl	%ebp
	popl	%eax
	jmp	.L998
.L997:
	pushl	%ebx
	pushl	$8
	pushl	%esi
	call	WriteToClient
	addl	$12, %esp
.L998:
	pushl	%edi
	movzbl	1(%ebx), %eax
	pushl	%eax
	pushl	%esi
	call	WriteToClient
	orl	$-1, %eax
	addl	$12, %esp
	movl	$-1, 40(%esi)
	jmp	.L995
.L996:
	movl	16(%esi), %edx
	movl	screenInfo+48, %eax
	incl	nClients
	testl	%edx, %edx
	movl	%eax, 8(%esp)
	movl	ConnectionInfo, %ebp
	movl	%edx, 4(%esp)
	movl	$SwappedProcVector, %eax
	jne	.L1000
	movl	$ProcVector, %eax
.L1000:
	movl	%ebp, %ecx
	xorl	%edi, %edi
	movl	%eax, 116(%esi)
	addl	connBlockScreenStart, %ecx
	movl	4(%esi), %eax
	cmpl	8(%esp), %edi
	movl	$0, 28(%esi)
	movl	%eax, 4(%ebp)
	movl	$2097151, 8(%ebp)
	jge	.L1016
	movl	WindowTable, %eax
	movl	%eax, (%esp)
.L1011:
	movl	(%esp), %edx
	movl	(%edx,%edi,4), %eax
	movl	108(%eax), %edx
	movl	124(%eax), %eax
	testl	%eax, %eax
	je	.L1005
	orl	16(%eax), %edx
.L1005:
	movl	%edx, 16(%ecx)
	xorl	%ebx, %ebx
	leal	40(%ecx), %edx
	movzbl	39(%ecx), %ecx
	cmpl	%ecx, %ebx
	jae	.L1018
.L1010:
	movzwl	2(%edx), %eax
	incl	%ebx
	imull	$24, %eax, %eax
	cmpl	%ecx, %ebx
	leal	8(%eax,%edx), %edx
	jb	.L1010
.L1018:
	incl	%edi
	cmpl	8(%esp), %edi
	movl	%edx, %ecx
	jl	.L1011
.L1016:
	cmpl	$0, 4(%esp)
	je	.L1012
	pushl	$connSetupPrefix
	pushl	%esi
	call	WriteSConnSetupPrefix
	movzwl	connSetupPrefix+6, %eax
	pushl	%ebp
	sall	$2, %eax
	pushl	%eax
	pushl	%esi
	call	WriteSConnectionInfo
	addl	$20, %esp
	jmp	.L1013
.L1012:
	pushl	$connSetupPrefix
	pushl	$8
	pushl	%esi
	call	WriteToClient
	movzwl	connSetupPrefix+6, %eax
	pushl	%ebp
	sall	$2, %eax
	pushl	%eax
	pushl	%esi
	call	WriteToClient
	addl	$24, %esp
.L1013:
	cmpl	$0, ClientStateCallback
	movl	$2, 132(%esi)
	je	.L1014
	leal	20(%esp), %eax
	movl	%esi, 20(%esp)
	movl	$connSetupPrefix, 24(%esp)
	movl	%ebp, 28(%esp)
	pushl	%eax
	pushl	$ClientStateCallback
	call	CallCallbacks
	popl	%ebx
	popl	%edi
.L1014:
	movl	40(%esi), %eax
.L995:
	addl	$36, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	SendConnSetup, .-SendConnSetup
	.section	.rodata.str1.1
.LC2:
	.string	"Protocol version mismatch"
	.text
	.align 4
.globl ProcEstablishConnection
	.type	ProcEstablishConnection, @function
ProcEstablishConnection:
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	8(%ebx), %eax
	leal	4(%eax), %edx
	leal	16(%eax), %ecx
	movzwl	6(%edx), %eax
	addl	$3, %eax
	andl	$-4, %eax
	cmpw	$11, 2(%edx)
	leal	(%eax,%ecx), %eax
	jne	.L1021
	cmpw	$0, 4(%edx)
	je	.L1020
.L1021:
	movl	$.LC2, %eax
	jmp	.L1022
.L1020:
	pushl	%eax
	movzwl	8(%edx), %eax
	pushl	%eax
	pushl	%ecx
	movzwl	6(%edx), %eax
	pushl	%eax
	pushl	%ebx
	call	ClientAuthorized
	addl	$20, %esp
.L1022:
	movl	132(%ebx), %edx
	cmpl	$5, %edx
	jne	.L1023
	movl	$6, 132(%ebx)
	jmp	.L1024
.L1023:
	decl	%edx
	je	.L1024
	pushl	%eax
	pushl	%ebx
	call	SendConnSetup
	popl	%ecx
	popl	%ebx
	jmp	.L1019
.L1024:
	movl	40(%ebx), %eax
.L1019:
	popl	%ebx
	ret
	.size	ProcEstablishConnection, .-ProcEstablishConnection
	.align 4
.globl SendErrorToClient
	.type	SendErrorToClient, @function
SendErrorToClient:
	subl	$32, %esp
	movl	36(%esp), %edx
	movb	$0, (%esp)
	movw	28(%edx), %ax
	movw	%ax, 2(%esp)
	movl	52(%esp), %eax
	movb	%al, 1(%esp)
	movl	40(%esp), %eax
	movb	%al, 10(%esp)
	movl	44(%esp), %eax
	movw	%ax, 8(%esp)
	movl	48(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esp, %eax
	pushl	%eax
	pushl	$1
	pushl	%edx
	call	WriteEventsToClient
	addl	$44, %esp
	ret
	.size	SendErrorToClient, .-SendErrorToClient
	.align 4
.globl MarkClientException
	.type	MarkClientException, @function
MarkClientException:
	movl	4(%esp), %eax
	movl	$-1, 40(%eax)
	ret
	.size	MarkClientException, .-MarkClientException
	.comm	checkForInput,8,4
	.comm	isItTimeToYield,1,1
	.comm	ClientStateCallback,4,4
	.comm	SmartScheduleTime,4,4
	.local	grabClient
	.comm	grabClient,4,4
	.local	grabWaiters
	.comm	grabWaiters,32,32
	.local	nextFreeClientID
	.comm	nextFreeClientID,4,4
	.local	nClients
	.comm	nClients,4,4
	.comm	clientErrorValue,4,4
	.local	SmartLastClient
	.comm	SmartLastClient,4,4
	.local	SmartLastIndex
	.comm	SmartLastIndex,164,32
	.ident	"GCC: (GNU) 3.3.2"
