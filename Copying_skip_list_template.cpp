#include "Postings_list_prototype.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// @include
template <typename T>
shared_ptr<node_t<T> > copy_postings_list(const shared_ptr<node_t<T> > &L) {
  // Return empty list if L is nullptr
  if (!L) {
    return nullptr;
  }

  // 1st stage: copy the nodes from L
  shared_ptr<node_t<T> > p = L;
  while (p) {
    auto temp =
      shared_ptr<node_t<T> >(new node_t<T>{p->data, p->next, nullptr});
    p->next = temp;
    p = temp->next;
  }

  // 2nd stage: update the jump field
  p = L;
  while (p) {
    if (p->jump) {
      p->next->jump = p->jump->next;
    }
    p = p->next->next;
  }

  // 3rd stage: restore the next field
  p = L;
  shared_ptr<node_t<T> > copied = p->next;
  while (p->next) {
    shared_ptr<node_t<T> > temp = p->next;
    p->next = temp->next;
    p = temp;
  }
  return copied;
}
// @exclude

template <typename T>
void check_postings_list_equal(shared_ptr<node_t<T> > a, shared_ptr<node_t<T> > b) {
  while (a && b) {
    cout << a->data << ' ';
    assert(a->data == b->data);
    assert((a->jump == shared_ptr<node_t<T> >(nullptr) && b->jump == shared_ptr<node_t<T> >(nullptr)) || (a->jump && b->jump && a->jump->data == b->jump->data));
    if (a->jump) {
      cout << a->jump->data;
    }
    cout << endl;
    a = a->next, b = b->next;
  }
  assert(a == shared_ptr<node_t<T> >(nullptr) && b == shared_ptr<node_t<T> >(nullptr));
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    shared_ptr<node_t<int> > L = shared_ptr<node_t<int> >(nullptr);
    shared_ptr<node_t<int> > curr = L;
    for (int i = 0; i < n; ++i) {
      shared_ptr<node_t<int> > temp = shared_ptr<node_t<int> >(new node_t<int>{i, nullptr});
      if (L) {
        curr->next = temp;
        curr = temp;
      } else {
        curr = L = temp;
      }
      // randomly assigned a jump node
      int jump_num = rand() % (i + 2);
      shared_ptr<node_t<int> > jump = L;
      while (jump_num--) {
        jump = jump->next;
      }
      temp->jump = jump;
    }
    shared_ptr<node_t<int> > copied = copy_postings_list<int>(L);
    check_postings_list_equal<int>(L, copied);
  }
  return 0;
}
