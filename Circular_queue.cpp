// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::vector;

// @include
class Queue {
 public:
  explicit Queue(size_t cap) : data_(cap) {}

  void enqueue(int x) {
    // Dynamically resizes due to data_.size() limit.
    if (count_ == data_.size()) {
      // Rearranges elements.
      rotate(data_.begin(), data_.begin() + head_, data_.end());
      head_ = 0, tail_ = count_;  // resets head and tail.
      data_.resize(data_.size() << 1);
    }
    // Performs enqueue.
    data_[tail_] = x;
    tail_ = (tail_ + 1) % data_.size(), ++count_;
  }

  int dequeue() {
    if (!count_) {
      throw length_error("empty queue");
    }
    --count_;
    int ret = data_[head_];
    head_ = (head_ + 1) % data_.size();
    return ret;
  }

  size_t size() const { return count_; }

 private:
  size_t head_ = 0, tail_ = 0, count_ = 0;
  vector<int> data_;
};
// @exclude

void test() {
  Queue q(8);
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.enqueue(4);
  q.enqueue(5);
  q.enqueue(6);
  q.enqueue(7);
  q.enqueue(8);
  // Now head = 0 and tail = 0

  assert(1 == q.dequeue());
  assert(2 == q.dequeue());
  assert(3 == q.dequeue());
  // Now head = 3 and tail = 0

  q.enqueue(11);
  q.enqueue(12);
  q.enqueue(13);
  // Ok till here. Now head = 3 and tail = 3

  q.enqueue(14);  // now the vector (data) is resized; but the head and tail.
                  // (or elements) does not change accordingly.
  q.enqueue(15);
  q.enqueue(16);
  q.enqueue(17);
  q.enqueue(18);
  // The elements starting from head=3 are overwriten!

  assert(4 == q.dequeue());
  assert(5 == q.dequeue());
  assert(6 == q.dequeue());
  assert(7 == q.dequeue());
  assert(8 == q.dequeue());
  assert(11 == q.dequeue());
  assert(12 == q.dequeue());
}

int main(int argc, char* argv[]) {
  test();
  Queue q(8);
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  assert(1 == q.dequeue());
  q.enqueue(4);
  assert(2 == q.dequeue());
  assert(3 == q.dequeue());
  assert(4 == q.dequeue());
  try {
    q.dequeue();
  }
  catch (const exception& e) {
    cout << e.what() << endl;
  }
  // test resize().
  q.enqueue(4);
  q.enqueue(4);
  q.enqueue(4);
  q.enqueue(4);
  q.enqueue(4);
  q.enqueue(4);
  q.enqueue(4);
  q.enqueue(4);
  q.enqueue(4);
  assert(q.size() == 9);
  return 0;
}
