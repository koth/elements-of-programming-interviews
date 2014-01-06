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
class Queue {
 public:
  void enqueue(int x) { A_.emplace(x); }

  int dequeue() {
    if (B_.empty()) {
      while (!A_.empty()) {
        B_.emplace(A_.top());
        A_.pop();
      }
    }
    if (!B_.empty()) {
      int ret = B_.top();
      B_.pop();
      return ret;
    }
    throw length_error("empty queue");
  }

 private:
  stack<int> A_, B_;
};
// @exclude

int main(int argc, char* argv[]) {
  Queue Q;
  Q.enqueue(1);
  Q.enqueue(2);
  assert(1 == Q.dequeue());  // 1
  assert(2 == Q.dequeue());  // 2
  Q.enqueue(3);
  assert(3 == Q.dequeue());  // 3
  try {
    Q.dequeue();
  }
  catch (const exception& e) {
    cout << e.what() << endl;  // throw
  }
  return 0;
}
