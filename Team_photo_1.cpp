// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

using std::vector;

// @include
template <typename HeightType>
struct Player {
  const bool operator<(const Player &that) const {
    return height < that.height;
  }

  HeightType height;
};

template <typename HeightType>
class Team {
 public:
  explicit Team(const vector<HeightType>& height) {
    for (const HeightType& h : height) {
      members_.emplace_back(Player<HeightType>{h});
    }
  }

  const bool operator<(const Team &that) const {
    vector<Player<HeightType>> this_sorted(sortHeightMembers());
    vector<Player<HeightType>> that_sorted(that.sortHeightMembers());
    for (int i = 0; i < this_sorted.size() && i < that_sorted.size(); ++i) {
      if (this_sorted[i] < that_sorted[i] == false) {
        return false;
      }
    }
    return true;
  }

 private:
  vector<Player<HeightType>> sortHeightMembers(void) const {
    vector<Player<HeightType>> sorted_members(members_);
    sort(sorted_members.begin(), sorted_members.end());
    return sorted_members;
  }

  vector<Player<HeightType>> members_;
};
// @exclude

int main(int argc, char *argv[]) {
  vector<int> height(3);
  height[0] = 1, height[1] = 5, height[2] = 4;
  Team<int> t1(height);
  height[0] = 2, height[2] = 3, height[3] = 4;
  Team<int> t2(height);
  assert((t1 < t2) == false && (t2 < t1) == false);
  height[0] = 0, height[1] = 3, height[2] = 2;
  Team<int> t3(height);
  assert(t3 < t1 && (t1 < t3) == false && t3 < t2 && (t1 < t2) == false);
  return 0;
}
