// Take a look at some of the previous examples to create your own program!

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

	char* myargv[16];	
	myargv[0]="/bin/ls";	
	myargv[1]="-F";		
	myargv[2]=NULL; 	
				
	if(fork()==0){		
		
		execve(myargv[0],myargv,NULL);
		printf("Child: Should never get here\n");
		exit(1);
	}else{
		wait(NULL); 
	}
	
	myargv[0]="/bin/echo";
	myargv[1]="testing";
	myargv[2]=NULL;

	if(fork()==0){


                execve(myargv[0],myargv,NULL);
                printf("Child: Should never get here\n");
                exit(1);
        }else{
                wait(NULL);
        }

	 myargv[0]="/bin/nl";
        myargv[1]="example1.c";
        myargv[2]=NULL;

        if(fork()==0){


                execve(myargv[0],myargv,NULL);
                printf("Child: Should never get here\n");
                exit(1);
        }else{
                wait(NULL);
        }


	return 0;
}
