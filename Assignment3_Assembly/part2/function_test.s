.global _start

.data
choice: .quad 0
a: .byte 0,0,0,0,0,0,0,0
b: .byte 0,0,0,0,0,0,0,0
vala: .long 0
valb: .long 0
answer: .long 0
final: .byte 0,0,0,0,0,0,0,0

.bss
	n: .skip 20

.text

_mult:
	.rec:
	imulq $10, %rdi
	subq $1, %r11
	cmpq $0, %r11
	jne .rec
	addq %rdi, vala
	ret

_getvaluea:
	movq $8, %r15
	movq $0, %r14
	movq $0, %rdi
	.loop:
	subq $1, %r15
	movb a(,%r15,1), %dil
	cmpb $0, %dil
	je .end
	cmpb $10, %dil
	je .loopa
	cmpb $45, %dil
	je .neg
	subb $48, %dil
	movq %rdi, %rsi
	movq %r14, %r11
	call _mult
	cmpq $0, %r15
	je .endline
	.neg:
	.end:
	jmp .loop
	.endline:
	ret	

_getvalueb:
	ret

_add:
	movq vala, %rdi
	movq valb, %rsi
	movq %rdi, %rdx
	movq %rsi, %rax
	addq %rdx, %rax
	ret

_subtract:
	movq vala, %rdi
        movq valb, %rsi
        movq %rsi, %rdx
        movq %rdi, %rax
        subq %rdx, %rax
	ret

_toascii:
	ret

_start:
	pushq %rbp
	#enter n
	movq $0, %rax
    	movq $0, %rdi
    	movq $0, n
    	movq $n, %rsi
    	movq $20, %rdx
    	syscall
	movq $0, %r11
	movq n, %r11
	movq %r11, %r12
	movq %r12, choice
	#enter a
	movq $0, n
	movq $0, %rax
        movq $0, %rdi
        movq $0, n
        movq $n, %rsi
        movq $20, %rdx
        syscall
	movq $0, %r11
        movq n, %r11
        movq %r11, %r12
        movq %r12, a
	#enter b
        movq $0, n
        movq $0, %rax
        movq $0, %rdi
        movq $0, n
        movq $n, %rsi
        movq $20, %rdx
        syscall
        movq $0, %r11
        movq n, %r11
        movq %r11, %r12
        movq %r12, b
	#get values of a and b
	call _getvaluea
	call _getvalueb
	cmpq $2, choice
	je .sub
	call _add
	jmp .finish
	.sub:
	call _sub
	.finish:
	call _toascii
	#exit
	movq $0, %rsi
	movq $60, %rax
	movq $0, %rdi
	syscall
	popq %rbp
