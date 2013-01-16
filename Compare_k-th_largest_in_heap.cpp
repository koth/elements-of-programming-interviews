#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// @include
template <typename T>
void compare_k_th_largest_heap_helper(const vector<T> &max_heap, const int &k,
                                      const T &x, const int &idx, int &larger,
                                      int &equal) {
  if (idx < max_heap.size()) {
    if (max_heap[idx] < x) {
      return;
    } else if (max_heap[idx] == x) {
      ++equal;
    } else {  // max_heap[idx] > x
      ++larger;
    }

    if (equal < k && larger < k) {
      compare_k_th_largest_heap_helper(max_heap, k, x, (idx << 1) + 1, larger,
                                       equal);
      compare_k_th_largest_heap_helper(max_heap, k, x, (idx << 1) + 2, larger,
                                       equal);
    }
  }
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
  //    4  4
  //  3  3 3 3
  // 2
  vector<int> max_heap;
  max_heap.emplace_back(5);
  max_heap.emplace_back(4);
  max_heap.emplace_back(4);
  max_heap.emplace_back(3);
  max_heap.emplace_back(3);
  max_heap.emplace_back(3);
  max_heap.emplace_back(3);
  max_heap.emplace_back(2);
  int k, x;
  if (argc == 3) {
    k = atoi(argv[1]), x = atoi(argv[2]);
    int res = compare_k_th_largest_heap(max_heap, k, x);
    cout << (res == -1 ? "smaller" : (res == 0 ? "equal" : "larger")) << endl;
  } else {
    assert(-1 == compare_k_th_largest_heap(max_heap, 1, 6));
    assert(0 == compare_k_th_largest_heap(max_heap, 1, 5));
    assert(0 == compare_k_th_largest_heap(max_heap, 2, 4));
    assert(1 == compare_k_th_largest_heap(max_heap, 2, 3));
  }
  return 0;
}
