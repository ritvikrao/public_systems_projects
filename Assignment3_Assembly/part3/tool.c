// Implement your cycle count tool here.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

int main(int argc, char** argv){
	FILE *fp;
	fp = fopen(argv[1], "r");
	char buff[255];
	char *p;
	int add=0;
	int sub=0;
	int mul=0;
	int div=0;
	int mov=0;
	int lea=0;
	int push=0;
	int pop=0;
	int ret=0;
	int total=0;
	while(fgets(buff, 255, (FILE*)fp)){
		p = strchr(buff, '#');
		if(p!=NULL){
			int index = p-buff;
			buff[index] = '\0';
		}
		p = strtok(buff, "\n\t");
		while(p!=NULL){
			//printf("%s\n", p);
			char four[] = "";
			strncat(four,p,4);
			int j;
			for(j=0; j<4; j++){
				four[j] = tolower(four[j]);
			}
			//printf("%s\n", four);
			int i;
			i = strcmp(four, "push");
                        if(i==0){
                                push = push + 1;
				total++;
                        }
                        i = strcmp(four, "imul");
                        if(i==0){
                                mul = mul + 1;
				total++;
                        }
                        i = strcmp(four, "lmul");
                        if(i==0){
                                mul = mul + 1;
				total++;
                        }
                        i = strcmp(four, "idiv");
                        if(i==0){
                                div = div + 1;
				total++;
                        }
                        i = strcmp(four, "ldiv");
                        if(i==0){
                                div = div + 1;
				total++;
                        }
			char three[] = "";
			strncat(three,four,3);
			for(j=0; j<3; j++){
                                three[j] = tolower(three[j]);
                        }
			i = strcmp(three, "mov");
			if(i==0){
				mov = mov + 1;
				total++;
			}
			i = strcmp(three, "lea");
                        if(i==0){
                                lea = lea + 1;
				total++;
                        }
			i = strcmp(three, "add");
                        if(i==0){
                                add = add + 1;
				total++;
                        }
			i = strcmp(three, "sub");
                        if(i==0){
                                sub = sub + 1;
				total++;
                        }
			i = strcmp(three, "mul");
                        if(i==0){
                                mul = mul + 1;
				total++;
                        }
			i = strcmp(three, "div");
                        if(i==0){
                                div = div + 1;
				total++;
                        }
			i = strcmp(three, "pop");
                        if(i==0){
                                pop = pop + 1;
				total++;
                        }
			i = strcmp(three, "ret");
                        if(i==0){
                                ret = ret + 1;
				total++;
                        }
			p = strtok (NULL, "\n\t");
		}
	}
	printf("mov: %d\n", mov);
	printf("lea: %d\n", lea);
	printf("add: %d\n", add);
	printf("sub: %d\n", sub);
	printf("mul: %d\n", mul);
	printf("div: %d\n", div);
	printf("pop: %d\n", pop);
	printf("ret: %d\n", ret);
	printf("push: %d\n", push);
	printf("\nTotal instructions: %d\n", total);
	int cycles = mov+lea+6*add+6*sub+5*mul+50*div+pop+2*ret+push;
	printf("Total cycles: %d\n", cycles);
	fclose(fp);
	return 0;
	
}

