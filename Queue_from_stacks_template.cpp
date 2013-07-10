// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::stack;

// @include
template <typename T>
class Queue {
 public:
  void enqueue(const T& x) {
    A_.emplace(x);
  }

  T dequeue(void) {
    if (B_.empty()) {
      while (!A_.empty()) {
        B_.emplace(A_.top());
        A_.pop();
      }
    }
    if (B_.empty() == false) {
      T ret = B_.top();
      B_.pop();
      return ret;
    }
    throw length_error("empty queue");
  }

 private:
  stack<T> A_, B_;
};
// @exclude

int main(int argc, char *argv[]) {
  Queue<int> Q;
  Q.enqueue(1);
  Q.enqueue(2);
  assert(1 == Q.dequeue());  // 1
  assert(2 == Q.dequeue());  // 2
  Q.enqueue(3);
  assert(3 == Q.dequeue());  // 3
  try {
    Q.dequeue();
  } catch(const exception& e) {
    cout << e.what() << endl;  // throw
  }
  return 0;
}
