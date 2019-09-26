# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello13.s -c -o hello13.o 
# 2.) ld hello13.o -o hello13
#
# ================== Tutorial 13 ================
# In this tutorial we will 'try to' print a big number
#
# Learnings:
# - Why we cannot just print an integer
# 
# In the next lesson we will more successfully print
# out our big number, see this lesson for the skeleton code

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
    # The first thing we need to decide is the datatype
    # Let's store a .quad so we can have some reasonably
    # large number stored.
    bignumber: .quad 5027 

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
_printBigNumber:

    movq $WRITE,%rax           
    movq $STDOUT,%rdi          
    leaq bignumber, %rsi    # Unfortunately here we cannot just
                            # print out the big number. 
                            # It would be nice, but assembly
                            # does not quite understand.
                            # It is worth seeing in gdb
                            # what is actually put in %rsi!
    movq $80, %rdx          # Note: I guess that 80 will be 
                            # enough arbitrarily as a buffer
                            # size                   
    syscall                 

    ret
 

# Program Entry 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _printBigNumber   # New Addition          
    callq _writeEndLine     
    callq _exitProgram

    popq %rbp
