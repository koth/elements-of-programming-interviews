// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Linked_list_prototype.h"

void append_node_and_advance(shared_ptr<ListNode<int>>* head,
                             shared_ptr<ListNode<int>>* tail,
                             shared_ptr<ListNode<int>>* node);
void append_node(const shared_ptr<ListNode<int>>& node,
                 shared_ptr<ListNode<int>>* head,
                 shared_ptr<ListNode<int>>* tail);

// @include
shared_ptr<ListNode<int>> merge_sorted_linked_lists(
    shared_ptr<ListNode<int>> F, shared_ptr<ListNode<int>> L) {
  shared_ptr<ListNode<int>> sorted_head = nullptr, tail = nullptr;

  while (F && L) {
    append_node_and_advance(&sorted_head, &tail, F->data < L->data ? &F : &L);
  }

  // Appends the remaining nodes of F.
  if (F) {
    append_node(F, &sorted_head, &tail);
  }
  // Appends the remaining nodes of L.
  if (L) {
    append_node(L, &sorted_head, &tail);
  }
  return sorted_head;
}

void append_node_and_advance(shared_ptr<ListNode<int>>* head,
                             shared_ptr<ListNode<int>>* tail,
                             shared_ptr<ListNode<int>>* node) {
  append_node(*node, head, tail);
  *node = (*node)->next;  // advances node.
}

void append_node(const shared_ptr<ListNode<int>>& node,
                 shared_ptr<ListNode<int>>* head,
                 shared_ptr<ListNode<int>>* tail) {
  *head ? (*tail)->next = node : *head = node;
  *tail = node;  // resets tail to the last node.
}
// @exclude
