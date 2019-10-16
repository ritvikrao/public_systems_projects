// Implement a lexer parser in this file that splits text into individual tokens.
// You may reuse any functions you write for your main shell.
// The point is that you get something small working first!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	char* input = argv[1];
	char* parseable = strtok(input, " ");
	while(parseable!=NULL){
		printf("%s\n", parseable);
		parseable = strtok(NULL, " ");
	}
	return 0;
}
