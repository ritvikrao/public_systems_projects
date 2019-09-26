# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello7.s -c -o hello7.o 
# 2.) ld hello7.o -o hello7
#
# ================== Tutorial 7 ================
# In this tutorial you will clean up your program
# a bit by using equ. This is roughly equivalent
# to the #define in the C language
#
# Learnings:
# - equ
# - EXIT_SUCCESS
#
# In the next lesson you will run through your program in
# gdb.

.global _start  

################## Data Section ################

# Here we create a few new symbols. 
# This is nice because I can then refer to the symbolic name
# rather than remembering that '1' for example is the WRITE
# system call. This can help prevent some errors in your program
# as your 'intent' is better captured in your code section.
.equ STDOUT, 1
.equ WRITE, 1
.equ EXIT,60
.equ EXIT_SUCCESS,0 # Note '0' typically means we are exiting 
                    # successfully in our programs. That is why
                    # we often 'return 0' from main.
                    # However, returning a different value
                    # (e.g. exit(1) indicates a failure, and
                    # different values indidicate different types
                    # of failures.

# For more information on 'equ' see: https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html#SEC86


.hello.str:
    .asciz "123456789\n"

################## Code Section ################
.text          

# Function: Sets up the system call to exit
_exitProgram:
    movq $EXIT, %rax            # Note we still prefix our
    movq $EXIT_SUCCESS, %rdi    # equ symbols we defined above with
    syscall                     # the dollar sign ($).
    ret                         # The dollar sign in this context
                                # always means to treat whatever
                                # the operand is (e.g. $1 or $EXIT)
                                # as the immediate value, as 
                                # opposed to an address
                                # (i.e. the address of data at 0x60)
# Function: Writes out a message   
_writeMessage: 
    movq $WRITE,%rax            # new addition
    movq $STDOUT,%rdi           # new addition
    leaq .hello.str, %rsi  
    movq $11, %rdx                   
    syscall                 
    ret            
 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _exitProgram

    popq %rbp
