#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;

// @include
template <typename T>
void generate_power_set_helper(const vector<T> &S, int idx, vector<T> &res) {
  if (res.empty() == false) {
    // Print the subset
    copy(res.cbegin(), res.cend() - 1, ostream_iterator<T>(cout, ","));
    cout << res.back();
  }
  cout << endl;

  for (int i = idx; i < S.size(); ++i) {
    res.emplace_back(S[i]);
    generate_power_set_helper(S, i + 1, res);
    res.pop_back();
  }
}

template <typename T>
void generate_power_set(const vector<T> &S) {
  vector<T> res;
  generate_power_set_helper(S, 0, res);
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
