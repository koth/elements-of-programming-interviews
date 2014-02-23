// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
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

bool exp_synthesis_helper(const vector<int>& A, int k, list<int>* operand_list,
                          list<char>* oper_list, int cur, int level);
int remaining_int(const vector<int>& A, int idx);
int evaluate(list<int> operand_list, const list<char>& oper_list);

list<int> operand_res;
list<char> oper_res;

// @include
void exp_synthesis(const vector<int>& A, int k) {
  list<char> oper_list;
  list<int> operand_list;
  if (!exp_synthesis_helper(A, k, &operand_list, &oper_list, 0, 0)) {
    cout << "no answer" << endl;
  }
}

bool exp_synthesis_helper(const vector<int>& A, int k,
                          list<int>* operand_list, list<char>* oper_list,
                          int cur, int level) {
  cur = cur * 10 + A[level];
  if (level == A.size() - 1) {
    operand_list->emplace_back(cur);
    if (evaluate(*operand_list, *oper_list) == k) {  // found a match.
      // @exclude
      operand_res = *operand_list, oper_res = *oper_list;
      // @include
      // Print the solution.
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
        remaining_int(A, level + 1)) {  // pruning.
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

// Calculate the int represented by A[idx:].
int remaining_int(const vector<int>& A, int idx) {
  int val = 0;
  for (size_t i = idx; i < A.size(); ++i) {
    val = val * 10 + A[idx];
  }
  return val;
}

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
// @exclude

void small_test() {
  vector<int> A = {1, 2, 3, 2, 5, 3, 7, 8, 5, 9};
  int k = 995;
  exp_synthesis(A, k);
  list<int> golden_operand_res = {123, 2, 5, 3, 7, 85, 9};
  assert(golden_operand_res.size() == operand_res.size());
  assert(equal(operand_res.begin(), operand_res.end(),
               golden_operand_res.begin()));
  list<char> golden_oper_res = {'+', '+', '*', '*', '+', '*'};
  assert(golden_oper_res.size() == oper_res.size());
  assert(equal(oper_res.begin(), oper_res.end(), golden_oper_res.begin()));
}

int main(int argc, char* argv[]) {
  small_test();
  default_random_engine gen((random_device())());
  vector<int> A;
  for (size_t i = 0; i < 10; ++i) {
    uniform_int_distribution<int> A_dis(0, 9);
    A.emplace_back(A_dis(gen));
  }
  int k;
  uniform_int_distribution<int> k_dis(0, 999);
  k = k_dis(gen);
  cout << "A = ";
  for (size_t i = 0; i < A.size(); ++i) {
    cout << A[i];
  }
  cout << ", k = " << k << endl;
  exp_synthesis(A, k);
  return 0;
}
