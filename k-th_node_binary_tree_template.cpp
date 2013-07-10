#include <memory>
#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

template <typename T>
class BinaryTree {
  public:
    T data;
    shared_ptr<BinaryTree<T>> left, right;
    int size;
};

// @include
template <typename T>
shared_ptr<BinaryTree<T>> find_kth_node_binary_tree(
    shared_ptr<BinaryTree<T>> r, int k) {
  while (r) {
    int left_size = r->left ? r->left->size : 0;
    if (left_size < k - 1) {
      k -= (left_size + 1);
      r = r->right;
    } else if (left_size == k - 1) {
      return r;
    } else {  // left_size > k - 1
      r = r->left;
    }
  }
  throw length_error("no k-th node in binary tree");
}
// @exclude

int main(int argc, char *argv[]) {
  //  size field
  //      6
  //    2   3
  //  1    1 1
  //
  //  data field
  //      3
  //    2   5
  //  1    4 6
  shared_ptr<BinaryTree<int>> root = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->size = 6;
  root->data = 3;
  root->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left->size = 2;
  root->left->data = 2;
  root->left->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->left->left->size = 1;
  root->left->left->data = 1;
  root->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->right->size = 3;
  root->right->data = 5;
  root->right->left = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->right->left->size = 1;
  root->right->left->data = 4;
  root->right->right = shared_ptr<BinaryTree<int>>(new BinaryTree<int>());
  root->right->right->size = 1;
  root->right->right->data = 6;
  // should throw
  try {
    find_kth_node_binary_tree<int>(root, 0);
  } catch (exception &e) {
    cout << e.what() << endl;
  };
  // should output 1
  assert(find_kth_node_binary_tree<int>(root, 1)->data == 1);
  cout << (find_kth_node_binary_tree<int>(root, 1))->data << endl;
  // should output 2
  assert(find_kth_node_binary_tree<int>(root, 2)->data == 2);
  cout << (find_kth_node_binary_tree<int>(root, 2))->data << endl;
  // should output 3
  assert(find_kth_node_binary_tree<int>(root, 3)->data == 3);
  cout << (find_kth_node_binary_tree<int>(root, 3))->data << endl;
  // should output 4
  assert(find_kth_node_binary_tree<int>(root, 4)->data == 4);
  cout << (find_kth_node_binary_tree<int>(root, 4))->data << endl;
  // should output 5
  assert(find_kth_node_binary_tree<int>(root, 5)->data == 5);
  cout << (find_kth_node_binary_tree<int>(root, 5))->data << endl;
  // should output 6
  assert(find_kth_node_binary_tree<int>(root, 6)->data == 6);
  cout << (find_kth_node_binary_tree<int>(root, 6))->data << endl;
  // should throw
  try {
    find_kth_node_binary_tree<int>(root, 7);
  } catch (exception &e) {
    cout << e.what() << endl;
  };
  return 0;
}
