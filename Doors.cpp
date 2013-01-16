#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cmath>

using namespace std;

// @include
bool is_door_open(const int &i) {
  double sqrt_i = sqrt(i);
  int floor_sqrt_i = floor(sqrt_i);
  return floor_sqrt_i * floor_sqrt_i == i;
}
// @exclude

void check_answer(const int &n) {
  vector<bool> doors(n + 1, false);  // false means closed door
  for (int i = 1; i <= n; ++i) {
    int start = 0;
    while (start + i <= n) {
      start += i;
      doors[start] = doors[start] ? false : true;
    }
  }

  for (int i = 1; i <= n; ++i) {
    assert(is_door_open(i) == doors[i]);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 1000;
  }
  cout << "n = " << n << endl;
  check_answer(n);
  return 0;
}
