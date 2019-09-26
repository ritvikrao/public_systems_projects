# ================== Instructions ==============
# How to assemble this source code
#
# 1.) gcc hello9.s -c -o hello9.o 
# 2.) ld hello9.o -o hello9
#
# ================== Tutorial 9 ================
# In this tutorial you will initialize some data
# We will learn how to store data, and learn about 
# the .bss section and the .data section.
#
# Learnings:
# - bss section
# - data section
# - More information on global
# 
# In the next lesson we will iterate through our data

.global _start  # Note that when we mark a symbol as 'global'
                # This is exposing a symbol to the linker so
                # that it knows it exists. '_start' is a symbol
                # that must exist, and it marks the entry point
                # of our assembly program.

################## Data Section ################

# Useful constants
.equ STDOUT, 1
.equ WRITE, 1
.equ EXIT,60
.equ EXIT_SUCCESS,0 

.hello.str:
    .asciz "123456789\n"

.bss            # Here I am creating a another section-- .bss
                # This section is specifically for static or global
                # variables that are initialized to zero.
            
    zeros:  .skip 16    # Within the bss section, we are going 
                        # to create some storage for 16 bytes 
                        # that are set to 0.
.data           # Here I am creating another section-- .data
                # This section is similar and adjacent to the
                # .bss section, except that I can explicitly
                # set the values to something.
                # The value after the comma is what value
                # will be filled with these bytes. 
    ones:   .skip 16, 1 # This will fill 16 bytes with '1' 

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
