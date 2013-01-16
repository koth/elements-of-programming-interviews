#include <iostream>
#include <cassert>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <stack>

using namespace std;

// @include
template <typename T>
void insert(stack<T> &S, const T &e) {
  if (S.empty() || S.top() <= e) {
    S.push(e);
  } else {
    T f = S.top();
    S.pop();
    insert(S, e);
    S.push(f);
  }
}

template <typename T>
void sort(stack<T> &S) {
  if (!S.empty()) {
    T e = S.top();
    S.pop();
    sort(S);
    insert(S, e);
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    stack<int> S;
    for (int i = 0; i < n; ++i) {
      S.push(rand());
    }
    sort(S);
    int pre = numeric_limits<int>::max();
    while (!S.empty()) {
      assert(pre >= S.top());
      cout << S.top() << endl;
      pre = S.top();
      S.pop();
    }
  }
  return 0;
}
