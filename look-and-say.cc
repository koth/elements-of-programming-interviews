// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stoi;
using std::string;
using std::stringstream;
using std::to_string;
using std::uniform_int_distribution;

string next_sequence(const string& s);

// @include
string look_and_say(int n) {
  string s = "1";
  for (int i = 1; i < n; ++i) {
    s = next_sequence(s);
  }
  return s;
}

string next_sequence(const string& s) {
  string ret;
  for (size_t i = 0; i < s.size(); ++i) {
    int count = 1;
    while (i + 1 < s.size() && s[i] == s[i + 1]) {
      ++i, ++count;
    }
    ret += to_string(count) + s[i];
  }
  return ret;
}
// @exclude

int main(int argc, char** argv) {
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis(1, 50);
    n = dis(gen);
  }
  assert(!look_and_say(1).compare("1"));
  assert(!look_and_say(2).compare("11"));
  assert(!look_and_say(3).compare("21"));
  assert(!look_and_say(5).compare("111221"));
  cout << "n = " << n << endl;
  cout << look_and_say(n) << endl;
  return 0;
}
