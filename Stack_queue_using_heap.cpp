// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::exception;
using std::pair;
using std::priority_queue;
using std::vector;

// @include
struct Compare {
  bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.first < rhs.first;
  }
};

class Stack {
 public:
  void push(int x) { H.emplace(order_++, x); }

  int pop() {
    int ret = H.top().second;
    H.pop();
    return ret;
  }

  const int& peek() const { return H.top().second; }

 private:
  int order_ = 0;
  // Uses a pair where first is the order_ and the second is the element.
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> H;
};

class Queue {
 public:
  void enqueue(int x) { H.emplace(order_--, x); }

  int dequeue() {
    int ret = H.top().second;
    H.pop();
    return ret;
  }

  const int& head() const { return H.top().second; }

 private:
  int order_ = 0;
  // Uses a pair where first is the order_ and the second is the element.
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> H;
};
// @exclude

int main(int argc, char* argv[]) {
  Stack s;
  s.push(1);
  s.push(2);
  s.push(3);
  assert(s.peek() == 3);
  s.pop();
  assert(s.peek() == 2);
  s.pop();
  s.push(4);
  assert(s.peek() == 4);
  s.pop();
  s.pop();
  try {
    s.pop();
  }
  catch (const exception& e) {
    cout << "empty stack" << endl;
    cout << e.what() << endl;
  }

  Queue q;
  q.enqueue(1);
  q.enqueue(2);
  assert(q.head() == 1);
  q.dequeue();
  assert(q.head() == 2);
  q.dequeue();
  try {
    q.dequeue();
  }
  catch (const exception& e) {
    cout << "empty queue" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
