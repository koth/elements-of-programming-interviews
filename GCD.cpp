#include <iostream>
#include <cassert>

using namespace std;

// @include
long long GCD(const long long &x, const long long &y) {
  if (x == 0) {
    return y;
  } else if (y == 0) {
    return x;
  } else if (!(x & 1) && !(y & 1)) {  // x and y are even integers
    return GCD(x >> 1, y >> 1) << 1;
  } else if (!(x & 1) && y & 1) {  // x is even integer, and y is odd integer
    return GCD(x >> 1, y);
  } else if (x & 1 && !(y & 1)) {  // x is odd integer, and y is even integer
    return GCD(x, y >> 1);
  } else if (x > y) {  // both x and y are odd integers, and x > y
    return GCD(x - y, y);
  }
  return GCD(x, y - x);  // both x and y are odd integers, and x <= y
}

long long another_GCD(long long a, long long b) {
  if (b) {
    while ((a %= b) && (b %= a));
  }
  return a + b;
}
// @exclude

int main(int argc, char *argv[]) {
  long long x = 18, y = 12;
  assert(GCD(x, y) == 6);
  if (argc == 3) {
    x = atoll(argv[1]), y = atoll(argv[2]);
    cout << GCD(x, y) << endl;
    assert(GCD(x, y) == another_GCD(x, y));
  } else {
    srand(time(nullptr));
    for (int times = 0; times < 1000; ++times) {
      x = rand(), y = rand();
      assert(GCD(x, y) == another_GCD(x, y));
    }
  }
  return 0;
}
