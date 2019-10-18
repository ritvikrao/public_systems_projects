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
char commands[128][BUFFER_SIZE];
int size= 0;

void help(char* args[]){
	printf("The built-in commands are:\nexit\nhelp\ncd\n");
}

void sigint_handler(int sig){
	wait(NULL);
	write(1, "mini-shell terminated\n", 35);
	exit(0);
}

void endShell(char* args[]){
	exit(1);
}

void cd(char* args[]){
	int a;
	if(args[1]==NULL){
		printf("Error: null\n");
		return;
	}
	a = chdir(args[1]);
	if(a!=0) printf("Invalid directory\n");
	return;
}

void history(char* args[]){
	printf("History:\n");
	int j = 0;
	for(j = 0; j<size; j++){
		printf("%s\n", commands[j]);
	}
	j = 0;
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
		printf("Command not found--Did you mean something else?\n");
	        exit(1);
	}else{
	        wait(NULL);
	}
	return;
}



void handleInputs(char* args[], char* builtins[], fun_ptr functions[]){
	int index = 0;
	int found = 0;
	while(builtins[index]!=NULL){
		if(strcmp(args[0], builtins[index]) == 0){
			functions[index](args);
			found = 1;
			break;
		}
	index++;
	if(index>=4) break;	
	}
	if(found==0) otherCommands(args);
	index = 0;
	return;
}

int checkBuiltins(char* args[], char* builtins[], fun_ptr functions[]){
        int index = 0;
        int found = 0;
        while(builtins[index]!=NULL){
                if(strcmp(args[0], builtins[index]) == 0){
                        functions[index](args);
                        found = 1;
                        break;
                }
	        index++;
	        if(index>=4) break;
        }
        index = 0;
        return found;
}


void handleTwoInputs(char* args1[], char* args2[], char* builtins[], fun_ptr functions[]){
	//make the pipe
	int fd[2];
	pid_t split1, split2;
	if (pipe(fd)<0){
		printf("Pipe error\n");
		return;
	}
	//fork the first command
	split1 = fork();
	if(split1<0){
		printf("Fork error\n");
		return;
	}
	if(split1 == 0){//child of first fork
		//write to start of pipe
		close(fd[0]);
		//close(STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		//close(fd[1]);
		int firstx = checkBuiltins(args1, builtins, functions);
		if(firstx==0){
			if(execvp(args1[0], args1)<0){
				printf("Incorrect command -- try again\n");
				exit(0);
			}
		}
		exit(0);
		
	}
	else{//parent
		//fork the second command
		split2 = fork();
		if(split2<0){
			printf("Fork error\n");
			return;
		}
		if(split2==0){
			//read from the pipe output to stdin
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		        //close(fd[0]);
			int secondx = checkBuiltins(args2, builtins, functions);
		        if(secondx==0){
				if(execvp(args2[0], args2)<0){
	                        	printf("Incorrect command -- try again\n");                                     
					exit(0);
	                	}
	        	}
			exit(0);	
		}
		else{
			//wait for children to wrap up
			wait(NULL);
			wait(NULL);
		}
	}
	return;
}

int main(int argc, char** argv){
	signal(SIGINT, sigint_handler);
	char inputs[BUFFER_SIZE];
	char* builtins[] = {"exit", "help", "cd", "history"};
	//typedef void (*fun_ptr) (char[]);
	fun_ptr functions[4];
	functions[0] = &endShell;
	functions[1] = &help;
	functions[2] = &cd;
	functions[3] = &history;
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
		//printf("%s\n", first);
		split = strtok(NULL, "|");
		int foundPipe = 0;
		if(split!=NULL){
			foundPipe = 1;
			strcpy(second, split);
			//printf("%s\n", second);
		}
		//tokenize arguments
		tokenize(first, args1);
		tokenize(second, args2);
		strcpy(commands[size++], args1[0]);
		size = size % 128;
		//process arguments
		if(foundPipe==0) handleInputs(args1, builtins, functions);
		//functions in case there is a pipe
		else{
		strcpy(commands[size++], args2[0]);
	          size= size % 128;	
		 handleTwoInputs(args1, args2, builtins, functions);
		}

	}	
	return 0;
}
