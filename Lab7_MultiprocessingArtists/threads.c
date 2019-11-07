// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char colors[64][64*3];

void paint(void* args){ 
	//printf("Artist %d is painting\n",workID);
	int x;
	int workID = (int) args;
	for(x=0; x<64*3; ++x){
		colors[workID][x]= workID;
	}
}

int main(int argc, char** argv){
	
	pthread_t pids[64];
	int i;
 	for(i =0; i < 64; ++i){
		pthread_create(&pids[i], NULL, paint, i);
	}
 
 	for(i =0; i < 64; ++i){
		pthread_join(pids[i], NULL);
	}
 

        //printf("parent is exiting(last artist out!)\n");
	
	FILE *fp;
	fp = fopen("threads.ppm","w+");
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

