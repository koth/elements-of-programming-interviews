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
    stack<pair<T, T> > s;

  public:
    const bool empty(void) const {
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
