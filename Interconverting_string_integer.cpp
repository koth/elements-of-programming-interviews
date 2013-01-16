#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

string rand_int_string(int len) {
  string ret;
  if (len == 0) {
    return {"0"};
  }
  if (rand() & 1) {
    ret.push_back('-');
  }
  ret.push_back('1' + rand() % 9);
  while (--len) {
    ret.push_back(rand() % 10 + '0');
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
    return {"0"};  // x is 0
  }

  if (is_negative) {
    s.push_back('-');
  }
  reverse(s.begin(), s.end());
  return s;
}

int stringToInt(const string &s) {
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

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int x = (rand() & 1 ? -1 : 1) * rand();
    string str = intToString(x);
    cout << x << " " << str << endl;
    assert(x == stoi(str));
    str = rand_int_string(rand() % 10);
    x = stringToInt(str);
    cout << str << " " << x << endl;
    assert(x == stoi(str));
  }
  try {
    stringToInt("123abc");
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  return 0;
}
