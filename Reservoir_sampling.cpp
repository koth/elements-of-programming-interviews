#include <iostream>
#include <random>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
template <typename T>
vector<T> reservoir_sampling(istringstream &sin, const int &k) {
  T x;
  vector<T> R;
  // Store the first k elements
  for (int i = 0; i < k && sin >> x; ++i) {
    R.emplace_back(x);
  }

  // After the first k elements
  int element_num = k + 1;
  while (sin >> x) {
    default_random_engine gen((random_device())());  // random num generator
    // Generate random int in [0, element_num]
    uniform_int_distribution<int> dis(0, element_num++);
    int tar = dis(gen);
    if (tar < k) {
      R[tar] = x;
    }
  }
  return R;
}
// @exclude

int main(int argc, char *argv[]) {
  int n, k;
  srand(time(nullptr));
  if (argc == 2) {
    n = atoi(argv[1]);
    k = 1 + rand() % n;
  } else if (argc == 3) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  } else {
    n = rand() % 100000;
    k = 1 + rand() % n;
  }
  vector<int> A;
  for (int i = 0; i < n; ++i) {
    A.emplace_back(i);
  }
  string s;
  for (int i = 0; i < A.size(); ++i) {
    stringstream ss;
    ss << A[i];
    s += ss.str();
    s += ' ';
  }
  cout << n << ' ' << k << endl;
  istringstream sin(s);
  vector<int> ans = reservoir_sampling<int>(sin, k);
  assert(ans.size() == k);
  /*
  copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  //*/
  return 0;
}
