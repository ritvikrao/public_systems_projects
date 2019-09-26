# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello11.s -c -o hello11.o 
# 2.) ld hello11.o -o hello11
#
# ================== Tutorial 11 ================
# In this tutorial you will iterate through some
# data using a different data type
#
# Learnings:
# - Iterate through a different data type
# 
# In the next lesson we will revert back to working
# with 'bytes' and learn how to set them in the array

.global _start  

################## Data Section ################

# Useful constants
.equ STDOUT         ,1
.equ WRITE          ,1
.equ EXIT           ,60
.equ EXIT_SUCCESS   ,0 

.hello.str:
    .asciz "starting!\n"    

.newline:                   
    .ascii "\n"             
                            
.bss           
    zeros:  .skip 16   

.data 
    lessBoring:    .quad 82,83,84,85,86,87,88     
                            # This time I have changed our data
                            # We are working with a quad which
                            # is 8 bytes, and I have 
                            # populaetd our values

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

# Function: Writes an endline character
_writeEndLine:

    movq $WRITE,%rax           
    movq $STDOUT,%rdi          
    leaq .newline, %rsi  
    movq $1, %rdx                   
    syscall                 
    
    ret            

# Function: Iterate
_iterate:
    movq $0,%r10    # counter
 
.loop:                  
    cmpq $7,%r10    # iterate 7 times
                        
    je .terminate       
                         
    movq $WRITE,%rax           
    movq $STDOUT,%rdi
    # In C code it looks like:
    # %rsi = ones[%r10] // where '%rsi is our counter
    #                   // The offset when we increse rsi is
    #                   // 8 bytes at a time
    # Note what is different here, we are offsetting by
    # 8, because a .quad is 8 bytes for our 'lessBoring'
    # data.
    leaq lessBoring(,%r10,8), %rsi
    movq $1, %rdx                   
    syscall                 
    
    incq %r10
        
    jmp .loop            # Jump back to our loop

.terminate:

    ret  # return from our function 


# Program Entry 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _iterate          
    callq _writeEndLine     
    callq _exitProgram

    popq %rbp
