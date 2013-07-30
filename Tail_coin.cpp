#include <iostream>
#include <random>

using namespace std;

// @include
// Return the number of fail trails
int simulate_biased_coin(const int &n, const int &trails) {
  default_random_engine gen((random_device())());  // random num generator
  // Generate random double in [0.0, 1.0]
  uniform_real_distribution<double> dis(0.0, 1.0);
  const double bias = 0.4;
  int fails = 0;
  for (int i = 0; i < trails; ++i) {
    int biased_num = 0;
    for (int j = 0; j < n; ++j) {
      biased_num += (dis(gen) >= bias);
    }

    if (biased_num < (n >> 1)) {
      ++fails;
    }
  }
  return fails;
}
// @exclude

int main(int argc, char *argv[]) {
  int n, trails;
  if (argc == 3) {
    n = atoi(argv[1]);
    trails = atoi(argv[2]);
  }
  int fails = simulate_biased_coin(n, trails);
  cout << "fails = " << fails << endl;
  cout << "ratio = " << static_cast<double>(fails) / trails << endl;
  return 0;
}
