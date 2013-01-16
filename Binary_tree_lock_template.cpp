#include <iostream>
#include <cassert>

using namespace std;

// @include
template <typename T>
class BinaryTree {
  private:
    bool locked;
    int numChildrenLocks;

  public:
    shared_ptr<BinaryTree<T> > left, right, parent;

    const bool &isLock(void) const {
      return locked;
    }

    void lock(void) {
      if (numChildrenLocks == 0 && locked == false) {
        // Make sure all parents do not lock
        shared_ptr<BinaryTree<T> > n = parent;
        while (n) {
          if (n->locked == true) {
            return;
          }
          n = n->parent;
        }

        // Lock itself and update its parents
        locked = true;
        n = parent;
        while (n) {
          ++n->numChildrenLocks;
          n = n->parent;
        }
      }
    }

    void unLock(void) {
      if (locked) {
        // Unlock itself and update its parents
        locked = false;
        shared_ptr<BinaryTree<T> > n = parent;
        while (n) {
          --n->numChildrenLocks;
          n = n->parent;
        }
      }
    }
};
// @exclude

int main(int argc, char *argv[]) {
  shared_ptr<BinaryTree<int> > root = shared_ptr<BinaryTree<int> >(new BinaryTree<int>());
  root->left = shared_ptr<BinaryTree<int> >(new BinaryTree<int>());
  root->left->parent = root;
  root->right = shared_ptr<BinaryTree<int> >(new BinaryTree<int>());
  root->right->parent = root;
  root->left->left = shared_ptr<BinaryTree<int> >(new BinaryTree<int>());
  root->left->left->parent = root->left;
  root->left->right = shared_ptr<BinaryTree<int> >(new BinaryTree<int>());
  root->left->right->parent = root->left;
  // should output false
  assert(root->isLock() == false);
  cout << boolalpha << root->isLock() << endl;
  root->lock();
  // should output true
  assert(root->isLock() == true);
  cout << boolalpha << root->isLock() << endl;
  root->unLock();
  root->left->lock();
  root->lock();
  // should output false
  assert(root->isLock() == false);
  cout << boolalpha << root->isLock() << endl;
  root->right->lock();
  // should output true
  assert(root->right->isLock() == true);
  cout << boolalpha << root->isLock() << endl;
  return 0;
}
