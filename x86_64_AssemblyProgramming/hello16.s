# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello16.s -c -o hello16.o 
# 2.) ld hello16.o -o hello16
#
# ================== Tutorial 16 ================
# In this tutorial we are going to just read in a 
# single digit from the terminal. We will then
# print a message if the user enters a 1 or not a 1.

# Learnings:
# - new system call for reading data
# - cmpq with user input   
# 
# In the next lesson we will ????  

.global _start  

################## Data Section ################

# Useful constants
.equ STDIN          ,0      # New Addition
.equ STDOUT         ,1
.equ READ           ,0      # New Addition
.equ WRITE          ,1
.equ EXIT           ,60
.equ EXIT_SUCCESS   ,0 

.hello.str:
    .asciz "starting!\n"    

.one.str:
    .asciz "You input 1!!!!!\n"    
.notone.str:
    .asciz "Did not input 1!\n"    

.newline:                   
    .ascii "\n"             
                        
.data 
    userinput:  .byte 0     # New addition a byte where we
                            # Will store user input
                                        
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

# Function: Takes user input and stores it in
# memory somewhere so we can later print it out.
_readSingleNumber:
    
    movq $READ,%rax     # Now we are using a syscall for read   
    movq $STDIN,%rdi    # We are reading information from 
                        # standard input now 
    movq $0,userinput   # Lets zero out our memory
                        # We have no gaureentee at this point
                        # so it is safe to do this.
    movq $userinput,%rsi # Store our result in a single byte  
    movq $1, %rdx       # Because we only have a single
                        # byte of storage, we need a buffer
                        # size of only 1.
    syscall                  
    
    # It will be useful to also compare input  
    # so we can execute different branches of code
    # based off of the input. 
    movq $WRITE,%rax           
    movq $STDOUT,%rdi          
   
    # Let's move userinput into a register as well
    # it's a little easier to debug with tools like
    # gdb so we can confirm the value
    # (So you can just monitor the value %r8)
    # (Alternatively you can do 'x ADDRESS' of userinput
    # (It is also handy to do print *($r8) in gdb to
    #  see the value)
    leaq userinput, %r8
    cmpq $0x31,(%r8)
    jne .notone
    
    leaq .one.str, %rsi
    jmp .result
.notone:
        leaq .notone.str, %rsi  
.result:   
    movq $18, %rdx                   
    syscall                 

ret            

# Program Entry 
_start:         

    movq %rsp, %rbp
   
    callq _writeMessage
    callq _readSingleNumber 
    callq _writeEndLine     
    callq _exitProgram

    popq %rbp
