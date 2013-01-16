#include <iostream>
#include <array>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// @include
class Star {
  public:
    int ID;
    double x, y, z;

    // The distance between this star to the Earth
    double distance() const {
      return sqrt(x * x + y * y + z * z);
    }

    bool operator<(const Star &s) const {
      return distance() < s.distance();
    }
};

vector<Star> find_closest_k_stars(istringstream &sin, const int &k) {
  // Use max_heap to find the closest k stars
  priority_queue<Star, vector<Star> > max_heap;
  string line;

  // Record the first k stars
  while (getline(sin, line)) {
    stringstream line_stream(line);
    string buf;
    getline(line_stream, buf, ',');
    int ID = stoi(buf);
    array<double, 3> data;  // stores x, y, and z
    for (int i = 0; i < 3; ++i) {
      getline(line_stream, buf, ',');
      data[i] = stod(buf);
    }
    Star s{ID, data[0], data[1], data[2]};

    if (max_heap.size() == k) {
      // Compare the top of heap with the incoming star
      Star far_star = max_heap.top();
      if (s < far_star) {
        max_heap.pop();
        max_heap.emplace(s);
      }
    } else {
      max_heap.emplace(s);
    }
  }

  // Store the closest k stars
  vector<Star> closest_stars;
  while (!max_heap.empty()) {
    closest_stars.emplace_back(max_heap.top());
    max_heap.pop();
  }
  return closest_stars;
}
// @exclude

int partition(vector<Star> &stars, int left, int right, int pivot_index) {
  double pivot_value(stars[pivot_index].distance());
  swap(stars[pivot_index], stars[right]);
  int less_index = left;
  for (int i = left; i < right; ++i) {
    if (stars[i].distance() < pivot_value) {
      swap(stars[i], stars[less_index++]);
    }
  }
  swap(stars[right], stars[less_index]);
  return less_index;
}

vector<Star> select_k(vector<Star> stars, int k) {
  if (stars.size() <= k) {
    return stars;
  }

  int left = 0, right = stars.size() - 1, pivot_index;
  while (left <= right) {
    pivot_index = partition(stars, left, right, left + (rand() % (right - left + 1)));
    if (k - 1 < pivot_index) {
      right = pivot_index - 1;
    } else if (k - 1 > pivot_index) {
      left = pivot_index + 1;
    } else {  // k - 1 == pivot_index
      break;
    }
  }

  vector<Star> closest_stars;
  double dist(stars[pivot_index].distance());
  for (int i = 0; i < stars.size(); ++i) {
    if (dist >= stars[i].distance()) {
      closest_stars.emplace_back(stars[i]);
    }
  }
  return closest_stars;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int num, k;
    if (argc == 2) {
      num = atoi(argv[1]);
      k = 1 + rand() % num;
    } else if (argc == 3) {
      num = atoi(argv[1]);
      k = atoi(argv[2]);
    } else {
      num = 1 + rand() % 1000000;
      k = 1 + rand() % num;
    }
    vector<Star> stars;
    // randomly generate num of stars
    for (int i = 0; i < num; ++i) {
      stars.emplace_back(Star{i, rand() + static_cast<double>(rand()) / static_cast<double>(RAND_MAX), rand() + static_cast<double>(rand()) / static_cast<double>(RAND_MAX), rand() + static_cast<double>(rand()) / static_cast<double>(RAND_MAX)});
    }
    string s;
    for (int i = 0; i < num; ++i) {
      stringstream ss;
      ss << stars[i].ID << ',' << stars[i].x << ',' << stars[i].y << ',' << stars[i].z << endl;
      s += ss.str();
      //cout << stars[i].ID << ' ' << stars[i].distance() << endl;
    }
    istringstream sin(s);
    vector<Star> closest_stars(find_closest_k_stars(sin, k));
    /*
    for (int i = 0; i < closest_stars.size(); ++i) {
      cout << "star :  (" << closest_stars[i].ID << ", " << closest_stars[i].x << ", " << closest_stars[i].y << ", " << closest_stars[i].z << ") dis : " << closest_stars[i].distance() << endl;
    }
    //*/
    vector<Star> selected_stars(select_k(stars, k));
    sort(selected_stars.begin(), selected_stars.end());
    sort(stars.begin(), stars.end());
    cout << k << endl;
    //assert(stars[k - 1].ID == closest_stars[0].ID);
    assert(stars[k - 1].distance() == selected_stars.back().distance());
  }
  return 0;
}
