#include <iostream>
#include <stdexcept>
#include <cassert>
#include <queue>

using namespace std;

// @include
template <typename T>
class Compare {
  public:
    bool operator()(const pair<int, T> &lhs, const pair<int, T> &rhs) const {
      return lhs.first < rhs.first;
    }
};

template <typename T>
class Stack :  // inherits empty(), pop(), and size() methods
  public priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> {
  private:
    int order;
    typedef priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> PQ;

  public:
    Stack() : order(0) {}

    const T &top() const {
      return PQ::top().second;
    }

    void push(const T &x) {
      PQ::emplace(order++, x);
    }
};

template <typename T>
class Queue :  // inherits empty(), pop(), and size() methods
  public priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> {
  private:
    int order;
    typedef priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> PQ;

  public:
    Queue() : order(0) {}

    const T &front() const {
      return PQ::top().second;
    }

    void push(const T &x) {
      PQ::emplace(order--, x);
    }
};
// @exclude

int main(int argc, char *argv[]) {
  Stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  assert(s.empty() == false);
  assert(s.size() == 3);
  assert(s.top() == 3);
  s.pop();
  assert(s.top() == 2);
  s.pop();
  s.push(4);
  assert(s.top() == 4);
  s.pop();
  s.pop();
  assert(s.empty() == true);
  try {
    s.pop();
  } catch (exception &e) {
    cout << "empty stack" << endl;
    cout << e.what() << endl;
  }

  Queue<int> q;
  q.push(1);
  q.push(2);
  assert(q.front() == 1);
  q.pop();
  assert(q.front() == 2);
  q.pop();
  assert(q.empty() == true);
  try {
    q.pop();
  } catch (exception &e) {
    cout << "empty queue" << endl;
    cout << e.what() << endl;
  }
  return 0;
}
