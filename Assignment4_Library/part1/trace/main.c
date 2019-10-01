#include <stdio.h>
#include <time.h>
#include <unistd.h>

extern int functions_called;


void msg(){
	printf("Hello!\n");
}


int main(){

	int i;
	for(i= 0;i  <100000; ++i){
		msg();
	}
	printf("\nFunctions called : %d\n", functions_called);
	return 0;
}
