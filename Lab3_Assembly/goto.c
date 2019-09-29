// Write a C program using the goto command and a label.

#include <stdio.h>

int main(){
	int x = 0;
	if(x==0) goto label;
	printf("Hello\n");
	label: printf("Hello\n");
	return 0;
}
