#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cassert>

using namespace std;

vector<int> rand_vector(int len) {
  vector<int> ret;
  while (len--) {
    ret.emplace_back(rand());
  }
  return ret;
}

int GCD(int a, int b) {
  if (b) {
    while ((a %= b) && (b %= a));
  }
  return a + b;
}

// @include
template <typename T>
void rotate_array(vector<T> &A, int i) {
  i %= A.size();
  int cycles = GCD(A.size(), i);  // number of cycles in this rotation
  int hops = A.size() / cycles;  // number of elements in a cycle

  for (int c = 0; c < cycles; ++c) {
    T temp = A[c];
    for (int j = 1; j < hops; ++j) {
      swap(A[(c + j * i) % A.size()], temp);
    }
    A[c] = temp;
  }
}
// @exclude

template <typename T>
void check_answer(vector<T> &A, const int &i, vector<T> &rotated) {
  assert(A.size() == rotated.size());
  for (size_t idx = 0; idx < A.size(); ++idx) {
    assert(rotated[(idx + i) % rotated.size()] == A[idx]);
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int len;
    if (argc == 2) {
      len = atoi(argv[1]);
    } else {
      len = 1 + rand() % 10000;
    }
    vector<int> A(rand_vector(len));
    int i = rand() % len;
    vector<int> B(A);
    rotate_array(B, i);
    check_answer(A, i, B);
  }
  return 0;
}
