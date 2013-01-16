#include <iostream>
#include <cassert>

using namespace std;

// @include
template <typename ValueType, size_t N>
class Array {
  private:
    ValueType A[N];
    int P[N], S[N], t;

    const bool isValid(const size_t &i) const {
      return (0 <= P[i] && P[i] < t && S[P[i]] == i);
    }

  public:
    Array(void) : t(0) {};

    const bool read(const size_t &i, ValueType &v) const {
      if (isValid(i)) {
        v = A[i];
        return true;
      }
      return false;
    }

    void write(const size_t &i, const ValueType &v) {
      if (!isValid(i)) {
        S[t] = i;
        P[i] = t++;
      }
      A[i] = v;
    }
};
// @exclude

int main(int argc, char* argv[]) {
  Array<int, 11> A;
  int x;
  assert(A.read(0, x) == false);
  assert(A.read(1, x) == false);
  A.write(1, 5);
  assert(A.read(1, x) == true && x == 5);
  assert(A.read(2, x) == false);
  A.write(2, 27);
  assert(A.read(2, x) == true && x == 27);
  assert(A.read(7, x) == false);
  A.write(7, -19);
  assert(A.read(7, x) == true && x == -19);
  return 0;
}
