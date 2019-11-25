//Implementation of quicksort
//Uses the choice of the last element as the pivot
//Parallelizes the quicksort branches and the random number generation
//However, due to cost of branching off, quicksort is slower with parallelization
//may be faster if element size is increased

#define ARRAY_SIZE 10000
#define ARRAY_RANGE 1000000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int nums[ARRAY_SIZE];

void populateArray(){
	srand(time(NULL));
	int i;
	#pragma omp parallel
	{
	#pragma omp for
	for(i=0; i<ARRAY_SIZE; ++i){
		nums[i]=rand()%ARRAY_RANGE;
	}
	}
	return;
}

void printArray(){
	int i;
	for(i=0; i<ARRAY_SIZE; ++i){
		printf("%d\n", nums[i]);
	}
	return;
}

int split(int l, int r){
        int data = nums[r];
        int i = l;
        int j;
        int temp;
        for(j=l; j<r; ++j){
                if(data > nums[j]){
                        temp = nums[i];
                        nums[i] = nums[j];
                        nums[j] = temp;
                        ++i;
                }
        }
        temp = nums[r];
        nums[r] = nums[i];
        nums[i] = temp;
        return i;
}

void quicksort(int l, int r){
	if(l < r){
		int s = split(l, r);
		#pragma omp parallel
		{
			quicksort(l, s-1);
			quicksort(s+1, r);
		}
	}
	return;
}

int main(){
	populateArray();
	quicksort(0, ARRAY_SIZE-1);
	printf("Printing array:\n");
	printArray();
	return 0;
}
