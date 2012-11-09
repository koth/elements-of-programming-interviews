public class SudokuChecker {

   // "Near worst case" example from
   // http://en.wikipedia.org/wiki/Sudoku_algorithms
   public static final String[] testCase =
				{"153", "178", "185",
				 "221", "242",
			 	 "335", "357",
				 "424", "461",
				 "519",
				 "605", "677", "683",
				 "722", "741",
				 "844", "889"};

   public static final int N = 9;

   public static long count = 0;

   public static void main(String[] args) {
     int[][] matrix = readInput(args);
     print("Initial configuration", matrix);
     if ( !isValid( matrix ) ) {
       System.out.println("Initial configuration violates constraints");
       return;
     }
     if (isSolvable(0,0,matrix)) {
       if ( !isValid( matrix ) ) {
         System.out.println("Buggy algorithm, returns true and a matrix that"
	 	+ "doesn't satisfy constraints");
         print("Buggy output", matrix);
       } else {
         print("Solved configuration", matrix);
       }
     } else {
       System.out.println("---no solution exists");
     }
   }

  public static boolean isSolvable(int i, int j, int[][] matrix) {
    if (i == N) {
      i = 0;
      if (++j == N)
        return true;
      }
      // skip nonempty entries
      if ( matrix[i][j] != 0 )
        return isSolvable(i+1,j,matrix);
      for ( int entryval = 1; entryval <= N; ++entryval ) {
        // Note: practically, it's substantially quicker to check if
        // entryval conflicts with any of the constraints if we add
        // it at (i,j) before adding it, rather than adding it
        // and then calling isValid.  The reason is that we know
        // we are starting with a valid configuration, and the
        // only entry which can cause a problem is entryval at (i,j).
        if ( validToAdd(i,j,entryval, matrix ) ) {
	  matrix[i][j] = entryval;
	  if ( isSolvable(i+1,j,matrix) ) {
            return true;
	  }
        }
      }
      // backtrack => undo assignment
      matrix[i][j] = 0;
      return false;
  }

  static boolean validToAdd(int i, int j, int entry, int[][] matrix) {
    // row constraints
    for (int k = 0; k < N; k++)
      if (entry == matrix[k][j])
        return false;

    // column constraints
    for (int k = 0; k < N; k++)
      if (entry == matrix[i][k])
        return false;

    // region constraints
    int I = i/3;
    int J = j/3;
    for (int k = 0; k < 3; k++)
      for (int m = 0; m < 3; m++)
        if (entry == matrix[3*I+k][3*J+m])
          return false;

    return true;
  }


   public static int[][] readInput( String[] args ) {
     if ( args.length == 0 ) {
       args = testCase;
     }
     int[][] result = new int[N][];
     for ( int k = 0 ; k < N; k++ ) {
       result[k] = new int[N];
     }
     for ( int k = 0 ; k < args.length; k++ ) {
       int val = new Integer( args[k] );
       // format: 634 -> in row 6, col 4 value is 4
       result[val / 100][(val % 100) / 10] = (val % 10);
     }
     return result;
   }

  // @include
  // Check if a partially filled matrix has any conflicts
  public static boolean isValid( int[][] matrix ) {
    // Row constraints
    for (int i = 0; i < N; ++i) {
      boolean[] present = new boolean[N + 1];
      for (int j = 0; j < N; ++j) {
        if (matrix[i][j] != 0 && present[matrix[i][j]]) {
          return false;
        } else {
          present[matrix[i][j]] = true;
        }
      }
    }

    // Column constraints
    for (int j = 0; j < N; ++j) {
      boolean[] present = new boolean[N + 1];
      for (int i = 0; i < N; ++i) {
        if (matrix[i][j] != 0 && present[matrix[i][j]]) {
          return false;
        } else {
          present[matrix[i][j]] = true;
        }
      }
    }

    // Region constraints
    for (int I = 0; I < 3; ++I) {
      for (int J = 0 ; J < 3; ++J) {
        boolean[] present = new boolean[N + 1];
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            if (matrix[3 * I + i][3 * J + j] != 0 &&
                present[matrix[3 * I + i][3 * J + j]]) {
              return false;
            } else {
              present[matrix[3 * I + i][3 * J + j]] = true;
            }
          }
        }
      }
    }
    return true;
  }
  // @exclude


   static void print(String msg, int[][] matrix) {
     System.out.println(msg);
     for ( int i  = 0 ; i < matrix.length; i++ ) {
       for ( int j  = 0 ; j < matrix[0].length; j++ ) {
         System.out.print(matrix[i][j] + ( (j < 8) ? " " : "\n" ) );
       }
     }
   }
}
