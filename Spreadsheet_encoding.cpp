#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

string rand_string(int len) {
  string ret;
  while (len--) {
    ret.push_back('A' + rand() % 26);
  }
  return ret;
}

// @include
int ssDecodeColID(const string &col) {
  int ret = 0;
  for (const char &c : col) {
    ret = ret * 26 + c - 'A' + 1;
  }
  return ret;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  assert(1 == ssDecodeColID("A"));
  assert(27 == ssDecodeColID("AA"));
  if (argc == 2) {
    cout << argv[1] << " " << ssDecodeColID(argv[1]) << endl;
  } else {
    string s(rand_string(1 + rand() % 5));
    cout << s << " " << ssDecodeColID(s) << endl;
  }
  return 0;
}
