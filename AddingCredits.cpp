// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <map>
#include <string>
#include <unordered_set>
#include <unordered_map>

using std::map;
using std::string;
using std::unordered_map;
using std::unordered_set;

// @include
class ClientsCreditsInfo {
  private:
    int offset;
    unordered_map<string, int> credits;
    map<int, unordered_set<string>> inverse_credits;

  public:
    ClientsCreditsInfo(void) : offset(0) {}

    void insert(const string &s, const int &c) {
      credits.emplace(s, c - offset);
      inverse_credits[c - offset].emplace(s);
    }

    void remove(const string &s) {
      auto credits_it = credits.find(s);
      if (credits_it != credits.end()) {
        inverse_credits[credits_it->second].erase(s);
        credits.erase(credits_it);
      }
    }

    int lookup(const string &s) const {
      auto it = credits.find(s);
      return it == credits.cend() ? -1 : it->second + offset;
    }

    void addAll(const int &C) {
      offset += C;
    }

    string max(void) const {
      auto it = inverse_credits.crbegin();
      return it == inverse_credits.crend() || it->second.empty() ?
             "" : *it->second.cbegin();
    }
};
// @exclude

int main(int argc, char *argv[]) {
  ClientsCreditsInfo a;
  assert(a.max() == "");
  a.insert( "foo", 1 );
  a.insert( "bar", 2 );
  a.addAll(5);
  a.insert( "widget", 3 );
  a.addAll(5);
  a.insert( "dothis", 4 );
  assert(11 == a.lookup("foo"));
  assert(12 == a.lookup("bar"));
  assert(8 == a.lookup("widget"));
  assert(4 == a.lookup("dothis"));
  a.remove("foo");
  assert(-1 == a.lookup("foo"));
  assert(a.max().compare("bar") == 0);
  a.insert("xyz", 13);
  assert(a.max().compare("xyz") == 0);
  a.insert("dd", 15);
  assert(a.max().compare("dd") == 0);
  return 0;
}
