#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cassert>

using namespace std;

// @include
void Eliminate_rows(vector<vector<bool> > &B, const int &i, const int &j) {
  // Use B[i] to eliminate other rows' entry j
  for (int a = 0; a < B.size(); ++a) {
    if (i != a && B[a][j]) {
      for (int b = 0; b < B[i].size(); ++b) {
        B[a][b] = B[a][b] ^ B[i][b];
      }
    }
  }
}

vector<bool> Gaussian_elimination(const vector<vector<bool> > &A,
                                  const vector<bool> &y) {
  vector<vector<bool> > B(A);
  for (int i = 0; i < B.size(); ++i) {
    B[i].push_back(y[i]);
  }

  for (int i = 0; i < B.size(); ++i) {
    // Find the coefficient starting with 1
    int idx = i;
    for (int j = i + 1; j < B.size(); ++j) {
      if (B[j][i]) {
        idx = j;
        break;
      }
    }
    swap(B[i], B[idx]);
    
    // Perform elimination except i-th row
    if (B[i][i]) {
      Eliminate_rows(B, i, i);
    }
  }

  for (int i = B.size() - 1; i >= 0; --i) {
    if (B[i][i] == false) {
      bool have_coefficient = false;
      for (int j = i + 1; j < A.size(); ++j) {
        if (B[i][j]) {
          Eliminate_rows(B, i, j);
          have_coefficient = true;
          swap(B[i], B[j]);  // row permutation
          break;
        }
      }

      if (have_coefficient == false && B[i].back() == true) {
        cout << "No solution." << endl;
        return {};
      }
    }
  }

  vector<bool> x;
  for (int i = 0; i < B.size(); ++i) {
    x.push_back(B[i].back());
  }
  return x;
}
// @exclude

bool check_answer_with_solution(const vector<vector<bool> > &A, const vector<bool> &b, const vector<bool> & x) {
  for (int i = 0; i < A.size(); ++i) {
    bool res = A[i][0] && x[0];
    for (int j = 1; j < A[i].size(); ++j) {
      res = res ^ (A[i][j] && x[j]);
    }

    if (res != b[i]) {
      return false;
    }
  }
  return true;
}

bool check_answer_no_solution(const vector<vector<bool> > &A, const vector<bool> &b) {
  // Generate all possible combinations of x to test there is no solution actually
  for (int val = 0; val < (1 << b.size()); ++val) {
    vector<bool> x;
    int temp = val;
    for (int i = 0; i < b.size(); ++i) {
      x.push_back(temp & 1);
      temp >>= 1;
    }
    /*
    copy(x.begin(), x.end(), ostream_iterator<bool>(cout, " "));
    cout << endl;
    */
    assert(check_answer_with_solution(A, b, x) == false);
  }
  return true;
}

void rand_matrix(vector<vector<bool> > &A) {
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < A[i].size(); ++j) {
      A[i][j] = rand() & 1;
    }
  }
}

void rand_vec(vector<bool> &b) {
  for (int i = 0; i < b.size(); ++i) {
    b[i] = rand() & 1;
  }
}

int main(int argc, char *argv[]) {
  // Predefined tests
  vector<vector<bool> > A(4);
  A[0] = {false, false, false, true};
  A[1] = {false, false, false, true};
  A[2] = {false, true, true, true};
  A[3] = {true, false, false, false};
  vector<bool> b = {true, true, false, true};
  vector<bool> x = Gaussian_elimination(A, b);
  copy(x.begin(), x.end(), ostream_iterator<bool>(cout, " "));
  cout << endl;
  if (x.empty()) {  // no solution
    assert(check_answer_no_solution(A, b));
  } else {  // solution
    assert(check_answer_with_solution(A, b, x));
  }

  // Perform random tests below
  for (int times = 0; times < 1000000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
      cout << "n = " << n << endl;
    } else {
      n = 1 + rand() % 16;
    }
    vector<vector<bool> > A(n, vector<bool>(n));
    rand_matrix(A);
    vector<bool> b(n);
    rand_vec(b);
    vector<bool> x = Gaussian_elimination(A, b);
    cout << "n = " << n << endl;
    cout << "A = \n";
    for (int i = 0; i < A.size(); ++i) {
      copy(A[i].begin(), A[i].end(), ostream_iterator<bool>(cout, " "));
      cout << endl;
    }
    cout << "b = \n";
    copy(b.begin(), b.end(), ostream_iterator<bool>(cout, " "));
    cout << endl << endl;
    if (x.empty()) {  // no solution
      assert(check_answer_no_solution(A, b));
    } else {  // solution
      cout << "x = \n";
      copy(x.begin(), x.end(), ostream_iterator<bool>(cout, " "));
      cout << endl << endl;
      assert(check_answer_with_solution(A, b, x));
    }
  }
  return 0;
}
