#include <iostream>
#include <numeric>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

string rand_string(int len) {
  string ret;
  while (len--) {
    ret += ((rand() & 1) ? 'a' : 'A') + rand() % 26;
  }
  return ret;
}

// @include
int string_hash(const string &str, const int &modulus) {
  const int MULT = 997;
  // @exclude
  /*
  return accumulate(str.cbegin(), str.cend(), 0,
    [MULT, modulus](const int &val, const char &c) -> int {
      return (val * MULT + c) % modulus;
    });
  */
  // @include
  int val = 0;
  for (const char &c : str) {
    val = (val * MULT + c) % modulus;
  }
  return val;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  string str;
  if (argc == 2) {
    str = argv[1];
  } else {
    str = rand_string(1 + rand() % 20);
  }
  cout << "string = " << str << endl;
  cout << string_hash(str, 1 << (16)) << endl;
  return 0;
}
