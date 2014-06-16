// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::move;
using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

string join_a_line_with_space(const vector<string>& words, size_t start,
                              size_t end, size_t num_spaces);

// @include
vector<string> left_justified_text(const vector<string>& words, size_t L) {
  size_t last_idx = 0, num_words = 0, len = 0;
  vector<string> res;
  for (size_t i = 0; i < words.size(); ++i) {
    ++num_words;
    size_t line_len = len + words[i].size() + (num_words - 1);
    if (line_len == L) {
      res.emplace_back(
          join_a_line_with_space(words, last_idx, i, i - last_idx));
      last_idx = i + 1, num_words = 0, len = 0;
    } else if (line_len > L) {
      res.emplace_back(
          join_a_line_with_space(words, last_idx, i - 1, L - len));
      last_idx = i, num_words = 1, len = words[i].size();
    } else {  // line_len < L.
      len += words[i].size();
    }
  }

  // Special case: handles the last line.
  if (num_words) {
    // Joins words into a line with one space after each word.
    string line = join_a_line_with_space(words, last_idx, words.size() - 1,
                                         num_words - 1);
    // Appends the remaining spceas at the end of line.
    line.append(L - len - (num_words - 1), ' ');
    res.emplace_back(line);
  }
  return res;
}

// Joins strings in words[start : end] with num_spaces spaces spread evenly.
string join_a_line_with_space(const vector<string>& words, size_t start,
                              size_t end, size_t num_spaces) {
  size_t num_words = end - start + 1;
  string line;
  for (size_t i = start; i < end; ++i) {
    line += words[i];
    --num_words;
    size_t num_curr_space = ceil(static_cast<double>(num_spaces) / num_words);
    line.append(num_curr_space, ' ');
    num_spaces -= num_curr_space;
  }
  line += words[end];
  line.append(num_spaces, ' ');
  return line;
}
// @exclude

void test_case(const vector<string>& words, size_t L) {
  auto res = left_justified_text(words, L);
  for (const auto& s : res) {
    cout << "\"" << s << "\"" << endl;
  }
  cout << endl;
}

int main(int argc, char** argv) {
  vector<string> words = {"Text", "justification", "is",    "trickier",
                          "than", "it",            "seems!"};
  size_t L = 14;
  cout << "L = " << L << endl;
  test_case(words, L);
  words = {"Listen", "to", "many,", "speak", "to", "a", "few."};
  L = 6;
  cout << "L = " << L << endl;
  test_case(words, L);
  words = {"The",  "quick", "brown", "fox",  "jumped",
           "over", "the",   "lazy",  "dogs."};
  L = 11;
  cout << "L = " << L << endl;
  test_case(words, L);
  L = 16;
  cout << "L = " << L << endl;
  test_case(words, L);
  L = 17;
  cout << "L = " << L << endl;
  test_case(words, L);
  words = {"What", "must", "be", "shall", "be."};
  L = 12;
  cout << "L = " << L << endl;
  test_case(words, L);
  return 0;
}
