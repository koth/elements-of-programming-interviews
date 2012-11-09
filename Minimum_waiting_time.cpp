#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

// @include
template <typename T>
T minimum_waiting_time(vector<T> service_time) {
  // Sort the query time in increasing order
  sort(service_time.begin(), service_time.end());

  T waiting = 0;
  for (int i = 0; i < service_time.size(); ++i) {
    waiting += service_time[i] * (service_time.size() - (i + 1));
  }
  return waiting;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100;
  }
  vector<int> waiting_time;
  for (int i = 0; i < n; ++i) {
    waiting_time.push_back(rand() % 1000);
  }
  for (int i = 0; i < n; ++i) {
    cout << waiting_time[i] << ' ';
  }
  cout << endl;
  cout << minimum_waiting_time(waiting_time) << endl;
  return 0;
}
