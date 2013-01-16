#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <stack>

using namespace std;

// @include
template <typename T>
class Stack {
  private:
    stack<T> s;
    stack<pair<T, int> > aux;

  const public:
    const bool empty(void) const {
      return s.empty();
    }

    const T &max(void) const {
      if (empty() == false) {
        return aux.top().first;
      }
      throw length_error("empty stack");
    }

    T pop(void) {
      if (empty() == false) {
        T ret = s.top();
        s.pop();
        if (ret == aux.top().first) {
          --aux.top().second;
          if (aux.top().second == 0) {
            aux.pop();
          }
        }
        return ret;
      }
      throw length_error("empty stack");
    }

    void push(const T &x) {
      s.emplace(x);
      if (aux.empty() == false) {
        if (x == aux.top().first) {
          ++aux.top().second;
        } else if (x > aux.top().first) {
          aux.emplace(x, 1);
        }
      } else {
        aux.emplace(x, 1);
      }
    }
};
// @exclude

int main(int argc, char *argv[]) {
  Stack<int> s;
  s.push(1);
  s.push(2);
  assert(s.max() == 2);
  cout << s.max() << endl;  // 2
  cout << s.pop() << endl;  // 2
  assert(s.max() == 1);
  cout << s.max() << endl;  // 1
  s.push(3);
  s.push(2);
  assert(s.max() == 3);
  cout << s.max() << endl;  // 3
  s.pop();
  assert(s.max() == 3);
  cout << s.max() << endl;  // 3
  s.pop();
  assert(s.max() == 1);
  cout << s.max() << endl;  // 1
  s.pop();
  try {
    s.max();
    s.pop();
    s.pop();
    s.pop();
    s.pop();
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  return 0;
}
