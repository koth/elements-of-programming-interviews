#include <stdlib.h>
#include <stdio.h>

#define N 3000000000

unsigned char c[N];

int print() {
  int i;
  for ( i = 0 ; i < N; i++ ) {
    printf("c[%d] = %d, ", i, c[i] );
  }
  return 0;
}

int comp(const unsigned char * a,const unsigned char * b)
{
  if (*a==*b)
    return 0;
  else
    if (*a < *b)
        return -1;
     else
      return 1;
}

int init() {
  unsigned int i;
  for ( i = 0 ; i < N; i++ ) {
    c[i] = i & 255;
  }
  qsort(c,N,sizeof(unsigned char),comp) ;
  return 0;
}


int binsearch(unsigned char *A, char key, int L, int U) {
  while ( L <= U ) {
    int M = L + (U-L)/2;
    if ( A[M] < key ) {
      L = M + 1;
    } else if ( A[M] > key ) {
      U = M - 1;
    } else {
      return M;
    }
  }
  return -1;
}

/*
int binsearchwrapper(unsigned char *A, char key){
  return binsearchiter(A, key, 0, N-1);
}
*/

int main() {
  init();
  // print();
  char key = 123;
  //@include
#define N 3000000000
char A[N];
char *B = (A - 1500000000);
int L = -1499000000;
int U = 1499000000;
// On a 32-bit machine (u-l) = -1296967296 because the actual value,
// 2998000000 is larger than 2^31-1. Consequently, the binsearch function
// called below sets m to -2147483648 instead of 0, which leads to an
// out-of-bounds access, since the most negative index that can be applied
// to B is -1500000000.
int result = binsearch(B + 1500000000, key, L, U);
  //@exclude
  // int index = binsearch( c, (unsigned char) 123);
  // printf("Index of 123 is %d\n", index );
  return 0;
}

