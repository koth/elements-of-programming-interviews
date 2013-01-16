#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

/*
template <typename T>
pair<int, int> find_positive_pair(const vector<T> &A, const T &k) {
  if (k < 0) {
    return make_pair(-1, -1);  // no pair for negative k
  }

  pair<int, int> ret(0, A.size() - 1);
  // Find the first positive or zero
  while (ret.first < ret.second && A[ret.first] < 0) {
    ++ret.first;
  }

  // Find the last positive or zero
  while (ret.first < ret.second && A[ret.second] < 0) {
    --ret.second;
  }

  while (ret.first < ret.second) {
    if (A[ret.first] + A[ret.second] == k) {
      return ret;
    } else if (A[ret.first] + A[ret.second] < k) {
      do {
        ++ret.first;
      } while (ret.first < ret.second && A[ret.first] < 0);
    } else {  // A[ret.first] + A[ret.second] > k
      do {
        --ret.second;
      } while (ret.first < ret.second && A[ret.second] < 0);
    }
  }
  return make_pair(-1, -1);  // no answer
}

template <typename T>
pair<int, int> find_negative_pair(const vector<T> &A, const T &k) {
  if (k >= 0) {
    return make_pair(-1, -1);  // no pair for positive k
  }

  pair<int, int> ret(0, A.size() - 1);
  // Find the first negative
  while (ret.first < ret.second && A[ret.first] >= 0) {
    ++ret.first;
  }

  // Find the last negative
  while (ret.first < ret.second && A[ret.second] >= 0) {
    --ret.second;
  }

  while (ret.first < ret.second) {
    if (A[ret.first] + A[ret.second] == k) {
      return ret;
    } else if (A[ret.first] + A[ret.second] < k) {
      do {
        --ret.second;
      } while (ret.first < ret.second && A[ret.second] >= 0);
    } else {  // A[ret.first] + A[ret.second] > k
      do {
        ++ret.first;
      } while (ret.first < ret.second && A[ret.first] >= 0);
    }
  }
  return make_pair(-1, -1);  // no answer
}
//*/

// @include
template <typename T, typename Comp>
pair<int, int> find_pair_using_comp(const vector<T> &A, const T &k,
                                    Comp comp) {
  pair<int, int> ret(0, A.size() - 1);
  while (ret.first < ret.second && comp(A[ret.first], 0)) {
    ++ret.first;
  }
  while (ret.first < ret.second && comp(A[ret.second], 0)) {
    --ret.second;
  }

  while (ret.first < ret.second) {
    if (A[ret.first] + A[ret.second] == k) {
      return ret;
    } else if (comp(A[ret.first] + A[ret.second], k)) {
      do {
        ++ret.first;
      } while (ret.first < ret.second && comp(A[ret.first], 0));
    } else {
      do {
        --ret.second;
      } while (ret.first < ret.second && comp(A[ret.second], 0));
    }
  }
  return {-1, -1};  // no answer
}

template <typename T>
pair<int, int> find_pos_neg_pair(const vector<T> &A, const T &k) {
  // ret.first for positive, and ret.second for negative
  pair<int, int> ret(A.size() - 1, A.size() - 1);
  // Find the last positive or zero
  while (ret.first >= 0 && A[ret.first] < 0) {
    --ret.first;
  }

  // Find the last negative
  while (ret.second >= 0 && A[ret.second] >= 0) {
    --ret.second;
  }

  while (ret.first >= 0 && ret.second >= 0) {
    if (A[ret.first] + A[ret.second] == k) {
      return ret;
    } else if (A[ret.first] + A[ret.second] > k) {
      do {
        --ret.first;
      } while (ret.first >= 0 && A[ret.first] < 0);
    } else {  // A[ret.first] + A[ret.second] < k
      do {
        --ret.second;
      } while (ret.second >= 0 && A[ret.second] >= 0);
    }
  }
  return {-1, -1};  // no answer
}

template <typename T>
pair<int, int> find_pair_sum_k(const vector<T> &A, const T &k) {
  pair<int, int> ret = find_pos_neg_pair(A, k);
  if (ret.first == -1 && ret.second == -1) {
    return k >= 0 ? find_pair_using_comp(A, k, less<T>()) :
           find_pair_using_comp(A, k, greater_equal<T>());
  }
  return ret;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc >= 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<int> A;
    for (size_t i = 0; i < n; ++i) {
      A.emplace_back(((rand() & 1) ? 1 : -1) * (rand() % 10000));
    }
    sort(A.begin(), A.end(), [](int x, int y) {return abs(x) < abs(y);});
    int k = ((rand() & 1) ? 1 : -1) * (rand() % 10000);
    /*
    for (const int & a : A) {
      cout << a << " ";
    }
    cout << endl << "k = " << k << endl;
    //*/
    pair<int, int> ans = find_pair_sum_k(A, k);
    if (ans.first != -1 && ans.second != -1) {
      assert(A[ans.first] + A[ans.second] == k);
      cout << A[ans.first] << "+" << A[ans.second] << "=" << k << endl;
    } else {
      sort(A.begin(), A.end());
      int l = 0, r = A.size() - 1;
      bool found = false;
      while (l < r) {
        if (A[l] + A[r] == k) {
          cout << A[l] << "+" << A[r] << "=" << k << endl;
          found = true;
          break;
        } else if (A[l] + A[r] < k) {
          ++l;
        } else {
          --r;
        }
      }
      cout << "no answer" << endl;
      assert(found == false);
    }
  }
  return 0;
}
