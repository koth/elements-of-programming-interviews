// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_PARITY3_H_
#define SOLUTIONS_PARITY3_H_

static bool is_initialized = false;

short precomputed_parity[1 << 16];

void build_table() {
  if (!is_initialized) {
    for (int i = 0; i < (1 << 16); ++i) {
      precomputed_parity[i] = parity1(i);
    }
    is_initialized = true;
  }
}

// @include
short parity3(unsigned long x) {
  return precomputed_parity[x >> 48] ^
         precomputed_parity[(x >> 32) & 0b1111111111111111] ^
         precomputed_parity[(x >> 16) & 0b1111111111111111] ^
         precomputed_parity[x & 0b1111111111111111];
}
// @exclude
#endif  // SOLUTIONS_PARITY3_H_
