#include <iostream>
#include <iterator>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

// @include
template <typename T>
void indirect_sort(const string &file_name) {
  // Store file records into A
  ifstream ifs(file_name.c_str());
  vector<T> A;
  T x;
  while (ifs >> x) {
    A.emplace_back(x);
  }

  // Initialize P
  vector<T*> P;
  for (T &a : A) {
    P.emplace_back(&a);
  }

  // Indirect sort file
  sort(P.begin(), P.end(), [](const T* a, const T* b) -> bool {
                             return *a < *b;
                           });

  // Output file
  ofstream ofs(file_name.c_str());
  for (const T* p : P) {
    ofs << *p << endl;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    cout << "times = " << times << endl;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<int> A;
    generate_n(back_inserter(A), n, [&]{ return rand(); });
    ofstream ofs("input.txt");
    for (const int &a : A) {
      ofs << a << endl;
    }

    indirect_sort<int>("input.txt");
    ifstream ifs("input.txt");
    A.clear();
    int x;
    while (ifs >> x) {
      A.emplace_back(x);
    }
    assert(is_sorted(A.begin(), A.end()));
    remove("input.txt");
  }
  return 0;
}
