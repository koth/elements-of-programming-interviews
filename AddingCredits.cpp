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
 public:
  void insert(const string& s, int c) {
    credits_.emplace(s, c - offset_);
    inverse_credits_[c - offset_].emplace(s);
  }

  void remove(const string& s) {
    auto credits_it = credits_.find(s);
    if (credits_it != credits_.end()) {
      inverse_credits_[credits_it->second].erase(s);
      credits_.erase(credits_it);
    }
  }

  int lookup(const string& s) const {
    auto it = credits_.find(s);
    return it == credits_.cend() ? -1 : it->second + offset_;
  }

  void addAll(int C) { offset_ += C; }

  string max() const {
    auto it = inverse_credits_.crbegin();
    return it == inverse_credits_.crend() || it->second.empty()
               ? ""
               : *it->second.cbegin();
  }

 private:
  int offset_ = 0;
  unordered_map<string, int> credits_;
  map<int, unordered_set<string>> inverse_credits_;
};
// @exclude

int main(int argc, char* argv[]) {
  ClientsCreditsInfo a;
  assert(a.max() == "");
  a.insert("foo", 1);
  a.insert("bar", 2);
  a.addAll(5);
  a.insert("widget", 3);
  a.addAll(5);
  a.insert("dothis", 4);
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
