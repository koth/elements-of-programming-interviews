// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::istringstream;
using std::endl;
using std::greater;
using std::priority_queue;
using std::random_device;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

// @include
template <typename T>
void find_k_th_largest_stream(istringstream &sin, int k) {
  priority_queue<T, vector<T>, greater<T>> min_heap;
  // The first k elements, output the minimum element.
  T x;
  for (int i = 0; i < k && sin >> x; ++i) {
    min_heap.emplace(x);
    cout << min_heap.top() << endl;
  }

  // After the first k elements, output the k-th largest one.
  while (sin >> x) {
    if (min_heap.top() < x) {
      min_heap.pop();
      min_heap.emplace(x);
    }
    cout << min_heap.top() << endl;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  int num, k;
  if (argc == 2) {
    num = atoi(argv[1]);
    uniform_int_distribution<int> dis(1, num);
    k = dis(gen);
  } else if (argc == 3) {
    num = atoi(argv[1]);
    k = atoi(argv[2]);
  } else {
    uniform_int_distribution<int> num_dis(0, 100);
    num = num_dis(gen);
    uniform_int_distribution<int> dis(1, num);
    k = dis(gen);
  }
  vector<int> stream;
  uniform_int_distribution<int> dis(0, 9999999);
  for (int i = 0; i < num; ++i) {
    stream.emplace_back(dis(gen));
  }
  sort(stream.begin(), stream.end());
  stringstream ss;
  for (int i = 0; i < num; ++i) {
    cout << stream[i] << ' ';
    ss << stream[i] << ' ';
  }
  cout << endl;
  istringstream sin(ss.str());
  find_k_th_largest_stream<int>(sin, k);
  cout << "n = " << num << ", k = " << k << endl;
  return 0;
}
