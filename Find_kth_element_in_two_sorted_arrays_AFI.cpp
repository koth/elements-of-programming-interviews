#include <limits.h>
#include <assert.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cassert>

using namespace std;

// below is the implementation from AFI, with FindOrderStatistic renamed to 
// find_kth_in_two_sorted_arrays for consistency with EFI
int find_kth_in_two_sorted_arrays(vector<int> a1, vector<int>a2, int k) {
  // Check the validity of input.
  assert(k > 0);
  assert(a1.size() + a2.size() >= k);
  // Find an index begin <= l < end such that a1[0]..a1[l-1]
  // and a2[0]..a2[k-l-1] are the smallest k numbers.
  int begin = max(0, (int) (k - a2.size()));
  int end = min((int) a1.size(), k) +1;
  long l;
  while(begin < end) {
    l = (begin + end)/2;
    // can we include a1[l] in the k smallest numbers?
    if((l < a1.size()) && (k-l > 0) && (a1[l] < a2[k-l-1])) {
      begin = l + 1;
    } else if ((l > 0) && (k-l < a2.size()) && (a1[l-1] > a2[k-l])) {
      // this is the case where we can discard a[l-1]
      // from the set of k smallest numbers.
      end = l;
    } else {
      // we found our answer since both inequalities were false.
      begin = l;
      break;
    }
  }
  if (begin == 0) {
    return a2[k - begin -1];
  } else if (begin == k) {
    return a1[k-1];
  } else {
    return max(a1[begin -1], a2[k - begin -1]);
  }
}

// O(n+m) brute-force checker
int check_answer(const vector<int> &A, const vector<int> &B, int k) {
  int i = 0, j = 0, count = 0, ret;
  while ((i < A.size() || j < B.size()) && count < k) {
    if (i < A.size() && j < B.size()) {
      if (A[i] < B[j]) {
        ret = A[i];
        ++i;
      } else {
        ret = B[j];
        ++j;
      }
    } else if (i < A.size()) {
      ret = A[i];
      ++i;
    } else {
      ret = B[j];
      ++j;
    }
    ++count;
  }
  return ret;
}


// test code, one directed test, then many random tests
int main(int argc, char **argv) {
  vector<int> A0;
  vector<int> B0;
  A0.push_back(0);
  A0.push_back(2);
  A0.push_back(4);
  A0.push_back(5);
  B0.push_back(1);
  B0.push_back(2);
  B0.push_back(3);
  B0.push_back(4);
  // directed test
  assert( 0 == find_kth_in_two_sorted_arrays(A0, B0, 1));
  assert( 1 == find_kth_in_two_sorted_arrays(A0, B0, 2));
  assert( 2 == find_kth_in_two_sorted_arrays(A0, B0, 3));
  assert( 2 == find_kth_in_two_sorted_arrays(A0, B0, 4));
  assert( 3 == find_kth_in_two_sorted_arrays(A0, B0, 5));
  assert( 4 == find_kth_in_two_sorted_arrays(A0, B0, 6));
  assert( 4 == find_kth_in_two_sorted_arrays(A0, B0, 7));
  assert( 5 == find_kth_in_two_sorted_arrays(A0, B0, 8));

  srand(time(NULL));
  // Random test 10000 times
  for (int times = 0; times < 10000; ++times) {
    vector<int> A, B;
    int n, m, k;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
      k = 1 + rand() % (n + m);
    } else if (argc == 4) {
      n = atoi(argv[1]), m = atoi(argv[2]), k = atoi(argv[3]);
    } else {
      n = 1 + rand() % 10000, m = 1 + rand() % 10000;
      k = 1 + rand() % (n + m);
    }
    for (size_t i = 0; i < n; ++i) {
      A.push_back(rand() % 100000);
    }
    for (size_t i = 0; i < m; ++i) {
      B.push_back(rand() % 100000);
    }
    sort(A.begin(), A.end()), sort(B.begin(), B.end());
    int ans = find_kth_in_two_sorted_arrays(A, B, k);
    cout << k << "th = " << ans << endl;
    // use O(n+m) brute-force checker to validate O(log n + log m) algo 
    // used in find_kth_in_two_sorted_arrays
    assert(ans == check_answer(A, B, k));
    A.clear(), B.clear();
  }
  return 0;
}
