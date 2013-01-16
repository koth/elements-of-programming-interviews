#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
template <typename CoinType>
CoinType pick_up_coins_helper(const vector<CoinType> &C, const int &a,
                              const int &b, vector<vector<CoinType> > &T) {
  if (a > b) {
    return 0;  // base condition
  }

  if (T[a][b] == -1) {
    T[a][b] = max(C[a] + min(pick_up_coins_helper(C, a + 2, b, T),
                             pick_up_coins_helper(C, a + 1, b - 1, T)),
                  C[b] + min(pick_up_coins_helper(C, a + 1, b - 1, T),
                             pick_up_coins_helper(C, a, b - 2, T)));
  }
  return T[a][b];
}

template <typename CoinType>
CoinType pick_up_coins(vector<CoinType> &C) {
  vector<vector<CoinType> > T(C.size(), vector<int>(C.size(), -1));
  return pick_up_coins_helper(C, 0, C.size() - 1, T);
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  vector<int> C;
  if (argc >= 2) {
    for (int i = 1; i < argc; ++i) {
      C.emplace_back(atoi(argv[i]));
    }
  } else {
    C.resize(1 + rand() % 1000);
    for (int i = 0; i < C.size(); ++i) {
      C[i] = rand() % 100;
    }
  }
  for (size_t i = 0; i < C.size(); ++i) {
    cout << C[i] << ' ';
  }
  cout << endl;
  cout << pick_up_coins(C) << endl;
  return 0;
}
