#include <iostream>
#include <string>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += rand() % 26 + 'a';
  }
  return ret;
}

// @include
// Use BFS to find the least steps of transformation
int transform_string(unordered_set<string> D, const string &s,
                     const string &t) {
  queue<pair<string, int>> q;
  D.erase(s);  // mark s as visited by erasing it in D
  q.emplace(s, 0);

  while (!q.empty()) {
    pair<string, int> f(q.front());
    // Return if we find a match
    if (f.first == t) {
      return f.second;  // number of steps reaches t
    }

    // Try all possible transformations of f.first
    string str = f.first;
    for (int i = 0; i < str.size(); ++i) {
      for (int j = 0; j < 26; ++j) {  // iterates through 'a' ~ 'z'
        str[i] = 'a' + j;  // change the (i + 1)-th char of str
        auto it(D.find(str));
        if (it != D.end()) {
          D.erase(it);  // mark str as visited by erasing it
          q.emplace(str, f.second + 1);
        }
      }
      str[i] = f.first[i];  // revert the change of str
    }
    q.pop();
  }

  return -1;  // cannot find a possible transformations
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int len;
  if (argc == 2) {
    len = atoi(argv[1]);
  } else {
    len = 1 + rand() % 10;
  }
  string s(rand_string(len)), t(rand_string(len));
  unordered_set<string> D;
  D.emplace(s), D.emplace(t);
  int n = 1 + rand() % 1000000;
  for (size_t i = 0; i < n; ++i) {
    D.emplace(rand_string(len));
  }
  /*
  for (const string &s : D) {
    cout << s << endl;
  }
  //*/
  cout << s << ' ' << t << ' ' << D.size() << endl;
  cout << transform_string(D, s, t) << endl;
  return 0;
}
