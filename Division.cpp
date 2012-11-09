#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
unsigned divide_x_y(const unsigned &x, const unsigned &y) {
  if (x < y) {
    return 0;
  }

  int power = 0;
  while ((1U << power) * y <= x) {
    ++power;
  }
  unsigned part = 1U << (power - 1);
  return part + divide_x_y(x - part * y, y);
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  if (argc == 3) {
    unsigned x = atoi(argv[1]), y = atoi(argv[2]);
    assert(x / y == divide_x_y(x, y));
  } else {
    for (int times = 0; times < 100000; ++times) {
      unsigned x = 1 + rand(), y = 1 + rand();
      assert(x / y == divide_x_y(x, y));
    }
  }
  return 0;
}
