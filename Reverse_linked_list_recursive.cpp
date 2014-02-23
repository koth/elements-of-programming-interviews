// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "./Linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<ListNode<int>> reverse_linked_list(
    const shared_ptr<ListNode<int>>& head) {
  if (!head || !head->next) {
    return head;
  }

  shared_ptr<ListNode<int>> new_head = reverse_linked_list(head->next);
  head->next->next = head;
  head->next = nullptr;
  return new_head;
}
// @exclude

void print(shared_ptr<ListNode<int>> head) {
  if (head) {
    cout << "(" << head->data << ")" << endl;
    print(head->next);
  }
}

int main(int argc, char* argv[]) {
  shared_ptr<ListNode<int>> L1 =
      make_shared<ListNode<int>>(ListNode<int>{1, nullptr});
  shared_ptr<ListNode<int>> L2 =
      make_shared<ListNode<int>>(ListNode<int>{2, nullptr});
  L1->next = L2;
  shared_ptr<ListNode<int>> L3 =
      make_shared<ListNode<int>>(ListNode<int>{3, nullptr});
  L2->next = L3;

  cout << "before reverse" << endl;
  print(L1);
  shared_ptr<ListNode<int>> newhead = reverse_linked_list(L1);
  assert(newhead->data == 3 && newhead->next->data == 2 && newhead->next->next->data == 1);
  cout << endl << "after reverse" << endl;
  print(newhead);
  newhead = reverse_linked_list(newhead);
  assert(newhead->data == 1 && newhead->next->data == 2 && newhead->next->next->data == 3);
  cout << endl << "after another reverse" << endl;
  print(newhead);
  return 0;
}
