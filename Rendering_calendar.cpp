#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// @include
template <typename TimeType>
class Interval {
  public:
    TimeType start, finish;
};

template <typename TimeType>
class Endpoint {
  public:
    TimeType time;
    bool isStart;

    bool operator<(const Endpoint &e) const {
      return time != e.time ? time < e.time : (isStart && !e.isStart);
    }
};

template <typename TimeType>
int find_max_concurrent_events(const vector<Interval<TimeType> > &A) {
  // Build the endpoint array
  vector<Endpoint<TimeType> > E;
  for (const Interval<TimeType> &i : A) {
    E.emplace_back(Endpoint<TimeType>{i.start, true});
    E.emplace_back(Endpoint<TimeType>{i.finish, false});
  }
  // Sort the endpoint array according to the time
  sort(E.begin(), E.end());

  // Find the maximum number of events overlapped
  int max_count = 0, count = 0;
  for (const Endpoint<TimeType> &e : E) {
    if (e.isStart) {
      max_count = max(++count, max_count);
    } else {
      --count;
    }
  }
  return max_count;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  }else {
    n = 1 + rand() % 100000;
  }
  vector<Interval<int> > A;
  for (int i = 0; i < n; ++i) {
    Interval<int> temp;
    temp.start = rand() % 100000;
    temp.finish = temp.start + 1 + rand() % 10000;
    A.emplace_back(temp);
  }
  int ans = find_max_concurrent_events(A);
  cout << ans << endl;
  return 0;
}
