In a brief sentence or two,  modify this file with your answers.

1. In each of the programs what was the bug?  *For prog, the bug was a seg fault when movzbl was called from (%rax) to %eax. For prog1, the bug was a seg fault when movl was called from $0x1f4 to (%rax).*
2. What file and lines did the bugs occur? *For prog, the error was at prog2.c:57. For prog1, the error was at seg.c:15.*
3. What would your educated guess be for a fix for each bug? *For prog, the solution is to avoid having to access the null pointer. For prog1, the solution is to delete line 15, as it does not appear to serve any purpose.*
