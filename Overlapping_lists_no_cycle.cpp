// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <cassert>
#include <memory>

#include "./Linked_list_prototype_template.h"
#include "./Overlapping_lists_no_cycle.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

int main(int argc, char* argv[]) {
  shared_ptr<node_t<int>> L1, L2;
  // L1: 1->2->3->null
  L1 = make_shared<node_t<int>>(node_t<int>{
      1, make_shared<node_t<int>>(node_t<int>{2, make_shared<node_t<int>>(node_t<int>{3, nullptr})})});
  L2 = L1->next->next;
  assert(overlapping_no_cycle_lists<int>(L1, L2)->data == 3);
  // L2: 4->5->null
  L2 = make_shared<node_t<int>>(node_t<int>{4, make_shared<node_t<int>>(node_t<int>{5, nullptr})});
  assert(!overlapping_no_cycle_lists<int>(L1, L2));
  return 0;
}
