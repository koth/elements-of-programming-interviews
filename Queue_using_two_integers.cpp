#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cmath>

using namespace std;

// @include
class Queue {
  private:
    unsigned val, size;

  public:
    Queue() : val(0), size(0) {}

    void enqueue(const unsigned &x) {
      val = val * 10 + x;
      ++size;
    }

    unsigned dequeue(void) {
      if (size) {
        unsigned ret = 0, d = floor(log10(val));
        if (d + 1 == size) {
          ret = val / pow(10.0, d);
          val -= pow(10.0, d) * ret;
        }
        --size;
        return ret;
      }
      throw length_error("empty queue");
    }
};
// @exclude

int main(int argc, char *argv[]) {
  Queue q;
  q.enqueue(0);
  q.enqueue(5);
  q.enqueue(0);
  q.enqueue(2);
  assert(0 == q.dequeue());
  assert(5 == q.dequeue());
  q.enqueue(3);
  assert(0 == q.dequeue());
  assert(2 == q.dequeue());
  assert(3 == q.dequeue());
  q.enqueue(0);
  q.enqueue(0);
  assert(0 == q.dequeue());
  assert(0 == q.dequeue());
  try {
    q.dequeue();
  } catch (exception &e) {
    cout << e.what() << endl;
  };
  return 0;
}
