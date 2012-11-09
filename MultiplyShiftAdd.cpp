#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cassert>
#include <cstring>

char *print_bits( unsigned int x ) {
  char tmpbuf[100];
  int numBits = 8 * sizeof(unsigned int);
  int k;
  for ( k = 0 ; k < numBits; k++ ) {
    tmpbuf[k] = ( x & (1 << k) ) ? '1' : '0';
  }
  tmpbuf[k] = '\0';
  return strdup( tmpbuf );
}

// @include
unsigned add_no_operator(const unsigned &a, const unsigned &b) {
  unsigned sum = 0, carryin = 0, k = 1;
  while (k) {
    unsigned ak = a & k, bk = b & k;
    unsigned carryout =  (ak & bk) | (ak & carryin) | (bk & carryin);
    sum |= (ak ^ bk ^ carryin);
    carryin = carryout << 1;
    k <<= 1;
  }
  return sum;
}

unsigned multiply_no_operator(const unsigned &x, const unsigned &y) {
  unsigned sum = 0, k = 1, scaled_y = y;
  while (k) {
    // Examine the k-th bit of x
    if (x & k) {
      sum = add_no_operator(sum, scaled_y);
    }
    k <<= 1;
    scaled_y <<= 1;
  }
  return sum;
}
// @exclude

int main(int argc, char *argv[]) {
  if (argc == 3) {
    unsigned int x = atoi(argv[1]), y = atoi(argv[2]);
    unsigned int res = add_no_operator(x, y);
    printf("x,y = %d,%d; res = %d\n", x, y, res );
    assert( res == x+y );
  } else {
    srand(time(nullptr));
    // random test, only works if the product not greater than 2^32 - 1
    int i;
    for (i = 0; i < 100000; ++i) {
      unsigned int x = rand() % 65536, y = rand() % 65536;
      unsigned int prod = multiply_no_operator(x, y);
      assert( prod == x*y );
      printf("PASS: x,y=%u,%u;\t prod=%u\n", x, y, prod );
    }
  }
  return 0;
}
