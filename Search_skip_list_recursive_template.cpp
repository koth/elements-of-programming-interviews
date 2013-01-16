#include <iostream>
#include <cassert>
#include <stack>

using namespace std;

template <typename T>
class node_t {
  public:
    T order;
    shared_ptr<node_t<T> > next, jump;
};

// @include
template <typename T>
void search_postings_list_helper(const shared_ptr<node_t<T> > &L,
                                 int &order) {
  if (L && L->order == -1) {
    L->order = order++;
    search_postings_list_helper<T>(L->jump, order);
    search_postings_list_helper<T>(L->next, order);
  }
}

template <typename T>
void search_postings_list(const shared_ptr<node_t<T> > &L) {
  int order = 0;
  search_postings_list_helper<T>(L, order);
}
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<node_t<int> > L = nullptr, curr;
  curr = L;
  // build a linked list L->1->2->3->4->5->nullptr
  for (size_t i = 0; i < 5; ++i) {
    shared_ptr<node_t<int> > temp = shared_ptr<node_t<int> >(new node_t<int>{-1, nullptr, nullptr});
    if (curr) {
      curr->next = temp;
      curr = temp;
    } else {
      curr = L = temp;
    }
  }
  L->jump = nullptr;  // no jump from 1
  L->next->jump = L->next->next->next;  // 2's jump points to 4
  L->next->next->jump = L;  // 3's jump points to 1
  L->next->next->next->jump = nullptr;  // no jump from 4
  L->next->next->next->next->jump = L->next->next->next->next;  // 5's jump points to 5
  shared_ptr<node_t<int> > temp = L;
  search_postings_list(L);
  // output the jump-first order, it should be 0, 1, 4, 2, 3
  assert(temp->order == 0);
  temp = temp->next;
  assert(temp->order == 1);
  temp = temp->next;
  assert(temp->order == 4);
  temp = temp->next;
  assert(temp->order == 2);
  temp = temp->next;
  assert(temp->order == 3);
  return 0;
}
