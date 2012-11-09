// Compile this with the support of C++0x since it uses back() of string
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

// @include
void count_occurrences(string S) {
  sort(S.begin(), S.end());

  int count = 1;
  for (int i = 1; i < S.size(); ++i) {
    if (S[i] == S[i - 1]) {
      ++count;
    } else {
      cout << '(' << S[i - 1] << ',' << count << "),";
      count = 1;
    }
  }
  cout << '(' << S.back() << ',' << count << ')' << endl;;
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
  string S;
  if (argc == 2) {
    S = argv[1];
  } else {
    S = rand_string(1 + rand() % 1000);
  }
  cout << S << endl;
  count_occurrences(S);
  return 0;
}
