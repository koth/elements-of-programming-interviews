#include <iostream>
#include <cassert>
#ifdef __clang__
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

// @include
double compute_best_payoff_helper(
    unordered_map<int,
                  unordered_map<int, unordered_map<int, double>>> &cache,
    const double &upper_bound, const int &cash, const int &num_red,
    const int &num_cards) {
  if (cash >= upper_bound) {
    return cash;
  }

  if (num_red == num_cards || num_red == 0) {
    return cash * pow(2, num_cards);
  }

  if (cache[cash][num_red].find(num_cards) == cache[cash][num_red].end()) {
    double best = numeric_limits<double>::min();
    for (int bet = 0; bet <= cash; ++bet) {
      double red_lower_bound = min(
        compute_best_payoff_helper(cache, upper_bound, cash + bet,
                                   num_red - 1, num_cards - 1),
        compute_best_payoff_helper(cache, upper_bound, cash - bet,
                                   num_red, num_cards - 1));

      double black_lower_bound = min(
        compute_best_payoff_helper(cache, upper_bound, cash - bet,
                                   num_red - 1, num_cards - 1),
        compute_best_payoff_helper(cache, upper_bound, cash + bet,
                                   num_red, num_cards - 1));
      best = max(best, max(red_lower_bound, black_lower_bound));
    }
    cache[cash][num_red][num_cards] = best;
  }
  return cache[cash][num_red][num_cards];
}

double compute_best_payoff(const int &cash) {
  double upper_bound = 9.09 * cash;
  unordered_map<int, unordered_map<int, unordered_map<int, double>>> cache;
  return compute_best_payoff_helper(cache, upper_bound, cash, 26, 52);
}
// @exclude

int main(int argc, char *argv[]) {
  int ans = compute_best_payoff(100);
  assert(ans == 808);
  cout << "100 cash can get " << ans << endl;
  return 0;
}
