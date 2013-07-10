#include <iostream>
#include <cassert>
#include <ctime>
#include <climits>
#include <cstdlib>

using namespace std;

unsigned divide_x_y_bsearch(const unsigned &x, const unsigned &y) {
  if (x < y) {
    return 0;
  }

  int power_left = 0;
  int power_right = sizeof(unsigned) << 3; 
  int power_mid = -1;
  while (power_left < power_right) {
    int tmp = power_mid;
    power_mid = power_left + ((power_right - power_left) >> 1);
    if ( tmp == power_mid ) {
      break;
    }
    unsigned yshift = y << power_mid;
    if ( (yshift >> power_mid) != y ) {
      // yshift overflowed, use a smaller shift
      power_right = power_mid;
      continue;
    }
    if ((y << power_mid) > x) {
      power_right = power_mid;
    } else if ((y << power_mid) < x) {
      power_left = power_mid;
    } else {
      return (1U << power_mid);
    }
  }
  unsigned part = 1U << power_left;
  return part | divide_x_y_bsearch(x - (y << power_left), y);
}

// @include
unsigned divide_x_y(const unsigned &x, const unsigned &y) {
  if (x < y) {
    return 0;
  }

  int power = 0;
  while ((y << power) <= x) {
    ++power;
  }
  unsigned part = 1U << (power - 1);
  return part | divide_x_y(x - (y << (power - 1)), y);
}
// @exclude


void foo() { } 

void simple_test(void) {
  assert(divide_x_y(64, 1) == 64);
  assert(divide_x_y(64, 2) == 32);
  assert(divide_x_y(64, 3) == 21);
  assert(divide_x_y(64, 4) == 16);
  assert(divide_x_y(64, 5) == 12);
  assert(divide_x_y(65, 2) == 32);
  assert(divide_x_y_bsearch(4u, 2u));
  assert(divide_x_y_bsearch(64, 1) == 64);
  assert(divide_x_y_bsearch(64, 2) == 32);
  assert(divide_x_y_bsearch(64, 3) == 21);
  assert(divide_x_y_bsearch(64, 4) == 16);
  assert(divide_x_y_bsearch(64, 5) == 12);
  assert(divide_x_y_bsearch(65, 2) == 32);
  assert(divide_x_y_bsearch(9444, 4714) == 2);
  assert(divide_x_y_bsearch(8186, 19) == 430);
  assert(divide_x_y_bsearch(8186, 19) == 430);
}

int main(int argc, char *argv[]) {
  simple_test();
  int MAX = UINT_MAX;
  //srand(time(nullptr));
  if (argc == 3) {
    unsigned x = atoi(argv[1]), y = atoi(argv[2]);
    assert(x / y == divide_x_y(x, y));
    assert(x / y == divide_x_y_bsearch(x, y));
  } else {
    for (int times = 0; times < 100000000; ++times) {
      unsigned x = rand() % MAX; 
      unsigned y = rand() % MAX;
      y = (y==0) ? 1 : y; // ensure no divide by 0
      assert((x/y) == divide_x_y(x, y));
      assert( (x/y) == divide_x_y_bsearch(x, y));
    }
  }
  return 0;
}
