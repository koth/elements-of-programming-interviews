#include <cassert>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// @include
string normalized_path_names(const string &path) {
  vector<string> s;  // Use vector as a stack
  // Special case: starts with "/", which is an absolute path
  if (path.front() == '/') {
    s.emplace_back("/");
  }

  stringstream ss(path);
  string token;
  while (getline(ss, token, '/')) {
    if (token == "..") {
      if (s.empty() || s.back() == "..") {
        s.emplace_back(token);
      } else {
        if (s.back() == "/") {
          throw invalid_argument("Path error");
        }
        s.pop_back();
      }
    } else if (token != "." && token != "") {  // name
      for (const char &c : token) {
        if (c != '.' && isalnum(c) == false) {
          throw invalid_argument("Invalid directory name");
        }
      }
      s.emplace_back(token);
    }
  }

  string normalized_path("");
  if (s.empty() == false) {
    auto it = s.cbegin();
    normalized_path += *it++;
    while (it != s.cend()) {
      if (*(it - 1) != "/") {  // previous one is not an absolute path
        normalized_path += "/";
      }
      normalized_path += *it++;
    }
  }
  return normalized_path;
}
// @exclude

int main(int argc, char *argv[]) {
  assert(normalized_path_names("123/456") == string("123/456"));
  assert(normalized_path_names("/123/456") == string("/123/456"));
  assert(normalized_path_names("usr/lib/../bin/gcc") == string("usr/bin/gcc"));
  assert(normalized_path_names("./../") == string(".."));
  assert(normalized_path_names("../../local") == string("../../local"));
  assert(normalized_path_names("./.././../local") == string("../../local"));
  try {
    normalized_path_names("/..");
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  try {
    normalized_path_names("/cpp_name/bin/");
  } catch (exception &e) {
    cout << e.what() << endl;
  }
  assert(normalized_path_names("scripts//./../scripts/awkscripts/././") == string("scripts/awkscripts"));
  if (argc == 2) {
    cout << normalized_path_names(argv[1]) << endl;
  }
  return 0;
}
