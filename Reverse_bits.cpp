#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

vector<long> precomputed_reverse;

long swap_bits(long x, const int &i, const int &j) {
  if (((x >> i) & 1) != ((x >> j) & 1)) {
    x ^= (1L << i) | (1L << j);
  }
  return x;
}

long reverse_x(long x, const int &n) {
  for (int i = 0, j = n; i < j; ++i, --j) {
    x = swap_bits(x, i, j);
  }
  return x;
}

void create_precomputed_table() {
  for (int i = 0; i < (1 << 16); ++i) {
    precomputed_reverse.emplace_back(reverse_x(i, 15));
  }
}

// @include
long reverse_bits(const long &x) {
  return precomputed_reverse[(x >> 48) & 0xFFFF] |
         precomputed_reverse[(x >> 32) & 0xFFFF] << 16 |
         precomputed_reverse[(x >> 16) & 0xFFFF] << 32 |
         precomputed_reverse[x & 0xFFFF] << 48;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  /*
  long x = 1;
  cout << reverse_x(x, 63) << endl;
  return 0;
  */
  create_precomputed_table();
  if (argc == 2) {
    long x = atoi(argv[1]);
    cout << "sizeof(x) = " << sizeof(x) << endl;
    cout << "x = " << x << ", reverse x = " << reverse_bits(x) << endl;
    cout << reverse_x(x, 63) << endl;
    assert(reverse_bits(x) == reverse_x(x, 63));
  } else {
    for (int times = 0; times < 1000; ++times) {
      long x = rand();
      cout << "x = " << x << ", reverse x = " << reverse_bits(x) << endl;
      assert(reverse_bits(x) == reverse_x(x, 63));
    }
  }
  return 0;
}
