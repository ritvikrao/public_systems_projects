.global _start  # Makes a symbol 'visible' to the linker

.is2.str:
    .asciz "it is 2!\n"    

.isnot2.str:
    .asciz "not  2 !\n"    

.text            

_start:        
 
    movq %rsp, %rbp # Move our stack pointer(%rsp) to the base
   
    # Write system call 
    movq $1,%rax            
    movq $1,%rdi            
    movq $10, %rdx                            

    # Show how cmpq works
    movq $2,%r15
    cmpq $2,%r15
    jne .not2    
    
    leaq .is2.str, %rsi   
    jmp .call                            
.not2:
    leaq .isnot2.str, %rsi                               
.call:
    
    syscall                 
    
# Sets up the system call to exit
    movq $60, %rax
    movq $0, %rdi
    syscall
    popq %rbp
