// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stoi;
using std::string;
using std::uniform_int_distribution;

// @include
string snake_string(const string& s) {
  string ret;
  // Processes the first row.
  size_t idx = 1;
  while (idx < s.size()) {
    ret += s[idx];
    idx += 4;
  }
  // Processes the second row.
  idx = 0;
  while (idx < s.size()) {
    ret += s[idx];
    idx += 2;
  }
  // Processes the third row.
  idx = 3;
  while (idx < s.size()) {
    ret += s[idx];
    idx += 4;
  }

  return ret;
}
// @exclude

string rand_string(size_t len) {
  default_random_engine gen((random_device())());
  uniform_int_distribution<char> dis('A', 'Z');
  string ret;
  while (len--) {
    ret += dis(gen);
  }
  return ret;
}

void small_test() {
  assert(!snake_string("Hello World!").compare("e lHloWrdlo!"));
}

int main(int argc, char** argv) {
  small_test();
  default_random_engine gen((random_device())());
  string s;
  if (argc == 2) {
    s = argv[1];
  } else {
    uniform_int_distribution<size_t> dis_s(1, 100);
    s = rand_string(dis_s(gen));
  }
  cout << snake_string(s) << endl;
  return 0;
}
