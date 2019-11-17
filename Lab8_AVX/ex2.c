// Simple Caeser Shift decrypt
// 
// Load the data from data2.txt. Increment all of the values by 1 then output
// the results to stdout on the terminal.
// 
// You will compile this source using the following:
// clang -std=c11 -mavx2 ex2.c -o ex2prog
//
// Run as normal with: 
// ./ex2prog
//
#include <stdio.h>
#include <immintrin.h>



// print (Note, you may need to change this function or write another for your data)
void print__m256(__m256 data){
	char*f = (char*)&data;
	printf("%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],
                                      f[8],f[9],f[10],f[11],f[12],f[13],f[14],f[15],
                                      f[16],f[17],f[18],f[19],f[20],f[21],f[22],f[23],
                                      f[24],f[25],f[26],f[27],f[28],f[29],f[30],f[31]);
}

void print__m256_int(__m256 data){
	int*f = (int*)&data;
	printf("%d %d %d %d %d %d %d %d\n", f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
}

int main(){
  FILE *fp;
  fp = fopen("data2.txt", "r");
  int buff[256];
  int i;
  while(fscanf(fp, "%d", &buff[i])!=EOF){
    ++i;
  }
  fclose(fp);
  int j;
  
  __m256 ones = _mm256_set1_epi8(1);
  for(j=0; j<i; j+=32){
    __m256 data = _mm256_set_epi8(buff[j+31], buff[j+30], buff[j+29], buff[j+28], buff[j+27], buff[j+26], buff[j+25], buff[j+24],
                                  buff[j+23], buff[j+22], buff[j+21], buff[j+20], buff[j+19], buff[j+18], buff[j+17], buff[j+16],
                                  buff[j+15], buff[j+14], buff[j+13], buff[j+12], buff[j+11], buff[j+10], buff[j+9], buff[j+8],
                                  buff[j+7], buff[j+6], buff[j+5], buff[j+4], buff[j+3], buff[j+2], buff[j+1], buff[j]);
    __m256 result = _mm256_add_epi8(ones,data);
    print__m256(result);
  }


	return 0;
}
