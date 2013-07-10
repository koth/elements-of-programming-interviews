// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_STACK_WITH_MAX_TEMPLATE_H_
#define SOLUTIONS_STACK_WITH_MAX_TEMPLATE_H_

#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

using std::length_error;
using std::pair;
using std::stack;

// @include
template <typename T>
class Stack {
 public:
  const bool empty(void) const {
    return s_.empty();
  }

  const T& max(void) const {
    if (empty() == false) {
      return s_.top().second;
    }
    throw length_error("empty stack");
  }

  T pop(void) {
    if (empty() == false) {
      T ret = s_.top().first;
      s_.pop();
      return ret;
    }
    throw length_error("empty stack");
  }

  void push(const T& x) {
    s_.emplace(x, std::max(x, empty() ? x : s_.top().second));
  }

 private:
  stack<pair<T, T>> s_;
};
// @exclude
#endif  // SOLUTIONS_STACK_WITH_MAX_TEMPLATE_H_
