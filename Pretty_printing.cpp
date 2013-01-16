#include <iostream>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += 'a' + rand() % 26;
  }
  return ret;
}

// @include
int find_pretty_printing(const vector<string> &W, const int &L) {
  // Calculate M(i)
  vector<long> M(W.size(), numeric_limits<long>::max());
  for (int i = 0; i < W.size(); ++i) {
    int b_len = L - W[i].size();
    M[i] = min((i - 1 < 0 ? 0 : M[i - 1]) + (1 << b_len), M[i]);
    for (int j = i - 1; j >= 0; --j) {
      b_len -= (W[j].size() + 1);
      if (b_len < 0) {
        break;
      }
      M[i] = min((j - 1 < 0 ? 0 : M[j - 1]) + (1 << b_len), M[i]);
    }
  }

  // Find the minimum cost without considering the last line
  long min_mess = (W.size() >= 2 ? M[W.size() - 2] : 0);
  int b_len = L - W.back().size();
  for (int i = W.size() - 2; i >= 0; --i) {
    b_len -= (W[i].size() + 1);
    if (b_len < 0) {
      return min_mess;
    }
    min_mess = min(min_mess, (i - 1 < 0 ? 0 : M[i - 1]));
  }
  return min_mess;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n, L;
  if (argc == 2) {
    n = atoi(argv[1]);
    L = 10 + rand() % 10;
  } else if (argc == 3) {
    n = atoi(argv[1]);
    L = atoi(argv[2]);
  } else {
    n = 1 + rand() % 30;
    L = 11 + rand() % 10;
  }
  vector<string> W;
  for (int i = 0; i < n; ++i) {
    W.push_back(rand_string(1 + rand() % 10));
  }
  for (int i = 0; i < n; ++i) {
    cout << W[i] << ' ';
  }
  cout << L << endl;
  cout << find_pretty_printing(W, L) << endl;
  return 0;
}
