# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello12.s -c -o hello12.o 
# 2.) ld hello12.o -o hello12
#
# ================== Tutorial 12 ================
# In this tutorial we will reset individual bytes
# in a collection of data
#
# Learnings:
# - Set data in a collection of data
# - We will check if a byte is a specific value
#   and then terminate as well.
# 
# In the next lesson we will print a big number

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

# Function: setBytes
# In this function we are going to set our bytes
# to a new value, and then iterate through them.
# If we find the number '85' however, we will stop
# setting any more bytes.
_setBytes:
    movq $0,%r10    # counter
 
.loop1:                  
    cmpq $7,%r10    # iterate 7 times
                        
    je .terminate1
                         
    movq $WRITE,%rax           
    movq $STDOUT,%rdi
    
    # Let's store our value in a register
    # for faster access and convenience
    leaq lessBoring(,%r10,8), %r11
    # Let's compare %r11's value with '85'
    # If the value is '85' then the loop will terminate
    # Don't forget to de-reference (i.e. put the ()'s)
    # around your register--we want the actual value.
    cmpq $85,(%r11)
    je .terminate1 
    # If the value is not 85, then proceed forward 
    # We'll add an arbitrary number to our loop. 
    addq $5, lessBoring(,%r10,8)
    leaq lessBoring(,%r10,8), %rsi
    # Finally we will print out our new values so
    # that they can be seen.
    movq $1, %rdx                   
    syscall                 
    
    incq %r10
        
    jmp .loop1            # Jump back to our loop

.terminate1:

    ret  # return from our function 


# Function: Iterate
_iterate:
    movq $0,%r10    # counter
 
.loop:                  
    cmpq $7,%r10    # iterate 7 times
                        
    je .terminate       
                         
    movq $WRITE,%rax           
    movq $STDOUT,%rdi
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
    callq _setBytes         # New Addition          
    callq _writeEndLine     # New Addition
    callq _exitProgram

    popq %rbp
