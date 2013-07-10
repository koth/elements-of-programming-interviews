#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// @include
int get_height_helper(vector<vector<int>> &F, const int &c, const int &d) {
  if (d == 0) {
    return 0;
  } else if (c == 1) {
    return d;
  } else {
    if (F[c][d] == -1) {
      F[c][d] = get_height_helper(F, c, d - 1) +
                get_height_helper(F, c - 1, d - 1) + 1;
    }
    return F[c][d];
  }
}

int getHeight(const int &c, const int &d) {
  vector<vector<int>> F(c + 1, vector<int>(d + 1, -1));
  return get_height_helper(F, c, d);
}
// @exclude

int main(int argc, char *argv[]) {
  assert(getHeight(1, 10) == 10);
  assert(getHeight(2, 1) == 1);
  assert(getHeight(2, 2) == 3);
  assert(getHeight(2, 3) == 6);
  assert(getHeight(2, 4) == 10);
  assert(getHeight(2, 5) == 15);
  assert(getHeight(3, 2) == 3);
  assert(getHeight(100, 2) == 3);
  assert(getHeight(3, 5) == 25);
  assert(getHeight(8, 11) == 1980);
  assert(getHeight(3, 0) == 0);
  assert(getHeight(3, 1) == 1);
  assert(getHeight(3, 3) == 7);
  return 0;
}
