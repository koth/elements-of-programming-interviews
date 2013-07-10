#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <complex>
#include <set>
#include <ctime>
#include <cstdlib>

using namespace std;

// @include
bool is_unit(const complex<int>& z) {
  return (z.real() == 1 && z.imag() == 0) || 
         (z.real() == -1 && z.imag() == 0) ||
         (z.real() == 0 && z.imag() == 1) ||
         (z.real() == 0 && z.imag() == -1);
}

class ComplexCompare {
  public:
    const bool operator()(const complex<double>& lhs,
                          const complex<double>& rhs) const {
      if (norm(lhs) != norm(rhs)) {
        return norm(lhs) < norm(rhs);
      } else if (lhs.real() != rhs.real()) {
        return lhs.real() < rhs.real();
      } else {
        return lhs.imag() < rhs.imag();
      }
    }
};

vector<complex<int>> generate_Gaussian_primes(const int& n) {
  set<complex<double>, ComplexCompare> candidates;
  vector<complex<int>> primes;

  // Generate all possible Gaussian prime candidates
  for (int i = -n; i <= n; ++i) {
    for (int j = -n; j <= n; ++j) {
      if (is_unit({i, j}) == false && abs(complex<double>(i, j)) != 0) {
        candidates.emplace(i, j);
      }
    }
  }

  while (candidates.empty() == false) {
    complex<double> p = *(candidates.begin());
    candidates.erase(candidates.begin());
    primes.emplace_back(p);
    int max_multiplier = n / floor(sqrt(norm(p))) + 1;

    for (int i = max_multiplier; i >= -max_multiplier; --i) {
      for (int j = max_multiplier; j >= -max_multiplier; --j) {
        complex<double> x = {i, j};
        if (is_unit(x) == false) {
          candidates.erase(x * p);
        }
      }
    }
  }
  return primes;
}
// @exclude

vector<complex<int>> generate_Gaussian_primes_canary(const int& n) {
  set<complex<double>, ComplexCompare> candidates;
  vector<complex<int>> primes;

  // Generate all possible Gaussian prime candidates
  for (int i = -n; i <= n; ++i) {
    for (int j = -n; j <= n; ++j) {
      if (is_unit({i, j}) == false && abs(complex<double>(i, j)) != 0) {
        candidates.emplace(i, j);
      }
    }
  }

  while (candidates.empty() == false) {
    complex<double> p = *(candidates.begin());
    candidates.erase(candidates.begin());
    primes.emplace_back(p);
    int max_multiplier = 2 * n / floor(sqrt(norm(p))) + 1;

    for (int i = max_multiplier; i >= -max_multiplier; --i) {
      for (int j = max_multiplier; j >= -max_multiplier; --j) {
        complex<double> x = {i, j};
        if (is_unit(x) == false) {
          complex<double> temp = x * p;
          if (temp.real() == 29 && temp.imag() == 28) {
            cout << "sieving 29 + 28i is " << x.real() << ", " << x.imag() << " " << p.real() << ", " << p.imag() << endl;
          }
          candidates.erase(x * p);
        }
      }
    }
  }
  return primes;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n;
  if (argc == 2) {
    n = atoi(argv[1]);
  } else {
    n = 1 + rand() % 100;
  }

  for (int i = 1; i <= 35; ++i) {
    cout << "n = " << i << endl;
    vector<complex<int>> first = generate_Gaussian_primes_canary(i);
    vector<complex<int>> g_primes = generate_Gaussian_primes(i);
    cout << first.size() << " " << g_primes.size() << endl;
    for (int i = 0; i < first.size(); ++i) {
      if (first[i].real() != g_primes[i].real() || first[i].imag() != g_primes[i].imag()) {
        cout << "(" << first[i].real() << "," << first[i].imag() << ") ";
        cout << "(" << g_primes[i].real() << "," << g_primes[i].imag() << ") ";
      }
    }
    for (int i = first.size(); i < g_primes.size(); ++i) {
      cout << "(" << g_primes[i].real() << "," << g_primes[i].imag() << ") ";
    }
    assert(first.size() == g_primes.size());
  }
  //copy(g_primes.begin(), g_primes.end(), ostream_iterator<complex<int>>(cout, " "));
  /*
  for (int i = 0; i < g_primes.size(); ++i) {
    if (g_primes[i].real() > 0 && g_primes[i].imag() > 0) {
      cout << "(" << g_primes[i].real() << "," << g_primes[i].imag() << ") ";
    }
  }
  */
  cout << endl;
  return 0;
}
