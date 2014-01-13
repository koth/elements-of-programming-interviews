// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_ROTATE_ARRAY_PERMUTATION_H_
#define SOLUTIONS_ROTATE_ARRAY_PERMUTATION_H_

#include <algorithm>
#include <vector>

#include "./GCD.h"

using std::swap;
using std::vector;

namespace rotate_array1 {

// @include
void rotate_array(int i, vector<int>* A) {
  i %= A->size();
  int cycles = GCD(A->size(), i);  // number of cycles in this rotation.
  int hops = A->size() / cycles;  // number of elements in a cycle.

  for (int c = 0; c < cycles; ++c) {
    int temp = (*A)[c];
    for (int j = 1; j < hops; ++j) {
      swap((*A)[(c + j * i) % A->size()], temp);
    }
    (*A)[c] = temp;
  }
}
// @exclude

}  // rotate_array1
#endif  // SOLUTIONS_ROTATE_ARRAY_PERMUTATION_H_
