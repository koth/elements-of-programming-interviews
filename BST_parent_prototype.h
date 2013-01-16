#include <iostream>
#include <memory>

using namespace std;
#pragma once
// @include
template <typename T>
class BinarySearchTree {
  public:
    T data;
    shared_ptr<BinarySearchTree<T> > left, right, parent;
};
// @exclude
