// gcc -std=c99 -fopenmp omp5.c -o omp5
// You fill in
#include <stdio.h>
#include <omp.h>

#define PAD 8
#define NUM_THREADS 8

static long num_steps = 100000000;
double step;

int main(){
  int i, nthreads=0;
  double pi;
  double sum[NUM_THREADS][PAD];
  
  step = 1.0/(double)num_steps;
  omp_set_num_threads(NUM_THREADS);
  
  #pragma omp parallel
  {
    int i, id, nthrds;
    double x;
    id=omp_get_thread_num();
    nthrds=omp_get_num_threads();
    if(id==0) {nthreads=omp_get_num_threads();}
    for(i =id, sum[id][0]=0.0; i < num_steps; i+=nthrds){
      x = (i+0.5)*step;
      sum[id][0] += 4.0/(1.0+x*x);
    }
  }
  for(i=0, pi=0.0; i<nthreads; i++)
  {
    pi += sum[i][0] * step;
  }
  
  printf("PI = %f\n", pi);
 
  return 0;
}