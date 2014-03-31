// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::pair;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;
using std::vector;

unordered_map<string, vector<string>> global_map;

// @include
void find_anagrams(const vector<string>& dictionary) {
  // Get the sorted string and then insert into hash table.
  unordered_map<string, vector<string>> hash;
  for (const string& s : dictionary) {
    string sorted_str(s);
    // Use sorted string as the hash code.
    sort(sorted_str.begin(), sorted_str.end());
    hash[sorted_str].emplace_back(s);
  }

  for (const pair<string, vector<string>>& p : hash) {
    // Multiple strings with the same hash code => anagrams.
    if (p.second.size() >= 2) {
      // Output all strings.
      for (const auto& s : p.second) {
        cout << s << " ";
      }
      cout << endl;
    }
  }
  // @exclude
  global_map = hash;
  // @include
}
// @exclude

string rand_string(int len) {
  default_random_engine gen((random_device())());
  string ret;
  while (len--) {
    uniform_int_distribution<int> dis('a', 'z');
    ret.push_back(static_cast<char>(dis(gen)));
  }
  return ret;
}

void small_test() {
  vector<string> D = {"debit card", "bad credit", "the morse code", "here come dots", "the eyes", "they see", "THL"};
  find_anagrams(D);
  assert(global_map.size() == 4);
  assert(global_map["  cdeeehmoorst"].size() == 2);
  assert(global_map[" abcddeirt"].size() == 2);
  assert(global_map[" eeehsty"].size() == 2);
  assert(global_map["HLT"].size() == 1);
}

int main(int argc, char* argv[]) {
  small_test();
  default_random_engine gen((random_device())());
  vector<string> dictionary;
  uniform_int_distribution<int> n_dis(0, 99999);
  int n = n_dis(gen);
  unordered_set<string> table;
  for (int i = 0; i < n; ++i) {
    uniform_int_distribution<int> dis(1, 12);
    table.emplace(rand_string(dis(gen)));
  }
  for (const string& s : table) {
    dictionary.emplace_back(s);
  }
  find_anagrams(dictionary);
  return 0;
}
