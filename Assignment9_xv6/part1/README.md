# xv6

# Logistics

For this assignment, you are working on the latest version of xv6 that you have downloaded locally to your computer from previous lecture/lab.  Please see the [InstallationInstructions.md](./InstallationInstructions.md) if you have not yet been able to successfully install and run xv6 in the QEMU emulator for your operating system.

# Introduction

In this assignment we will continue looking through xv6. First we will investigate the source code of the operating system, and then we will make further modifications.

1. A handy resource will be to use grep
	- `grep -ir "proc" .` for example.
	- As a reminder, it is handy to look at both the '.h' and '.c' files.
	- [grep examples](https://www.linuxtechi.com/linux-grep-command-with-14-different-examples/)
2. Another way to browse the source (and can be helpful for jumping to function definitions) is to use this doxygen generated documentation.
	- https://course.ccs.neu.edu/cs3650/unix-xv6/	
	- I recommend using grep and this above documentation to jump around.
3. A final useful resource for this exercise is located here -- [xv6-rev10.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/xv6-rev10.pdf)

# Part 1 - Exploration Questions

In this part you will answer some questions about the xv6 operating system. Modify this README.md file directly with your answers.
Processes:

### Processes

1. In which file does the the process table exist? *your answer here*
2. What is the struct name of the process table? *your answer here*
3. When there is a context switch from one process to another, where are the values of the registers of the old process saved? *your answer here*
4. What are the 6 possible states of a process?  Also, give a brief phrase describing the purpose of each state.
	1. *your answer here*
	2. *your answer here*
	3. *your answer here*
	4. *your answer here*
	5. *your answer here*
	6. *your answer here*
5. What is the function that does a context switch between two processes? *your answer here*
6. Explain how the context switch function works (Note, this "function" *may* be in an assembly file). *your answer here*

### Process Startup and running

1. What function from 'main.c' creates the first user process? *your answer here*
2. Where do we actually start running processes in our code? That is, what is the actual function that has an infinite loop for running processes? *your answer here*

### Files and File Descriptors:

In class, we have briefly used and talked about files and file descriptors.  We have not yet discussed i-nodes.  For these questions, you can think of an i-node as a location on disk that has the "table of contents" for all information about a file.

In these questions, we will follow the chain of control from open() to a file descriptor, to a "file handle" (including the
offset into the file), to the i-node. Note: What I call a "file handle", UNIX xv6 calls a "struct file".

1.  The function 'sys_open()' returns a file descriptor 'fd'. To do this, it opens a new file handle 'filealloc()', and it allocates a new file descriptor with 'fdalloc()'. Where is the file descriptor allocated?  
	- Hint: You will see that the file descriptor is one entry in an array in an important struture you have already looked at.
	- *your answer here*
2. What is the algorithm used to choose which entry in the array to use for the new file descriptor?
    	- Note: The name 'NOFILE' means "file number".  "No." is sometimes used as an abbreviation for the word "number".
	- *your answer here*
3.  As you saw above, the file descriptor turned out to be an index in an array.  What is the name of the array for which the file descriptor is an index?  Also, what is the type of one entry in that array.
	- *your answer here*
4.  The type that you saw in the above question is what I was calling a "file handle" (with an offset into the file, etc.). What is the name of the field that holds the offset into the file? We saw it in the function 'sys_open()' (*hint, it's towards the bottom of the function*).
	- *your answer here*
5.  The file handle type was initialized to 'FD_INODE' in the sys_open function.  What are the other types that it could have been initialized to (*hint, look for the file struct*)?
	- *your answer here*
    
# Part 2 - Proc Priority modification

We have spent time in class talking about how we do not have control over how processes threads are scheduled, and the order in which they execute. Sometimes the operating system needs to interrupt for example to perform some task (e.g. a new device is plugged in, some data is ready to be read from disk, etc.). However, a question remains of how are processes and threads actually scheduled. The answer is based on a 'scheduling' algorithm, and we can begin exploring this idea by modifying a structure you saw a few times in Part 1.

## Task 1 - Implementing priorities

Below is the 'proc' data structure found in the proc.h file. The `struct proc` as we know, contains information about processes running in our operating system.

```c
// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)
};
```

### Modifying Proc with priorities

1. Add an `int priority;` to the struct above found in proc.h.
	- You might also add a comment along the lines of `// stores the processes priority (i.e. importance) for running`
	- Note: The higher the value, the more important a process is.
2. Now since we have added an additional field to our proc structure, we also need to modify what happens when we iniitalize a new process.
	- Find the function 'allocproc' - which stands for allocate process.
	- Under the 'found:' label, and after `p->pid=nextpid++;` add `p->priority=10; // This is around line 90`

### Testing our priorities

1. Now, it is up to you to create a system call, called `cps`. cps stands for 'current process state'
	- The `int cps()` command should print out the following information about a process.
		- I implemented 'cps' in proc.c 
	- It will return the value '22' matching its system call.
		- e.g. 
		```c
			struct proc *p;
			// Enable interrupts
			sti();
			
			// Maybe acquire some lock?
			// Maybe a loop here?
				if(p->state == SLEEPING)
					cprintf("%s \t %d \t SLEEPING \t %d\n", p->name, p->pid, p->priority);
				else if(p->state == RUNNING)
					cprintf("%s \t %d \t RUNNING \t %d\n", p->name, p->pid, p->priority);
				else if(p->state == RUNNABLE)
					cprintf("%s \t %d \t RUNNABLE \t %d\n", p->name, p->pid, p->priority);
					
			return ??
		```
	- Your 'sys_cps()' command will merely calls cps. You can do this in sysproc.c
	- Don't forget to modify syscall.c
	- Don't forget to modify usys.S
	- Note: I used the 'scheduler' as inspiration for figuring out how to loop through all of the processes.
	- Note: You can use your previous lab as an additional resource to make sure all of the steps are implemented.
2. Next, write a program called 'mycommand' that will make a call to 'cps()'
	- This can be a very simple program.
3. Go ahead and run 'make' again, and then run your xv6.
	- Now run the 'cps' command on the terminal to see the processes running and their priority.
	- Congratulations on your first modification to the xv6 operating system!
	- Note: You can use `ps -c` on your regular unix terminal to get a reference, where 'PRI' is a priority.
    
# Deliverable

- Run `make clean` on your xv6 directory 
	- (The reason is we do not want large .img files--we will build your xv6 from source with your modifications)
	- Then upload your xv6 repository to github.

# Rubric


<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>50% - Part 1</td>
      <td align="left"><ul><li>Based on correctness of written responses</li></ul></td>
    </tr>
    <tr>
      <td>50% - Part 2</td>
      <td align="left"><ul><li>A working 'mycommand' program that prints out processes with a default priority value of 10.</li></ul></td>
    </tr>          
  </tbody>
</table> 


### Glossary and Tips
1. Commit your code changes to the repository often, this is best practice.
2. Do not commit your .o file or your executable file to the repository, this is considered bad practice!
3. On Functionality/Style
	1. You should have comments in your code to explain what is going on, and use good style (80 characters per line maximum for example, functions that are less than 50 lines, well named variables, well named functions etc.).

# Going Further

- Implement a priority queue that runs processes based on their priority number. Every timeslice a process gets, it should then decrement its priority, and then reset its priority to its 'initial' priority for when it was created.
	- (You can of course modify this heuristic as you like, but think about how to create a 'fair' scheduler).

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- xv6 is based on the original UNIX, Sixth Edition (also called [Version 6 UNIX](https://en.wikipedia.org/wiki/Version_6_Unix))
	- There is a commentary for the original v6 here: https://en.wikipedia.org/wiki/Lions%27_Commentary_on_UNIX_6th_Edition,_with_Source_Code
