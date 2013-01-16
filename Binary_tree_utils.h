#include "Binary_tree_prototype_template.h"
#include <vector>
#include <string>
#include <list>

using namespace std;

template <typename T>
shared_ptr<BinaryTree<T> > generate_rand_binary_tree(int n, bool unique = false) {
  srand(time(nullptr));
  list<shared_ptr<BinaryTree<T> >*> l;
  shared_ptr<BinaryTree<T> > root = shared_ptr<BinaryTree<T> >(new BinaryTree<T>{(unique ? n-- : rand() % 10000)});
  l.emplace_back(&(root->left));
  l.emplace_back(&(root->right));
  while (n--) {
    int x = rand() % l.size();
    typename list<shared_ptr<BinaryTree<T> >*>::iterator it = l.begin();
    advance(it, x);
    **it = shared_ptr<BinaryTree<T> >(new BinaryTree<T>{(unique ? n : rand() % 10000)});
    l.emplace_back(&((**it)->left));
    l.emplace_back(&((**it)->right));
    l.erase(it);
  }
  return root;
}

template <typename T>
void delete_binary_tree(shared_ptr<BinaryTree<T> > n) {
  if (n) {
    delete_binary_tree(n->left);
    delete_binary_tree(n->right);
    n = nullptr;
  }
}

template <typename T>
bool is_two_binary_trees_equal(shared_ptr<BinaryTree<T> > r1, shared_ptr<BinaryTree<T> > r2) {
  if (r1 && r2) {
    return is_two_binary_trees_equal(r1->left, r2->left) && is_two_binary_trees_equal(r1->right, r2->right) && r1->data == r2->data;
  } else if (!r1 && !r2) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
void generate_preorder_helper(shared_ptr<BinaryTree<T> > r, vector<T> &ret) {
  if (r) {
    ret.emplace_back(r->data);
    generate_preorder_helper(r->left, ret);
    generate_preorder_helper(r->right, ret);
  }
}

template <typename T>
vector<T> generate_preorder(shared_ptr<BinaryTree<T> > r) {
  vector<T> ret;
  generate_preorder_helper(r, ret);
  return ret;
}

template <typename T>
void generate_inorder_helper(shared_ptr<BinaryTree<T> > r, vector<T> &ret) {
  if (r) {
    generate_inorder_helper(r->left, ret);
    ret.emplace_back(r->data);
    generate_inorder_helper(r->right, ret);
  }
}

template <typename T>
vector<T> generate_inorder(shared_ptr<BinaryTree<T> > r) {
  vector<T> ret;
  generate_inorder_helper(r, ret);
  return ret;
}

template <typename T>
void generate_postorder_helper(shared_ptr<BinaryTree<T> > r, vector<T> &ret) {
  if (r) {
    generate_postorder_helper(r->left, ret);
    generate_postorder_helper(r->right, ret);
    ret.emplace_back(r->data);
  }
}

template <typename T>
vector<T> generate_postorder(shared_ptr<BinaryTree<T> > r) {
  vector<T> ret;
  generate_postorder_helper(r, ret);
  return ret;
}
