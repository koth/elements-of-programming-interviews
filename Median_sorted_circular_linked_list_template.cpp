#include "Linked_list_prototype_template.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// @include
template <typename T>
double find_median_sorted_circular_linked_list(
  const shared_ptr<node_t<T> > &r_node) {
  if (!r_node) {
    return 0.0;  // no node in this linked list
  }

  // Check all nodes are identical or not,
  shared_ptr<node_t<T> > curr = r_node;
  int count = 0;
  bool is_identical = true;
  do {
    if (curr->data != curr->next->data) {
      is_identical = false;
    }
    ++count, curr = curr->next;
  } while (curr != r_node);
  // If all values are identical, median = curr->data
  if (is_identical == true) {
    return curr->data;
  }

  // Try to identify the start of this linked list
  shared_ptr<node_t<T> > head = r_node;
  while (head->data <= head->next->data) {
    head = head->next;
  }
  head = head->next;

  // Traverse to the middle of the list and return the median
  for (int i = 0; i < (count - 1) >> 1; ++i) {
    head = head->next;
  }
  return count & 1 ? head->data : 0.5 * (head->data + head->next->data);
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    shared_ptr<node_t<int> > head;
    for (int i = n; i >= 0; --i) {
      shared_ptr<node_t<int> > curr = shared_ptr<node_t<int> >(new node_t<int>{i, nullptr});
      curr->next = head;
      head = curr;
    }
    shared_ptr<node_t<int> > curr = head;
    if (curr != shared_ptr<node_t<int> >(nullptr)) {
      while (curr->next != shared_ptr<node_t<int> >(nullptr)) {
        curr = curr->next;
      }
      curr->next = head;  // make the list become circular
    }
    double res = find_median_sorted_circular_linked_list<int>(head->next);
    cout << res << endl;
    assert(res == 0.5 * n);
  }
  return 0;
}
