// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

bool is_match_here(const string &r, const string &s);

// @include
bool is_match(const string &r, const string &s) {
  // Case (2.) : starts with '^'.
  if (r.front() == '^') {
    return is_match_here(r.substr(1), s);
  }

  for (int i = 0; i <= s.size(); ++i) {
    if (is_match_here(r, s.substr(i))) {
      return true;
    }
  }
  return false;
}

bool is_match_here(const string &r, const string &s) {
  // Case (1.)
  if (r.empty()) {
    return true;
  }

  // Case (2) : ends with '$'.
  if (r == "$") {
    return s.empty();
  }

  // Case (4.)
  if (r.size() >= 2 && r[1] == '*') {
    for (string::size_type i = 0;
         i < s.size() && (r.front() == '.' || r.front() == s[i]);
         ++i) {
      if (is_match_here(r.substr(2), s.substr(i + 1))) {
        return true;
      }
    }
    return is_match_here(r.substr(2), s);
  }

  // Case (3.)
  return !s.empty() && (r.front() == '.' || r.front() == s.front()) &&
         is_match_here(r.substr(1), s.substr(1));
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
