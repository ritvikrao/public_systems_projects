// Implement a lexer parser in this file that splits text into individual tokens.
// You may reuse any functions you write for your main shell.
// The point is that you get something small working first!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseFunction(char* input){
	char* function = strtok(input, " ");
	while(function!=NULL){
		printf("%s\n", function);
		function = strtok(NULL, " ");
	}
}

int main(int argc, char** argv){
	char* input = argv[1];
	parseFunction(input);
	return 0;
}
