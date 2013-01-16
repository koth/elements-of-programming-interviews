#include <iostream>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
template <typename T>
vector<T> offline_sampling(vector<T> A, const int &k) {
  for (int i = 0; i < k; ++i) {
    default_random_engine gen((random_device())());  // random num generator
    // Generate random int in [i, A.size() - 1]
    uniform_int_distribution<int> dis(i, A.size() - 1);
    swap(A[i], A[dis(gen)]);
  }
  A.resize(k);
  return A;
}
// @exclude

int main(int argc, char *argv[]) {
  int n, k;
  srand(time(nullptr));
  vector<int> A;
  if (argc == 2) {
    n = atoi(argv[1]);
    k = 1 + rand() % n;
  } else if (argc == 3) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  } else {
    n = rand() % 1000000;
    k = 1 + rand() % n;
  }
  for (int i = 0; i < n; ++i) {
    A.emplace_back(i);
  }
  cout << n << ' ' << k << endl;
  vector<int> ans = offline_sampling(A, k);
  assert(ans.size() == k);
  for (int i = 0; i < k; ++i) {
    cout << ans[i] << ' ';
  }
  cout << endl;
  return 0;
}
