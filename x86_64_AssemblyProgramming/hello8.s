# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello8.s -c -o hello8.o 
# 2.) ld hello8.o -o hello8
#
# ================== Tutorial 8 ================
# In this tutorial you will run your program through gdb
# See video here: https://www.youtube.com/watch?v=xmvCoi3zfDY&list=PLvv0ScY6vfd9BSBznpARlKGziF1xrlU54&index=6
#
# Learnings:
# - Using GDB
#
# In the next lesson we will learn about data storage 

.global _start  

################## Data Section ################

# Useful constants
.equ STDOUT, 1
.equ WRITE, 1
.equ EXIT,60
.equ EXIT_SUCCESS,0 


.hello.str:
    .asciz "123456789\n"

################## Code Section ################
.text          

# Function: Sets up the system call to exit
_exitProgram:
    movq $EXIT, %rax            
    movq $EXIT_SUCCESS, %rdi    
    syscall                     
    ret                         
                                 
# Function: Writes out a message   
_writeMessage: 
    movq $WRITE,%rax           
    movq $STDOUT,%rdi          
    leaq .hello.str, %rsi  
    movq $11, %rdx                   
    syscall                 
    ret            

# Program Entry 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _exitProgram

    popq %rbp
