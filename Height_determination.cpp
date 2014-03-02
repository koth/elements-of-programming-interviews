// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int get_height_helper(int c, int d, vector<vector<int>>* F);

// @include
int get_height(int c, int d) {
  vector<vector<int>> F(c + 1, vector<int>(d + 1, -1));
  return get_height_helper(c, d, &F);
}

int get_height_helper(int c, int d, vector<vector<int>>* F) {
  if (c == 0 || d == 0) {
    return 0;
  } else if (c == 1) {
    return d;
  } else {
    if ((*F)[c][d] == -1) {
      (*F)[c][d] = get_height_helper(c, d - 1, F) +
                   get_height_helper(c - 1, d - 1, F) + 1;
    }
    return (*F)[c][d];
  }
}
// @exclude

int main(int argc, char* argv[]) {
  assert(get_height(1, 10) == 10);
  assert(get_height(2, 1) == 1);
  assert(get_height(2, 2) == 3);
  assert(get_height(2, 3) == 6);
  assert(get_height(2, 4) == 10);
  assert(get_height(2, 5) == 15);
  assert(get_height(3, 2) == 3);
  assert(get_height(100, 2) == 3);
  assert(get_height(3, 5) == 25);
  assert(get_height(8, 11) == 1980);
  assert(get_height(3, 0) == 0);
  assert(get_height(3, 1) == 1);
  assert(get_height(3, 3) == 7);
  assert(get_height(0, 10) == 0);
  assert(get_height(0, 0) == 0);
  return 0;
}
