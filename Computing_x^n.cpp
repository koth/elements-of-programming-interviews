#include <iostream>
#include <limits>
#include <list>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// @include
list<int> get_minimum_expression(const int &n) {
  list<int> init_list;
  init_list.emplace_back(1);

  list<list<int> > exp_lists;
  exp_lists.emplace_back(init_list);
  list<int> min_exp;
  int shortest_size = numeric_limits<int>::max();

  while (exp_lists.empty() == false) {
    list<int> exp = exp_lists.front();
    exp_lists.pop_front();
    // Try all possible combinations in a list
    for (const int &i : exp) {
      for (const int &j : exp) {
        int sum = i + j;
        if (shortest_size > exp.size() + 1) {
          if (sum == n) {
            min_exp = exp;
            min_exp.emplace_back(sum);
            shortest_size = exp.size() + 1;
          } else if (sum < n && sum > exp.back()) {
            list<int> ext = exp;
            ext.emplace_back(sum);
            exp_lists.emplace_back(ext);
          }
        }
      }
    }
  }
  return min_exp;
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
  return 0;
}
