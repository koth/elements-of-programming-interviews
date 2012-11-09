#include <iostream>
#include <stdexcept>
#include <cassert>
#include <stack>

using namespace std;

// @include
template <typename T>
class Queue {
  private:
    stack<T> A, B;

  public:
    void enqueue(const T &x) {
      A.emplace(x);
    }

    T dequeue(void) {
      if (B.empty()) {
        while (!A.empty()) {
          B.emplace(A.top());
          A.pop();
        }
      }
      if (B.empty() == false) {
        T ret = B.top();
        B.pop();
        return ret;
      }
      throw length_error("empty queue");
    }
};
// @exclude

int main(int argc, char *argv[]) {
  Queue<int> Q;
  Q.enqueue(1);
  Q.enqueue(2);
  assert(1 == Q.dequeue());  // 1
  assert(2 == Q.dequeue());  // 2
  Q.enqueue(3);
  assert(3 == Q.dequeue());  // 3
  try {
    Q.dequeue();
  } catch (exception &e) {
    cout << e.what() << endl;  // throw
  }
  return 0;
}
