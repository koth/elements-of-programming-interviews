import java.util.Set;
import java.util.HashSet;

public class StringInMatrix {

  static int[][] A = { {1,2,3,4}, {4,5,6,5}, {7,8,9,10}, {10,11,12,13} };

  static int[] searchString = {13,12,11,10,7,4,1};

  // @include
  static Set<Integer[]> cache = new HashSet<Integer[]>();

  public static boolean matchHelper(int [][] A, int [] S, int i, int j, int k) {
    if (S.length == k) {
      return true;
    }

    if (cache.contains(new Integer[] {i, j, k}) || i < 0 || j < 0 ||
        i >= A.length || j >= A[i].length || A[i][j] != S[k]) {
      return false;
    }

    if (matchHelper(A, S, i - 1, j, k + 1) || matchHelper(A, S, i + 1, j, k + 1) ||
        matchHelper(A, S, i, j - 1, k + 1) || matchHelper(A, S, i, j + 1, k + 1)) {
      System.out.println("A[" + i + "," + j + "] = " + A[i][j]);
      return true;
    }
    cache.add(new Integer[] {i, j, k});
    return false;
  }

  public static boolean match(int [][] A, int [] S) {
    for (int i = 0; i < A.length; ++i) {
      for (int j = 0; j < A[i].length; ++j) {
        if (matchHelper(A, S, i, j, 0)) {
          return true;
        }
      }
    }
    return false;
  }
  // @exclude

  public static void main(String [] args) {
    boolean success = false;
    success = match(A, searchString);
    if ( !success ) {
      System.out.println("There is no occurrence of the target array");
   }
  }
}
