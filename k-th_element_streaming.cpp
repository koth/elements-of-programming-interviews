#include <iostream>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
template <typename T>
void find_k_th_largest_stream(istringstream &sin, const int &k) {
  priority_queue<T, vector<T>, greater<T>> min_heap;
  // The first k elements, output the minimum element
  T x;
  for (int i = 0; i < k && sin >> x; ++i) {
    min_heap.emplace(x);
    cout << min_heap.top() << endl;
  }

  // After the first k elements, output the k-th largest one
  while (sin >> x) {
    if (min_heap.top() < x) {
      min_heap.pop();
      min_heap.emplace(x);
    }
    cout << min_heap.top() << endl;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int num, k;
  if (argc == 2) {
    num = atoi(argv[1]);
    k = 1 + rand() % num;
  } else if (argc == 3) {
    num = atoi(argv[1]);
    k = atoi(argv[2]);
  } else {
    num = rand() % 100;
    k = 1 + rand() % num;
  }
  vector<int> stream;
  for (int i = 0; i < num; ++i) {
    stream.emplace_back(rand());
  }
  sort(stream.begin(), stream.end());
  stringstream ss;
  for (int i = 0; i < num; ++i) {
    cout << stream[i] << ' ';
    ss << stream[i] << ' ';
  }
  cout << endl;
  istringstream sin(ss.str());
  find_k_th_largest_stream<int>(sin, k);
  cout << "n = " << num << ", k = " << k << endl;
  return 0;
}
