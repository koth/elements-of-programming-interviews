#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

int zero_one_random(void) {
  return rand() & 1;
}

// @include
int uniform_random_a_b(const int &a, const int &b) {
  int l = b - a + 1, res;
  do {
    res = 0;
    for (int i = 0; (1 << i) < l; ++i) {
      // zero_one_random is the system-provided random number generator
      res = (res << 1) | zero_one_random();
    }
  } while (res >= l);
  return res + a;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int a, b;
    if (argc == 3) {
      a = atoi(argv[1]), b = atoi(argv[2]);
    } else {
      a = rand() % 100;
      b = a + 1 + rand() % 100;
    }
    int x = uniform_random_a_b(a, b);
    cout << "a = " << a << " b = " << b << endl;
    cout << "random result = " << x << endl;
    assert(x >=a && x <= b);
  }
  return 0;
}
