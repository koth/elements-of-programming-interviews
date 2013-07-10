#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

// @include
// prob is the probability that each Republican wins.
// r is the number of Republicans wins, and n is the number of elections.
double house_majority_helper(const vector<double> &prob, const int &r,
                             const int &n, vector<vector<double>> &P) {
  if (r > n) {
    return 0.0;  // base case: not enough Republicans
  } else if (r == 0 && n == 0) {
    return 1.0;  // base case
  } else if (r < 0) {
    return 0.0;
  }

  if (P[r][n] == -1.0) {
    P[r][n] = house_majority_helper(prob, r - 1, n - 1, P) * prob[n - 1] +
              house_majority_helper(prob, r, n - 1, P) * (1.0 - prob[n - 1]);
  }
  return P[r][n];
}

double house_majority(const vector<double> &prob, const int &n) {
  // Initialize DP table
  vector<vector<double>> P(n + 1, vector<double>(n + 1, -1.0));

  // Accumulate the probabilities of majority cases
  double prob_sum = 0.0;
  for (int r = ceil(0.5 * n); r <= n; ++r) {
    prob_sum += house_majority_helper(prob, r, n, P);
  }
  return prob_sum;
}
// @exclude

void print_vector(vector<double> prob) {
  sort(prob.begin(), prob.end());
  for (int i = 0; i < prob.size(); ++i) {
    cout << i << ":" << static_cast<int>( 100 * prob[i]) << (((i + 1) % 10 == 0)? "\n" : " ");
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n = 435;
  vector<double> prob;
  prob.emplace_back(0.0);
  for (int i = 0; i < n; ++i) {
    prob.emplace_back(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
  }
  print_vector(prob);
  double ans = house_majority(prob, n);
  assert(0.0 <= ans && ans <= 1.0);
  cout << ans << endl;
  return 0;
}
