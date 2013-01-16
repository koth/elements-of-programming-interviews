#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
template <typename ItemType, typename CapacityType>
class TournamentTree {
  private:
    class TreeNode {
      public:
        CapacityType cap;  // leaf: remaining capacity in the box
                           // non-leaf: max remaining capacity in the subtree
        vector<ItemType> items;  // stores the items in the leaf node
    };

    // Store the complete binary tree. For tree[i],
    // left subtree is tree[2i + 1], and right subtree is tree[2i + 2].
    vector<TreeNode> tree;

    // Recursively inserts item in tournament tree
    void insertHelper(const int &idx, const ItemType &item,
                      const CapacityType &cap) {
      int left = (idx << 1) + 1, right = (idx << 1) + 2;
      if (left < tree.size()) {  // internal node
        insertHelper(tree[left].cap >= cap ? left : right, item, cap);
        tree[idx].cap = max(tree[left].cap, 
                            right < tree.size() ? tree[right].cap : 
                            numeric_limits<CapacityType>::min());
      } else {  // leaf node
        tree[idx].cap -= cap, tree[idx].items.emplace_back(item);
      }
    }

  public:
    // n items, and each box has unit_cap
    TournamentTree(int n, const CapacityType &unit_cap) :
      // Complete tree with n leafs has 2n - 1 nodes
      tree(vector<TreeNode>((n << 1) - 1, TreeNode{unit_cap})) {}

    void insert(const ItemType &item, const CapacityType &item_cap) {
      insertHelper(0, item, item_cap);
    }
    // @exclude
    void printLeaf(void) {
      for (int i = 0; i < tree.size(); ++i) {
        cout << "i = " << i << ", cap = " << tree[i].cap << endl;
        for (const ItemType &item : tree[i].items) {
          cout << item << ' ';
        }
        cout << endl;
      }
    }
    // @include
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
  // Due to the precision error of floating point number, Item 5 will be inserted into 5-th box. However, if we are not using floating point number, everything is fine.
  t.printLeaf();
  return 0;
}
