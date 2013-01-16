#include <iostream>
#include <algorithm>
#include <cassert>
#ifdef __clang__
#include <unordered_map>
#include <unordered_set>
#else
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#endif
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
#ifndef __clang__
using namespace std::tr1;
#endif

int GCD(int a, int b) {
  if (b) {
    while ((a %= b) && (b %= a));
  }
  return a + b;
}

// @include
class Point {
  public:
    int x, y;

    //Equal function for hash
    const bool operator==(const Point &that) const {
      return x == that.x && y == that.y;
    }
};

// Hash function for Point
class HashPoint {
  public:
    const size_t operator()(const Point &p) const {
      return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

// Line function of two points, a and b, and the equation is
// y = x(b.y - a.y) / (b.x - a.x) + (b.x * a.y - a.x * b.y) / (b.x - a.x)
class Line {
  private:
    static pair<int, int> get_canonical_fractional(int a, int b) {
      int gcd = GCD(abs(a), abs(b));
      a /= gcd, b /= gcd;
      return b < 0 ? make_pair(-a, -b) : make_pair(a, b);
    }

  public:
    // Store the numerator and denominator pair of slope unless the line is
    // parallel to y-axis that we store 1/0
    pair<int, int> slope;
    // Store the numerator and denominator pair of the y-intercept unless
    // the line is parallel to y-axis that we store the x-intercept
    pair<int, int> intercept;

    Line(const Point &a, const Point &b) :
      slope(a.x != b.x ? get_canonical_fractional(b.y - a.y, b.x - a.x) :
            make_pair(1, 0)),
      intercept(a.x != b.x ? 
                get_canonical_fractional(b.x * a.y - a.x * b.y, b.x - a.x) :
                make_pair(a.x, 1)) {}

    // Equal function for hash
    const bool operator==(const Line &that) const {
      return slope == that.slope && intercept == that.intercept;
    }
};

// Hash function for Line
class HashLine {
  public:
    const size_t operator()(const Line &l) const {
      return hash<int>()(l.slope.first) ^ hash<int>()(l.slope.second) ^
             hash<int>()(l.intercept.first) ^ hash<int>()(l.intercept.second);
    }
};
// @exclude

// n^3 checking
int check(const vector<Point> &P) {
  int max_count = 0;
  for (int i = 0; i < P.size(); ++i) {
    for (int j = i + 1; j < P.size(); ++j) {
      int count = 2;
      Line temp(P[i], P[j]);
      for (int k = j + 1; k < P.size(); ++k) {
        if (Line(P[i], P[k]) == temp) {
          ++count;
        }
      }
      max_count = max(max_count, count);
    }
  }

  return max_count;
}
// @include

Line find_line_with_most_points(const vector<Point> &P) {
  // Add all possible lines into hash table
  unordered_map<Line, unordered_set<Point, HashPoint>, HashLine> table;
  for (int i = 0; i < P.size(); ++i) {
    for (int j = i + 1; j < P.size(); ++j) {
      Line l(P[i], P[j]);
      table[l].emplace(P[i]), table[l].emplace(P[j]);
    }
  }

  // @exclude
  auto line_max_points = max_element(table.cbegin(), table.cend(),
    [](const pair<Line, unordered_set<Point, HashPoint> > &a,
       const pair<Line, unordered_set<Point, HashPoint> > &b) {
      return a.second.size() < b.second.size();
    });
  int res = check(P);
  //cout << res << " " << line_max_points.second.size() << endl;
  assert(res == line_max_points->second.size());
  // @include
  // Return the line with most points have passed
  return max_element(table.cbegin(), table.cend(),
    [](const pair<Line, unordered_set<Point, HashPoint> > &a,
       const pair<Line, unordered_set<Point, HashPoint> > &b) {
      return a.second.size() < b.second.size();
    })->first;
}
// @exclude

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    cout << times << endl;
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 1000;
    }
    vector<Point> points;
    unordered_set<Point, HashPoint> t;
    do {
      Point p{rand() % 1000, rand() % 1000};
      if (t.find(p) == t.cend()) {
        points.push_back(p);
        t.emplace(p);
      }
    } while (t.size() < n);
    /*
    for (int i = 0; i < points.size(); ++i) {
      cout << points[i].x << ", " << points[i].y << endl;
    }
    */
    Line l = find_line_with_most_points(points);
    cout << l.slope.first << " " << l.slope.second << " " << l.intercept.first << " " << l.intercept.second << endl;
  }
  return 0;
}
