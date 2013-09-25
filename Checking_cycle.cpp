#include <cstdio>
#include <cassert>
#include <iostream>
#include <cstdlib>

using namespace std;

class node_t {
  public:
    int data;
    node_t* next;
    node_t(int val = 0, node_t* ptr = NULL)
      : data(val), next(ptr) {}
};

// @include
node_t* has_cycle(node_t* head) {
  node_t *fast = head, *slow = head;

  while (slow && slow->next &&
      fast && fast->next && fast->next->next) {
    slow = slow->next, fast = fast->next->next;
    // Found cycle
    if (slow == fast) {
      // Calculate the cycle length
      int cycle_len = 0;
      do {
        ++cycle_len;
        fast = fast->next;
      } while (slow != fast);

      // Try to find the start of the cycle
      slow = head, fast = head;
      // Fast pointer advances cycle_len first
      while (cycle_len--) {
        fast = fast->next;
      }
      // Both pointers advance at the same time
      while (slow != fast) {
        slow = slow->next, fast = fast->next;
      }
      return slow;  // the start of cycle
    }
  }
  return NULL;  // no cycle
}
// @exclude

int main(int argc, char *argv[]) {
  node_t* L3 = new node_t(3);
  node_t* L2 = new node_t(2, L3);
  node_t* L1 = new node_t(1, L2);

  // should output "L1 does not have cycle."
  assert(has_cycle(L1) == NULL);
  cout << "L1 " << (has_cycle(L1) ? "has" : "does not have") << " cycle." << endl;

  // make it a cycle
  L3->next = L2;
  // should output "L1 has cycle, located at node has value 2"
  assert(has_cycle(L1) != NULL);
  assert(has_cycle(L1)->data == 2);
  node_t* temp = has_cycle(L1);
  if (temp) {
    cout << "L1 has cycle, located at node has value " << temp->data << endl;
  } else {
    cout << "L1 does not have cycle" << endl;
  }

  return 0;
}

