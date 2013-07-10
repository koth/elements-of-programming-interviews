#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <stdexcept>

using namespace std;

// @include
template <typename T>
class Queue {
  private:
    size_t head, tail, count;
    vector<T> data;

  public:
    Queue(const size_t &cap = 8) : head(0), tail(0), count(0), data({cap}) {}

    void enqueue(const T &x) {
      // Dynamically resize due to data.size() limit
      if (count == data.size()) {
        // Rearrange elements.
        rotate(data.begin(), data.begin() + head, data.end());
        head = 0, tail = count;  // reset head and tail
        data.resize(data.size() << 1);
      }
      // Perform enqueue
      data[tail] = x;
      tail = (tail + 1) % data.size(), ++count;
    }

    T dequeue(void) {
      if (count) {
        --count;
        T ret = data[head];
        head = (head + 1) % data.size();
        return ret;
      }
      throw length_error("empty queue");
    }

    const size_t &size(void) const {
      return count;
    }
};
// @exclude

void test(void) {
  Queue<int> q;
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

  q.enqueue(14); // now the vector (data) is resized; but the head and tail (or elements) does not change accordingly. data[tail]=data[3]=14!
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

int main(int argc, char *argv[]) {
  test();
  Queue<int> q;
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
  } catch (exception &e) {
    cout << e.what() << endl;
  };
  // test resize()
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
