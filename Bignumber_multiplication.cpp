#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// @include
class BigInt {
  private:
    int sign;  // -1 or 1;
    vector<char> digits;

  public:
    BigInt(const int &capacity) : sign(1), digits(capacity) {}

    BigInt(const string &s)
      : sign(s[0] == '-' ? -1 : 1), digits(s.size() - (s[0] == '-')) {
        for (int i = s.size() - 1, j = 0; i >= (s[0] == '-'); --i, ++j) {
          if (isdigit(s[i])) {
            digits[j] = s[i] - '0';
          }
        }
    }

    BigInt operator*(const BigInt &n) const {
      BigInt result(digits.size() + n.digits.size());
      result.sign = sign * n.sign;
      int i, j;
      for (i = 0; i < n.digits.size(); ++i) {
        if (n.digits[i]) {
          int carry = 0;
          for (j = 0; j < digits.size() || carry; ++j) {
            int n_digit = result.digits[i + j] + 
                          (j < digits.size() ? n.digits[i] * digits[j] : 0) +
                          carry;
            result.digits[i + j] = n_digit % 10;
            carry = n_digit / 10;
          }
        }
      }

      // If one number is 0, the result size should be 0
      if ((digits.size() == 1 && digits[0] == 0) ||
        (n.digits.size() == 1 && n.digits[0] == 0)) {
        result.digits.resize(1);
      } else {
        result.digits.resize(i + j - 1);
      }
      return result;
    }

    string toString() const {
      string s = (sign > 0 ? "" : "-");
      for (int i = digits.size() - 1; i >= 0; --i) {
        s += digits[i] + '0';
      }
      if (digits.empty() == true) {
        s += '0';
      }
      return s;
    }
    // @exclude
    const BigInt &operator=(const BigInt &n);
    // @include
};
// @exclude

const BigInt &BigInt::operator=(const BigInt &n) {
  if (&n != this) {
    *this = n;
  }
  return *this;
}

string rand_string(int len) {
  string ret;
  if (!len) {
    ret += '0';
  } else {
    if (rand() & 1) {
      ret += '-';
    }
    ret += 1 + rand() % 9 + '0';
    --len;
    while (len--) {
      ret += rand() % 10 + '0';
    }
  }
  return ret;
}

int main(int argc, char *argv[]) {
  string s1, s2;
  if (argc == 3) {
    s1 = argv[1], s2 = argv[2];
  } else {
    srand(time(nullptr));
    s1 = rand_string(rand() % 20), s2 = rand_string(rand() % 20);
  }
  BigInt res = BigInt(s1) * BigInt(s2);
  cout << s1 << " * " << s2 << " = " << res.toString() << endl;
  return 0;
}
