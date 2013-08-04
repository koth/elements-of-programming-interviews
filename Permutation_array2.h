// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_PERMUTATION_ARRAY2_H_
#define SOLUTIONS_PERMUTATION_ARRAY2_H_

#include <vector>

using std::vector;

// @include
template <typename T>
void apply_permutation2(vector<int>* perm, vector<T>* A) {
  for (int i = 0; i < A->size(); ++i) {
    // Traverse the cycle to see if i is the min element.
    bool is_min = true;
    int j = (*perm)[i];
    while (j != i) {
      if (j < i) {
        is_min = false;
        break;
      }
      j = (*perm)[j];
    }

    if (is_min) {
      int a = i;
      T temp = (*A)[i];
      do {
        int next_a = (*perm)[a];
        T next_temp = (*A)[next_a];
        (*A)[next_a] = temp;
        a = next_a, temp = next_temp;
      } while (a != i);
    }
  }
}
// @exclude
#endif  // SOLUTIONS_PERMUTATION_ARRAY2_H_
