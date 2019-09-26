# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello15.s -c -o hello15.o 
# 2.) ld hello15.o -o hello15
#
# ================== Tutorial 15 ================
# In this tutorial we will print a big number
# in the correct direction.
#
# Learnings:
# - Iterating backwards
#
# 
# In the next lesson we will gather user input

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
                            
.data 
    bignumber:  .quad 5027 
    digits:     .byte 0,0,0,0,0,0,0,0   # New addition -- 
                                        # Storage for each
                                        # digit in our division
                                        # Stores up to 8 digits

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

# Function: Print Big Number
# The goal of this function is to print one digit at a time
# data that has been stored in a long
_printBigNumber:
    
    # Move our number in %rax.
    # %rax is where we do our division
    movq bignumber,%rax

    # This time I am going to have a counter
    # Keeping track of how many divisions I perform
    movq $0, %r15

.loop:  # Label where will loop from
    movq $10, %rdi  # What we'll divide by 
    movq $0, %rdx   # Remainder
    idivq %rdi      # Quotient stored in rax
    movq %rdx,digits(,%r15,1)  # remainder stored in 'digit'

    # convert remainder to 'ascii'
    # We add '48' to our digit to do so
    addq $48,digits(,%r15,1)
    # Move to the next digit   
    incq %r15
       
    # Check if we're done
    cmpq $0,%rax
    jne .loop
 
# Here is our second loop for printing the digits in the 
# correct order
# In this case I am just looping through the characters
# we have stored backwards from our counter.
.chars:
    decq %r15
    leaq digits(,%r15,1),%rsi 
    movq $WRITE,%rax           
    movq $STDOUT,%rdi          
    movq $1, %rdx          
    syscall                 
    
    cmpq $0,%r15
    jne .chars   
 
    ret 

# Program Entry 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _printBigNumber         
    callq _writeEndLine     
    callq _exitProgram

    popq %rbp
