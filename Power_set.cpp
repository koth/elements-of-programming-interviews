#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

// @include
template <typename T>
void generate_power_set(const vector<T> &S) {
  for (int i = 0; i < (1 << S.size()); ++i) {
    int x = i;
    while (x) {
      int tar = log2(x & ~(x - 1));
      cout << S[tar];
      if (x &= x - 1) {
        cout << ',';
      }
    }
    cout << endl;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  vector<int> S;
  if (argc >= 2) {
    for (int i = 1; i < argc; ++i) {
      S.emplace_back(atoi(argv[i]));
    }
  } else {
    srand(time(nullptr));
    S.resize(rand() % 10 + 1);
    for (int i = 0; i < S.size(); ++i) {
      S[i] = i;
    }
  }
  generate_power_set(S);
  return 0;
}
