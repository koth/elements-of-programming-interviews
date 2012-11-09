#include <iostream>
#include <memory>

using namespace std;
#pragma once
// @include
template <typename T>
class BinaryTree {
  public:
    T data;
    shared_ptr<BinaryTree<T> > left, right;
};
// @exclude
