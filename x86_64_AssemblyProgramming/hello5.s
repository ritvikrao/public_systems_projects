# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello5.s -c -o hello5.o 
# 2.) ld hello5.o -o hello5
#
# ================== Tutorial 5 ================
# In this tutorial fix our bug to use functions
# just like we would in 'C'
#
# Learnings:
# - ret - is how we return from our procedure call.
#
# In the next tutorial we will make one tiny change

.global _start  

################## Data Section ################
.hello.str:
    .ascii "123456789\n"

################## Code Section ################
.text          

# Function: Sets up the system call to exit
_exitProgram:
    movq $60, %rax
    movq $0, %rdi
    syscall
    ret             # The 'ret' instruction returns from
                    # where we last called from.
                    # In assembly lingo this means we are
                    # 'popping' the return address from the
                    # 'call' stack and jumping back there.
                    # When we do the 'callq' instruction,
                    # that actually pushes a return
                    # address on the stack so we can later return.

# Function: Writes out a message   
_writeMessage: 
    movq $1,%rax           
    movq $1,%rdi           
    leaq .hello.str, %rsi  
    movq $10, %rdx          
    syscall                 
    ret             # New addition

_start:         

    movq %rsp, %rbp
   
    # callq pushes a return address, so we can continue executing.
    callq _writeMessage
    callq _exitProgram

    popq %rbp
