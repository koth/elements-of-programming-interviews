#include "Linked_list_prototype_template.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cassert>

using namespace std;

// @include
template <typename T>
void add_node_last(
  shared_ptr<node_t<T> > &head,
  shared_ptr<node_t<T> > &tail,
  const shared_ptr<node_t<T> > &n) {
  if (head) {
    tail->next = n;
  } else {
    head = n;
  }
  tail = n;
}

template <typename T>
shared_ptr<node_t<T> > merge_sorted_linked_lists(
  shared_ptr<node_t<T> > F, shared_ptr<node_t<T> > L) {
  shared_ptr<node_t<T> > sorted_head = nullptr, sorted_tail = nullptr;

  while (F && L) {
    if (F->data < L->data) {
      add_node_last<T>(sorted_head, sorted_tail, F);
      F = F->next;
    } else {
      add_node_last<T>(sorted_head, sorted_tail, L);
      L = L->next;
    }
  }

  while (F) {
    add_node_last<T>(sorted_head, sorted_tail, F);
    F = F->next;
  }
  while (L) {
    add_node_last<T>(sorted_head, sorted_tail, L);
    L = L->next;
  }
  return sorted_head;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    shared_ptr<node_t<int> > F = shared_ptr<node_t<int> >(nullptr), L = shared_ptr<node_t<int> >(nullptr);
    int n, m;
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else if (argc == 2) {
      n = atoi(argv[1]), m = atoi(argv[1]);
    } else {
      n = rand() % 100, m = rand() % 100;
    }
    for (int i = n; i >= 0; --i) {
      shared_ptr<node_t<int> > temp = shared_ptr<node_t<int> >(new node_t<int>{i, nullptr});
      temp->next = F;
      F = temp;
    }
    for (int j = m; j >= 0; --j) {
      shared_ptr<node_t<int> > temp = shared_ptr<node_t<int> >(new node_t<int>{j, nullptr});
      temp->next = L;
      L = temp;
    }

    shared_ptr<node_t<int> > sorted_head = merge_sorted_linked_lists(F, L);
    int pre = numeric_limits<int>::min();
    while (sorted_head) {
      assert(pre <= sorted_head->data);
      //cout << sorted_head->data <<endl;
      pre = sorted_head->data;
      sorted_head = sorted_head->next;
    }
  }
  return 0;
}
