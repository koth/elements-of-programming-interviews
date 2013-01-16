#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cassert>

using namespace std;

class node_t {
  public:
    int data;
    node_t* next;
    node_t(int val = 0, node_t *ptr = NULL) : data(val), next(ptr) {}
};

// @include
void add_node_last(node_t* &head, node_t* &tail, node_t* n) {
  if (head == NULL) {
    head = n;
  } else {
    tail->next = n;
  }
  tail = n;
}

node_t* merge_sorted_linked_lists(node_t* F, node_t* L) {
  node_t *sorted_head = NULL, *sorted_tail = NULL;

  while (F != NULL && L != NULL) {
    if (F->data < L->data) {
      add_node_last(sorted_head, sorted_tail, F);
      F = F->next;
    } else {
      add_node_last(sorted_head, sorted_tail, L);
      L = L->next;
    }
  }

  while (F != NULL) {
    add_node_last(sorted_head, sorted_tail, F);
    F = F->next;
  }
  while (L != NULL) {
    add_node_last(sorted_head, sorted_tail, L);
    L = L->next;
  }
  return sorted_head;
}
// @exclude

int main(int argc, char *argv[]) {
  // input 2 two lists using -1 as delimiter.
  node_t *F = NULL, *L = NULL, **sorted_tail;
  srand(time(NULL));
  int n, m;
  if (argc > 3) {
    sorted_tail = &F;
    for (int i = 1; i < argc; ++i) {
      if (atoi(argv[i]) == -1) {
        sorted_tail = &L;
      } else {
        node_t *temp = new node_t(atoi(argv[i]));
        temp->next = *sorted_tail;
        *sorted_tail = temp;
      }
    }
  } else {
    if (argc == 3) {
      n = atoi(argv[1]), m = atoi(argv[2]);
    } else if (argc == 2) {
      n = atoi(argv[1]), m = atoi(argv[1]);
    } else {
      n = rand() % 100, m = rand() % 100;
    }
    for (int i = n; i >= 0; --i) {
      node_t *temp = new node_t(i);
      temp->next = F;
      F = temp;
    }
    for (int j = m; j >= 0; --j) {
      node_t *temp = new node_t(j);
      temp->next = L;
      L = temp;
    }
  }
  node_t *sorted_head = merge_sorted_linked_lists(F, L);
  int pre = numeric_limits<int>::min();
  while (sorted_head != NULL) {
    assert(pre <= sorted_head->data);
    cout << sorted_head->data <<endl;
    pre = sorted_head->data;
    sorted_head = sorted_head->next;
  }
  return 0;
}
