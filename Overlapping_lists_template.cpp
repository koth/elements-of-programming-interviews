#include "Linked_list_prototype_template.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

template <typename T>
shared_ptr<node_t<T> > has_cycle(const shared_ptr<node_t<T> > &head) {
  shared_ptr<node_t<T> > fast = head, slow = head;

  while (slow && slow->next && fast && fast->next && fast->next->next) {
    slow = slow->next, fast = fast->next->next;
    // Found cycle
    if (slow == fast) {
      // Calculate the cycle length
      int cycle_len = 0;
      do {
        ++cycle_len;
        fast = fast->next;
      } while (slow != fast);

      // Try to find the start of the cycle
      slow = head, fast = head;
      // Fast pointer advances cycle_len first
      while (cycle_len--) {
        fast = fast->next;
      }
      // Both pointers advance at the same time
      while (slow != fast) {
        slow = slow->next, fast = fast->next;
      }
      return slow;  // the start of cycle
    }
  }
  return nullptr;  // no cycle
}

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
shared_ptr<node_t<T> > overlapping_no_cycle_lists(
  shared_ptr<node_t<T> > L1, shared_ptr<node_t<T> > L2) {
  // Count the lengths of L1 and L2
  int L1_len = count_len<T>(L1), L2_len = count_len<T>(L2);

  while (L1_len > L2_len) {
    L1 = L1->next, --L1_len;
  }
  while (L2_len > L1_len) {
    L2 = L2->next, --L2_len;
  }

  while (L1 && L2 && L1 != L2) {
    L1 = L1->next, L2 = L2->next;
  }
  return L1;  // nullptr means no overlap between L1 and L2
}

// @include
template <typename T>
shared_ptr<node_t<T> > overlapping_lists(shared_ptr<node_t<T> > L1,
                                         shared_ptr<node_t<T> > L2) {
  // Store the start of cycle if any
  shared_ptr<node_t<T> > s1 = has_cycle<T>(L1), s2 = has_cycle<T>(L2);

  if (!s1 && !s2) {
    return overlapping_no_cycle_lists(L1, L2);
  } else if (s1 && s2) {  // both lists have cycles
    shared_ptr<node_t<T> > temp = s2;
    do {
      temp = temp->next;
    } while (temp != s1 && temp != s2);
    return temp == s1 ? s1 : nullptr;
  }
  return nullptr;  // one list has cycle, one list has no cycle
}
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<node_t<int> > L1, L2;
  // L1: 1->2->3->null
  L1 = shared_ptr<node_t<int> >(new node_t<int>{1, shared_ptr<node_t<int> >(new node_t<int>{2, shared_ptr<node_t<int> >(new node_t<int>{3, nullptr})})});
  L2 = L1->next->next;
  assert(overlapping_lists<int>(L1, L2)->data == 3);
  // L2: 4->5->null
  L2 = shared_ptr<node_t<int> >(new node_t<int>{4, shared_ptr<node_t<int> >(new node_t<int>{5, nullptr})});
  assert(!overlapping_lists<int>(L1, L2));
  L1->next->next->next = L1;
  assert(!overlapping_lists<int>(L1, L2));
  L2->next->next = L2;
  assert(!overlapping_lists<int>(L1, L2));
  L2->next->next = L1;
  assert(overlapping_lists<int>(L1, L2));
  return 0;
}
