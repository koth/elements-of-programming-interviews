#include <iostream>
#include <cassert>
#include <string>
#include <ctime>
#include <cstdlib>
#ifdef __clang__
#include <unordered_set>
#include <unordered_map>
#else
#include <tr1/unordered_set>
#include <tr1/unordered_map>
#endif

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
class Trie {
  private:
    class TrieNode {
      public:
        bool isString;
        unordered_map<char, shared_ptr<TrieNode> > l;
    };

    shared_ptr<TrieNode> root;
    // @exclude
    void clear(shared_ptr<TrieNode> p) {
      for (const pair<char, shared_ptr<TrieNode> > &e : p->l) {
        if (e.second) {
          clear(e.second);
        }
      }
      p = nullptr;
    }
    // @include

  public:
    Trie() : root(shared_ptr<TrieNode>(new TrieNode{false})) {}

    // @exclude
    ~Trie() {
      clear();
    }
    // @include
    bool insert(const string &s) {
      shared_ptr<TrieNode> p = root;
      for (const char &c : s) {
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

    string getShortestUniquePrefix(const string &s) {
      shared_ptr<TrieNode> p = root;
      string prefix;
      for (const char &c : s) {
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
      clear(root);
    }
    // @include
};

string find_shortest_prefix(const string &s, const unordered_set<string> &D) {
  // Build a trie according to given dictionary D
  Trie T;
  for (const string &word : D) {
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
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    unordered_set<string> D;
    string s;
    if (argc == 2) {
      s = argv[1];
    } else {
      s = rand_string(1 + rand() % 10);
    }
    int n = 1 + rand() % 10000;
    while (n--) {
      D.emplace(rand_string(1 + rand() % 10));
    }
    /*
    for (unordered_set<string>::iterator iter = D.begin(); iter != D.end(); ++iter) {
      cout << *iter << ' ';
    }
    cout << endl;
    //*/
    cout << s << ' '  << "shortest prefix = " << find_shortest_prefix(s, D) << endl;
    assert(find_shortest_prefix(s, D) == check_ans(s, D));
  }
  return 0;
}
