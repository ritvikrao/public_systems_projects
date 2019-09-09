// Add your program here!
#include <stdio.h>

double power(double base, double n){
	if(n==0) return 1;
	return base*power(base, n-1);
}

int main(){
	for(int i=1; i<=10; i++){
		printf("2^%d=%f\n", i, power(2, i));
	}
	return 0;
}
