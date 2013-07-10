// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::shared_ptr;
using std::vector;
using std::unordered_set;

// @include
template <typename XaxisType, typename ColorType, typename HeightType>
struct LineSegment {
  XaxisType left, right;  // specifies the interval
  ColorType color;
  HeightType height;
};

template <typename XaxisType, typename ColorType, typename HeightType>
class Endpoint {
 public:
  const bool operator<(const Endpoint &that) const {
    return val() < that.val();
  }

  const XaxisType &val(void) const {
    return isLeft_ ? l_->left : l_->right;
  }

  bool isLeft_;
  const LineSegment<XaxisType, ColorType, HeightType>* l_;
};

template <typename XaxisType, typename ColorType, typename HeightType>
void calculate_view_from_above(
    const vector<LineSegment<XaxisType, ColorType, HeightType>>& A) {
  vector<Endpoint<XaxisType, ColorType, HeightType>> E;
  for (const auto& a : A) {
    E.emplace_back(Endpoint<XaxisType, ColorType, HeightType>{true, &a});
    E.emplace_back(Endpoint<XaxisType, ColorType, HeightType>{false, &a});
  }
  sort(E.begin(), E.end());

  XaxisType prev_xaxis = E.front().val();  // the first left end point
  shared_ptr<LineSegment<XaxisType, ColorType, HeightType>> prev = nullptr;
  map<HeightType, const LineSegment<XaxisType, ColorType, HeightType>*> T;
  for (const auto& e: E) {
    if (T.empty() == false && prev_xaxis != e.val()) {
      if (prev == nullptr) {  // found first segment
        prev = shared_ptr<LineSegment<XaxisType, ColorType, HeightType>>(
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

    if (e.isLeft_ == true) {  // left end point
      T.emplace(e.l_->height, e.l_);
    } else {  // right end point
      T.erase(e.l_->height);
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
  vector<LineSegment<int, int, int>> A;
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
  for (const LineSegment<int, int, int> &s : A) {
    cout << "line segment, left = " << s.left << ", right = " << s.right
         << ", color = " << s.color << ", height = " << s.height << endl;
  }
  calculate_view_from_above(A);
  return 0;
}
