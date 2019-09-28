## Static Analysis 
 
Our Cycle Count Tool is what we call a 'static analysis'. That is, it uncovers information about our programs before it is running (during compile-time). Given that our tool uncovers information before the program, what is (at least) one pro of this, and one con you can think of?

Pro:
1. *It is pretty easy to calculate and gives a rough estimate that is good for most applications.*

Con:
1. *It does not take loops/other dynamic features into account and is therefore less accurate than dynamic analysis.*

## Dyanmic Analysis

The opposite of a static analysis is a dynamic analysis. Dynamic analysis tools record and return information about programs that are in the process or have finished executing. An example of a dynamic analysis tool is [valgrind](http://valgrind.org/). What do you think a pro and con of dynamic analysis would be?

Pro:
1. *It is more accurate than static analysis as it takes into account runtime factors.*

Con:
1. *It is much more difficult to do dynamic analysis.*
