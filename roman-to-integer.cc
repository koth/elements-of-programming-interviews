// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

// @include
int roman_to_integer(const string& s) {
  unordered_map<char, int> T = { { 'I', 1 },
                                 { 'V', 5 },
                                 { 'X', 10 },
                                 { 'L', 50 },
                                 { 'C', 100 },
                                 { 'D', 500 },
                                 { 'M', 1000 } };

  int sum = T[s.back()];
  for (int i = s.length() - 2; i >= 0; --i) {
    if (T[s[i]] < T[s[i + 1]]) {
      sum -= T[s[i]];
    } else {
      sum += T[s[i]];
    }
  }
  return sum;
}
// @exclude

int main(int argc, char** argv) {
  assert(7 == roman_to_integer("VII"));
  assert(184 == roman_to_integer("CLXXXIV"));
  assert(9 == roman_to_integer("IX"));
  assert(40 == roman_to_integer("XL"));
  assert(60 == roman_to_integer("LX"));
  assert(1500 == roman_to_integer("MD"));
  assert(400 == roman_to_integer("CD"));
  assert(1900 == roman_to_integer("MCM"));
  assert(9919 == roman_to_integer("MMMMMMMMMCMXIX"));
  if (argc == 2) {
    cout << argv[1] << " equals to " << roman_to_integer(argv[1]) << endl;
  }
  return 0;
}
