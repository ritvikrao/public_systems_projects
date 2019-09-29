// Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.

#include <stdlib.h>

int main(){
	int *myArray = (int*) malloc(400*sizeof(int));
	myArray[0] = 72;
	myArray[70] = 56;
	myArray[250] = 15;
	myArray[399] = 5;

}
