#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

// @include
string convert_base(const string &s, const int &b1, const int &b2) {
  bool neg = (s[0] == '-');
  int x = 0;
  for (int i = (neg == true ? 1 : 0); i < s.size(); ++i) {
    x *= b1;
    x += isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
  }

  string ans;
  while (x) {
    int r = x % b2;
    ans.push_back(r >= 10 ? 'A' + r - 10: '0' + r);
    x /= b2;
  }

  if (ans.empty()) {
    ans.push_back('0');
  }
  if (neg) {
    ans.push_back('-');
  }
  reverse(ans.begin(), ans.end());
  return ans;
}
// @exclude

string rand_int_string(int len) {
  string ret;
  if (rand() & 1) {
    ret.push_back('-');
  }
  ret.push_back('1' + rand() % 9);
  --len;
  while (len--) {
    ret.push_back('0' + rand() % 10);
  }
  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  if (argc == 4) {
    string input(argv[1]);
    cout << convert_base(input, atoi(argv[2]), atoi(argv[3])) << endl;
    assert(input == convert_base(convert_base(input, atoi(argv[2]), atoi(argv[3])), atoi(argv[3]), atoi(argv[2])));
  } else {
    for (int times = 0; times < 100000; ++times) {
      string input = rand_int_string(1 + rand() % 9);
      int base = 2 + rand() % 15;
      cout << "input is " << input << ", base1 = 10, base2 = " << base << ", ans = " << convert_base(input, 10, base) << endl;
      assert(input == convert_base(convert_base(input, 10, base), base, 10));
    }
  }
  return 0;
}
