#include <iostream>
#include <random>
#ifdef __clang__
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
vector<int> online_sampling(const int &n, const int &k) {
  unordered_map<int, int> table;
  vector<int> res;
  for (int i = 0; i < k; ++i) {
    default_random_engine gen((random_device())());  // random num generator
    // Generate random int in [i, n - 1]
    uniform_int_distribution<int> dis(i, n - 1);
    int r = dis(gen);
    auto it = table.find(r);
    if (it == table.end()) {  // r is not in table
      res.emplace_back(r);
      table.emplace(r, i);
    } else {  // r is in table
      res.emplace_back(it->second);
      it->second = i;
    }
  }
  return res;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n, k;
  if (argc == 2) {
    n = atoi(argv[1]);
    k = 1 + rand() % n;
  } else if (argc == 3) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  } else {
    n = 1 + rand() % 10000;
    k = 1 + rand() % n;
  }
  cout << "n = " << n << " k = " << k << endl;
  for (int i = 0; i < 6; ++i) {
    vector<int> res = online_sampling(n, k);
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
  return 0;
}
