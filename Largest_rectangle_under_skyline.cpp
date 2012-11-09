#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stack>

using namespace std;

// @include
template <typename T>
T calculate_largest_rectangle(const vector<T> &A) {
  // Calculate L
  stack<int> s;
  vector<int> L;
  for (int i = 0; i < A.size(); ++i) {
    while (!s.empty() && A[s.top()] >= A[i]) {
      s.pop();
    }
    L.emplace_back(s.empty() ? -1 : s.top());
    s.emplace(i);
  }

  // Clear stack for calculating R
  while (!s.empty()) {
    s.pop();
  }
  vector<int> R(A.size());
  for (int i = A.size() - 1; i >= 0; --i) {
    while (!s.empty() && A[s.top()] >= A[i]) {
      s.pop();
    }
    R[i] = s.empty() ? A.size() : s.top();
    s.emplace(i);
  }

  // For each A[i], find its maximum area include it
  T max_area = 0;
  for (int i = 0; i < A.size(); ++i) {
    max_area = max(max_area, A[i] * (R[i] - L[i] - 1));
  }
  return max_area;
}
// @exclude

// O(n^2) implementation checks answer
template <typename T>
T check_answer(const vector<T> &A) {
  T max = -1;
  for (int i = 0; i < A.size(); ++i) {
    int left = i - 1, right = i + 1;
    while (left >= 0 && A[left] >= A[i]) {
      --left;
    }
    while (right < A.size() && A[right] >= A[i]) {
      ++right;
    }
    T area = (right - left - 1) * A[i];
    if (area > max) {
      max = area;
    }
  }
  cout << max << endl;
  return max;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    vector<int> A;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    while (n--) {
      A.emplace_back(rand() % 1000);
    }
    int area = calculate_largest_rectangle(A);
    cout << area << endl;
    assert(check_answer(A) == area);
  }
  return 0;
}
