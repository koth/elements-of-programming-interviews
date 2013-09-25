// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::exception;
using std::invalid_argument;
using std::max;
using std::numeric_limits;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

string rand_int_string(int len) {
  default_random_engine gen((random_device())());
  string ret;
  if (len == 0) {
    return {"0"};
  }
  uniform_int_distribution<int> pos_or_neg(0, 1);
  if (pos_or_neg(gen)) {
    ret.push_back('-');
  }
  uniform_int_distribution<int> num_dis('1', '9');
  ret.push_back(num_dis(gen));
  while (--len) {
    uniform_int_distribution<int> dis('0', '9');
    ret.push_back(dis(gen));
  }
  return ret;
}

// @include
string intToString(int x) {
  bool is_negative;
  if (x < 0) {
    x = -x, is_negative = true;
  } else {
    is_negative = false;
  }

  string s;
  while (x) {
    s.push_back('0' + x % 10);
    x /= 10;
  }
  if (s.empty()) {
    return {"0"};  // x is 0.
  }

  if (is_negative) {
    s.push_back('-');
  }
  reverse(s.begin(), s.end());
  return s;
}

// We define the valid strings for this function as those matching regexp
// -?[0-9]+.
int stringToInt(const string& s) {
  // "-" starts as a valid integer, but has no digits.
  if (s == "-") {
    throw invalid_argument("illegal input");
  }

  bool is_negative = s[0] == '-';
  int x = 0;
  for (int i = is_negative; i < s.size(); ++i) {
    if (isdigit(s[i])) {
      x = x * 10 + s[i] - '0';
    } else {
      throw invalid_argument("illegal input");
    }
  }
  return is_negative ? -x : x;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  if (argc == 2) {
    try {
      cout << stringToInt(argv[1]) << endl;
    }
    catch (const exception& e) {
      cout << e.what() << endl;
    }
  } else {
    for (int times = 0; times < 10000; ++times) {
      uniform_int_distribution<int> dis(numeric_limits<int>::min(),
                                        numeric_limits<int>::max());
      int x = dis(gen);
      string str = intToString(x);
      cout << x << " " << str << endl;
      assert(x == stoi(str));
      uniform_int_distribution<int> len_dis(0, 9);
      str = rand_int_string(len_dis(gen));
      x = stringToInt(str);
      cout << str << " " << x << endl;
      assert(x == stoi(str));
    }
    try {
      stringToInt("123abc");
    }
    catch (const exception& e) {
      cout << e.what() << endl;
    }
  }
  return 0;
}
