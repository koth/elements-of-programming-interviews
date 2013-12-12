// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <array>
#include <iostream>
#include <random>
#include <string>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

void phone_mnemonic_helper(const string &num, int d, string* ans);

// @include
void phone_mnemonic(const string &num) {
  string ans(num.size(), 0);
  phone_mnemonic_helper(num, 0, &ans);
}

const array<string, 10> M = {{"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO",
                              "PQRS", "TUV", "WXYZ"}};

void phone_mnemonic_helper(const string &num, int d, string* ans) {
  if (d == num.size()) {  // get enough characters and output answer.
    cout << *ans << endl;
  } else {
    for (const char &c : M[num[d] - '0']) {  // try all combinations.
      (*ans)[d] = c;
      phone_mnemonic_helper(num, d + 1, ans);
    }
  }
}
// @exclude

string rand_string(int len) {
  default_random_engine gen((random_device())());
  string ret;
  while (len--) {
    uniform_int_distribution<char> dis('0', '9');
    ret += dis(gen);
  }
  return ret;
}

int main(int argc, char *argv[]) {
  string num;
  if (argc == 2) {
    num = argv[1];
  } else {
    num = rand_string(10);
  }
  phone_mnemonic(num);
  cout << "number = " << num << endl;
  return 0;
}
