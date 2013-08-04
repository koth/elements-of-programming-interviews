// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "./execute-shell.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

// @include
class BigInt {
 public:
  explicit BigInt(int capacity) : sign_(1), digits_(capacity) {}

  explicit BigInt(const string &s) : sign_(s[0] == '-' ? -1 : 1),
                                     digits_(s.size() - (s[0] == '-')) {
    for (int i = s.size() - 1, j = 0; i >= (s[0] == '-'); --i, ++j) {
      if (isdigit(s[i])) {
        digits_[j] = s[i] - '0';
      }
    }
  }

  BigInt operator*(const BigInt &n) const {
    BigInt result(digits_.size() + n.digits_.size());
    result.sign_ = sign_ * n.sign_;
    int i, j;
    for (i = 0; i < n.digits_.size(); ++i) {
      if (n.digits_[i]) {
        int carry = 0;
        for (j = 0; j < digits_.size() || carry; ++j) {
          int n_digit = result.digits_[i + j] +
                        (j < digits_.size() ? n.digits_[i] * digits_[j] : 0) +
                        carry;
          result.digits_[i + j] = n_digit % 10;
          carry = n_digit / 10;
        }
      }
    }

    // If one number is 0, the result size should be 0.
    if ((digits_.size() == 1 && digits_.front() == 0) ||
        (n.digits_.size() == 1 && n.digits_.front() == 0)) {
      result.sign_ = 1, result.digits_.resize(1);
    } else {
      result.digits_.resize(i + j - 1);
    }
    return result;
  }

  // @exclude
  string toString() const {
    string s = (sign_ > 0 ? "" : "-");
    for (int i = digits_.size() - 1; i >= 0; --i) {
      s += digits_[i] + '0';
    }
    if (digits_.empty() == true) {
      s += '0';
    }
    return s;
  }
  // @include
 private:
  int sign_;  // -1 or 1;
  vector<char> digits_;
};
// @exclude

string rand_string(int len) {
  string ret;
  if (!len) {
    ret += '0';
  } else {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> positive_or_negative(0, 1);
    if (positive_or_negative(gen)) {
      ret += '-';
    }
    uniform_int_distribution<int> dis(1, 9);
    ret += dis(gen) + '0';
    --len;
    while (len--) {
      uniform_int_distribution<int> dis(0, 9);
      ret += dis(gen) + '0';
    }
  }
  return ret;
}

void simple_test() {
  assert((BigInt("0") * BigInt("1000")).toString() == "0");
  assert((BigInt("131412") * BigInt("-1313332")).toString() == "-172587584784");
}

int main(int argc, char *argv[]) {
  simple_test();
  for (int times = 0; times < 1000; ++times) {
    string s1, s2;
    if (argc == 3) {
      s1 = argv[1], s2 = argv[2];
    } else {
      default_random_engine gen((random_device())());
      uniform_int_distribution<int> dis(0, 19);
      s1 = rand_string(dis(gen)), s2 = rand_string(dis(gen));
    }
    BigInt res = BigInt(s1) * BigInt(s2);
    cout << s1 << " * " << s2 << " = " << res.toString() << endl;
    string command = "bc <<<" + s1 + "*" + s2;
    string result = execute_shell(command);
    cout << "answer = " << result;
    assert(res.toString().compare(result.substr(0, result.size() - 1)) == 0);
  }
  return 0;
}
