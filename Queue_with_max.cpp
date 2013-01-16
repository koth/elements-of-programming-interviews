#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <stack>

using namespace std;

template <typename T>
class Stack {
  private:
    stack<pair<T, T> > s;

  public:
    bool empty(void) const {
      return s.empty();
    }

    const T &max(void) const {
      if (empty() == false) {
        return s.top().second;
      }
      throw length_error("empty stack");
    }

    T pop(void) {
      if (empty() == false) {
        T ret = s.top().first;
        s.pop();
        return ret;
      }
      throw length_error("empty stack");
    }

    void push(const T &x) {
      s.emplace(x, std::max(x, empty() ? x : s.top().second));
    }
};

// @include
template <typename T>
class Queue {
  private:
    Stack<T> A, B;

  public:
    void enqueue(const T &x) {
      A.push(x);
    }

    T dequeue(void) {
      if (B.empty()) {
        while (A.empty() == false) {
          B.push(A.pop());
        }
      }
      if (B.empty() == false) {
        return B.pop();
      }
      throw length_error("empty queue");
    }

    const T &max(void) const {
      if (A.empty() == false) {
        return B.empty() ? A.max() : std::max(A.max(), B.max());
      } else {  // A.empty() == true
        if (B.empty() == false) {
          return B.max();
        }
        throw length_error("empty queue");
      }
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
