// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_POSTINGS_LIST_PROTOTYPE_H_
#define SOLUTIONS_POSTINGS_LIST_PROTOTYPE_H_

#include <memory>

using std::shared_ptr;

// @include
template <typename T>
class node_t {
  public:
    T data;
    shared_ptr<node_t<T>> next, jump;
};
// @exclude
#endif  // SOLUTIONS_POSTINGS_LIST_PROTOTYPE_H_
