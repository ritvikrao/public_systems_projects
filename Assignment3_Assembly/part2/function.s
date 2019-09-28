.global _start

.welcome.str:
    .asciz "Enter 1 for addition, 2 for subtraction:\n"

.negative.string:
	.asciz "-"

.endline.string:
	.asciz "\n"

.data
choice: .quad 0
a: .byte 0,0,0,0,0,0,0,0
b: .byte 0,0,0,0,0,0,0,0
spacer1: .long 0
vala: .long 0
spacer2: .long 0
valb: .long 0
spacer3: .long 0
answer: .long 0
spacer4: .long 0
final: .byte 0,0,0,0,0,0,0,0

.bss
	n: .skip 20

.text

_writeEndLine:
    	movq $1,%rax
    	movq $1,%rdi
    	leaq .endline.string, %rsi
    	movq $1, %rdx
    	syscall
    	ret


_printWelcome:
    	movq $1, %rax
    	movq $1, %rdi
    	leaq .welcome.str,%rsi
    	movq $42, %rdx
    	syscall
    	ret

_mult:
	.rec:
	cmpq $0, %r11
	je .endmult
	imulq $10, %rsi
	subq $1, %r11
	jmp .rec
	.endmult:
	addq %rsi, vala
	ret

_multb:
        .recb:
        cmpq $0, %r11
        je .endmultb
        imulq $10, %rsi
        subq $1, %r11
        jmp .recb
        .endmultb:
        addq %rsi, valb
        ret

_getvaluea:
	movq $8, %r15 #byte count
	movq $0, %r14 #power of 10 tracker
	movq $0, %rdi #zeroes out rdi
	movq $0, vala
	.loop:
	subq $1, %r15
	movb a(,%r15,1), %dil
	cmpb $0, %dil
	je .end
	cmpb $10, %dil
	je .end
	cmpb $45, %dil
	je .neg
	subb $48, %dil
	movzbq %dil, %rsi
	movq %r14, %r11
	call _mult
	addq $1, %r14
	jmp .end
	.neg:
	movq vala, %r8
	subq %r8, vala
	subq %r8, vala
	.end:
	cmpq $0, %r15
	jne .loop
	.endline:
	ret	

_getvalueb:
	movq $8, %r15 #byte count
        movq $0, %r14 #power of 10 tracker
        movq $0, %rdi #zeroes out rdi
	movq $0, valb
        .loopb:
        subq $1, %r15
        movb b(,%r15,1), %dil
        cmpb $0, %dil
        je .endb
        cmpb $10, %dil
        je .endb
        cmpb $45, %dil
        je .negb
        subb $48, %dil
        movzbq %dil, %rsi
        movq %r14, %r11
        call _multb
        addq $1, %r14
	jmp .endb
        .negb:
	movq valb, %r8
        subq %r8, valb
        subq %r8, valb
        .endb:
        cmpq $0, %r15
        jne .loopb
        .endlineb:
        ret

_add:
	movq vala, %r8
	movq valb, %rsi
	movq %r8, %rdx
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
	cmpq $0, answer
	jg .initial
	movq answer, %r8
	subq %r8, answer
	subq %r8, answer

	leaq .negative.string, %rsi
        movq $1, %rax
        movq $1, %rdi
        movq $1, %rdx
        syscall

	.initial:
    	movq answer, %rax
    	movq $0, %r15
    	.loopf:
    	movq $10, %rdi 
    	movq $0, %rdx 
    	idivq %rdi     
    	movq %rdx, final(,%r15,1) 
    	addq $48, final(,%r15,1)
    	incq %r15
    	cmpq $0, %rax
    	jne .loopf
    	.display:
    	decq %r15
    	leaq final(,%r15,1),%rsi 
    	movq $1, %rax           
    	movq $1, %rdi          
    	movq $1, %rdx          
    	syscall
    	cmpq $0, %r15
    	jne .display  
    	ret

_start:
	pushq %rbp
	call _printWelcome
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
	cmpq $2610, choice
	je .sub
	call _add
	jmp .finish
	.sub:
	call _subtract
	.finish:
	movq %rax, answer
	call _toascii
	call _writeEndLine
	#exit
	movq $0, %rsi
	movq $60, %rax
	movq $0, %rdi
	syscall
	popq %rbp
