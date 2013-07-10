#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// @include
template <typename T>
void compare_k_th_largest_heap_helper(const vector<T> &max_heap, const int &k,
                                      const T &x, const int &idx, int &larger,
                                      int &equal) {
  if (larger >= k || idx >= max_heap.size() || max_heap[idx] < x) {
    return;
  } else if (max_heap[idx] == x) {
    if (++equal >= k) {
      return;
    } 
  } else {  // max_heap[idx] > x
    ++larger;
  }
  compare_k_th_largest_heap_helper(max_heap, k, x, (idx << 1) + 1, larger,
                                   equal);
  compare_k_th_largest_heap_helper(max_heap, k, x, (idx << 1) + 2, larger,
                                   equal);
}

// -1 means smaller, 0 means equal, and 1 means larger
template <typename T>
int compare_k_th_largest_heap(const vector<T> &max_heap, const int &k,
                              const T &x) {
  int larger = 0, equal = 0;
  compare_k_th_largest_heap_helper(max_heap, k, x, 0, larger, equal);
  return larger >= k ? 1 : (larger + equal >= k ? 0 : -1);
}
// @exclude

int main(int argc, char *argv[]) {
  //      5
  //    4  5
  //  4  4 4 3
  // 4
  vector<int> max_heap;
  max_heap.emplace_back(5);
  max_heap.emplace_back(4);
  max_heap.emplace_back(5);
  max_heap.emplace_back(4);
  max_heap.emplace_back(4);
  max_heap.emplace_back(4);
  max_heap.emplace_back(3);
  max_heap.emplace_back(4);
  int k, x;
  if (argc == 3) {
    k = atoi(argv[1]), x = atoi(argv[2]);
    int res = compare_k_th_largest_heap(max_heap, k, x);
    cout << (res == -1 ? "smaller" : (res == 0 ? "equal" : "larger")) << endl;
  } else {
    assert(-1 == compare_k_th_largest_heap(max_heap, 1, 6));  // expect smaller
    assert(0 == compare_k_th_largest_heap(max_heap, 1, 5));   // expect equal
    assert(0 == compare_k_th_largest_heap(max_heap, 6, 4));   // expect equal
    assert(0 == compare_k_th_largest_heap(max_heap, 3, 4));   // expect equal
    assert(-1 == compare_k_th_largest_heap(max_heap, 8, 4));   // expect smaller
    assert(1 == compare_k_th_largest_heap(max_heap, 2, 4));   // expect larger
    assert(1 == compare_k_th_largest_heap(max_heap, 2, 3));   // expect larger
  }
  return 0;
}
