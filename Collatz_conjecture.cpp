#include <iostream>
#include <stdexcept>
#include <cassert>
#ifdef __clang__
#include <unordered_set>
#else
#include <tr1/unordered_set>
#endif
#include <ctime>
#include <cstdlib>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
bool test_Collatz_conjecture(const int &n) {
  // Stores the odd number that converges to 1
  unordered_set<long> table;

  // Start from 2 since we don't need to test 1
  for (int i = 2; i <= n; ++i) {
    unordered_set<long> sequence;
    long test_i = i;
    while (test_i >= i) {
      // Emplace failed, it mean we met some number encountered before.
      if (sequence.emplace(test_i).second == false) {
        return false;
      }

      if (test_i & 1) {  // odd number
        if (table.emplace(test_i).second == false) {
          break;  // this number have already be proven to converge to 1
        }
        long next_test_i = 3 * test_i + 1;  // 3n + 1
        if (next_test_i <= test_i) {
          throw overflow_error("test process overflow");
        }
        test_i = next_test_i;
      } else {  // even number
        test_i >>= 1;  // n / 2
      }
    }
    table.erase(i);  // removes i from table
  }
  return true;
}
// @exclude

// Slow check without any pruning
bool check(const int &n) {
  for (int i = 2; i <= n; ++i) {
    int test_i = i;
    while (test_i != 1 && test_i >= i) {
      if (test_i & 1) {
        test_i = test_i * 3 + 1;
      } else {
        test_i >>= 1;
      }
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 100000;
    }
    cout << "n = " << n << endl;
    bool res;
    cout << boolalpha << (res = test_Collatz_conjecture(n)) << endl;
    assert(res == check(n));
  }
  return 0;
}
