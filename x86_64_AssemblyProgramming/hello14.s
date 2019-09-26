# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello14.s -c -o hello14.o 
# 2.) ld hello14.o -o hello14
#
# ================== Tutorial 14 ================
# In this tutorial we will print a big number
# backwards...We'll fix it in the next tutorial!
#
# Learnings:
# - Printing one digit at a time
# 
# In the next lesson we will print
# our numbers out properly.

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
    digit:      .byte 0     # New addition -- handy
                            # temporary storage for us to use
                            # for our division

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
    
    # Strategy Now we are going to have to divide out each digit
    # one at a time from our quad.
    # We can use a loop to do this.
    # We will know when we are done when the quotient is 0.
    # It can also be helpful to keep track of how many
    # division we have performed    

    # Move big number into a register
    # %rdx happens to be where the number we
    # divide is stored.
    # https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf

    # The number we want to divide by each time must
    # be in %rax
    movq bignumber,%rax

.loop:  # Label where will loop from
    movq $10, %rdi  # We are going to divide by '10' each
                    # time.
    movq $0, %rdx   # Remainder of the division instruction
                    # is stored in rdx, so zero it out every
                    # loop.
    idivq %rdi      # Perform our division
                    # Quotient is stored in rax
    mov %rdx,digit  # Each time we will print out the
                    # remainder, and save the quotient
                    # for the next iteration
                    # I will reserver a byte of storage
                    # for this storage
    movq %rax,bignumber # Store back in 'bignumber'
                        # the remaining quotient
                        # This is not 'optimal' but simple
                        # for us to do in this example
                        # It is not optimal, because we
                        # are causing a side effect, but
                        # I want to save it somewhere before
                        # I use %rax again.

    # convert remainder to 'ascii'
    # We add '48' to our digit to do so
    addq $48,digit
    leaq digit,%rsi 
    movq $WRITE,%rax           
    movq $STDOUT,%rdi          
    movq $1, %rdx          
    syscall                 
                 
    # Do a comparison that checks if what is in memory in
    # bignumber is 0. If it is, then we are done, otherwise
    # we continue our division.
    movq bignumber,%rax

    cmpq $0,%rax
    jne .loop
 
    ret 

# Program Entry 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _printBigNumber         
    callq _writeEndLine     
    callq _exitProgram

    popq %rbp
