// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void compare_kth_largest_heap_helper(const vector<int>& max_heap, int k, int x,
                                     int idx, int* larger, int* equal);

// @include
// -1 means smaller, 0 means equal, and 1 means larger.
int compare_kth_largest_heap(const vector<int>& max_heap, int k, int x) {
  int larger = 0, equal = 0;
  compare_kth_largest_heap_helper(max_heap, k, x, 0, &larger, &equal);
  return larger >= k ? 1 : (larger + equal >= k ? 0 : -1);
}

void compare_kth_largest_heap_helper(const vector<int>& max_heap, int k,
                                     int x, int idx, int* larger,
                                     int* equal) {
  if (*larger >= k || idx >= max_heap.size() || max_heap[idx] < x) {
    return;
  } else if (max_heap[idx] == x) {
    if (++*equal >= k) {
      return;
    }
  } else {  // max_heap[idx] > x.
    ++*larger;
  }
  compare_kth_largest_heap_helper(max_heap, k, x, (idx << 1) + 1, larger,
                                  equal);
  compare_kth_largest_heap_helper(max_heap, k, x, (idx << 1) + 2, larger,
                                  equal);
}
// @exclude

void small_test() {
  vector<int> max_heap = {10, 2, 9, 2, 2, 8, 8, 2, 2, 2, 2, 7, 7, 7, 7};
  assert(1 == compare_kth_largest_heap(max_heap, 3, 2));  // kth is larger.
  assert(1 == compare_kth_largest_heap(max_heap, 6, 2));  // kth is larger.
}

int main(int argc, char* argv[]) {
  small_test();
  //      5
  //    4  5
  //  4  4 4 3
  // 4
  vector<int> max_heap = {5, 4, 5, 4, 4, 4, 3, 4};
  int k, x;
  if (argc == 3) {
    k = atoi(argv[1]), x = atoi(argv[2]);
    int res = compare_kth_largest_heap(max_heap, k, x);
    cout << (res == -1 ? "smaller" : (res == 0 ? "equal" : "larger")) << endl;
  } else {
    assert(-1 == compare_kth_largest_heap(max_heap, 1, 6));  // expect smaller
    assert(0 == compare_kth_largest_heap(max_heap, 1, 5));   // expect equal
    assert(0 == compare_kth_largest_heap(max_heap, 6, 4));   // expect equal
    assert(0 == compare_kth_largest_heap(max_heap, 3, 4));   // expect equal
    assert(-1 == compare_kth_largest_heap(max_heap, 8, 4));  // expect smaller
    assert(1 == compare_kth_largest_heap(max_heap, 2, 4));   // expect larger
    assert(1 == compare_kth_largest_heap(max_heap, 2, 3));   // expect larger
  }
  return 0;
}
