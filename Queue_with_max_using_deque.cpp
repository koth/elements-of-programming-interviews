#include <iostream>
#include <queue>
#include <stdexcept>
#include <cassert>

using namespace std;

// @include
template <typename T>
class Queue {
  private:
    queue<T> Q;
    deque<T> D;

  public:
    void enqueue(const T &x) {
      Q.emplace(x);
      while (D.empty() == false && D.back() < x) {
        D.pop_back();
      }
      D.emplace_back(x);
    }

    T dequeue(void) {
      if (Q.empty() == false) {
        T ret = Q.front();
        if (ret == D.front()) {
          D.pop_front();
        }
        Q.pop();
        return ret;
      }
      throw length_error("empty queue");
    }

    const T &max(void) const {
      if (D.empty() == false) {
        return D.front();
      }
      throw length_error("empty queue");
    }
};
// @exclude

int main(int argc, char *argv[]) {
  Queue<int> Q;
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
  } catch (exception &e) {
    cout << e.what() << endl;  // throw
  }
  try {
    Q.dequeue();
  } catch (exception &e) {
    cout << e.what() << endl;  // throw
  }
  return 0;
}
