// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <stack>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::stack;
using std::stoi;
using std::string;
using std::uniform_int_distribution;
using std::vector;

void generate_parentheses_helper(int remained, int left_parens, string* s,
                                 vector<string>* res);

// @include
vector<string> generate_parentheses(int n) {
  string s;
  vector<string> res;
  generate_parentheses_helper(n << 1, 0, &s, &res);
  return res;
}

void generate_parentheses_helper(int remained, int left_parens, string* s,
                                 vector<string>* res) {
  if (!remained) {
    res->emplace_back(*s);
    return;
  }

  if (left_parens < remained) {  // is able to insert '('.
    s->push_back('(');
    generate_parentheses_helper(remained - 1, left_parens + 1, s, res);
    s->pop_back();
  }
  if (left_parens > 0) {  // is able to insert ')'.
    s->push_back(')');
    generate_parentheses_helper(remained - 1, left_parens - 1, s, res);
    s->pop_back();
  }
}
// @exclude

void small_test() {
  auto res = generate_parentheses(1);
  assert(res.size() == 1 && !res.front().compare("()"));
  res = generate_parentheses(2);
  assert(res.size() == 2 && ((!res.front().compare("(())") && !res.back().compare("()()")) || (!res.front().compare("()()") && !res.back().compare("(())"))));
}

int main(int argc, char** argv) {
  small_test();
  default_random_engine gen((random_device())());
  int n;
  if (argc == 2) {
    n = stoi(argv[1]);
  } else {
    uniform_int_distribution<int> dis_n(0, 10);
    n = dis_n(gen);
  }
  cout << "n = " << n << endl;
  auto res = generate_parentheses(n);
  for (const string& s : res) {
    cout << s << " ";
  }
  cout << endl;
  return 0;
}
