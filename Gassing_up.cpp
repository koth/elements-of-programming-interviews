#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
int find_start_city(const vector<T> &G, const vector<T> &D) {
  T carry = 0;
  pair<int, T> min(0, 0);
  for (int i = 1; i < G.size(); ++i) {
    carry += G[i - 1] - D[i - 1];
    if (carry < min.second) {
      min = {i, carry};
    }
  }
  return min.first;
}
// @exclude

template <typename T>
void check_ans(const vector<T> &G, const vector<T> &D, int c) {
  int s = c;
  T gas = 0;
  do {
    gas += G[s] - D[s];
    assert(gas >= 0);
    s = (s + 1) % G.size();
  } while (s != c);
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<int> G, D;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      int x = 1 + rand() % 200;
      sum += x;
      G.emplace_back(x);
    }
    sum -= n;
    for (int i = 0; i < n; ++i) {
      int x = 0;
      if (sum) {
        x = 1 + rand() % sum;
      }
      D.emplace_back(x + 1);
      sum -= x;
    }
    D.back() += sum;
    /*
    for (int i = 0; i < n; ++i) {
      cout << G[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
      cout << D[i] << ' ';
    }
    cout << endl;
    */
    int c = find_start_city(G, D);
    cout << "start city = " << c << endl;
    check_ans(G, D, c);
  }
  return 0;
}
