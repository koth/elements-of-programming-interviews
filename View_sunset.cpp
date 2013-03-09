#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
vector<pair<int, T>> examine_buildings_with_sunset(istringstream &sin) {
  int idx = 0;  // building's index
  T height;
  // Stores (building_idx, building_height) pair with sunset views
  vector<pair<int, T>> buildings_with_sunset;
  while (sin >> height) {
    while (buildings_with_sunset.empty() == false &&
           height >= buildings_with_sunset.back().second) {
      buildings_with_sunset.pop_back();
    }
    buildings_with_sunset.emplace_back(idx++, height);
  }

  // Returns buildings with its index and height.
  return buildings_with_sunset;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    stringstream ss;
    for (int i = 0; i < n; ++i) {
      int height = 1 + rand() % (2 * n);
      ss << height << ' ';
    }
    istringstream sin(ss.str());
    vector<pair<int, int>> res = examine_buildings_with_sunset<int>(sin);
    cout << res[0].first << ' ' << res[0].second << endl;
    for (int i = 1; i < res.size(); ++i) {
      cout << res[i].first << ' ' << res[i].second << endl;
      assert(res[i - 1].first < res[i].first);
      assert(res[i - 1].second > res[i].second);
    }
  }
  return 0;
}
