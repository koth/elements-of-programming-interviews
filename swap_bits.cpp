#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// @include
long swap_bits(long x, const int &i, const int &j) {
  if (((x >> i) & 1) != ((x >> j) & 1)) {
    x ^= (1L << i) | (1L << j);
  }
  return x;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  long x;
  int i, j;
  if (argc == 4) {
    x = atol(argv[1]), i = atoi(argv[2]), j = atoi(argv[3]);
  } else {
    x = rand();
    i = rand() % 64, j = rand() % 64;
  }
  cout << "x = " << x << ", i = " << i << ", j = " << j << endl;
  cout << swap_bits(x, i, j) << endl;
  return 0;
}
