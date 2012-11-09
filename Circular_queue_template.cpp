#include <iostream>
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

int main(int argc, char *argv[]) {
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
