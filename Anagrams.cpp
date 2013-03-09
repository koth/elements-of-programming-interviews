#include <iostream>
#include <string>
#include <cstdlib>
#ifdef __clang__
#include <unordered_set>
#include <unordered_map>
#else
#include <tr1/unordered_set>
#include <tr1/unordered_map>
#endif
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
void find_anagrams(const vector<string> &dictionary) {
  // Get the sorted string and then insert into hash table
  unordered_map<string, vector<string>> hash;
  for (const string &s : dictionary) {
    string sorted_str(s);
    // Use sorted string as the hash code
    sort(sorted_str.begin(), sorted_str.end());
    hash[sorted_str].emplace_back(s);
  }

  for (const pair<string, vector<string>> &p : hash) {
    // Multiple strings with the same hash code => anagrams
    if (p.second.size() >= 2) {
      // Output all strings
      copy(p.second.begin(), p.second.end(),
           ostream_iterator<string>(cout, " "));
      cout << endl;
    }
  }
}
// @exclude

string rand_string(int len) {
  string ret;
  while (len--) {
    ret.push_back('a' + rand() % 26);
  }
  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  vector<string> dictionary;
  int n = rand() % 100000;
  unordered_set<string> table;
  for (size_t i = 0; i < n; ++i) {
    table.emplace(rand_string(1 + rand() % 12));
  }
  for (const string &s : table) {
    dictionary.emplace_back(s);
  }
  find_anagrams(dictionary);
  return 0;
}
