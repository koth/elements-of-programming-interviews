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

    const bool operator<(const LineSegment &that) const {
      return height < that.height;
    }
};

template <typename XaxisType, typename ColorType, typename HeightType>
class Endpoint {
  public:
    bool isLeft;
    const LineSegment<XaxisType, ColorType, HeightType>* l;

    const bool operator<(const Endpoint &that) const {
      return val() < that.val();
    }

    const XaxisType &val(void) const {
      return isLeft ? l->left : l->right;
    }
};

template <typename XaxisType, typename ColorType, typename HeightType>
void calculate_view_from_above(
  const vector<LineSegment<XaxisType, ColorType, HeightType> > &A) {
  vector<Endpoint<XaxisType, ColorType, HeightType> > E;
  for (int i = 0; i < A.size(); ++i) {
    E.emplace_back(Endpoint<XaxisType, ColorType, HeightType>{true, &A[i]});
    E.emplace_back(Endpoint<XaxisType, ColorType, HeightType>{false, &A[i]});
  }
  sort(E.begin(), E.end());

  XaxisType prev_xaxis = E.front().val();  // the first left end point
  shared_ptr<LineSegment<XaxisType, ColorType, HeightType> > prev = nullptr;
  map<HeightType, const LineSegment<XaxisType, ColorType, HeightType>*> T;
  for (const Endpoint<XaxisType, ColorType, HeightType> &e: E) {
    if (T.empty() == false && prev_xaxis != e.val()) {
      if (prev == nullptr) {  // found first segment
        prev = shared_ptr<LineSegment<XaxisType, ColorType, HeightType> >(
          new LineSegment<XaxisType, ColorType, HeightType>{
            prev_xaxis, e.val(), T.crbegin()->second->color, 
            T.crbegin()->second->height});
      } else {
        if (prev->height == T.crbegin()->second->height &&
            prev->color == T.crbegin()->second->color) {
          prev->right = e.val();
        } else {
          cout << "[" << prev->left << ", " << prev->right << "]"
               << ", color = " << prev->color << ", height = "
               << prev->height << endl;
          *prev = {prev_xaxis, e.val(), T.crbegin()->second->color,
                   T.crbegin()->second->height};
        }
      }
    }
    prev_xaxis = e.val();

    if (e.isLeft == true) {  // left end point
      T.emplace(make_pair(e.l->height, e.l));
    } else {  // right end point
      T.erase(e.l->height);
    }
  }

  // Output the remaining segment if any
  if (prev) {
    cout << "[" << prev->left << ", " << prev->right << "]"
         << ", color = " << prev->color << ", height = "
         << prev->height << endl;
  }
}
// @exclude

int main(int argc, char *argv[]) {
  vector<LineSegment<int, int, int> > A;
  A.emplace_back(LineSegment<int, int, int>{0, 4, 0, 0});
  A.emplace_back(LineSegment<int, int, int>{1, 3, 1, 2});
  A.emplace_back(LineSegment<int, int, int>{2, 7, 2, 1});
  A.emplace_back(LineSegment<int, int, int>{4, 5, 3, 3});
  A.emplace_back(LineSegment<int, int, int>{5, 7, 3, 0});
  A.emplace_back(LineSegment<int, int, int>{6, 10, 0, 2});
  A.emplace_back(LineSegment<int, int, int>{8, 9, 0, 1});
  A.emplace_back(LineSegment<int, int, int>{9, 18, 4, 0});
  A.emplace_back(LineSegment<int, int, int>{11, 13, 3, 2});
  A.emplace_back(LineSegment<int, int, int>{12, 15, 4, 1});
  A.emplace_back(LineSegment<int, int, int>{14, 15, 2, 2});
  A.emplace_back(LineSegment<int, int, int>{16, 17, 3, 2});
  //*
  for (const LineSegment<int, int, int> &s : A) {
    cout << "line segment, left = " << s.left << ", right = " << s.right << ", color = " << s.color << ", height = " << s.height << endl;
  }
  /*/
  calculate_view_from_above(A);
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100000;
  }
  A.clear();
  unordered_set<int> heights;
  for (int i = 0; i < n; ++i) {
    int l = rand() % n;
    int r = l + 1 + rand() % 100;
    int c = rand() % 100;
    int h;
    do {
      h = rand() % (3 * n);
    } while (heights.find(h) != heights.cend());
    heights.emplace(h);
    A.emplace_back(LineSegment<int, int, int>{l, r, c, h});
  }
  for (const LineSegment<int, int, int> &s : A) {
    cout << "line segment, left = " << s.left << ", right = " << s.right << ", color = " << s.color << ", height = " << s.height << endl;
  }
  //*/
  calculate_view_from_above(A);
  return 0;
}
