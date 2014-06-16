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
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

bool is_palindrome(const string& s);
void palindrome_partitioning_helper(const string& s,
                                    size_t begin,
                                    vector<string>* partition,
                                    vector<vector<string>>* res);

// @include
vector<vector<string>> palindrome_partitioning(const string& s) {
  vector<vector<string>> res;
  vector<string> partition;
  palindrome_partitioning_helper(s, 0, &partition, &res);
  return res;
}

void palindrome_partitioning_helper(const string& s,
                                    size_t begin,
                                    vector<string>* partition,
                                    vector<vector<string>>* res) {
  if (begin == s.size()) {
    res->emplace_back(*partition);
    return;
  }

  for (size_t i = begin + 1; i <= s.size(); ++i) {
    string prefix = s.substr(begin, i - begin);
    if (is_palindrome(prefix)) {
      partition->emplace_back(prefix);
      palindrome_partitioning_helper(s, i, partition, res);
      partition->pop_back();
    }
  }
}

bool is_palindrome(const string& s) {
  for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
    if (s[i] != s[j]) {
      return false;
    }
  }
  return true;
}
// @exclude

void check_ans(const vector<vector<string>> &vecs, const string& input) {
  for (const auto& vec : vecs) {
    string temp;
    for (const auto& s : vec) {
      assert(is_palindrome(s));
      temp += s;
    }
    assert(!temp.compare(input));
  }
}

string rand_string(size_t len) {
  default_random_engine gen((random_device())());
  string ret;
  uniform_int_distribution<char> dis('a', 'z');
  while (len) {
    --len;
    ret += dis(gen);
  }
  return ret;
}

int main(int argc, char** argv) {
  if (argc == 2) {
    string s = argv[1];
  } else {
    default_random_engine gen((random_device())());
    for (int times = 0; times < 1000; ++times) {
      uniform_int_distribution<size_t> dis_len(0, 10);
      string s = rand_string(dis_len(gen));
      auto res = palindrome_partitioning(s);
      check_ans(res, s);
      cout << "string s = " << s << endl;
      for (const auto& vec : res) {
        for (const auto& t : vec) {
          cout << t << " ";
        }
        cout << endl;
      }
    }
  }
  return 0;
}
