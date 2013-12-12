// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_PARITY4_H_
#define SOLUTIONS_PARITY4_H_

short four_bit_parity_lookup(int x);

// @include
short parity4(unsigned long x) {
  x ^= x >> 32;
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x &= 0xf; // only want the last 4 bits of x.
  // Return the LSB, which is the parity.
  return four_bit_parity_lookup(x) & 1;
}

// The LSB of kFourBitParityLookupTable is the parity of 0,
// next bit is parity of 1, followed by the parity of 2, etc.

const int kFourBitParityLookupTable = 0x6996; // = 0b0110100110010110.

short four_bit_parity_lookup(int x) {
  return kFourBitParityLookupTable >> x;
}
// @exclude
#endif  // SOLUTIONS_PARITY4_H_
