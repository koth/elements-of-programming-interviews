// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>

#include "./Postings_list_prototype.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::random_device;
using std::shared_ptr;
using std::uniform_int_distribution;

// @include
template <typename T>
shared_ptr<node_t<T>> copy_postings_list(const shared_ptr<node_t<T>>& L) {
  // Return empty list if L is nullptr.
  if (!L) {
    return nullptr;
  }

  // 1st stage: Copy the nodes from L.
  shared_ptr<node_t<T>> p = L;
  while (p) {
    auto temp = make_shared<node_t<T>>(node_t<T>{p->data, p->next, nullptr});
    p->next = temp;
    p = temp->next;
  }

  // 2nd stage: Update the jump field.
  p = L;
  while (p) {
    if (p->jump) {
      p->next->jump = p->jump->next;
    }
    p = p->next->next;
  }

  // 3rd stage: Restore the next field.
  p = L;
  shared_ptr<node_t<T>> copied = p->next;
  while (p->next) {
    shared_ptr<node_t<T>> temp = p->next;
    p->next = temp->next;
    p = temp;
  }
  return copied;
}
// @exclude

template <typename T>
void check_postings_list_equal(shared_ptr<node_t<T>> a,
                               shared_ptr<node_t<T>> b) {
  while (a && b) {
    cout << a->data << ' ';
    assert(a->data == b->data);
    assert((a->jump == shared_ptr<node_t<T>>(nullptr) &&
            b->jump == shared_ptr<node_t<T>>(nullptr)) ||
           (a->jump && b->jump && a->jump->data == b->jump->data));
    if (a->jump) {
      cout << a->jump->data;
    }
    cout << endl;
    a = a->next, b = b->next;
  }
  assert(a == shared_ptr<node_t<T>>(nullptr) &&
         b == shared_ptr<node_t<T>>(nullptr));
}

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> n_dis(1, 1000);
      n = n_dis(gen);
    }
    shared_ptr<node_t<int>> L = nullptr;
    shared_ptr<node_t<int>> curr = L;
    for (int i = 0; i < n; ++i) {
      auto temp = make_shared<node_t<int>>(node_t<int>{i, nullptr});
      if (L) {
        curr->next = temp;
        curr = temp;
      } else {
        curr = L = temp;
      }
      // Randomly assigned a jump node.
      uniform_int_distribution<int> dis(0, i + 1);
      int jump_num = dis(gen);
      shared_ptr<node_t<int>> jump = L;
      while (jump_num--) {
        jump = jump->next;
      }
      temp->jump = jump;
    }
    shared_ptr<node_t<int>> copied = copy_postings_list<int>(L);
    check_postings_list_equal<int>(L, copied);
  }
  return 0;
}
