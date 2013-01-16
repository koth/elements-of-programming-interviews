#include <iostream>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <vector>
#include <cassert>
#include <map>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
class ClientsCreditsInfo {
  private:
    int offset;
    map<string, int> credits;
    map<int, unordered_set<string> > inverse_credits;

  public:
    ClientsCreditsInfo(void) : offset(0) {}

    void insert(const string &s, const int &c) {
      credits.emplace(make_pair(s, c - offset));
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
      auto hash_it = inverse_credits.crbegin()->second;
      return hash_it.empty() ? "" : *hash_it.begin();
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
  assert(a.max() == "bar");
  a.insert( "xyz", 12);
  assert(a.max() == "bar");
  a.insert( "dd", 13);
  assert(a.max() == "dd");
  return 0;
}
