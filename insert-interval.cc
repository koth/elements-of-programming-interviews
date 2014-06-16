// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::min;
using std::random_device;
using std::stoul;
using std::uniform_int_distribution;
using std::vector;

// @include
struct Interval {
  int left, right;
};

vector<Interval> insert_interval(const vector<Interval>& intervals,
                                 Interval new_interval) {
  size_t i = 0;
  vector<Interval> res;
  // Insert intervals appeared before new_interval.
  while (i < intervals.size() && new_interval.left > intervals[i].right) {
    res.emplace_back(intervals[i++]);
  }

  // Merges intervals that overlap with new_interval.
  while (i < intervals.size() && new_interval.right >= intervals[i].left) {
    new_interval = {min(new_interval.left, intervals[i].left),
                    max(new_interval.right, intervals[i].right)};
    ++i;
  }
  res.emplace_back(new_interval);

  // Insert intervals appearing after new_interval.
  res.insert(res.end(), intervals.begin() + i, intervals.end());
  return res;
}
// @exclude

void check_intervals(const vector<Interval>& res) {
  // Only check the intervals do not overlap with each other.
  for (size_t i = 1; i < res.size(); ++i) {
    assert(res[i - 1].right < res[i].left);
  }
}

void small_test() {
  vector<Interval> A = {{1, 5}};
  Interval new_one = {0, 3};
  auto res = insert_interval(A, new_one);
  assert(res.size() == 1 && res.front().left == 0 && res.front().right == 5);
  new_one = {0, 0};
  res = insert_interval(A, new_one);
  assert(res.size() == 2 && res.front().left == 0 && res.front().right == 0 && res.back().left == 1 && res.back().right == 5);
}

int main(int argc, char* argv[]) {
  small_test();
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    size_t n;
    if (argc == 2) {
      n = stoul(argv[1]);
    } else {
      uniform_int_distribution<size_t> dis(1, 10000);
      n = dis(gen);
    }
    vector<Interval> A;
    int pre = 0;
    uniform_int_distribution<int> dis(1, 10);
    for (size_t i = 0; i < n; ++i) {
      Interval temp;
      temp.left = pre + dis(gen);
      temp.right = temp.left + dis(gen);
      pre = temp.right;
      A.emplace_back(temp);
    }
    uniform_int_distribution<int> tar_dis(0, 100);
    Interval target;
    target.left = tar_dis(gen);
    target.right = target.left + tar_dis(gen);
    /*
    cout << "A = ";
    for (const auto& a : A) {
      cout << "[" << a.left << ", " << a.right << "] ";
    }
    cout << endl;
    cout << "target = " << target.left << ", " << target.right << endl;
    //*/
    auto res = insert_interval(A, target);
    /*
    cout << "res = ";
    for (const auto& a : res) {
      cout << "[" << a.left << ", " << a.right << "] ";
    }
    cout << endl;
    //*/
    check_intervals(res);
  }
  return 0;
}
