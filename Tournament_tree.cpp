// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using std::cout;
using std::endl;
using std::max;
using std::vector;

// @include
template <typename ItemType, typename CapacityType>
class TournamentTree {
 public:
  // n items, and each box has unit_cap.
  TournamentTree(int n, const CapacityType& unit_cap) :
    // Complete binary tree with n leafs has 2n - 1 nodes.
    tree_(vector<TreeNode>((n << 1) - 1, {unit_cap})) {}

  void insert(const ItemType& item, const CapacityType& item_cap) {
    insertHelper(0, item, item_cap);
  }
  // @exclude
  void printLeaf(void) {
    for (int i = 0; i < tree_.size(); ++i) {
      cout << "i = " << i << ", cap = " << tree_[i].cap << endl;
      for (const ItemType &item : tree_[i].items) {
        cout << item << ' ';
      }
      cout << endl;
    }
  }
  // @include

 private:
  struct TreeNode {
    CapacityType cap;  // leaf: remaining capacity in the box.
                       // non-leaf: max remaining capacity in the subtree.
    vector<ItemType> items;  // stores the items in the leaf node.
  };

  // Stores the complete binary tree. For tree_[i],
  // left subtree is tree_[2i + 1], and right subtree is tree_[2i + 2].
  vector<TreeNode> tree_;

  // Recursively inserts item in tournament tree.
  void insertHelper(int idx, const ItemType& item, const CapacityType& cap) {
    int left = (idx << 1) + 1, right = (idx << 1) + 2;
    if (left < tree_.size()) {  // tree_[idx] is an internal node.
      insertHelper(tree_[left].cap >= cap ? left : right, item, cap);
      tree_[idx].cap = max(tree_[left].cap, tree_[right].cap);
    } else {  // tree_[idx] is a leaf node.
      tree_[idx].cap -= cap, tree_[idx].items.emplace_back(item);
    }
  }
};
// @exclude

int main(int argc, char *argv[]) {
  // following is the example in the book
  TournamentTree<int, double> t(6, 1.0);
  t.insert(0, 0.60);
  t.insert(1, 0.60);
  t.insert(2, 0.55);
  t.insert(3, 0.80);
  t.insert(4, 0.50);
  t.insert(5, 0.45);
  // Due to the precision error of floating point number, Item 5 will be
  // inserted into 5-th box. However, if we are not using floating point
  // number, everything is fine.
  t.printLeaf();
  return 0;
}
