# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello4.s -c -o hello4.o 
# 2.) ld hello4.o -o hello4
#
# ================== Tutorial 4 ================
# In this tutorial we are going to break our program
# and show a subtle bug that may happen. I have simply
# 'flipped' the order of our _exitPrograma and _writeMessage
#
# Learnings:
# - Pressing 'Ctrl+C' terminates program execution
# - Assembly executes one line after the other
#   - Remember, cpu's are very simple machines!
#
# We will fix the bug in the next tutorial

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

# Function: Writes out a message   
_writeMessage: 
    movq $1,%rax           
    movq $1,%rdi           
    leaq .hello.str, %rsi  
    movq $10, %rdx          
    syscall                 

_start:         

    movq %rsp, %rbp
   
    # Here in our program flow we make calls to each procedure
    # The issue however, is when we call _writeMessage, each
    # instruction is going to 'fall-through' to the next line,
    # and eventually we will end in _start, and then call 
    # _writeMessage again.
    # This is an 'infinite-loop', and not the desired functionality
    # of our program.
    # Press 'Ctrl+C' to terminate execution. 
    callq _writeMessage
    callq _exitProgram

    popq %rbp
