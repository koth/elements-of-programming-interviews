// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::min;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

string rand_string(int len) {
  default_random_engine gen((random_device())());
  string ret = "";
  while (len--) {
    uniform_int_distribution<int> dis('a', 'z');
    ret += dis(gen);
  }
  return ret;
}

// @include
int find_nearest_repetition(const vector<string>& s) {
  unordered_map<string, int> string_to_location;
  int closest_dis = numeric_limits<int>::max();
  for (int i = 0; i < s.size(); ++i) {
    auto it = string_to_location.find(s[i]);
    if (it != string_to_location.end()) {
      closest_dis = min(closest_dis, i - it->second);
    }
    string_to_location[s[i]] = i;
  }
  return closest_dis;
}
// @exclude

// O(n^2) checking
int check_answer(const vector<string>& s) {
  int closest_dis = numeric_limits<int>::max();
  for (int i = 0; i < s.size(); ++i) {
    for (int j = i + 1; j < s.size(); ++j) {
      if (s[i] == s[j]) {
        closest_dis = min(closest_dis, j - i);
      }
    }
  }
  return closest_dis;
}

int main(int argc, char* argv[]) {
  vector<string> A = {"foo",    "bar",    "widget", "foo",
                      "widget", "widget", "adnan"};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {"foo", "bar", "widget", "foo", "xyz", "widget", "bar", "adnan"};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {"foo", "bar", "widget", "adnan"};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {"foo", "foo", "foo"};
  assert(check_answer(A) == find_nearest_repetition(A));
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<string> s;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(1, 10);
      s.emplace_back(rand_string(dis(gen)));
    }
    assert(check_answer(s) == find_nearest_repetition(s));
  }
  return 0;
}
