// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_QUEUE_WITH_MAX_USING_DEQUE_H_
#define SOLUTIONS_QUEUE_WITH_MAX_USING_DEQUE_H_

#include <algorithm>
#include <deque>
#include <queue>
#include <stdexcept>

using std::deque;
using std::length_error;
using std::queue;

// @include
template <typename T>
class Queue {
 public:
  void enqueue(const T& x) {
    Q_.emplace(x);
    while (D_.empty() == false && D_.back() < x) {
      D_.pop_back();
    }
    D_.emplace_back(x);
  }

  T dequeue(void) {
    if (Q_.empty() == false) {
      T ret = Q_.front();
      if (ret == D_.front()) {
        D_.pop_front();
      }
      Q_.pop();
      return ret;
    }
    throw length_error("empty queue");
  }

  const T& max(void) const {
    if (D_.empty() == false) {
      return D_.front();
    }
    throw length_error("empty queue");
  }
  // @exclude
  T& head(void) {
    return Q_.front();
  }

  const T& head(void) const {
    return Q_.front();
  }
  // @include

 private:
  queue<T> Q_;
  deque<T> D_;
};
// @exclude
#endif  // SOLUTIONS_QUEUE_WITH_MAX_USING_DEQUE_H_
