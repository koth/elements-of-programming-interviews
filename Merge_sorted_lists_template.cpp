#include "Linked_list_prototype_template.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cassert>

using namespace std;

// @include
template <typename T>
void append_node_and_advance(shared_ptr<node_t<T> > &head,
                             shared_ptr<node_t<T> > &tail,
                             shared_ptr<node_t<T> > &n) {
  head ? tail->next = n : head = n;
  tail = n;  // reset tail to the last node
  n = n->next;  // advance n
}

template <typename T>
shared_ptr<node_t<T> > merge_sorted_linked_lists(shared_ptr<node_t<T> > F,
                                                 shared_ptr<node_t<T> > L) {
  shared_ptr<node_t<T> > sorted_head = nullptr, sorted_tail = nullptr;

  while (F && L) {
    append_node_and_advance(sorted_head, sorted_tail,
                            F->data < L->data ? F : L);
  }

  // Append the remaining of F
  while (F) {
    append_node_and_advance(sorted_head, sorted_tail, F);
  }
  // Append the remaining of L
  while (L) {
    append_node_and_advance(sorted_head, sorted_tail, L);
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
