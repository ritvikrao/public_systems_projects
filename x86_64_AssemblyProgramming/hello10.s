# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello10.s -c -o hello10.o 
# 2.) ld hello10.o -o hello10
#
# ================== Tutorial 10 ================
# In this tutorial you will iterate through some
# data that you have initialized in the _iterate
# function.
#
# Learnings:
# - I am formatting the program a little neater
# - You will learn about loops in assembly
# - How to iterate through a collection of data
# 
# In the next lesson we will use a different data type
# so that you can understand the offset in the area
# there will only be a few changes.

.global _start  

################## Data Section ################

# Useful constants
.equ STDOUT         ,1
.equ WRITE          ,1
.equ EXIT           ,60
.equ EXIT_SUCCESS   ,0 

.hello.str:
    .asciz "starting!\n"    # New addition -- a new message

.newline:                   # New addition -- a handy
    .ascii "\n"             # newline character stored in
                            # memory so we can always write
                            # it out.

.bss           
    zeros:  .skip 16   

.data 
    ones:    .skip 7,49     # Why the value '49 here?
                            # This is instruction is creating
                            # '7' bytes all filled with 49.
                            # '49' happens to be the ascii
                            # character for '1'

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
# This is just a handy little function to have
# in order to clean up our output.
_writeEndLine:

    movq $WRITE,%rax           
    movq $STDOUT,%rdi          
    leaq .newline, %rsi  
    movq $1, %rdx                   
    syscall                 
    
    ret            

# Function: Iterate
# In this function we are going to write out each byte stored
# in our data from 'ones'
_iterate:
    movq $0,%r10        # %r10 is going to hold a 'counter'
                        # for us. We'll start counting from
                        # zero. 
                   
.loop:                  # Create a label for our loop
    # Our strategy is going to be to loop '7' times, because
    # we have seven pieces of data.

    # What this comparison will do each iteration is
    # %r10 == 7? 
    cmpq $7,%r10        # Compare our counter with 7
                        # The first iteration (i.e. is 0 != 7)
    je .terminate       # If we are equal to '7' items, 
                        # then terminate our loop
 
    # In order to write out some data, we perform
    # the same system call we have been doing.
    movq $WRITE,%rax           
    movq $STDOUT,%rdi
    # Now grab the first byte in our long
    # Effectively this is grabbing 
    # This line is a little tricky
    # 
    # It is essentially loading the address of 'ones'
    # into %rsi. That is, because 'ones' is a collection of
    # bytes, it is really an array. And we are loading the
    # address of the first element of that array.
    # We are then offsetting by %r10 
    # (%rsi = 0 the first iteration), and our offset
    # between data is '1' byte.
    # 
    # In C code it looks like:
    # %rsi = ones[%r10] // where '%rsi is our counter
    #                   // The offset when we increse rsi is
    #                   // 1 byte at a time
    leaq ones(,%r10,1), %rsi
    movq $1, %rdx                   
    syscall                 
    # Increment our offset %r10 by 1, thus we will scan
    # the next byte.
    incq %r10
        
    jmp .loop            # Jump back to our loop

.terminate:

    ret  # return from our function 


# Program Entry 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _iterate          # New Addition
    callq _writeEndLine     # New Addition
    callq _exitProgram

    popq %rbp
