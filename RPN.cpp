#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <stack>

using namespace std;

// @include
int eval(const string &s) {
  stack<int> eval_stack;
  stringstream ss(s);
  string symbol;

  while (getline(ss, symbol, ',')) {
    if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/") {
      int x = eval_stack.top();
      eval_stack.pop();
      int y = eval_stack.top();
      eval_stack.pop();
      switch (symbol.front()) {
        case '+':
          eval_stack.emplace(x + y);
          break;
        case '-':
          eval_stack.emplace(x - y);
          break;
        case '*':
          eval_stack.emplace(x * y);
          break;
        case '/':
          eval_stack.emplace(x / y);
          break;
      }
    } else {  // number
      eval_stack.emplace(stoi(symbol));
    }
  }
  return eval_stack.top();
}
// @exclude

int main(int argc, char *argv[]) {
  assert (-5 == eval("2,-10,/"));
  assert (12 == eval("10,2,+"));
  assert (15 == eval("1,2,+,3,4,*,+"));
  assert (42 == eval("1,2,3,4,5,+,*,+,+,3,4,*,+"));
  return 0;
}
