# x86-64 Assembly 

> "Nearing Machine Code Representation"

## Introduction/Motivation

Not so long ago (in a galaxy not so far away), programmers wrote most of their code in assembly. While programmers today primarily use higher level languages (Python, C, etc), it is not uncommon to debug the assembly of your code. These higher level languages afterall typically translate down to an assembly or assembly-like language. 

If you are interested in cybersecurity and reverse engineering, folks more frequently write and analyze assembly code. For high performance applications like [games](https://www.gamasutra.com/view/news/169946/CC_low_level_curriculum_Looking_at_optimized_assembly.php), programmers may write very optimized code using assembly to get things *just* right. If you are working in hardware or an embededd device, you might also do some assembly programming, as other languages environments are too bulky to support on a small device. Even web developers are using something called 'webassembly'. Hmm, the list is getting long here--I think the point is that learning assembly has quite some relevance! Let's dig in and get some practice.

In today's lab you are going to get some practice looking at and writing assembly.

# Part 1 - Assembly - A first program

The first task is to actually just write a 'hello world' in assembly.

- Enter the following text into a file called [hello.s](./hello.s)
- ```asm
	  # Example for x86-64 processor using AT&T Style syntax
	.global _start

	.text

	_start:
		# Write a message to the screen
		mov $1, %rax
		mov $1, %rdi
		mov $message, %rsi
		mov $13, %rdx
		syscall

		# Exit the program
		mov $60, %rax
		xor %rdi, %rdi
		syscall

	message:
		.ascii "Hello, World\n"
  ```
- Save the file and then we will assemble the program using the GNU Assembler (https://en.wikipedia.org/wiki/GNU_Assembler)
  - `gcc -c hello.s`
  - This step builds an object file (.o suffix).
  - We now need to create an executable object file using our previously created hello.o file using a tool called *ld*
  - `ld hello.o -o hello`
    - Run `man ld` to learn more.
  - When this has been completed, push hello.s to your repo, and move on!

There are a few interesting things with this program.
1. First, there is a *global* symbol. The global sets up the starting point, as our program needs some entry point. You could think of '_start' as 'main' like in a C program. You can learn more here: http://web.mit.edu/gnu/doc/html/as_7.html#SEC89
2. The next directive (remember, lines that start with a '.' are directives) is .text. These are where our instructions start. https://stackoverflow.com/questions/14544068/what-are-data-and-text-in-x86
3. The next few lines are moving some values into registers. The first statement moves the immediate value $1 into register %rax. A few more lines down we see a syscall.
	  1. What is a syscall? In short, it is a call to a function built into the operating system (More here: https://www.geeksforgeeks.org/operating-system-introduction-system-call/).
	  2. To figure out which syscall it is, use this resource: https://filippo.io/linux-syscall-table/
4. Finally at the end there is a label ('message:') with a string literal (.ascii "Hello, World\n"). https://docs.oracle.com/cd/E26502_01/html/E28388/eoiyg.html

## Aside - Machine Representation of Numbers

  * Note: it may be beneficial to look at this ascii table to see how numbers and letters are represented. https://www.asciitable.com Remember, we do not have a 'text' datatype in assembly. Text instead is represented by numbers shown in the ascii table.

# Godbolt

I **strongly** recommend using the godbolt tool (https://godbolt.org/) to write and experiment with your C programs for this exercise.  The color mappings will help you see what is going on with the generated assembly. You **should** try using both godbolt and your compiler to generate assembly.

Here is an example of the Godbolt tool (and also shows part 4 of this lab)
<img src="./assembly.PNG">

# Part 2- Compiler Generated Assembly

Let us get some experience reading assembly code generated by the compiler (or godbolt)! It is actually kind of fun, you may learn some new instructions, and at the very least gain some intuition for what code the compiler is generating.

## Compiler generated assembly 1 - Swap

- Write a C program that swaps two integers(in the main body of code).
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as swap_int.s).
  - Use: `gcc -O0 -fno-builtin swap_int.c -S -o swap_int.s`
- Now modify your program to swap two long's.
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as swap_long.s).
  - Use: `gcc -O0 -fno-builtin swap_long.c -S -o swap_long.s`
- Compare each of the two assembly files using diff. See what changed.
- diff syntax
  - Use: `diff -y swap_int.s swap_long.s`
  
### Response/Observations

*The types of operations changed. Because longs are bigger than ints, operations such as movq were used instead of movl. q is used for quad words while l is used for 32-bit words.*

## Compiler generated assembly 2 - Functions

- Write a C program that swaps two integers in a **function** (You may use today's slide as a reference)
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as swap.s).
  - Use: `gcc -O0 -fno-builtin  swap.c -S -o swap.s`
- Do the instructions use memory/registers in a different way?

### Response/Observations

*The only difference was the use of the registers esi and edi to represent the arguments. The "e" registers are used because ints are 32 bits long.*

## Compiler generated assembly 3 - Static Array
- Write a C program called array.c that has an array of 400 integers in the function of main.
  - Initialize some of the values to something (do not use a loop) (e.g. myArray[0]=72; myArray[70]=56; etc)
  	- Note that it is helpful to use 'weird' numbers so you can see where they jump out.
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as array.s).
  - Use: `gcc -O0 -fno-builtin -mno-red-zone array.c -S -o array.s`
- How much are the offsets from the address?

### Response/Observations

*The offsets are based off of the base pointer. The value at index 0 is stored 400x4=1600 bytes away from the base, while the last element is just 4 bytes off of the base.*

## Compiler generated assembly 4 - Dynamic Array 

- Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.
  - Initialize some of the values to something (do not use a loop) (e.g. myArray[66]=712; myArray[70]=536; etc)
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as array2.s).
  - Use: `gcc -O0 -fno-builtin  array2.c -S -o array2.s`
- Study the assembly and think about what is different from the static array.

### Response/Observations

*The offsets are the same as the base pointer, but the method of memory management is different. In the static array, the values were placed directly at memory locations, but for the dynamic array, the address of -8(%rbp) plus the index offset was placed into %rax, then the value was placed at that address.*

## Compiler generated assembly 5 - Goto
The C programming language has a 'goto' command, search how to use it if you have not previously.
(Note that the usage of 'goto' is strongly discouraged in your programs--even mentionining such a keyword may anger programmers due to the difficulty of following many goto statements!)

- Write a C program using the goto command and a label.
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as goto.s).
  - Use: `gcc -O0 -fno-builtin  goto.c -S -o goto.s`
- Observe what kind of jmp statement is inserted.

### Response/Observations

*Because I used an if==0 to call the goto, there is a jne (not equal) statement used to not call the goto and there is a jmp (unconditional) used to call the goto.*

## Compiler generated assembly 6 - For-loops
- Write a C program using a for-loop that counts to 5.
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as for.s).
  - Use: `gcc -O0 -fno-builtin  for.c -S -o for.s`
- Observe where the code goes for the condition statement (at the start or at the end?).

### Response/Observations

*In assembly, there is first an unconditional jump to a loop location (.L2), then there is a comparison followed by a jle (less than or equal to) to some .L3, which is where the incrementing happens. This means that the condition statement is at the end of the increment loop.*

## Compiler generated assembly 7 - Switch Statements

- Write a C program using a switch statement (Sample here)[https://www.tutorialspoint.com/cprogramming/switch_statement_in_c.htm].
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as switch.s).
  - Use: `gcc -O0 -fno-builtin switch.c -S -o switch.s`
- See what code a switch statement generates. Is it optimal?

### Response/Observations

*The switch variable is first compared placed into the %eax register, and then is successively compared to each case, jumping to the corresponding case if equal. Ultimately, it does not seem very optimal when compared to an if-else chain.*

## Compiler generated assembly 8 - Add Function

- Write a C program that calls an add function(long add(long a, long b).
  - Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as add.s).
  - Use: `gcc -O0 -fno-builtin add.c -S -o add.s`
- Observe the outputs
- Observe arguments put into registers
- Observe where 'popq' is called.

### Response/Observations

*The result of the add function is ultimately stored on the stack. The add arguments are placed into rsi and rdi, then in the add function they are moved into rdx and rax to be added. popq is called within the add function, which pops the top of the stack (the addition result) into the rbp register.*

# Part 3 - Check your understanding

Provided in Part 3 is an assembly file called [barebones.s](./barebones.s) which contains a minimal assembly program--very similar to part 1. Fill in the questions to make sure you understand all of the parts of an assembly program. Because every instruction in assembly matters, it's important to pay attention to the details of what is going on. I think this is also one of the reasons why assembly programming is fun and very satisfying when things work however!

# More resources to help

- Matt Godbolt has written a great tool to help understand assembly generated from the compiler. 
  - https://godbolt.org/
- An assembly cheat sheet from Brown
  - https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf
- MIT Cheat sheet
  - http://6.035.scripts.mit.edu/sp17/x86-64-architecture-guide.html

# Deliverable

1. Complete the [hello.s](./hello.s) world from part 1
2. For part 2, add your .S files that you have generated to this repository.
  - Note this submission will be auto graded for completion (i.e. save the file names as shown).
  - Add your observations (brief 1-2 sentences) in the appropriate response/observations section for each code in this readme file.
3. Answer the questions in [barebones.s](./barebones.s) for part 3
  

# Going Further

- (Optional) Try the objdump example to read the disassembly from your programs executables. Observe how close the output is to the compiler generated output.
