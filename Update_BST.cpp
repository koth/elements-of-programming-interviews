#include <iostream>
#include <cassert>

using namespace std;

// @include
template <typename T>
class BinarySearchTree {
  private:
    class TreeNode {
      public:
        T data;
        shared_ptr<TreeNode> left, right;
    };

    void clear(shared_ptr<TreeNode> &n) {
      if (n) {
        clear(n->left), clear(n->right);
        n = nullptr;
      }
    }

    // Replace the link between par and child by new_link
    void replaceParentChildLink(shared_ptr<TreeNode> par,
                                shared_ptr<TreeNode> child,
                                shared_ptr<TreeNode> new_link) {
      if (!par) {
        return;
      }

      if (par->left == child) {
        par->left = new_link;
      } else {
        par->right = new_link;
      }
    }

    shared_ptr<TreeNode> root;

  public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
      clear();
    }

    const bool empty() const {
      return !root;
    }

    void clear() {
      clear(root);
    }

    const bool insert(const T &key) {
      shared_ptr<TreeNode>
        t = shared_ptr<TreeNode>(new TreeNode{key, nullptr, nullptr}),
        par = nullptr;

      if (empty()) {
        root = t;
      } else {
        shared_ptr<TreeNode> curr;
        curr = root;
        while (curr) {
          par = curr;
          if (t->data == curr->data) {
            t = nullptr;
            return false;  // no insertion for duplicate key
          } else if (t->data < curr->data) {
            curr = curr->left;
          } else {  // t->data > curr->data
            curr = curr->right;
          }
        }

        // Insert key according to key and par
        if (t->data < par->data) {
          par->left = t;
        } else {
          par->right = t;
        }
      }
      return true;
    }

    const bool erase(const T &key) {
      // Find the node with key
      shared_ptr<TreeNode> curr = root, par = nullptr;
      while (curr && curr->data != key) {
        par = curr;
        curr = key < curr->data ? curr->left : curr->right;
      }

      // No node with key in this binary tree
      if (!curr) {
        return false;
      }

      if (curr->right) {
        // Find the minimum of the right subtree
        shared_ptr<TreeNode> r_curr = curr->right, r_par = curr;
        while (r_curr->left) {
          r_par = r_curr;
          r_curr = r_curr->left;
        }
        // Move links to erase the node
        replaceParentChildLink(par, curr, r_curr);
        replaceParentChildLink(r_par, r_curr, r_curr->right);
        r_curr->left = curr->left, r_curr->right = curr->right;

        // Update root link if needed
        if (root == curr) {
          root = r_curr;
        }
      } else {
        // Update root link if needed
        if (root == curr) {
          root = curr->left;
        }
        replaceParentChildLink(par, curr, curr->left);
      }
      curr = nullptr;
      return true;
    }
    // @exclude
    T getRootVal() const {
      return root->data;
    }
    // @include
};
// @exclude

int main(int argc, char *argv[]) {
  BinarySearchTree<int> BST;
  assert(BST.insert(4) == true);
  assert(BST.insert(5) == true);
  assert(BST.insert(2) == true);
  assert(BST.insert(3) == true);
  assert(BST.insert(1) == true);
  assert(BST.erase(0) == false);
  assert(BST.erase(2) == true);
  assert(BST.erase(2) == false);
  assert(BST.insert(4) == false);
  // should output 4
  assert(BST.getRootVal() == 4);
  cout << BST.getRootVal() << endl;
  assert(BST.erase(4) == true);
  // should output 5
  assert(BST.getRootVal() == 5);
  cout << BST.getRootVal() << endl;
  assert(BST.erase(5) == true);
  // should output 3
  assert(BST.getRootVal() == 3);
  cout << BST.getRootVal() << endl;
  return 0;
}
