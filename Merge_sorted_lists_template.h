// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include "./Linked_list_prototype_template.h"

// @include
template <typename T>
void append_node(shared_ptr<node_t<T>>* head, shared_ptr<node_t<T>>* tail,
                 shared_ptr<node_t<T>>* n) {
  *head ? (*tail)->next = *n : *head = *n;
  *tail = *n;  // reset tail to the last node
}

template <typename T>
void append_node_and_advance(shared_ptr<node_t<T>>* head,
                             shared_ptr<node_t<T>>* tail,
                             shared_ptr<node_t<T>>* n) {
  append_node(head, tail, n);
  *n = (*n)->next;  // advance n
}

template <typename T>
shared_ptr<node_t<T>> merge_sorted_linked_lists(shared_ptr<node_t<T>> F,
                                                shared_ptr<node_t<T>> L) {
  shared_ptr<node_t<T>> sorted_head = nullptr, tail = nullptr;

  while (F && L) {
    append_node_and_advance(&sorted_head, &tail, F->data < L->data ? &F : &L);
  }

  // Append the remaining nodes of F
  if (F) {
    append_node(&sorted_head, &tail, &F);
  }
  // Append the remaining nodes of L
  if (L) {
    append_node(&sorted_head, &tail, &L);
  }
  return sorted_head;
}
// @exclude
