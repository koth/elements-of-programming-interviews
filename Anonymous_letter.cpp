#include <iostream>
#include <algorithm>
#include <cassert>
#ifdef __clang__
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

string rand_string(int len) {
  string ret;
  while (len--) {
    int x = rand() % 27;
    ret += (x < 26) ? 'a' + x : ' ';
  }
  return ret;
}

// @include
bool anonymous_letter(const string &L, const string &M) {
  unordered_map<char, int> hash;
  // Insert all chars in L into a hash table
  for_each(L.begin(), L.end(), [&hash](const char &c) { ++hash[c]; });

  // Check chars in M that could cover chars in a hash table
  for (const char &c : M) {
    auto it = hash.find(c);
    if (it != hash.cend()) {
      if (--it->second == 0) {
        hash.erase(it);
        if (hash.empty() == true) {
          return true;
        }
      }
    }
  }
  // No entry in hash means L can be covered by M
  return hash.empty();
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  string L, M;
  if (argc == 3) {
    L = argv[1], M = argv[2];
  } else {
    L = rand_string(1 + rand() % 1000), M = rand_string(1 + rand() % 100000);
  }
  cout << L << endl;
  cout << M << endl;
  assert(anonymous_letter("123", "456") == false);
  assert(anonymous_letter("123", "12222222") == false);
  assert(anonymous_letter("123", "1123") == true);
  assert(anonymous_letter("123", "123") == true);
  cout << boolalpha << anonymous_letter(L, M) << endl;
  return 0;
}
