#include <iostream>
#include <numeric>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// @include
int Levenshtein_distance(string A, string B) {
  // Try to reduce the space usage
  if (A.size() < B.size()) {
    swap(A, B);
  }

  vector<int> D(B.size() + 1);
  // Initialization
  iota(D.begin(), D.end(), 0);

  for (int i = 1; i <= A.size(); ++i) {
    int pre_i_1_j_1 = D[0];  // stores the value of D[i - 1][j - 1]
    D[0] = i;
    for (int j = 1; j <= B.size(); ++j) {
      int pre_i_1_j = D[j];  // stores the value of D[i -1][j]
      D[j] = A[i - 1] == B[j - 1] ?
             pre_i_1_j_1 : 1 + min(pre_i_1_j_1, min(D[j - 1], D[j]));
      // Previous D[i - 1][j] will become the next D[i - 1][j - 1]
      pre_i_1_j_1 = pre_i_1_j;
    }
  }
  return D.back();
}
// @exclude

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += rand() % 26 + 'a';
  }
  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  string A, B;
  // Wiki example (http://en.wikipedia.org/wiki/Levenshtein_distance)
  A = "Saturday", B = "Sunday";
  assert(3 == Levenshtein_distance(A, B));
  A = "kitten", B = "sitting";
  assert(3 == Levenshtein_distance(A, B));

  if (argc == 3) {
    A = argv[1], B = argv[2];
  } else {
    A = rand_string(1 + rand() % 100);
    B = rand_string(1 + rand() % 100);
  }
  cout << A << endl << B << endl;
  cout << Levenshtein_distance(A, B) << endl;
  return 0;
}
