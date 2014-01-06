// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Queue_with_max_using_deque.h"

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;
using std::exception;

// Just for testing.
int main(int argc, char* argv[]) {
  Queue Q;
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
  }
  catch (const exception& e) {
    cout << e.what() << endl;  // throw
  }
  try {
    Q.dequeue();
  }
  catch (const exception& e) {
    cout << e.what() << endl;  // throw
  }
  return 0;
}
