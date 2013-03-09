#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<int> rand_vector(int len) {
  vector<int> ret;
  while (len--) {
    ret.emplace_back(rand() % 100);
  }
  return ret;
}

// @include
template <typename ValueType>
ValueType knapsack(const int &w, const vector<pair<int, ValueType>> &items) {
  vector<ValueType> V(w + 1, 0);
  for (int i = 0; i < items.size(); ++i) {
    for (int j = w; j >= items[i].first; --j) {
      V[j] = max(V[j], V[j - items[i].first] + items[i].second);
    }
  }
  return V[w];
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  vector<int> weight, value;
  int n, W;
  if (argc == 1) {
    n = 1 + rand() % 100;
    W = 1 + rand() % 1000;
    weight = rand_vector(n), value = rand_vector(n);
  } else if (argc == 2) {
    n = atoi(argv[1]);
    W = 1 + rand() % 1000;
    weight = rand_vector(n), value = rand_vector(n);
  } else {
    n = atoi(argv[1]);
    W = atoi(argv[2]);
    for (int i = 0; i < n; ++i) {
      weight.emplace_back(atoi(argv[3 + i]));
    }
    for (int i = 0; i < n; ++i) {
      value.emplace_back(atoi(argv[3 + i + n]));
    }
  }
  cout << "Weight: ";
  for (int i = 0; i < n; ++i) {
    cout << weight[i] << ' ';
  }
  cout << endl << "Value: ";
  for (int i = 0; i < n; ++i) {
    cout << value[i] << ' ';
  }
  cout << endl;
  vector<pair<int, int>> items;
  for (int i = 0; i < weight.size(); ++i) {
    items.emplace_back(weight[i], value[i]);
  }
  cout << "knapsack size = " << W << endl;
  cout << "all value = " << knapsack(W, items) << endl;
  return 0;
}
