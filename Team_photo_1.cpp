#include <iostream>
#include <algorithm>
#include <limits>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
template <typename HeightType>
class Player {
  public:
    HeightType height;

    const bool operator<(const Player &that) const {
      return height < that.height;
    }
};

template <typename HeightType>
class Team {
  private:
    vector<Player<HeightType> > members;

    vector<Player<HeightType> > sortHeightMembers(void) const {
      vector<Player<HeightType> > sorted_members(members);
      sort(sorted_members.begin(), sorted_members.end());
      return sorted_members;
    }

  public:
    const bool operator<(const Team &that) const {
      vector<Player<HeightType> > this_sorted(sortHeightMembers());
      vector<Player<HeightType> > that_sorted(that.sortHeightMembers());
      for (int i = 0; i < this_sorted.size() && i < that_sorted.size(); ++i) {
        if (this_sorted[i] < that_sorted[i] == false) {
          return false;
        }
      }
      return true;
    }
    // @exclude
    Team(const vector<HeightType> &height) {
      for (const HeightType &h : height) {
        members.emplace_back(Player<HeightType>{h});
      }
    }
    // @include
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
