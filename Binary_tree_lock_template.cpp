// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

using std::boolalpha;
using std::cout;
using std::endl;
using std::shared_ptr;

// @include
template <typename T>
class BinaryTree {
 public:
  const bool &isLock(void) const {
    return locked_;
  }

  void lock(void) {
    if (numChildreLocks_ == 0 && locked_ == false) {
      // Make sure all parents do not lock
      shared_ptr<BinaryTree<T>> n = parent_;
      while (n) {
        if (n->locked_ == true) {
          return;
        }
        n = n->parent_;
      }

      // Lock itself and update its parents
      locked_ = true;
      n = parent_;
      while (n) {
        ++n->numChildreLocks_;
        n = n->parent_;
      }
    }
  }

  void unLock(void) {
    if (locked_) {
      // Unlock itself and update its parents
      locked_ = false;
      shared_ptr<BinaryTree<T>> n = parent_;
      while (n) {
        --n->numChildreLocks_;
        n = n->parent_;
      }
    }
  }

  // @exclude
  shared_ptr<BinaryTree<T>>& left() {
    return left_;
  }

  shared_ptr<BinaryTree<T>>& right() {
    return right_;
  }

  shared_ptr<BinaryTree<T>>& parent() {
    return parent_;
  }
  // @include
 private:
  shared_ptr<BinaryTree<T>> left_, right_, parent_;

  bool locked_;
  int numChildreLocks_;
};
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<BinaryTree<int>> root =
    shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left() = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left()->parent() = root;
  root->right() = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->right()->parent() = root;
  root->left()->left() = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left()->left()->parent() = root->left();
  root->left()->right() = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left()->right()->parent() = root->left();
  // should output false
  assert(root->isLock() == false);
  cout << boolalpha << root->isLock() << endl;
  root->lock();
  // should output true
  assert(root->isLock() == true);
  cout << boolalpha << root->isLock() << endl;
  root->unLock();
  root->left()->lock();
  root->lock();
  // should output false
  assert(root->isLock() == false);
  cout << boolalpha << root->isLock() << endl;
  root->right()->lock();
  // should output true
  assert(root->right()->isLock() == true);
  cout << boolalpha << root->isLock() << endl;
  return 0;
}
