#include <iostream>
#include <array>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
const array<string, 10> M = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", 
                             "PQRS", "TUV", "WXYZ"};

void phone_mnemonic_helper(const string &num, const int &d, string &ans) {
  if (d == num.size()) {
    cout << ans << endl;
  } else {
    for (const char &c : M[num[d] - '0']) {
      ans[d] = c;
      phone_mnemonic_helper(num, d + 1, ans);
    }
  }
}

void phone_mnemonic(const string &num) {
  string ans;
  ans.resize(num.size());
  phone_mnemonic_helper(num, 0, ans);
}
// @exclude

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += '0' + rand() % 10;
  }
  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  string num;
  if (argc == 2) {
    num = argv[1];
  } else {
    num = rand_string(10);
  }
  phone_mnemonic(num);
  cout << num << endl;
  return 0;
}
