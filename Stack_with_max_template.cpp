// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "./Stack_with_max_template.h"

using std::cout;
using std::endl;
using std::exception;

int main(int argc, char* argv[]) {
  Stack<int> s;
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
