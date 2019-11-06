// Implement your part 1 solution here
// gcc vfork.c -o vfork

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char colors[64][64*3];

void paint(int workID){ 
	//printf("Artist %d is painting\n",workID);
	int x;
	for(x=0; x<64*3; ++x){
		colors[workID][x]= workID;
	}
}

int main(int argc, char** argv){

        int numberOfArtists = 64;
	
	pid_t pid;

	int i;
	for(i =0; i < numberOfArtists; i++){

		pid = vfork();

	if(pid== 0){
		paint(i);
		exit(1);
	}

        }
	

        //printf("parent is exiting(last artist out!)\n");
	
	FILE *fp;
	fp = fopen("vfork.ppm","w+");
	fputs("P3\n",fp);
	fputs("64 64\n",fp);
	fputs("255\n",fp);
	int j;
	for(i =0; i < 64;i++){
		for(j =0; j < 64*3; j++){
			fprintf(fp,"%d",colors[i][j]);
			fputs(" ",fp);		
		}
		fputs("\n",fp);
	}
	fclose(fp);
	return 0;
}
