#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// @include
template <typename CoordType, typename HeightType>
class Skyline {
  public:
    CoordType left, right;
    HeightType height;
};

template <typename CoordType, typename HeightType>
void merge_intersect_skylines(vector<Skyline<CoordType, HeightType> > &merged,
                              Skyline<CoordType, HeightType> &a, int &a_idx,
                              Skyline<CoordType, HeightType> &b, int &b_idx) {
  if (a.right <= b.right) {
    if (a.height > b.height) {
      if (b.right != a.right) {
        merged.emplace_back(a), ++a_idx;
        b.left = a.right;
      } else {
        ++b_idx;
      }
    } else if (a.height == b.height) {
      b.left = a.left, ++a_idx;
    } else {  // a.height < b.height
      if (a.left != b.left) {
        merged.emplace_back(
          Skyline<CoordType, HeightType>{a.left, b.left, a.height});
      }
      ++a_idx;
    }
  } else {  // a.right > b.right
    if (a.height >= b.height) {
      ++b_idx;
    } else {
      if (a.left != b.left) {
        merged.emplace_back(
          Skyline<CoordType, HeightType>{a.left, b.left, a.height});
      }
      a.left = b.right;
      merged.emplace_back(b), ++b_idx;
    }
  }
}

template <typename CoordType, typename HeightType>
vector<Skyline<CoordType, HeightType> > merge_skylines(
    vector<Skyline<CoordType, HeightType> > &L,
    vector<Skyline<CoordType, HeightType> > &R) {
  int i = 0, j = 0;
  vector<Skyline<CoordType, HeightType> > merged;

  while (i < L.size() && j < R.size()) {
    if (L[i].right < R[j].left) {
      merged.emplace_back(L[i++]);
    } else if (R[j].right < L[i].left) {
      merged.emplace_back(R[j++]);
    } else if (L[i].left <= R[j].left) {
      merge_intersect_skylines(merged, L[i], i, R[j], j);
    } else {  // L[i].left > R[j].left
      merge_intersect_skylines(merged, R[j], j, L[i], i);
    }
  }

  copy(L.cbegin() + i, L.cend(), back_inserter(merged));
  copy(R.cbegin() + j, R.cend(), back_inserter(merged));
  return merged;
}

template <typename CoordType, typename HeightType>
vector<Skyline<CoordType, HeightType> > drawing_skylines_helper(
    vector<Skyline<CoordType, HeightType> > &skylines,
    const int &start, const int &end) {
  if (end - start <= 1) {
    // 0 or 1 skyline, just copy it
    return {skylines.cbegin() + start, skylines.cbegin() + end};
  }
  int mid = start + ((end - start) >> 1);
  auto L = drawing_skylines_helper(skylines, start, mid);
  auto R = drawing_skylines_helper(skylines, mid, end);
  return merge_skylines(L, R);
}

template <typename CoordType, typename HeightType>
vector<Skyline<CoordType, HeightType> > drawing_skylines(
    vector<Skyline<CoordType, HeightType> > skylines) {
  return drawing_skylines_helper(skylines, 0, skylines.size());
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  // Random test 10000 times
  for (int times = 0; times < 2000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 5000;
    }
    vector<Skyline<int, int> > A;
    for (int i = 0; i < n; ++i) {
      int left = rand() % 1000;
      int right = left + 1 + rand() % 200;
      int height = rand() % 100;
      A.emplace_back(Skyline<int, int>{left, right, height});
    }
    /*
    for (int i = 0; i < A.size(); ++i) {
      cout << A[i].left << ' ' << A[i].right << ' ' << A[i].height << endl;
    }
    cout << endl;
    //*/
    vector<Skyline<int, int> > ans = drawing_skylines(A);
    /*
    for (int i = 0; i < ans.size(); ++i) {
      cout << ans[i].left << ' '  << ans[i].right << ' ' << ans[i].height << endl;
    }
    cout << endl;
    //*/
    cout << "n = " << n << endl;
    // just check there is no overlap
    // TODO : use O(n^2) method to check
    //cout << ans[0].left << " " << ans[0].right << " " << ans[0].height << endl;
    for (int i = 0; i < ans.size(); ++i) {
      //cout << ans[i].left << " " << ans[i].right << " " << ans[i].height << endl;
      assert(ans[i].left <= ans[i].right);
      if (i > 0) {
        assert(ans[i - 1].right <= ans[i].left);
        assert(ans[i - 1].right != ans[i].left || ans[i - 1].height != ans[i].height);
      }
    }
  }
  return 0;
}
