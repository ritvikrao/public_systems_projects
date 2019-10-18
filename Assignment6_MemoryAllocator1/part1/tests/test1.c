// Basic test

#include <stdio.h>
#include <malloc.h>

#define DATA_SIZE 1024

int main(){

  // Allocate some data
  int* data = (int*)malloc(DATA_SIZE);
  
  // Do something with the data
  int i=0;
  for(i =0; i < DATA_SIZE; i++){
    data[i] = i;
  }

  // Free the data
  free(data);

  return 0;
}
