// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

bool is_match_here(const string &r, size_t r_idx, const string &s,
                   size_t s_idx);

// @include
bool is_match(const string &r, const string &s) {
  // Case (2.): r starts with '^'.
  if (r.front() == '^') {
    return is_match_here(r, 1, s, 0);
  }

  for (size_t i = 0; i <= s.size(); ++i) {
    if (is_match_here(r, 0, s, i)) {
      return true;
    }
  }
  return false;
}

bool is_match_here(const string &r, size_t r_idx, const string &s,
                   size_t s_idx) {
  // Case (1.).
  if (r_idx == r.size()) {
    return true;
  }

  // Case (2): r ends with '$'.
  if (r_idx == r.size() - 1 && r[r_idx] == '$') {
    return s_idx == s.size();
  }

  // Case (4.).
  if (r.size() - r_idx >= 2 && r[r_idx + 1] == '*') {
    // Don't use any character of r[r_idx].
    if (is_match_here(r, r_idx + 2, s, s_idx)) {
      return true;
    }

    // Tries all possible number of r[r_idx].
    while (s_idx < s.size() && (r[r_idx] == '.' || r[r_idx] == s[s_idx])) {
      if (is_match_here(r, r_idx + 2, s, ++s_idx)) {
        return true;
      }
    }
  }

  // Case (3.).
  return s_idx < s.size() && (r[r_idx] == '.' || r[r_idx] == s[s_idx]) &&
         is_match_here(r, r_idx + 1, s, s_idx + 1);
}
// @exclude

int main(int argc, char *argv[]) {
  assert(is_match(".", "a"));
  assert(is_match("a", "a"));
  assert(!is_match("a", "b"));
  assert(is_match("a.9", "aW9"));
  assert(!is_match("a.9", "aW19"));
  assert(is_match("^a.9", "aW9"));
  assert(!is_match("^a.9", "baW19"));
  assert(is_match(".*", "a"));
  assert(is_match(".*", ""));
  assert(is_match("c*", "c"));
  assert(!is_match("aa*", "c"));
  assert(is_match("ca*", "c"));
  assert(is_match(".*",  "asdsdsa"));
  assert(is_match("9$" , "xxxxW19"));

  assert(is_match(".*a", "ba"));

  assert(is_match(".*a", "ba"));
  assert(is_match("^a.*9$", "axxxxW19"));

  assert(is_match("^a.*W19$", "axxxxW19"));
  assert(is_match(".*a.*W19", "axxxxW19123"));
  assert(!is_match(".*b.*W19", "axxxxW19123"));
  assert(is_match("n.*", "n"));
  assert(is_match("a*n.*", "an"));
  assert(is_match("a*n.*", "ana"));
  assert(is_match("a*n.*W19", "anaxxxxW19123"));
  assert(is_match(".*a*n.*W19", "asdaaadnanaxxxxW19123"));
  assert(is_match(".*.*.a*n.*W19", "asdaaadnanaxxxxW19123"));
  return 0;
}
