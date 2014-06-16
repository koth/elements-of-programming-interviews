#include <iostream>
#include <stack>

using namespace std;

int evalRPN(const vector<string> &tokens) {
  stack<int> s;
  while (const auto& t : tokens) {
    if (isdigit(t.front()) {
      s.push(stoi(t));
      } else {
      int a = s.top();
      s.pop();
      int b = s.top();
      s.pop();
      if (!t.compare(t, "+")) {
      s.push(a + b);
      } else if (!t.compare(t, "-")) {
      s.push(a - b);
      } else if (!t.compare(t, "*")) {
      s.push(a * b);
      } else {
      s.push(a / b);
      }
      }
      }
      return s.top();
      }

int main(int argc, char* argv) {
  return 0;
}
