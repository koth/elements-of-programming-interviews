#include <iostream>
#include <cassert>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// @include
string replace_and_remove(string s) {
  // Remove "b" and count the number of "a"
  int write_idx = 0, a_count = 0;
  for (const char &c : s) {
    if (c != 'b') {
      s[write_idx++] = c;
    }
    if (c == 'a') {
      ++a_count;
    }
  }

  // Allocate space according to the number of "a"
  s.resize(write_idx + a_count);
  // Replace "a" with "dd";
  int cur_idx = write_idx - 1;
  write_idx = s.size() - 1;
  while (cur_idx >= 0) {
    if (s[cur_idx] == 'a') {
      s[write_idx--] = s[write_idx--] = 'd';
    } else {
      s[write_idx--] = s[cur_idx];
    }
    --cur_idx;
  }
  return s;
}
// @exclude

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += 'a' + rand() % 4;
  }
  return ret;
}

void check_ans(string &s, string &ans) {
  string temp;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'a') {
      temp += 'd', temp += 'd';
    } else if (s[i] != 'b') {
      temp += s[i];
    }
  }
  assert(ans.compare(temp) == 0);
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    string s;
    if (argc == 2) {
      s = argv[1];
    } else {
      s = rand_string(1 + rand() % 1000);
    }
    cout << s << endl << endl;
    string ans = replace_and_remove(s);
    cout << ans << endl;
    check_ans(s, ans);
  }
  return 0;
}
