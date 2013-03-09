#include <iostream>
#include <limits>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cassert>

using namespace std;

// @include
// 0 means equal, -1 means smaller, 1 means larger
int compare(const double &a, const double &b) {
  // Use normalization for precision problem
  double diff = (a - b) / b;
  return diff < -numeric_limits<double>::epsilon() ?
         -1 : diff > numeric_limits<double>::epsilon();
}

double square_root(const double &x) {
  // Decide the search range according to x
  double l, r;
  if (compare(x, 1.0) < 0) {  // x < 1.0
    l = x, r = 1.0;
  } else {  // x >= 1.0
    l = 1.0, r = x;
  }

  // Keep searching if l < r
  while (compare(l, r) == -1) {
    double m = l + 0.5 * (r - l);
    double square_m = m * m;
    if (compare(square_m, x) == 0) {
      return m;
    } else if (compare(square_m, x) == 1) {
      r = m;
    } else {
      l = m;
    }
  }
  return l;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 100000; ++times) {
    double x;
    if (argc == 2) {
      x = atof(argv[1]);
    } else {
      double f = static_cast<double>(rand()) / numeric_limits<double>::max();
      x = f * numeric_limits<double>::max();
    }
    double res[2];
    cout << "x is " << x << endl;
    cout << (res[0] = square_root(x)) << ' ' << (res[1] = sqrt(x)) << endl;
    assert(compare(res[0], res[1]) == 0);
  }
  return 0;
}
