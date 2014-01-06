// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::stack;
using std::pair;

// @include
class Stack {
 public:
  bool empty() const { return s_.empty(); }

  int max() const {
    if (!empty()) {
      return aux_.top().first;
    }
    throw length_error("empty stack");
  }

  int pop() {
    if (empty()) {
      throw length_error("empty stack");
    }
    int ret = s_.top();
    s_.pop();
    if (ret == aux_.top().first) {
      --aux_.top().second;
      if (aux_.top().second == 0) {
        aux_.pop();
      }
    }
    return ret;
  }

  void push(int x) {
    s_.emplace(x);
    if (!aux_.empty()) {
      if (x == aux_.top().first) {
        ++aux_.top().second;
      } else if (x > aux_.top().first) {
        aux_.emplace(x, 1);
      }
    } else {
      aux_.emplace(x, 1);
    }
  }

 private:
  stack<int> s_;
  stack<pair<int, int>> aux_;
};
// @exclude

int main(int argc, char* argv[]) {
  Stack s;
  s.push(1);
  s.push(2);
  assert(s.max() == 2);
  cout << s.max() << endl;  // 2
  cout << s.pop() << endl;  // 2
  assert(s.max() == 1);
  cout << s.max() << endl;  // 1
  s.push(3);
  s.push(2);
  assert(s.max() == 3);
  cout << s.max() << endl;  // 3
  s.pop();
  assert(s.max() == 3);
  cout << s.max() << endl;  // 3
  s.pop();
  assert(s.max() == 1);
  cout << s.max() << endl;  // 1
  s.pop();
  try {
    s.max();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
  }
  catch (const exception& e) {
    cout << e.what() << endl;
  }
  return 0;
}
