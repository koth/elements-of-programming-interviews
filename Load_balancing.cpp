#include <vector>
#include <numeric>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <numeric>

using namespace std;

// @include
bool greedy_assignment(const vector<int> &user_file_size,
                       const int &server_num, const int &limit,
                       vector<int> &assign_res) {
  int server_idx = 0;
  for (const int &file : user_file_size) {
    while (server_idx < server_num && file + assign_res[server_idx] > limit) {
      ++server_idx;
    }

    if (server_idx >= server_num) {
      return false;
    } else {
      assign_res[server_idx] += file;
    }
  }
  return true;
}

vector<int> decide_load_balancing(vector<int> user_file_size,
                                  const int &server_num) {
  // Uses binary search to find the assignment with minimized maximum load
  int l = 0,
      r = accumulate(user_file_size.cbegin(), user_file_size.cend(), 0);
  vector<int> feasible_assignment;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    vector<int> assign_res(server_num, 0);
    bool is_feasible = greedy_assignment(user_file_size, server_num, m,
                                         assign_res);
    if (is_feasible) {
      feasible_assignment = assign_res;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return feasible_assignment;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  int n, m;
  if (argc == 3) {
    n = atoi(argv[1]);
    m = atoi(argv[2]);
  } else {
    n = 1 + rand() % 50000;
    m = 1 + rand() % n;
  }
  cout << n << " " << m << endl;
  vector<int> users;  // stores user i's data size
  for (int i = 0; i < n; ++i) {
    users.emplace_back(1 + rand() % 100);
  }
  for (const int &u : users) {
    cout << u << " ";
  }
  cout << endl;
  vector<int> res = decide_load_balancing(users, m);
  for (const int &file : res) {
    cout << file << ' ';
  }
  cout << endl;
  return 0;
}
