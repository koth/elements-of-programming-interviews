// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// @include
bool is_palindrome(const string& s) {
  int i = 0, j = s.size() - 1;
  while (i < j) {
    while (!isalnum(s[i]) && i < j) {
      ++i;
    }
    while (!isalnum(s[j]) && i < j) {
      --j;
    }
    if (tolower(s[i]) != tolower(s[j])) {
      return false;
    }
    ++i, --j;
  }
  return true;
}
// @exclude

int main(int argc, char** argv) {
  assert(is_palindrome("A man, a plan, a canal: Panama"));
  assert(!is_palindrome("race a car"));
  assert(is_palindrome(""));
  return 0;
}
