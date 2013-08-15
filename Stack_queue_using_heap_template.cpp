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
template <typename T>
struct Compare {
  bool operator()(const pair<int, T>& lhs, const pair<int, T>& rhs) const {
    return lhs.first < rhs.first;
  }
};

template <typename T>
class Stack {
 public:
  void push(const T& x) {
    H.emplace(order_++, x);
  }

  T pop(void) {
    T ret = H.top().second;
    H.pop();
    return ret;
  }

  const T& peek() const {
    return H.top().second;
  }

 private:
  int order_ = 0;
  // Uses a pair where first is the order_ and the second is the element.
  priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> H;
};

template <typename T>
class Queue {
 public:
  void enqueue(const T& x) {
    H.emplace(order_--, x);
  }

  T dequeue(void) {
    T ret = H.top().second;
    H.pop();
    return ret;
  }

  const T& head() const {
    return H.top().second;
  }

 private:
  int order_ = 0;
  // Uses a pair where first is the order_ and the second is the element.
  priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> H;
};
// @exclude

int main(int argc, char *argv[]) {
  Stack<int> s;
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
  } catch(const exception& e) {
    cout << "empty stack" << endl;
    cout << e.what() << endl;
  }

  Queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  assert(q.head() == 1);
  q.dequeue();
  assert(q.head() == 2);
  q.dequeue();
  try {
    q.dequeue();
  } catch(const exception& e) {
    cout << "empty queue" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
