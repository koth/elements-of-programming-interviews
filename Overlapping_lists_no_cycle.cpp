#include "Linked_list_prototype_template.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// @include
// Count the list length till end
template <typename T>
int count_len(shared_ptr<node_t<T> > L) {
  int len = 0;
  while (L) {
    ++len, L = L->next;
  }
  return len;
}

template <typename T>
void advance_list_by_k(shared_ptr<node_t<T> > &L, int k) {
  while (k--) {
    L = L->next;
  }
}

template <typename T>
shared_ptr<node_t<T> > overlapping_no_cycle_lists(shared_ptr<node_t<T> > L1,
                                                  shared_ptr<node_t<T> > L2) {
  // Count the lengths of L1 and L2
  int L1_len = count_len<T>(L1), L2_len = count_len<T>(L2);

  // Advance the longer list
  advance_list_by_k(L1_len > L2_len ? L1 : L2, abs(L1_len - L2_len));

  while (L1 && L2 && L1 != L2) {
    L1 = L1->next, L2 = L2->next;
  }
  return L1;  // nullptr means no overlap between L1 and L2
}
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<node_t<int> > L1, L2;
  // L1: 1->2->3->null
  L1 = shared_ptr<node_t<int> >(new node_t<int>{1, shared_ptr<node_t<int> >(new node_t<int>{2, shared_ptr<node_t<int> >(new node_t<int>{3, nullptr})})});
  L2 = L1->next->next;
  assert(overlapping_no_cycle_lists<int>(L1, L2)->data == 3);
  // L2: 4->5->null
  L2 = shared_ptr<node_t<int> >(new node_t<int>{4, shared_ptr<node_t<int> >(new node_t<int>{5, nullptr})});
  assert(!overlapping_no_cycle_lists<int>(L1, L2));
  return 0;
}
