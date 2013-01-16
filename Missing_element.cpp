#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <fstream>
#include <cassert>
#include <bitset>
#include <vector>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
int find_missing_element(ifstream &ifs) {
  vector<size_t> counter(1 << 16, 0);
  unsigned int x;
  while (ifs >> x) {
    ++counter[x >> 16];
  }

  for (int i = 0; i < counter.size(); ++i) {
    // Find one bucket contains less than (1 << 16) elements
    if (counter[i] < (1 << 16)) {
      bitset<(1 << 16)> bit_vec;
      ifs.clear();
      ifs.seekg(0, ios::beg);
      while (ifs >> x) {
        if (i == (x >> 16)) {
          bit_vec.set(((1 << 16) - 1) & x);  // gets the lower 16 bits of x
        }
      }
      ifs.close();

      for (int j = 0; j < (1 << 16); ++j) {
        if (bit_vec.test(j) == 0) {
          return (i << 16) | j;
        }
      }
    }
  }
  // @exclude
  throw invalid_argument("no missing element");
  // @include
}
// @exclude

int main(int argc, char *argv[]) {
  int n = 300000000;
  srand(time(nullptr));
  if (argc == 2) {
    n = atoi(argv[1]);
  }
  unordered_set<int> hash;
  ofstream ofs("missing.txt");
  for (int i = 0; i < n; ++i) {
    int x;
    do {
      x = rand();
    } while (hash.emplace(x).second == false);
    ofs << x << endl;
  }
  ofs.close();
  ifstream ifs("missing.txt");
  int missing = find_missing_element(ifs);
  assert(hash.find(missing) == hash.cend());
  // Remove file after the execution
  remove("missing.txt");
  cout << missing << endl;
  return 0;
}
