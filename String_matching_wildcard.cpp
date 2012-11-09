#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

// @include
bool is_match_helper(const string &s, int a, const string &m, const int &b) {
  if (b == m.size()) {
    return (a == s.size());
  } else if (b == m.size() - 1) {
    if (a == s.size() - 1) {
      return (s[a] == m[b] || m[b] == '.');
    } else {
      return false;
    }
  } else {
    if (m[b + 1] == '*') {
      if (is_match_helper(s, a, m, b + 2)) {
        return true;
      }
      while (a < s.size() && (s[a] == m[b] || m[b] == '.')) {
        if (is_match_helper(s, a + 1, m, b + 2)) {
          return true;
        }
        ++a;
      }
      return false;
    } else {
      return
        a < s.size() &&
        (s[a] == m[b] || m[b] == '.') &&
        is_match_helper(s, a + 1, m, b + 1);
    }
  }
}

bool is_match(const string &s, const string &m) {
  return is_match_helper(s, 0, m, 0);
}
// @exclude

int main(int argc, char *argv[]) {
  if (argc == 3) {
    // Remember to put '\' before any special metacharater you input
    cout << boolalpha << is_match(argv[1], argv[2]) << endl;
  }
  assert(true == is_match("c", "."));
  assert(true == is_match("ac", ".c"));
  assert(true == is_match("c", "c"));
  assert(false == is_match("cc", "c"));
  assert(true == is_match("c", "c*"));
  assert(true == is_match("ac", ".*c"));
  assert(true == is_match("acac", ".*a.*"));
  assert(true == is_match("ac", ".*a.*c"));
  assert(true == is_match("acac", ".*a.*c"));
  assert(true == is_match("", ".*"));
  assert(true == is_match("cagt", ".*c.*a.*g.*t"));
  assert(true == is_match("cagt", "c*ca*ag*gt*"));
  assert(true == is_match("cagtt", "c*ca*ag*gt*tt"));
  return 0;
}
