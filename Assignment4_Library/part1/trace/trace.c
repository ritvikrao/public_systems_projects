#include <stdio.h>
#include <time.h>
#include <unistd.h>

int functions_called = 0;
void* first_fun;
time_t start_of_fn;
time_t end_of_fn;
double runtime_of_fn;

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){

	printf("Function entered\n");
	if(functions_called==0){
		time(&start_of_fn);
		first_fun = this_fn;
	}
	functions_called++;

}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){
	printf("Function exited\n");
	if(first_fun==this_fn){
		time(&end_of_fn);
		runtime_of_fn = difftime(end_of_fn, start_of_fn);
		printf("Runtime of function: %.8f seconds\n", runtime_of_fn);
	}

}

