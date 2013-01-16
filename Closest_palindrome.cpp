#include <iostream>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include <string>

using namespace std;

// @include
unsigned diff(const unsigned &a, const unsigned &b) {
  return a > b ? a - b : b - a;
}

unsigned find_closest_palindrome(const unsigned &x) {
  string str(to_string(x));
  // Make str a palindrome by mirroring the left half to the right half
  copy(str.cbegin(), str.cbegin() + (str.size() >> 1), str.rbegin());

  unsigned mirror_left = stoul(str);
  int idx = (str.size() - 1) >> 1;
  if (mirror_left >= x) {
    // Subtract one from the left half
    while (idx >= 0) {
      if (str[idx] == '0') {
        str[idx--] = '9';
      } else {
        --str[idx];
        break;
      }
    }
    if (str[0] == '0') {  // special case, make the whole string as "99...9"
      str = to_string(stoul(str));  // removes the leading 0
      fill(str.begin(), str.end(), '9');
    }
  } else {  // mirror_left < x
    // Add one to the left half
    while (idx >= 0) {
      if (str[idx] == '9') {
        str[idx--] = '0';
      } else {
        ++str[idx];
        break;
      }
    }
  }

  // Make str a palindrome again by mirroring the left half to the right half
  copy(str.cbegin(), str.cbegin() + (str.size() >> 1), str.rbegin());
  return diff(x, mirror_left) < diff(x, stoul(str)) ?
         mirror_left : stoul(str);
}
// @exclude

bool is_palindrome(const unsigned &x) {
  string str(to_string(x));
  for (int i = 0, j = str.size() - 1; i < j; ++i, --j) {
    if (str[i] != str[j]) {
      return false;
    }
  }
  return true;
}

void check_answer(const unsigned &x, const unsigned &ans) {
  if (is_palindrome(x)) {
    assert(ans == x);
    return;
  }
  unsigned small = x - 1;
  while (is_palindrome(small) == false) {
    --small;
  }
  unsigned big = x + 1;
  while (is_palindrome(big) == false) {
    ++big;
  }
  if (x - small > big - x) {
    assert(big - x == ans > x ? ans - x : x - ans);
  } else {
    assert(x - small == ans > x ? ans - x : x - ans);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 100000; ++times) {
    unsigned x;
    if (argc == 2) {
      x = atol(argv[1]);
    } else {
      x = 1 + rand() % 10000000;
    }
    unsigned ret = find_closest_palindrome(x);
    cout << x << ' ' << ret << endl;
    assert(is_palindrome(ret));
    check_answer(x, ret);
  }
  return 0;
}
