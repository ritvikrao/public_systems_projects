# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
					# (1) What are we setting up here?
					# Ans: We are setting up our stack pointers.
	pushq %rbp			# rbp is the base pointer and rsp is
	movq  %rsp, %rbp		# the top of the stack.

					# (2) What is going on here
					# Ans: We are printing the string in .hello.str.
	movq $1, %rax			# 
	movq $1, %rdi			#
	leaq .hello.str,%rsi		#


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans: syscall contacts the kernel to carry out a function.
	syscall				# Which syscall is being run?
					# Ans: We are writing output to stdout.

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans: Borrow something from c such as printf.

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
					# Ans:	This is the program exit command with exit code 0.
	syscall

	popq %rbp			# (Note we do not really need
					# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans:	It tells the computer that the string is 13 characters/bytes long.
