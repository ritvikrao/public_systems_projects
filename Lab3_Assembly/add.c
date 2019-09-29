// Write a C program that calls an add function(long add(long a, long b).

#include <stdio.h>

long add(long a, long b){
	return a + b;
}

int main(){
	long a = add(5, 7);
	return 0;
}
