// Implement your shell in this source file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define BUFFER_SIZE 80

typedef void (*fun_ptr) (char* args[]);

void help(char* args[]){
	printf("The built-in commands are:\nexit\nhelp\ncd\n");
}

void sigint_handler(int sig){
	write(1, "mini-shell terminated\n", 35);
	exit(0);
}

void endShell(char* args[]){
	exit(0);
}

void cd(char* args[]){
	//TODO
	int a;
	a = chdir(args[1]);
	printf("%d\n", a);
	return;
}

void tokenize(char input[], char* args[]){
	char* split = strtok(input, " \t\n");
	int i = 0;
	while(split!=NULL){
		args[i++] = split;
		split = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return;
}

void otherCommands(char* args[]){
	char *envp[] = {"HOME=/", "PATH=/bin:/usr/bin", NULL};
	if(fork()==0){
		execvp(args[0], args);
		printf("should not get here\n");
	        exit(1);
	}else{
	        wait(NULL);
	}
	return;
}

void handleInputs(char* args[], char* builtins[], fun_ptr functions[]){
	int i;
	int found = 0;
	while(builtins[i]!=NULL){
		if(strcmp(args[0], builtins[i]) == 0){
			functions[i](args);
			found = 1;
			break;
		}
	i++;
	if(i>=3) break;	
	}
	if(found==0) otherCommands(args);
	return;
}

int main(int argc, char** argv){
	signal(SIGINT, sigint_handler);
	char inputs[BUFFER_SIZE];
	char* builtins[] = {"exit", "help", "cd"};
	//typedef void (*fun_ptr) (char[]);
	fun_ptr functions[3];
	functions[0] = &endShell;
	functions[1] = &help;
	functions[2] = &cd;
	functions[3] = NULL;
	while(1){
		//start by printing line prompt and reading input
		printf("mini-shell> ");
		fgets(inputs, BUFFER_SIZE, stdin);
		//then process the inputs by putting them into string arrays
		char* split= strtok(inputs, "|");
		char first[BUFFER_SIZE];
		char* args1[BUFFER_SIZE];
		char second[BUFFER_SIZE];
		char* args2[BUFFER_SIZE];
		strcpy(first, split);
		printf("%s\n", first);
		split = strtok(NULL, "|");
		if(split!=NULL){
			strcpy(second, split);
			printf("%s\n", second);
		}
		//tokenize arguments
		tokenize(first, args1);
		tokenize(second, args2);
		//process arguments
		handleInputs(args1, builtins, functions);
	}	
	return 0;
}
