// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Linked_list_prototype_template.h"

void append_node_and_advance(shared_ptr<node_t<int>>* head,
                             shared_ptr<node_t<int>>* tail,
                             shared_ptr<node_t<int>>* n);
void append_node(shared_ptr<node_t<int>>* head,
                 shared_ptr<node_t<int>>* tail,
                 shared_ptr<node_t<int>>* n);

// @include
shared_ptr<node_t<int>> merge_sorted_linked_lists(shared_ptr<node_t<int>> F,
                                                  shared_ptr<node_t<int>> L) {
  shared_ptr<node_t<int>> sorted_head = nullptr, tail = nullptr;

  while (F && L) {
    append_node_and_advance(&sorted_head, &tail, F->data < L->data ? &F : &L);
  }

  // Append the remaining nodes of F.
  if (F) {
    append_node(&sorted_head, &tail, &F);
  }
  // Append the remaining nodes of L.
  if (L) {
    append_node(&sorted_head, &tail, &L);
  }
  return sorted_head;
}

void append_node_and_advance(shared_ptr<node_t<int>>* head,
                             shared_ptr<node_t<int>>* tail,
                             shared_ptr<node_t<int>>* n) {
  append_node(head, tail, n);
  *n = (*n)->next;  // advance n.
}

void append_node(shared_ptr<node_t<int>>* head,
                 shared_ptr<node_t<int>>* tail,
                 shared_ptr<node_t<int>>* n) {
  *head ? (*tail)->next = *n : *head = *n;
  *tail = *n;  // reset tail to the last node.
}
// @exclude
