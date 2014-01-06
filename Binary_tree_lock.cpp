// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
class BinaryTree {
 public:
  bool isLock() const { return locked_; }

  void lock() {
    if (numChildreLocks_ == 0 && !locked_) {
      // Make sure all parents do not lock.
      shared_ptr<BinaryTree> n = parent_;
      while (n) {
        if (n->locked_) {
          return;
        }
        n = n->parent_;
      }

      // Lock itself and update its parents.
      locked_ = true;
      n = parent_;
      while (n) {
        ++n->numChildreLocks_;
        n = n->parent_;
      }
    }
  }

  void unLock() {
    if (locked_) {
      // Unlock itself and update its parents.
      locked_ = false;
      shared_ptr<BinaryTree> n = parent_;
      while (n) {
        --n->numChildreLocks_;
        n = n->parent_;
      }
    }
  }

  // @exclude
  shared_ptr<BinaryTree>& left() { return left_; }

  shared_ptr<BinaryTree>& right() { return right_; }

  shared_ptr<BinaryTree>& parent() { return parent_; }
  // @include
 private:
  shared_ptr<BinaryTree> left_, right_, parent_;

  bool locked_;
  int numChildreLocks_;
};
// @exclude

int main(int argc, char* argv[]) {
  auto root = make_shared<BinaryTree>(BinaryTree());
  root->left() = make_shared<BinaryTree>(BinaryTree());
  root->left()->parent() = root;
  root->right() = make_shared<BinaryTree>(BinaryTree());
  root->right()->parent() = root;
  root->left()->left() = make_shared<BinaryTree>(BinaryTree());
  root->left()->left()->parent() = root->left();
  root->left()->right() = make_shared<BinaryTree>(BinaryTree());
  root->left()->right()->parent() = root->left();
  // Should output false.
  assert(!root->isLock());
  cout << boolalpha << root->isLock() << endl;
  root->lock();
  // Should output true.
  assert(root->isLock());
  cout << boolalpha << root->isLock() << endl;
  root->unLock();
  root->left()->lock();
  root->lock();
  // Should output false.
  assert(!root->isLock());
  cout << boolalpha << root->isLock() << endl;
  root->right()->lock();
  // Should output true.
  assert(root->right()->isLock());
  cout << boolalpha << root->right()->isLock() << endl;
  return 0;
}
