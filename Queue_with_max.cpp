// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Stack_with_max_template.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::exception;
using std::length_error;

// @include
template <typename T>
class Queue {
 public:
  void enqueue(const T& x) {
    A_.push(x);
  }

  T dequeue(void) {
    if (B_.empty()) {
      while (A_.empty() == false) {
        B_.push(A_.pop());
      }
    }
    if (B_.empty() == false) {
      return B_.pop();
    }
    throw length_error("empty queue");
  }

  const T& max(void) const {
    if (A_.empty() == false) {
      return B_.empty() ? A_.max() : std::max(A_.max(), B_.max());
    } else {  // A_.empty() == true
      if (B_.empty() == false) {
        return B_.max();
      }
      throw length_error("empty queue");
    }
  }

 private:
  Stack<T> A_, B_;
};
// @exclude

int main(int argc, char *argv[]) {
  Queue<int> Q;
  Q.enqueue(1);
  Q.enqueue(2);
  assert(2 == Q.max());
  assert(1 == Q.dequeue());  // 1
  assert(2 == Q.max());
  assert(2 == Q.dequeue());  // 2
  Q.enqueue(3);
  assert(3 == Q.max());
  assert(3 == Q.dequeue());  // 3
  try {
    Q.max();
  } catch(const exception &e) {
    cout << e.what() << endl;  // throw
  }
  try {
    Q.dequeue();
  } catch(const exception &e) {
    cout << e.what() << endl;  // throw
  }
  return 0;
}
