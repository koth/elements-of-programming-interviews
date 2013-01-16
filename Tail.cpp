#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

// @include
string tail(const string &file_name, const int &tail_count) {
  fstream file_ptr(file_name.c_str());

  file_ptr.seekg(0, ios::end);
  int file_size = file_ptr.tellg(), newline_count = 0;
  string output;  // stores the last tail_count lines
  // Reads file in reverse looking for '\n'
  for (int i = 0; i < file_size; ++i) {
    file_ptr.seekg(file_size - i - 1, ios::beg);
    char c;
    file_ptr.get(c);
    if (c == '\n') {
      ++newline_count;
      if (newline_count > tail_count) {
        break;
      }
    }
    output.push_back(c);
  }
  // Reverse the output string using the reverse function
  // from the <algorithm> library in STL. The arguments
  // are iterators to the start and end of String object.
  reverse(output.begin(), output.end());
  return output;
}
// @exclude

int main(int argc, char *argv[]) {
  cout << "Usage: file name and tail count" << endl;
  int tail_count = 10;
  char* file_name;
  if (argc == 2) {
    file_name = argv[1];
  } else if (argc == 3) {
    file_name = argv[1];
    tail_count = atoi(argv[2]);
  } else {
    exit(1);
  }
  string output = tail(file_name, tail_count);
  cout << output;
  return 0;
}
