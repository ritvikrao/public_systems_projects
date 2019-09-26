# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello6.s -c -o hello6.o 
# 2.) ld hello6.o -o hello6
#
# ================== Tutorial 6 ================
# In this tutorial you will learn about how to
# represent 'null' terminated strings. This
# can be useful for C compatibility, or rather
# the motivation for why C-strings are null-terminated
#
# Learnings:
# - asciz
#
# In the next lesson we'll clean our program up just a bit more
# so we don't have to keep as much information in our heads.

.global _start  

################## Data Section ################
.hello.str:
    .asciz "123456789\n"    # *NEW CHANGE*
                            # By adding a 'z' at the end, this
                            # makes it a zero-terminated
                            # literal string.

# This guide here again is handy for finding these directives
# (Hint search '.asciz')
# https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html#SEC72

################## Code Section ################
.text          

# Function: Sets up the system call to exit
_exitProgram:
    movq $60, %rax
    movq $0, %rdi
    syscall
    ret            

# Function: Writes out a message   
_writeMessage: 
    movq $1,%rax           
    movq $1,%rdi           
    leaq .hello.str, %rsi  
    movq $11, %rdx          # Because our String is now
                            # zero-terminated, I added 1 extra
                            # byte to store that zero from our
                            # previous example.          
    syscall                 
    ret            
 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _exitProgram

    popq %rbp
