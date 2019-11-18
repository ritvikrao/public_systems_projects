#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char** shared_data;

void* some_thread1(){
  char* string1 = (char*) malloc(5*sizeof(char));
  strcpy(string1, "hello");
  shared_data[0] = string1;
}

void* some_thread2(){
  char* string2 = (char*) malloc(5*sizeof(char));
  strcpy(string2, "there");
  shared_data[1] = string2;
}

int main(){
  shared_data=malloc(2*sizeof(char*));
  int i;
  pthread_t tids[2];
  pthread_create(&tids[0], NULL, some_thread1, NULL);
  pthread_create(&tids[1], NULL, some_thread2, NULL);
  pthread_join(tids[0], NULL);
  pthread_join(tids[1], NULL);
  free(shared_data[0]);
  free(shared_data[1]);
  free(shared_data);
  return 0;
}
