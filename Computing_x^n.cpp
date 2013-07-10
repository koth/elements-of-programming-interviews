#include <iostream>
#include <stdexcept>
#include <cassert>
#include <limits>
#include <list>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

// @include
list<int> get_minimum_expression(const int &n) {
  if (n == 1) {
    return {1};
  }

  queue<list<int>> exp_lists;
  exp_lists.emplace(1, 1);  // construct the initial list with one node 
                            // whose value is 1
  while (exp_lists.empty() == false) {
    list<int> exp = exp_lists.front();
    exp_lists.pop();
    // Try all possible combinations in list exp
    for (const int &a : exp) {
      int sum = a + exp.back();
      if (sum > n) {
        break;  // no possible solution
      }

      list<int> new_exp(exp);
      new_exp.emplace_back(sum);
      if (sum == n) {
        return new_exp;
      }
      exp_lists.emplace(new_exp);
    }
  }
  // @exclude
  throw invalid_argument("unknown error");  // this line should never be called
  // @include
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100;
  }
  cout << "n = " << n << endl;
  list<int> min_exp = get_minimum_expression(n);
  for (const int &t : min_exp) {
    cout << t << ' ';
  }
  cout << endl;
  cout << "size = " << min_exp.size() << endl;
  return 0;
}
