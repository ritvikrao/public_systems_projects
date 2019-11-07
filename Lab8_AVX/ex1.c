// For this exercise, you are going to read in data from a file called 'data.txt'
// Increment all of the values by 1 and print them to the stdout on the terminal.
// 
// You will compile this source using the following:
// clang -std=c11 -mavx2 ex1.c -o ex1prog
//
// Run as normal with: 
// ./ex1prog
//
#include <stdio.h>
#include <immintrin.h>



// print (Note, you may need to change this function or write another for your data)
void print__m256(__m256 data){
	float*f = (float*)&data;
	printf("%f %f %f %f %f %f %f %f\n", f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
}

int main(){
  FILE *fp;
  fp = fopen("data.txt", "r");
  int buff[256];
  int i;
  while(fscanf(fp, "%d", &buff[i])!=EOF){
    ++i;
  }
  fclose(fp);
  int j;
  
  for(j=0; j<i; j+=8){
    __m256 data = _mm256_set_ps(buff[j+7], buff[j+6], buff[j+5], buff[j+4], buff[j+3], buff[j+2], buff[j+1], buff[j]);
    __m256 result = 
  }

	return 0;
}
