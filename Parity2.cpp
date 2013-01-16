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

// @include
short parity2(unsigned long x) {
  short result = 0;
  while (x) {
    result ^= 1;
    x &= (x - 1);  // drops the LSB of x
  }
  return result;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  if (argc == 2) {
    long int x = atol(argv[1]);
    assert(parity1(x) == parity2(x));
    cout << "x = " << x << ", parity = " << parity2(x) << endl;
  } else {
    for (int times = 0; times < 1000; ++times) {
      long int x = rand();
      assert(parity1(x) == parity2(x));
      cout << "x = " << x << ", parity = " << parity2(x) << endl;
    }
  }
  return 0;
}
