// Implement your part 1 solution here
// gcc vfork.c -o vfork

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void paint(int workID){ 
	printf("Artist %d is painting\n",workID);
}

int main(int argc, char** argv){

        int numberOfArtists = 8;
	
	pid_t pid;

	int* integers = malloc(sizeof(int)*8000);

	int i;
	for(i =0; i < numberOfArtists; i++){

		pid = fork();

	if(pid== 0){
		paint(i);
		exit(1);
	}

        }
	
	pid_t wpid;
        int status = 0;
        while ((wpid = wait(&status)) > 0);

        printf("parent is exiting(last artist out!)\n");
	
	free(integers);
	return 0;
}
