# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello3.s -c -o hello3.o 
# 2.) ld hello3.o -o hello3
#
# ================== Tutorial 3 ================
# In this tutorial we are going to clean up our
# program a bit by introducing a procedure.
# We are going to use what we learned in the first
# tutorial (labels) to separate out some of the
# logic program. You will then learn about 'call'
#
# Learnings:
# - Creating procedures with labels
# - call
#
# Unfortunately, there is yet another subtle bug
# that we will uncover in the next two tutorials

.global _start  

################## Data Section ################
.hello.str:
    .ascii "123456789\n"

################## Code Section ################
.text          

# Function: Writes out a message   
# Here we have created a new label '_writeMessage'
# Because a label is an address or location we can jump to
# then we can use the 'callq' to jump to this address of
# _writeMessage, and then execute instructions offset from this
# label 
_writeMessage: 
    movq $1,%rax           
    movq $1,%rdi           
    leaq .hello.str, %rsi  
    movq $10, %rdx          
    syscall                 

# Function: Sets up the system call to exit
# We repeat the same thing for the exit program
_exitProgram:
    movq $60, %rax
    movq $0, %rdi
    syscall

_start:         

    movq %rsp, %rbp
   
    # Here in our program flow we make calls to each procedure 
    callq _writeMessage
    callq _exitProgram

    popq %rbp
