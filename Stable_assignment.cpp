#include <iostream>
#include <numeric>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cassert>

using namespace std;

// @include
vector<pair<int, int> > find_stable_assignment(
    const vector<vector<int> > &professor_preference,
    const vector<vector<int> > &student_preference) {
  queue<int> free_student;  // stores currently free students
  for (int i = 0; i < student_preference.size(); ++i) {
    free_student.emplace(i);
  }

  // Records the professor each student have asked
  vector<int> student_pref_idx(student_preference.size(), 0);
  // Records each professor currently student choice
  vector<int> professor_choice(professor_preference.size(), -1);

  while (free_student.empty() == false) {
    int i = free_student.front();   // free student
    int j = student_preference[i][student_pref_idx[i]];   // target professor
    if (professor_choice[j] == -1) {  // this professor is free
      professor_choice[j] = i;
      free_student.pop();
    } else {  // this professor has student now
      int original_pref = find(professor_preference[j].cbegin(),
                               professor_preference[j].cend(),
                               professor_choice[j]) -
                          professor_preference[j].cbegin();
      int new_pref = find(professor_preference[j].cbegin(),
                          professor_preference[j].cend(), i) -
                     professor_preference[j].cbegin();
      if (new_pref < original_pref) {   // this professor prefers the new one
        free_student.emplace(professor_choice[j]);
        professor_choice[j] = i;
        free_student.pop();
      }
    }
    ++student_pref_idx[i];
  }

  vector<pair<int, int> > match_result;
  for (int j = 0; j < professor_choice.size(); ++j) {
    match_result.emplace_back(professor_choice[j], j);
  }
  return match_result;
}
// @exclude

void check_ans(const vector<vector<int> > &professor_preference, const vector<vector<int> > &student_preference, const vector<pair<int, int> > &match_result) {
  assert(match_result.size() == professor_preference.size());
  vector<bool> professor(professor_preference.size(), false), student(student_preference.size(), false);
  for (const pair<int, int> &p: match_result) {
    //cout << p.first << " " << p.second << endl;
    student[p.first] = true;
    professor[p.second] = true;
  }
  for (const bool &p : professor) {
    assert(p);
  }
  for (const bool &s : student) {
    assert(s);
  }

  for (int i = 0; i < match_result.size(); ++i) {
    for (int j = i + 1; j < match_result.size(); ++j) {
      int s0 = match_result[i].first, a0 = match_result[i].second;
      int s1 = match_result[j].first, a1 = match_result[j].second;
      int a0_in_s0_order = find(student_preference[s0].cbegin(), student_preference[s0].cend(), a0) - student_preference[s0].cbegin();
      int a1_in_s0_order = find(student_preference[s0].cbegin(), student_preference[s0].cend(), a1) - student_preference[s0].cbegin();
      int s0_in_a1_order = find(professor_preference[a1].cbegin(), professor_preference[a1].cend(), s0) - professor_preference[a1].cbegin();
      int s1_in_a1_order = find(professor_preference[a1].cbegin(), professor_preference[a1].cend(), s1) - professor_preference[a1].cbegin();
      assert(a0_in_s0_order < a1_in_s0_order || s1_in_a1_order < s0_in_a1_order);
    }
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      n = 1 + rand() % 300;
    }
    vector<vector<int> > professor_preference(n), student_preference(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        professor_preference[i].emplace_back(j);
        student_preference[i].emplace_back(j);
      }
      random_shuffle(professor_preference[i].begin(), professor_preference[i].end());
      random_shuffle(student_preference[i].begin(), student_preference[i].end());
    }

    /*
    for (int i = 0; i < n; ++i) {
      cout << "professor " << i << endl;
      for (int j = 0; j < n; ++j) {
        cout << professor_preference[i][j] << " ";
      }
      cout << endl;
    }
    for (int i = 0; i < n; ++i) {
      cout << "student " << i << endl;
      for (int j = 0; j < n; ++j) {
        cout << student_preference[i][j] << " ";
      }
      cout << endl;
    }
    */

    vector<pair<int, int> > res = find_stable_assignment(professor_preference, student_preference);
    check_ans(professor_preference, student_preference, res);
  }
  return 0;
}
