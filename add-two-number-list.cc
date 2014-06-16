// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "./Linked_list_prototype.h"

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::shared_ptr;

bool handle_carry(shared_ptr<ListNode<int>>* L);

// @include
shared_ptr<ListNode<int>> add_two_numbers(shared_ptr<ListNode<int>> L1,
                                          shared_ptr<ListNode<int>> L2) {
  const auto S = L1;
  while (L2) {
    L1->data += L2->data;
    handle_carry(&L1);
    if (!L1->next) {
      L1->next = L2->next;
      return S;
    }
    L1 = L1->next, L2 = L2->next;
  }

  // handle_carry returns boolean indicating if we can short circuit.
  while (L1 && handle_carry(&L1)) {
    L1 = L1->next;
  }
  return S;
}

// Return true if L has a carry to the next digit; otherwise, return false.
bool handle_carry(shared_ptr<ListNode<int>>* L) {
  if ((*L)->data < 10) {
    return false;
  }

  (*L)->data -= 10;
  if (!(*L)->next) {
    (*L)->next = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  }
  ++(*L)->next->data;
  return true;
}
// @exclude

int main(int argc, char* argv[]) {
  shared_ptr<ListNode<int>> L;
  L = make_shared<ListNode<int>>(ListNode<int>{
      2, make_shared<ListNode<int>>(ListNode<int>{
             4, make_shared<ListNode<int>>(ListNode<int>{3, nullptr})})});
  shared_ptr<ListNode<int>> R;
  R = make_shared<ListNode<int>>(ListNode<int>{
      5, make_shared<ListNode<int>>(ListNode<int>{
             6, make_shared<ListNode<int>>(ListNode<int>{7, nullptr})})});
  auto S = add_two_numbers(L, R);
  assert(S->data == 7 && S->next->data == 0 && S->next->next->data == 1 &&
         S->next->next->next->data == 1);
  L = make_shared<ListNode<int>>(ListNode<int>{
      9, make_shared<ListNode<int>>(ListNode<int>{9, nullptr})});
  R = make_shared<ListNode<int>>(ListNode<int>{9, nullptr});
  S = add_two_numbers(L, R);
  assert(S->data == 8 && S->next->data == 0 && S->next->next->data == 1);
  return 0;
}
