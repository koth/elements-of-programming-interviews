public class PrintMatrixSpiral {
  // @include
  static void printCycle(int A[][], int offset) {
    for (int j = offset; j < A.length - offset - 1; ++j) { 
      System.out.print(A[offset][j] + ",");
    }
    for (int i = offset; i < A.length - offset - 1; ++i) {
      System.out.print(A[i][A.length - offset - 1] + ",");
    }
    for (int j = A.length - offset - 1; j > offset; --j) {
      System.out.print(A[A.length - offset - 1][j] + ",");
    }
    for (int i = A.length - offset - 1; i > offset; --i) {
      System.out.print(A[i][offset] + ",");
    }
  }

  static void printMatrix(int [][] A) {
    for (int l = 0; l <= A.length / 2; ++l) {
      printCycle(A, l);
    }
  }
  // @exclude

  public static int A1[][] = {{0}};
  public static int A2[][] = {{0,1,2},{7,8,3},{6,5,4}};
  public static int A3[][] = {{0,1,2},{7,8,3},{6,5,4}};
  public static int A4[][] = {{0,1,2,3},{11,12,13,4},{10,15,14,5},{9,8,7,6}};
  public static int A5[][] = {{0,1,2,3,4},{15,16,17,18,5},{14,23,24,19,6},{13,22,21,20,7},{12,11,10,9,8}};
  public static int A6[][] = {{0,1,2,3,4,5},{19,20,21,22,23,6},{18,31,32,33,24,7},{17,30,35,34,25,8},{16,29,28,27,26,9},{15,14,13,12,11,10}};

  public static void main(String [] args) {
    printMatrix(A1);
    System.out.println();
    printMatrix(A2);
    System.out.println();
    printMatrix(A3);
    System.out.println();
    printMatrix(A4);
    System.out.println();
    printMatrix(A5);
    System.out.println();
    printMatrix(A6);
    System.out.println();
  }
}
