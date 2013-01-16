#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
#ifdef __clang__
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <string>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
bool can_string_be_a_palindrome(const string &s) {
  unordered_map<char, int> hash;
  // Insert each char into hash
  for_each(s.begin(), s.end(), [&hash](const char &c) { ++hash[c]; });

  // A string can be permuted as a palindrome if the number of odd time 
  // chars <= 1
  int odd_count = 0;
  for (const pair<char, int> &p : hash) {
    if (p.second & 1 && ++odd_count > 1) {
      break;
    }
  }
  return odd_count <= 1;
}
// @exclude

bool check_ans(string &s) {
  // Sort the string and count the number of occurrence for each char
  sort(s.begin(), s.end());
  int odd_count = 0, num_curr_char = 1;
  for (int i = 1; i < s.size() && odd_count <= 1; ++i) {
    if (s[i] != s[i - 1]) {
      if (num_curr_char & 1) {
        ++odd_count;
      }
      num_curr_char = 1;
    } else {
      ++num_curr_char;
    }
  }
  if (num_curr_char & 1) {
    ++odd_count;
  }
  // A string can be permuted as palindrome
  // if the number of odd time chars is less than or equal to 1
  return odd_count <= 1;
}

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += 'a' + rand() % 26;
  }
  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    string s;
    if (argc == 2) {
      s = argv[1];
    } else {
      s = rand_string(1 + rand() % 10);
    }
    cout << s << endl;
    cout << boolalpha << can_string_be_a_palindrome(s) << endl;
    assert(can_string_be_a_palindrome(s) == check_ans(s));
  }
  return 0;
}
