#include "Linked_list_prototype_template.h"
#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T>
shared_ptr<node_t<T>> reverse_linked_list(const shared_ptr<node_t<T>> &head) {
  shared_ptr<node_t<T>> prev = nullptr, curr = head;
  while (curr) {
    shared_ptr<node_t<T>> temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  return prev;
}

// @include
template <typename T>
void connect_a_next_to_b_advance_a(shared_ptr<node_t<T>> &a, 
                                   const shared_ptr<node_t<T>> &b) {
  shared_ptr<node_t<T>> temp = a->next;
  a->next = b;
  a = temp;
}

template <typename T>
shared_ptr<node_t<T>> zipping_linked_list(const shared_ptr<node_t<T>> &L) {
  shared_ptr<node_t<T>> slow = L, fast = L, pre_slow = nullptr;

  // Find the middle point of L
  while (fast) {
    fast = fast->next;
    if (fast) {
      pre_slow = slow;
      fast = fast->next, slow = slow->next;
    }
  }

  if (!pre_slow) {
    return L;  // only contains one node in the list
  }
  pre_slow->next = nullptr;  // split the list into two lists
  shared_ptr<node_t<T>> reverse = reverse_linked_list<T>(slow), curr = L;

  // Zipping the list
  while (curr && reverse) {
    // connect curr->next to reverse, and advance curr
    connect_a_next_to_b_advance_a(curr, reverse);
    if (curr) {
      // connect reverse->next to curr, and advance reverse
      connect_a_next_to_b_advance_a(reverse, curr);
    }
  }
  return L;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  shared_ptr<node_t<int>> head = nullptr;
  int n;
  if (argc > 2) {
    for (size_t i = 1; i < argc; ++i) {
      shared_ptr<node_t<int>> curr = shared_ptr<node_t<int>>(new node_t<int>{atoi(argv[i]), nullptr});
      curr->next = head;
      head = curr;
    }
  } else {
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    for (int i = n; i >= 0; --i) {
      shared_ptr<node_t<int>> curr = shared_ptr<node_t<int>>(new node_t<int>{i, nullptr});
      curr->next = head;
      head = curr;
    }
  }
  shared_ptr<node_t<int>> curr = zipping_linked_list<int>(head);
  int idx = 0, pre;
  while (curr) {
    if (argc <= 2) {
      if (idx & 1) {
        assert(pre + curr->data == n);
      }
    }
    ++idx;
    cout << curr->data << endl;
    pre = curr->data;
    curr = curr->next;
  }
  return 0;
}
