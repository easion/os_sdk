.text
	.align 4

	.global	_mystart
	.global	asm_sig_restore
	.type	_start,%function
	.type	main,%function
	.type	_exit,%function

_mystart:
	/* locate the start of the environment variables */
	popl %ecx	/* Store argc into %ecx */
	movl %esp,%ebx  /* Store argv into ebx */
	movl %esp,%eax  /* Store argv into eax as well*/
	movl %ecx,%edx	/* Stick argc into %edx so we can do some math in a sec */
	leal 4(%eax,%edx,4),%eax

	
	//xorl %ebp,%ebp  /* NULL */
	pushl %ebp      /* callers %cs */
	pushl %ebp      /* callers %eip (return address) */
	pushl %ebp      /* callers %ebp (frame pointer) */
	movl %esp,%ebp  /* mark callers stack frame as invalid */


	/* Push envp, argc, and argc arguments to __uClibc_start_main() on the stack */ 
	pushl %eax	/* Environment pointer */
	pushl %ebx	/* Argument pointer */
	pushl %ecx	/* And the argument count */

	call  main

	pushl %eax
	call _exit

asm_sig_restore:
ret

