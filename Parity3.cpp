#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

short parity1(unsigned long x) {
  short result = 0;
  while (x) {
    result ^= (x & 1);
    x >>= 1;
  }
  return result;
}

short precomputed_parity[1 << 16];

short parity2(long x) {
  short result = 0;
  while (x) {
    result ^= 1;
    x &= (x - 1);
  }
  return result;
}

// @include
short parity3(const unsigned long &x) {
  return precomputed_parity[x >> 48] ^
         precomputed_parity[(x >> 32) & 0xFFFF] ^
         precomputed_parity[(x >> 16) & 0xFFFF] ^
         precomputed_parity[x & 0xFFFF];
}
// @exclude

int main(int argc, char *argv[]) {
  for (int i = 0; i < (1 << 16); ++i) {
    precomputed_parity[i] = parity1(i);
  }
  srand(time(nullptr));
  if (argc == 2) {
    long int x = atol(argv[1]);
    assert(parity1(x) == parity3(x));
    assert(parity2(x) == parity3(x));
    cout << "x = " << x << ", parity = " << parity3(x) << endl;
  } else {
    for (int times = 0; times < 1000; ++times) {
      long int x = rand();
      assert(parity1(x) == parity3(x));
      assert(parity2(x) == parity3(x));
      cout << "x = " << x << ", parity = " << parity3(x) << endl;
    }
  }
  return 0;
}
