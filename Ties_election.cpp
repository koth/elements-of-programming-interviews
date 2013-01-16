#include <iostream>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// @include
// V contains the number of votes for each state
long ties_election(const vector<int> &V) {
  int total_votes = accumulate(V.cbegin(), V.cend(), 0);

  // No way to tie if the total number of votes is odd
  if (total_votes & 1) {
    return 0;
  }

  vector<vector<long> > table(V.size() + 1, vector<long>(total_votes + 1, 0));
  table[0][0] = 1;  // base condition: 1 way to reach 0
  for (int i = 0; i < V.size(); ++i) {
    for (int j = 0; j <= total_votes; ++j) {
      table[i + 1][j] = table[i][j] + (j >= V[i] ? table[i][j - V[i]] : 0);
    }
  }
  return table[V.size()][total_votes >> 1];
}
// @exclude

int main(int argc, char *argv[]) {
  int elec_votes[] = {9, 3, 11, 6, 55, 9, 7, 3, 29, 16, 4, 4, 20, 11, 6, 6, 8, 8, 4, 10, 11, 16, 10, 6, 10, 3, 5, 6, 4, 14, 5, 29, 15, 3, 18, 7, 7, 20, 4, 9, 3, 11, 38, 6, 3, 13, 12, 5, 10, 3, 3};
  vector<int> votes(elec_votes, elec_votes + sizeof(elec_votes) / sizeof(int));
  cout << ties_election(votes) << endl;
  return 0;
}
