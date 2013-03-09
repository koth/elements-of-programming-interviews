#include <iostream>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
template <typename T>
void online_median(istringstream &sin) {
  // Min-heap stores the bigger part of the stream
  priority_queue<T, vector<T>, greater<T>> H;
  // Max-heap stores the smaller part of the stream
  priority_queue<T, vector<T>, less<T>> L;

  T x;
  while (sin >> x) {
    if (L.empty() == false && x > L.top()) {
      H.emplace(x);
    } else {
      L.emplace(x);
    }
    if (H.size() > L.size() + 1) {
      L.emplace(H.top());
      H.pop();
    } else if (L.size() > H.size() + 1) {
      H.emplace(L.top());
      L.pop();
    }

    if (H.size() == L.size()) {
      cout << 0.5 * (H.top() + L.top()) << endl;
    } else {
      cout << (H.size() > L.size() ? H.top() : L.top()) << endl;
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int num;
  if (argc == 2) {
    num = atoi(argv[1]);
  } else {
    num = 1 + rand() % 100000;
  }
  vector<int> stream;
  for (int i = 0; i < num; ++i) {
    stream.emplace_back(rand() % 10000);
  }
  string s;
  for (int i = 0; i < stream.size(); ++i) {
    cout << stream[i] << endl;
    stringstream ss;
    ss << stream[i];
    s += ss.str();
    s += ' ';
  }
  cout << endl;
  istringstream sin(s);
  online_median<int>(sin);
  return 0;
}
