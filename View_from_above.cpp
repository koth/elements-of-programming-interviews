#include <iostream>
#include <memory>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
template <typename XaxisType, typename ColorType, typename HeightType>
class LineSegment {
  public:
    XaxisType left, right;  // specifies the interval
    ColorType color;
    HeightType height;

    bool operator<(const LineSegment &that) const {
      return height < that.height;
    }
};

template <typename XaxisType, typename ColorType, typename HeightType>
class Endpoint {
  public:
    XaxisType val;
    bool isLeft;
    int idx;

    bool operator<(const Endpoint &that) const {
      return val < that.val;
    }
};

template <typename XaxisType, typename ColorType, typename HeightType>
void calculate_view_from_above(
  const vector<LineSegment<XaxisType, ColorType, HeightType> > &A) {
  vector<Endpoint<XaxisType, ColorType, HeightType> > E;
  for (int i = 0; i < A.size(); ++i) {
    E.emplace_back(Endpoint<XaxisType, ColorType, HeightType>{A[i].left, true, i});
    E.emplace_back(
      Endpoint<XaxisType, ColorType, HeightType>{A[i].right, false, i});
  }
  sort(E.begin(), E.end());

  map<HeightType, int> T;
  for (const Endpoint<XaxisType, ColorType, HeightType> &e: E) {
    if (e.isLeft == true) {
      T[A[e.idx].height] = e.idx;
    } else {  // e.isLeft == false
      cout << A[T.rbegin()->second].color << " "
        << A[T.rbegin()->second].height << endl;
      T.erase(A[e.idx].height);
    }
  }
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100000;
  }
  unordered_set<int> heights;
  vector<LineSegment<int, int, int> > A;
  for (int i = 0; i < n; ++i) {
    int l = rand() % n;
    int r = l + 1 + rand() % 100;
    int c = rand() % 100;
    int h;
    do {
      h = rand() % (3 * n);
    } while (heights.find(h) != heights.end());
    heights.emplace(h);
    A.emplace_back(LineSegment<int, int, int>{l, r, c, h});
  }
  /*
  for (const LineSegment<int, int, int> &s : A) {
    cout << s.left << " " << s.right << " " << s.color << " " << s.height << endl;
  }
  //*/
  calculate_view_from_above(A);
  return 0;
}
