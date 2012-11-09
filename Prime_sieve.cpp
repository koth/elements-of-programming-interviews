#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <cstring>

using namespace std;

// @include
// Given n, return the primes from 1 to n
vector<int> generate_primes_from_1_to_n(const int &n) {
  int size = floor(0.5 * (n - 3)) + 1;
  // is_prime[i] represents (2i + 3) is prime or not
  vector<int> primes;  // stores the primes from 1 to n
  primes.emplace_back(2);
  vector<bool> is_prime(size, true);
  for (long i = 0; i < size; ++i) {
    if (is_prime[i]) {
      int p = (i << 1) + 3;
      primes.emplace_back(p);
      // Sieving from p^2, whose index is 2i^2 + 6i + 3
      for (long j = ((i * i) << 1) + 6 * i + 3; j < size; j += p) {
        is_prime[j] = false;
      }
    }
  }
  return primes;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  if (argc == 2) {
    int n = atoi(argv[1]);
    cout << "n = " << n << endl;
    vector<int> primes = generate_primes_from_1_to_n(n);
    for (size_t i = 0; i < primes.size(); ++i) {
      for (int j = 2; j < primes[i]; ++j) {
        assert(primes[i] % j);
      }
      //cout << primes[i] << ' ' << n << endl;
    }
  } else {
    for (int times = 0; times < 100; ++times) {
      int n = 2 + rand() % 100000;
      cout << "n = " << n << endl;
      vector<int> primes = generate_primes_from_1_to_n(n);
      for (size_t i = 0; i < primes.size(); ++i) {
        for (int j = 2; j < primes[i]; ++j) {
          assert(primes[i] % j);
        }
        //cout << primes[i] << ' ' << n << endl;
      }
    }
  }
  return 0;
}
