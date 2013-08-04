// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_ROTATE_ARRAY_H_
#define SOLUTIONS_ROTATE_ARRAY_H_

#include <algorithm>
#include <vector>

using std::vector;

namespace rotate_array2 {

// @include
template <typename T>
void rotate_array(vector<T>* A, int i) {
  i %= A->size();
  reverse(A->begin(), A->end());
  reverse(A->begin(), A->begin() + i);
  reverse(A->begin() + i, A->end());
}
// @exclude

}  // rotate_array2
#endif  // SOLUTIONS_ROTATE_ARRAY_H_
