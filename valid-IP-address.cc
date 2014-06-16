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
using std::stoi;
using std::string;
using std::uniform_int_distribution;
using std::vector;

bool is_valid(const string& s);

// @include
vector<string> get_valid_IP_address(const string& s) {
  vector<string> res;
  for (size_t i = 1; i < 4 && i < s.size(); ++i) {
    auto first = s.substr(0, i);
    if (is_valid(first)) {
      for (size_t j = 1; i + j < s.size() && j < 4; ++j) {
        auto second = s.substr(i , j);
        if (is_valid(second)) {
          for (size_t k = 1; i + j + k < s.size() && k < 4; ++k) {
            auto third = s.substr(i + j, k), fourth = s.substr(i + j + k);
            if (is_valid(third) && is_valid(fourth)) {
              res.emplace_back(first + "." + second + "." + third + "." +
                               fourth);
            }
          }
        }
      }
    }
  }
  return res;
}

bool is_valid(const string& s) {
  if ((s.front() == '0' && s.size() > 1) || s.size() > 3) {
    return false;
  }
  int val = stoi(s);
  return val <= 255 && val >= 0;
}
// @exclude

int main(int argc, char** argv) {
  if (argc == 2) {
    auto res = get_valid_IP_address(argv[1]);
    for (const auto& s : res) {
      cout << s << endl;
    }
  }
  auto res1 = get_valid_IP_address("255255255255");
  for (const auto& s : res1) {
    cout << s << endl;
  }
  auto res2 = get_valid_IP_address("19216811");
  for (const auto& s : res2) {
    cout << s << endl;
  }
  return 0;
}
