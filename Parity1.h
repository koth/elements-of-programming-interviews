// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_PARITY1_H_
#define SOLUTIONS_PARITY1_H_

// @include
short parity1(unsigned long x) {
  short result = 0;
  while (x) {
    result ^= (x & 1);
    x >>= 1;
  }
  return result;
}
// @exclude
#endif  // SOLUTIONS_PARITY1_H_
