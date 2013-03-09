#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <cstdlib>
#include <cassert>
#include <ctime>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += 'a' + rand() % 26;
  }
  return ret;
}

// @include
vector<string> word_breaking(const string &s,
                             const unordered_set<string> &dict) {
  // T[i] stores the length of the last string which composed of s(0, i)
  vector<int> T(s.size(), 0);
  for (int i = 0; i < s.size(); ++i) {
    // Set T[i] if s(0, i) is a valid word
    if (dict.find(s.substr(0, i + 1)) != dict.cend()) {
      T[i] = i + 1;
    }

    // Set T[i] if T[j] != 0 and s(j + 1, i) is a valid word
    for (int j = 0; j < i && T[i] == 0; ++j) {
      if (T[j] != 0 && dict.find(s.substr(j + 1, i - j)) != dict.cend()) {
        T[i] = i - j;
      }
    }
  }

  vector<string> ret;
  // s can be assembled by valid words
  if (T.back()) {
    int idx = s.size() - 1;
    while (idx >= 0) {
      ret.emplace_back(s.substr(idx - T[idx] + 1, T[idx]));
      idx -= T[idx];
    }
    reverse(ret.begin(), ret.end());
  }
  return ret;
}
// @exclude

// Verify the strings in ans can be assembled into s
void check_ans(const string &s, vector<string> &ans) {
  string temp;
  cout << s << endl;
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i] << ' ';
    temp += ans[i];
  }
  cout << endl;
  assert(!ans.size() || !s.compare(temp));
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    unordered_set<string> dictionary;
    string target;
    if (argc >= 3) {
      target = argv[1];
      for (int i = 3; i < argc; ++i) {
        dictionary.emplace(argv[i]);
      }
    } else if (argc == 2) {
      target = argv[1];
      int n = 1 + rand() % 10000;
      while (n--) {
        dictionary.emplace(rand_string(1 + rand() % 15));
      }
    } else {
      target = rand_string(1 + rand() % 50);
      int n = 1 + rand() % 10000;
      while (n--) {
        dictionary.emplace(rand_string(1 + rand() % 15));
      }
    }
    vector<string> ans(word_breaking(target, dictionary));
    check_ans(target, ans);
    if (argc == 3) {
      break;
    }
  }
  return 0;
}
