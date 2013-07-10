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
#include <array>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
vector<int> online_sampling(const int &n, const int &k) {
  unordered_map<int, int> H;
  default_random_engine gen((random_device())());  // random num generator
  for (int i = 0; i < k; ++i) {
    // Generate random int in [i, n - 1].
    uniform_int_distribution<int> dis(0, n - 1 - i);
    int r = dis(gen);
    auto ptr1 = H.find(r), ptr2 = H.find(n - 1 - i);
    if (ptr1 == H.end() && ptr2 == H.end()) {
      H[r] = n - 1 - i;
      H[n - 1 - i] = r;
    } else if (ptr1 == H.end() && ptr2 != H.end()) {
      H[r] = ptr2->second;
      ptr2->second = r;
    } else if (ptr1 != H.end() && ptr2 == H.end()) {
      H[n - 1 - i] = ptr1->second;
      ptr1->second = n - 1 - i;
    } else {
      int temp = ptr2->second;
      H[n - 1 - i] = ptr1->second;
      H[r] = temp;
    }
  }
  vector<int> res;
  for (int i = 0; i < k; ++i) {
    res.emplace_back(H[n - 1 - i]);
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
    cout << "result = ";
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
  return 0;
}
