// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::vector;

// @include
struct Compare {
  bool operator()(const pair<size_t, int> &a, const pair<size_t, int> &b) {
    return a.second < b.second;
  }
};

vector<int> k_largest_in_binary_heap(const vector<int>& A, int k) {
  if (k <= 0) {
    return {};
  }

  // Stores the (index, value)-pair in this max-heap. Ordered by value.
  priority_queue<pair<size_t, int>,
                 vector<pair<size_t, int>>,
                 Compare> max_heap;
  max_heap.emplace(0, A[0]);  // the largest element stores at index 0.
  vector<int> res;
  for (int i = 0; i < k; ++i) {
    size_t idx = max_heap.top().first;
    res.emplace_back(max_heap.top().second);
    max_heap.pop();
    
    if ((idx << 1) + 1 < A.size()) {
      max_heap.emplace((idx << 1) + 1, A[(idx << 1) + 1]);
    }
    if ((idx << 1) + 2 < A.size()) {
      max_heap.emplace((idx << 1) + 2, A[(idx << 1) + 2]);
    }
  }
  return res;
}
// @exclude

int main(int argc, char* argv[]) {
  vector<int> max_heap = {10, 2, 9, 2, 2, 8, 8, 2, 2, 2, 2, 7, 7, 7, 7};
  auto res = k_largest_in_binary_heap(max_heap, 3);
  vector<int> expected_res = {10, 9, 8};
  assert(res.size() == 3 && equal(res.begin(), res.end(), expected_res.begin()));
  res = k_largest_in_binary_heap(max_heap, 5);
  expected_res = {10, 9, 8, 8, 7};
  assert(res.size() == 5 && equal(res.begin(), res.end(), expected_res.begin()));
  return 0;
}
