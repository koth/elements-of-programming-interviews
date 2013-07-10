// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::pair;
using std::random_device;
using std::shared_ptr;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::unordered_set;

string rand_string(int len) {
  default_random_engine gen((random_device())());
  string ret;
  while (len--) {
    uniform_int_distribution<int> dis(0, 25);
    ret += dis(gen) + 'a';
  }
  return ret;
}

// @include
class Trie {
 public:
  // @exclude
  ~Trie() {
    clear();
  }
  // @include
  bool insert(const string& s) {
    shared_ptr<TrieNode> p = root_;
    for (const char& c : s) {
      if (p->l.find(c) == p->l.cend()) {
        p->l[c] = shared_ptr<TrieNode>(new TrieNode{false});
      }
      p = p->l[c];
    }

    // s already existed in this trie
    if (p->isString == true) {
      return false;
    } else {  // p->isString == false
      p->isString = true;  // inserts s into this trie
      return true;
    }
  }

  string getShortestUniquePrefix(const string& s) {
    shared_ptr<TrieNode> p = root_;
    string prefix;
    for (const char& c : s) {
      prefix += c;
      if (p->l.find(c) == p->l.cend()) {
        return prefix;
      }
      p = p->l[c];
    }
    return {};
  }
  // @exclude
  void clear() {
    clear(root_);
  }
  // @include

 private:
  struct TrieNode {
    bool isString;
    unordered_map<char, shared_ptr<TrieNode>> l;
  };

  shared_ptr<TrieNode> root_ = shared_ptr<TrieNode>(new TrieNode{false});
  // @exclude
  void clear(shared_ptr<TrieNode> p) {
    for (const pair<char, shared_ptr<TrieNode>> &e : p->l) {
      if (e.second) {
        clear(e.second);
      }
    }
    p = nullptr;
  }
  // @include
};

string find_shortest_prefix(const string& s, const unordered_set<string>& D) {
  // Build a trie according to given dictionary D
  Trie T;
  for (const string& word : D) {
    T.insert(word);
  }
  return T.getShortestUniquePrefix(s);
}
// @exclude

string check_ans(const string &s, unordered_set<string> &D) {
  int len = 0;
  for (auto iter = D.cbegin(); iter != D.cend(); ++iter) {
    int i;
    for (i = 0; i < s.size() && i < (*iter).size(); ++i) {
      if (s[i] != (*iter)[i]) {
        break;
      }
    }
    if (i > len) {
      len = i;
    }
  }
  if (len == s.size()) {
    return string();
  } else {
    return s.substr(0, len + 1);
  }
}

int main(int argc, char *argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 100; ++times) {
    unordered_set<string> D;
    string s;
    if (argc == 2) {
      s = argv[1];
    } else {
      uniform_int_distribution<int> dis(1, 10);
      s = rand_string(dis(gen));
    }
    uniform_int_distribution<int> dis(1, 10000);
    int n = dis(gen);
    while (n--) {
      uniform_int_distribution<int> dis(1, 10);
      D.emplace(rand_string(dis(gen)));
    }
    /*
    for (unordered_set<string>::iterator iter = D.begin(); iter != D.end(); ++iter) {
      cout << *iter << ' ';
    }
    cout << endl;
    //*/
    cout << s << ' '  << "shortest prefix = " << find_shortest_prefix(s, D)
         << endl;
    assert(find_shortest_prefix(s, D) == check_ans(s, D));
  }
  return 0;
}
