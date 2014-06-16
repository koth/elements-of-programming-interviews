// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::stack;
using std::string;
using std::vector;

// @include
size_t longest_valid_parentheses(const string& s) {
  size_t max_len = 0, last_end = 0;
  stack<int> left_parentheses;
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == '(') {
      left_parentheses.emplace(i);
    } else {
      if (left_parentheses.empty()) {
        last_end = i + 1;
      } else {
        left_parentheses.pop();
        size_t start = left_parentheses.empty() ?
                       last_end - 1 : left_parentheses.top();
        max_len = max(max_len, i - start);
      }
    }
  }
  return max_len;
}
// @exclude

void small_test() {
  assert(longest_valid_parentheses("((())()(()(") == 6);
  assert(longest_valid_parentheses("()()())") == 6);
}

int main(int argc, char** argv) {
  small_test();
  string s;
  if (argc == 2) {
    s = argv[1];
  }
  cout << "s = " << s << endl;
  cout << longest_valid_parentheses(s) << endl;
  return 0;
}
