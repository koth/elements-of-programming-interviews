// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <stack>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::stack;
using std::uniform_int_distribution;
using std::vector;

// @include
template <typename T>
void insert(stack<T>* S, const T& e) {
  if (S->empty() || S->top() <= e) {
    S->push(e);
  } else {
    T f = S->top();
    S->pop();
    insert(S, e);
    S->push(f);
  }
}

template <typename T>
void sort(stack<T>* S) {
  if (!S->empty()) {
    T e = S->top();
    S->pop();
    sort(S);
    insert(S, e);
  }
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    stack<int> S;
    uniform_int_distribution<int> dis(0, 999999);
    for (int i = 0; i < n; ++i) {
      S.push(dis(gen));
    }
    sort(&S);
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
