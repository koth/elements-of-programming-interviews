public class EquivClasses {

  static int N = 7;
  static int A[] = {1,2,2,3,5,6};
  static int B[] = {2,4,1,0,2,0};

  // @include
  /*
   * A and B encode pairwise equivalences on a cardinality N set whose elements
   * are indexed by 0,1,2,...,N-1
   *
   * For example A[5] = 6 and B[5] = 0 indicates that the sixth and
   * zeroth elements are to be grouped into the same equivalence class
   *
   * We return the weakest equivalence relation implied by A and B in an array
   * F of length N; F[i] holds the smallest index of all the elements that
   * i is equivalent to.
   */

  public static int [] ComputeEquivalenceClasses(int N, int A[], int B[]) {
    int[] F = new int[N];
    int numEquivalentPairs = A.length;
    for (int i = 0 ; i < F.length; ++i) {
      F[i] = i;
    }

    for (int k = 0 ; k < numEquivalentPairs; ++k) {
      int i = A[k];
      while (F[i] != i) {
        i = F[i];
      }
      int j = B[k];
      while (F[j] != j) {
        j = F[j];
      }

      if (i != j) {
        if (i < j) {
          F[j] = i;
        } else {
          F[i] = j;
        }
      }
    }

    for (int i = 0 ; i < N; ++i) {
      while (F[i] != F[F[i]]) {
        F[i] = F[F[i]];
      }
    }
    return F;
  }
  // @exclude

  public static void main(String[] args) {
    int F[] = ComputeEquivalenceClasses(N, A, B);

    for (int i = 0 ; i < N; i++)
      System.out.println("F[" + i + "] = " + F[i] );
  }

  static void print(String s, int [] F) {
    System.out.println(s);
    for (int i = 0 ; i < N; i++) {
      System.out.println("F[" + i + "] = " + F[i] );
    }
  }
}
