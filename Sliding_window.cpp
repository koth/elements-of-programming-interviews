#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <cassert>

using namespace std;

template <typename T>
class Queue {
  private:
    queue<T> Q;
    deque<T> D;

  public:
    void enqueue(const T &x) {
      Q.emplace(x);
      while (D.empty() == false && D.back() < x) {
        D.pop_back();
      }
      D.emplace_back(x);
    }

    T &front(void) {
      return Q.front();
    }

    const T &front(void) const {
      return Q.front();
    }

    T dequeue(void) {
      if (Q.empty() == false) {
        T ret = Q.front();
        if (ret == D.front()) {
          D.pop_front();
        }
        Q.pop();
        return ret;
      }
      throw length_error("empty queue");
    }

    const T &max(void) const {
      if (D.empty() == false) {
        return D.front();
      }
      throw length_error("empty queue");
    }
};

// @include
class TrafficElement {
  public:
    int time, volume;

    const bool operator<(const TrafficElement &that) const {
      return time < that.time;
    }
    
    const bool operator==(const TrafficElement &that) const {
      return time == that.time && volume == that.volume;
    }
};

void TrafficVolumes(const vector<TrafficElement> &A, const int &w) {
  Queue<TrafficElement> Q;
  for (int i = 0; i < A.size(); ++i) {
    Q.enqueue(A[i]);
    while (A[i].time - Q.front().time > w) {
      Q.dequeue();
    }
    cout << "Max after inserting " << i << " is " << Q.max().volume << endl;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  int w = 3;
  vector<TrafficElement> A = {TrafficElement{0,0}, TrafficElement{1,1}, 
                              TrafficElement{2,3}, TrafficElement{3,1}, 
                              TrafficElement{4,0}, TrafficElement{5,2},
                              TrafficElement{6,2}, TrafficElement{7,2}};
  TrafficVolumes(A, w);
}
