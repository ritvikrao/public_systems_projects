	.file	"switch.c"
	.section	.rodata
.LC0:
	.string	"0\n"
.LC1:
	.string	"1\n"
.LC2:
	.string	"2\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$2, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$1, %eax
	je	.L3
	cmpl	$2, %eax
	je	.L4
	testl	%eax, %eax
	je	.L5
	jmp	.L6
.L5:
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L6
.L3:
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	jmp	.L6
.L4:
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	nop
.L6:
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-36)"
	.section	.note.GNU-stack,"",@progbits
