#include <iostream>
#include <random>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
int find_set(vector<int> &set, const int &x) {
  if (set[x] != x) {
    set[x] = find_set(set, set[x]);  // path compression
  }
  return set[x];
}

void union_set(vector<int> &set, const int &x, const int &y) {
  int x_root = find_set(set, x), y_root = find_set(set, y);
  set[min(x_root, y_root)] = max(x_root, y_root);
}

vector<int> offline_minimum(const vector<int> &A, const vector<int> &E) {
  vector<int> R(A.size(), E.size());
  int pre = 0;

  // Initialize the collection of subsets
  for (int i = 0; i < E.size(); ++i) {
    for (int j = pre; j <= E[i]; ++j) {
      R[A[j]] = i;
    }
    pre = E[i] + 1;
  }

  vector<int> ret(E.size(), -1);  // stores the answer
  vector<int> set(E.size() + 1);  // the disjoint-set
  iota(set.begin(), set.end(), 0);  // initializes the disjoint-set
  for (int i = 0; i < A.size(); ++i) {
    if (find_set(set, R[i]) != E.size() && ret[find_set(set, R[i])] == -1) {
      ret[set[R[i]]] = i;
      union_set(set, set[R[i]], set[R[i]] + 1);
    }
  }
  return ret;
}
// @exclude

// O(nm) checking method
vector<int> check_answer(const vector<int> &A, const vector<int> &E) {
  vector<bool> exist(A.size(), false);
  vector<int> ans(E.size());

  for (int i = 0; i < E.size(); ++i) {
    int min_val = numeric_limits<int>::max();
    for (int j = 0; j <= E[i]; ++j) {
      if (A[j] < min_val && exist[A[j]] == false) {
        min_val = min(A[j], min_val);
      }
    }
    exist[min_val] = true;
    ans[i] = min_val;
  }
  /*
  cout << "ans2 = ";
  copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  */
  return ans;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n, m;
    if (argc == 2) {
      n = atoi(argv[1]);
      m = 1 + rand() % n;
    } else if (argc == 3) {
      n = atoi(argv[1]);
      m = atoi(argv[2]);
    } else {
      n = 1 + rand() % 1000;
      m = 1 + rand() % n;
    }
    cout << "n = " << n << ", m = " << m << endl;
    vector<int> A(n);
    iota(A.begin(), A.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(A.begin(), A.end(), g);
    //random_shuffle(A.begin(), A.end());
    /*
    cout << "A = ";
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    */
    vector<int> E;
    for (int i = 0; i < m; ++i) {
      E.emplace_back(i + rand() % (n - i));
    }
    sort(E.begin(), E.end());
    /*
    cout << "E = ";
    copy(E.begin(), E.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    */
    vector<int> ans = offline_minimum(A, E);
    /*
    cout << "ans1 = ";
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    */
    vector<int> tmp = check_answer(A, E);
    assert(equal(ans.begin(), ans.end(), tmp.begin()));
  }
  return 0;
}
