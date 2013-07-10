#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

// @include
template <typename T>
void approximate_sort(istringstream &sin, const int &k) {
  priority_queue<T, vector<T>, greater<T>> min_heap;
  // Firstly push k elements into min_heap
  T x;
  for (int i = 0; i < k && sin >> x; ++i) {
    min_heap.push(x);
  }

  // Extract the minimum one for every incoming element
  while (sin >> x) {
    min_heap.push(x);
    cout << min_heap.top() << endl;
    min_heap.pop();
  }

  // Extract the remaining elements in min_heap
  while (!min_heap.empty()) {
    cout << min_heap.top() << endl;
    min_heap.pop();
  }
}
// @exclude

// It should print 1, 2, 3, 4, 5, 6, 7, ,8, 9
void simple_test(void) {
  vector<int> A = {2, 1, 5, 4, 3, 9, 8, 7, 6};
  stringstream ss;
  for (const int &a : A) {
    ss << a << ' ';
  }
  istringstream sin(ss.str());
  approximate_sort<int>(sin, 3);
}

int main(int argc, char *argv[]) {
  simple_test();
  srand(time(nullptr));
  int n, k;
  if (argc == 2) {
    n = atoi(argv[1]);
    k = 1 + rand() % n;
  } else if (argc == 3) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  } else {
    n = 1 + rand() % 100000;
    k = 1 + rand() % n;
  }
  cout << "n = " << n << " k = " << k << endl;
  vector<int> A;
  for (int i = 0; i < n; ++i) {
    A.push_back(rand());
  }
  stringstream ss;
  for (const int &a : A) {
    ss << a << ' ';
  }
  istringstream sin(ss.str());
  approximate_sort<int>(sin, n - 1);
  return 0;
}
