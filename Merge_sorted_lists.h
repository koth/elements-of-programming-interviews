// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Linked_list_prototype.h"

void append_node_and_advance(shared_ptr<ListNode<int>>* head,
                             shared_ptr<ListNode<int>>* tail,
                             shared_ptr<ListNode<int>>* node);
void append_node(shared_ptr<ListNode<int>>* head,
                 shared_ptr<ListNode<int>>* tail,
                 shared_ptr<ListNode<int>>* node);

// @include
shared_ptr<ListNode<int>> merge_sorted_linked_lists(
    shared_ptr<ListNode<int>> F, shared_ptr<ListNode<int>> L) {
  shared_ptr<ListNode<int>> sorted_head = nullptr, tail = nullptr;

  while (F && L) {
    append_node_and_advance(&sorted_head, &tail, F->data < L->data ? &F : &L);
  }

  // Appends the remaining nodes of F.
  if (F) {
    append_node(&sorted_head, &tail, &F);
  }
  // Appends the remaining nodes of L.
  if (L) {
    append_node(&sorted_head, &tail, &L);
  }
  return sorted_head;
}

void append_node_and_advance(shared_ptr<ListNode<int>>* head,
                             shared_ptr<ListNode<int>>* tail,
                             shared_ptr<ListNode<int>>* node) {
  append_node(head, tail, node);
  *node = (*node)->next;  // advances node.
}

void append_node(shared_ptr<ListNode<int>>* head,
                 shared_ptr<ListNode<int>>* tail,
                 shared_ptr<ListNode<int>>* node) {
  *head ? (*tail)->next = *node : *head = *node;
  *tail = *node;  // resets tail to the last node.
}
// @exclude
