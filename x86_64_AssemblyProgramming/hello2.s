# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello2.s -c -o hello2.o 
# 2.) ld hello2.o -o hello2
#
# ================== Tutorial 2 ================
# In this tutorial we fix a small bug, and also
# rearrange our assembly to make it slightly more
# manageable
#
# Learnings:
# - We can move sections around in assembly
#   - Separating code and data is good
# - Finding bugs can be a little tricky
#   - i.e. count sizes of things very carefully!
#

.global _start  

################## Data Section ################
# Now I have moved the 'data' section of my code
# to the top. I think it is easier to see here.
.hello.str:
    .ascii "123456789\n"

################## Code Section ################
.text          

_start:         

    movq %rsp, %rbp
    
    # Print Function 
    movq $1,%rax           
    movq $1,%rdi           
    leaq .hello.str, %rsi  
    movq $10, %rdx          # Did you catch this last time?
                            # We forgot to print the endline 
                            # character in our program
                            # i.e. we miscalculated how long our
                            # ascii string was.
    syscall                 

    # Sets up the system call to exit
    movq $60, %rax
    movq $0, %rdi
    syscall

    popq %rbp
