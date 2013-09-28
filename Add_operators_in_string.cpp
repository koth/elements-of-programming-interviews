// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::list;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

// @include
int evaluate(list<int> operand_list, const list<char>& oper_list) {
  // Evaluate '*' first.
  auto operand_it = operand_list.begin();
  for (const char& oper : oper_list) {
    if (oper == '*') {
      int product = *operand_it;
      operand_it = operand_list.erase(operand_it);
      product *= *operand_it;
      *operand_it = product;
    } else {
      ++operand_it;
    }
  }

  // Evaluate '+' second.
  return accumulate(operand_list.cbegin(), operand_list.cend(), 0);
}

bool exp_synthesis_helper(const vector<int>& A,
                          int k,
                          list<int>* operand_list,
                          list<char>* oper_list,
                          int cur,
                          int level) {
  cur = cur * 10 + A[level] - '0';
  if (level == A.size() - 1) {
    operand_list->emplace_back(cur);
    if (evaluate(*operand_list, *oper_list) == k) {
      auto operand_it = operand_list->cbegin();
      cout << *operand_it++;
      for (const char& oper : *oper_list) {
        cout << ' ' << oper << ' ' << *operand_it++;
      }
      cout << " = " << k << endl;
      return true;
    }
    operand_list->pop_back();
  } else {
    // No operator.
    if (exp_synthesis_helper(A, k, operand_list, oper_list, cur, level + 1)) {
      return true;
    }

    // Add operator '+'.
    operand_list->emplace_back(cur);
    if (k - evaluate(*operand_list, *oper_list) <=
        stoi(string(A.cbegin() + level + 1, A.cend()))) {  // pruning.
      oper_list->emplace_back('+');
      if (exp_synthesis_helper(A, k, operand_list, oper_list, 0, level + 1)) {
        return true;
      }
      oper_list->pop_back();  // revert.
    }
    operand_list->pop_back();  // revert.

    // Add operator '*'.
    operand_list->emplace_back(cur), oper_list->emplace_back('*');
    if (exp_synthesis_helper(A, k, operand_list, oper_list, 0, level + 1)) {
      return true;
    }
    operand_list->pop_back(), oper_list->pop_back();  // revert.
  }
  return false;
}

void exp_synthesis(const vector<int>& A, int k) {
  list<char> oper_list;
  list<int> operand_list;
  if (!exp_synthesis_helper(A, k, &operand_list, &oper_list, 0, 0)) {
    cout << "no answer" << endl;
  }
}
// @exclude

string rand_string(int len) {
  string ret;
  default_random_engine gen((random_device())());
  uniform_int_distribution<int> dis('1', '9');
  ret += dis(gen);
  while (--len) {
    uniform_int_distribution<int> dis('0', '9');
    ret += dis(gen);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  string s;
  int k;
  default_random_engine gen((random_device())());
  if (argc == 3) {
    s = argv[1];
    k = atoi(argv[2]);
  } else {
    s = rand_string(10);
    uniform_int_distribution<int> k_dis(0, 999);
    k = k_dis(gen);
  }
  vector<int> A;
  for (const char& c : s) {
    A.emplace_back(c);
  }
  cout << "s = " << s << ", k = " << k << endl;
  exp_synthesis(A, k);
  return 0;
}
