# ================== Instructions ==============
# (Note: Comments start with hash marks)
# How to assemble this source code
#
# 1.) gcc hello1.s -c -o hello1.o 
# 2.) ld hello1.o -o hello1
#
# ================== Tutorial 1 ================
# In this tutorial you will print out a message
# and then exit.
#
# Learnings
# - .global and _start (the true entry point of a program)
# - .text
# - syscall (write and exit)
# - Saving our stack pointer (in rbp)when we move into a function
# - popq
#
# Note: The program works, but there is 1 tiny bug we will
# fix in the next tutorial


.global _start  # Makes a symbol 'visible' to the linker
                # For our purpose, _start is actually the
                # entry point to the program. So we are making
                # '_start' a location known to the linker
                # and then we can run a program from here.
                # https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html

.text           # This marks the section of 'instructions' or
                # source code.


_start:         # A 'symbolic label' 
                # labels have an addresses so they can be
                # jumped to from our program counter. 
                # Most assemblers require us to align these
                # to the leftmost column.

    movq %rsp, %rbp # Move our stack pointer(%rsp) to the base
                    # pointer.
                    # Remember our %rsp always points to the top of
                    # the stack, so moving it to the 
                    # base pointer(%rbp) makes everything in '_start'
                    # easier to offset from the base pointer
                    # Thus 'rbp' is the top of the stack when
                    # the function is first called.
                    # You might ask why this is necessary?
                    
                    # More info: https://practicalmalwareanalysis.com/2012/04/03/all-about-ebp/

    # Print a message to the screen
    # This link has a nice table of the syscalls
    # that the operating system has implemented
    # https://filippo.io/linux-syscall-table/
    movq $1,%rax            # Select the 'write' syscall
    movq $1,%rdi            # rdi stores the 'file descriptor'
                            # The value '1' happens to be a 
                            # file descriptor(fd) that writes 
                            # output to the terminal
    leaq .hello.str, %rsi   # 'load effective address' (lea)
                            # You can think of this like the
                            # '&' or address-of operator in the
                            # C language.
                            # This loads an address of the location
                            # of some data into a register.
                            # %rsi stores the 'buffer' or 'string'
                            # of data we want to write out.
    movq $9, %rdx           # The literal decimal value '$9' 
                            # is then stored into the register
    syscall                 # When we call the syscall, this
                            # makes a function call in the 
                            # operating system based on the 
                            # contents of %rax, and any arguments.

    # Sets up the system call to exit
    movq $60, %rax
    movq $0, %rdi
    syscall


    popq %rbp       # When we 'popq' this is returning us
                    # back to the 'top' of the stack when we
                    # started executing this function.
                    # i.e. We are restoring %rbp to the stack


################## Data Section ################
#
# I typically like to separate programs into 'data'
# sections and code(i.e. .text sections) to make them
# a little bit more managable.
# It does not matter if I have this at the top or bottom
.hello.str:
    .ascii "123456789\n"
