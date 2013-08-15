// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_SWAP_BITS_H_
#define SOLUTIONS_SWAP_BITS_H_

// @include
long swap_bits(long x, int i, int j) {
  if (((x >> i) & 1) != ((x >> j) & 1)) {
    x ^= (1L << i) | (1L << j);
  }
  return x;
}
// @exclude
#endif  // SOLUTIONS_SWAP_BITS_H_
