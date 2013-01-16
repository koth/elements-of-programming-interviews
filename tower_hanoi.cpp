#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <array>

using namespace std;

// @include
void transfer(const int &n, array<stack<int>, 3> &pegs,
              const int &from, const int &to, const int &use) {
  if (n > 0) {
    transfer(n - 1, pegs, from, use, to);
    pegs[to].push(pegs[from].top());
    pegs[from].pop();
    cout << "Move from peg " << from << " to peg " << to << endl;
    transfer(n - 1, pegs, use, to, from);
  }
}

void move_tower_hanoi(const int &n) {
  array<stack<int>, 3> pegs;
  // Initialize pegs
  for (int i = n; i >= 1; --i) {
    pegs[0].push(i);
  }
  
  transfer(n, pegs, 0, 1, 2);
}
// @exclude

int main(int argc, char *argv[]) {
  int n;
  srand(time(nullptr));
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 10;
  }
  cout << "n = " << n << endl;
  move_tower_hanoi(n);
  return 0;
}
