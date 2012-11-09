#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
void dutch_flag_partition(vector<T> &A, const int &pivot_index) {
  T pivot = A[pivot_index];
  /**
   * Keep the following invariants during partitioning:
   * bottom group: A[0 : smaller - 1]
   * middle group: A[smaller : equal - 1]
   * unclassified group: A[equal : larger]
   * top group: A[larger + 1 : A.size() - 1]
   */
  int smaller = 0, equal = 0, larger = A.size() - 1;
  // When there is any unclassified element
  while (equal <= larger) {
    // A[equal] is the incoming unclassified element
    if (A[equal] < pivot) {
      swap(A[smaller++], A[equal++]);
    } else if (A[equal] == pivot) {
      ++equal;
    } else {  // A[equal] > pivot
      swap(A[equal], A[larger--]);
    }
  }
}
// @exclude

template <typename T>
vector<T> rand_vector(int len) {
  vector<T> ret;
  while (len--) {
    ret.emplace_back(rand() % 3);
  }
  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 100;
    }
    vector<int> A(rand_vector<int>(n));
    int pivot_index = rand() % A.size();
    int pivot = A[pivot_index];
    dutch_flag_partition(A, pivot_index);
    int i = 0;
    while (A[i] < pivot && i < A.size()) {
      cout << A[i] << ' ';
      ++i;
    }
    while (A[i] == pivot && i < A.size()) {
      cout << A[i] << ' ';
      ++i;
    }
    while (A[i] > pivot && i < A.size()) {
      cout << A[i] << ' ';
      ++i;
    }
    cout << endl;
    assert(i == A.size());
  }
  return 0;
}
