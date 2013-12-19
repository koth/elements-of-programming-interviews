#include <iostream>
#include <limits>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#ifdef __clang__
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

string rand_string(int len) {
  string ret = "";
  while (len--) {
    ret += 'a' + rand() % 26;
  }
  return ret;
}

// @include
int find_nearest_repetition(const vector<string> &s) {
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
int check_answer(const vector<string> &s) {
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

int main(int argc, char *argv[]) {
  vector<string> A = {"foo", "bar", "widget", "foo", "widget", "widget", "adnan"};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {"foo", "bar", "widget", "foo", "xyz", "widget", "bar", "adnan"};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {"foo", "bar", "widget", "adnan"};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {};
  assert(check_answer(A) == find_nearest_repetition(A));
  A = {"foo", "foo", "foo"};
  assert(check_answer(A) == find_nearest_repetition(A));
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 10000;
    }
    vector<string> s;
    for (int i = 0; i < n; ++i) {
      s.emplace_back(rand_string(1 + rand() % 10));
    }
    assert(check_answer(s) == find_nearest_repetition(s));
  }
  return 0;
}
