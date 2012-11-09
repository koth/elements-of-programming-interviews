#include <iostream>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

string rand_string(int len) {
  string ret;
  while (len--) {
    int ch = rand() % 53;
    if (ch == 52) {
      ret += ' ';
    } else if (ch < 26) {
      ret += ch + 'a';
    } else {
      ret += ch - 26 + 'A';
    }
  }
  return ret;
}

// @include
void reverse_words(string &input) {
  // Reverse the whole string first
  reverse(input.begin(), input.end());

  size_t start = 0, end;
  while ((end = input.find(" ", start)) != string::npos) {
    // Reverse each word in the string
    reverse(input.begin() + start, input.begin() + end);
    start = end + 1;
  }
  // Reverse the last word
  reverse(input.begin() + start, input.end());
}
// @exclude

void check_answer(const string &ori, string &str) {
  reverse_words(str);
  assert(ori.compare(str) == 0);
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    string str;
    if (argc >= 2) {
      str += argv[1];
      for (int i = 2; i < argc; ++i) {
        str += ' ';
        str += argv[i];
      }
    } else {
      str = rand_string(rand() % 10000);
    }
    string original_str(str);
    cout << str << endl;
    reverse_words(str);
    cout << str << endl;
    check_answer(original_str, str);
  }
  return 0;
}
