#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
string majority_search(istringstream &sin) {
  string candidate, buf;
  int count = 0;
  while (sin >> buf) {
    if (count == 0) {
      candidate = buf;
      count = 1;
    } else if (candidate == buf) {
      ++count;
    } else {
      --count;
    }
  }
  return candidate;
}
// @exclude

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += 'a' + rand() % 26;
  }
  return ret;
}

void check_ans(vector<string> &stream, const string &ans) {
  sort(stream.begin(), stream.end());
  int count = 1;
  bool find = false;
  for (int i = 1; i < stream.size(); ++i) {
    if (stream[i].compare(stream[i - 1])) {
      if (count * 2 >= stream.size()) {
        assert(ans.compare(stream[i - 1]) == 0);
        find = true;
      }
      count = 1;
    } else {
      ++count;
    }
  }
  if (count * 2 >= stream.size()) {
    assert(ans.compare(stream.back()) == 0);
    find = true;
  }
  assert(find == true);
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n;
    vector<string> stream;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    for (int i = 0; i < n; ++i) {
      stream.emplace_back(rand_string(1 + (rand() % 5)));
    }
    // generate the majority
    for (int i = 0; i < n; ++i) {
      stream.emplace_back(stream.back());
    }
    string s;
    for (int i = 0; i < stream.size(); ++i) {
      s += stream[i];
      s += ' ';
    }
    istringstream sin(s);
    string ret(majority_search(sin));
    cout << ret << endl;
    check_ans(stream, ret);
  }
  return 0;
}
