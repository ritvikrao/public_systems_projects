(In a brief sentence or two)

1. What do you notice that is different about the functions(*Hint* search for foo)? 

*The main function is referred to as just main, while foo is called _Z3fooii.*

2. Do we have some information that could be useful for LD_PRELOAD if we were writing a function to override that function? That is, what information do we need to use to name a function?

*We are given that foo is a global/external symbol and a function, and we are also given foo's size. The g and F tags tell us that we can externally override foo.*

3. How many add_generic functions are there? What is your best guess for what the compiler is doing behind the scenes to implement the 'templating' feature?

*There are 4 add_generic functions. Behind the scenes, the compiler creates a new add_generic function if a new datatype is used. For example, if ints are passed, the compiler will create an int version of the function.*
