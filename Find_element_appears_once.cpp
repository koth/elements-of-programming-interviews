#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// @include
int find_element_appears_once(const vector<int> &A) {
  int ones = 0, twos = 0;
  int next_ones, next_twos;
  for (const int &i : A) {
    next_ones = (~i & ones) | (i & ~ones & ~twos);
    next_twos = (~i & twos) | (i & ones);
    ones = next_ones, twos = next_twos;
  }
  return ones;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    vector<int> A;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    int single = rand() % n;
    for (int i = 0; i < n; ++i) {
      A.emplace_back(i);
      if (i != single) {
        A.emplace_back(i);
        A.emplace_back(i);
      }
    }
    cout << "Singleton element: " << find_element_appears_once(A) << endl;
    assert(find_element_appears_once(A) == single);
  }
  return 0;
}
