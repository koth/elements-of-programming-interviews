#include <iostream>
#include <memory>

using namespace std;

#pragma once
// @include
template <typename T>
class node_t {
  public:
    T data;
    shared_ptr<node_t<T> > next, jump;
};
// @exclude
