// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stoi;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

bool match_all_words_in_dict(const string& s,
                             const unordered_map<string, int>& dict,
                             size_t start, size_t num_words, size_t unit_size);

// @include
vector<int> find_all_substrings(const string& s,
                                const vector<string>& words) {
  unordered_map<string, int> dict;
  for (const string& word : words) {
    ++dict[word];
  }

  auto unit_size = words.front().size();
  vector<int> res;
  for (size_t i = 0; i + unit_size * words.size() <= s.size(); ++i) {
    if (match_all_words_in_dict(s, dict, i, words.size(), unit_size)) {
      res.emplace_back(i);
    }
  }
  return res;
}

bool match_all_words_in_dict(const string& s,
                             const unordered_map<string, int>& dict,
                             size_t start, size_t num_words,
                             size_t unit_size) {
  unordered_map<string, int> curr_dict;
  for (size_t i = 0; i < num_words; ++i) {
    string curr_word = s.substr(start + i * unit_size, unit_size);
    auto iter = dict.find(curr_word);
    if (iter == dict.end()) {
      return false;
    }
    ++curr_dict[curr_word];
    if (curr_dict[curr_word] > iter->second) {
      return false;
    }
  }
  return true;
}
// @exclude

void small_test() {
  string s = "barfoothefoobarman";
  auto res = find_all_substrings(s, {"foo", "bar"});
  assert(res.size() == 2 && res[0] == 0 && res[1] == 9);
  s = "dcacdabcd";
  res = find_all_substrings(s, {"cd", "ab"});
  assert(res.size() == 2 && res[0] == 3 && res[1] == 5);
}

int main(int argc, char** argv) {
  small_test();
  return 0;
}
