#include <iostream>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

// @include
double house_majority_helper(const vector<double> &prob, const int &a, 
                             const int &b, vector<vector<double> > &P) {
  if (a < b) {
    return 0.0;  // base case: not enough Republicans
  } else if (a == 0 && b == 0) {
    return 1.0;  // base case
  }

  if (P[a][b] == -1.0) {
    P[a][b] = house_majority_helper(prob, a - 1, b - 1, P) * prob[a] +
              house_majority_helper(prob, a - 1, b, P) * (1.0 - prob[a]);
  }
  return P[a][b];
}

double house_majority(const vector<double> &prob, const int &n) {
  // Initialize DP table
  vector<vector<double> > P(n + 1, vector<double>(n + 1, -1.0));

  // Accumulate the probabilities of majority cases
  double prob_sum = 0.0;
  for (int i = (n >> 1) + 1; i <= n; ++i) {
    prob_sum += house_majority_helper(prob, n, i, P);
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
