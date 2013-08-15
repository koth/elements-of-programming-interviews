// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>

#include "./Checking_cycle.h"
#include "./Linked_list_prototype_template.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  shared_ptr<node_t<int>> L3 =
      shared_ptr<node_t<int>>(new node_t<int>{3, nullptr});
  shared_ptr<node_t<int>> L2 = shared_ptr<node_t<int>>(new node_t<int>{2, L3});
  shared_ptr<node_t<int>> L1 = shared_ptr<node_t<int>>(new node_t<int>{1, L2});

  // should output "L1 does not have cycle."
  assert(has_cycle(L1) == shared_ptr<node_t<int>>(nullptr));
  cout << "L1 " << (has_cycle(L1) ? "has" : "does not have")
       << " cycle." << endl;

  // make it a cycle
  L3->next = L2;
  // should output "L1 has cycle, located at node has value 2"
  assert(has_cycle(L1) != shared_ptr<node_t<int>>(nullptr));
  assert(has_cycle(L1)->data == 2);
  shared_ptr<node_t<int>> temp = has_cycle(L1);
  if (temp) {
    cout << "L1 has cycle, located at node has value " << temp->data << endl;
  } else {
    cout << "L1 does not have cycle" << endl;
  }
  return 0;
}
