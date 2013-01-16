import java.lang.Math;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;
import java.util.HashSet;

// assumes elements in subsequence are distinct
public class SubseqCover {

  public static void printMap( String prefix, Map<Integer,Integer> aMap ) {
    System.out.println( prefix );
    for ( Integer s : aMap.keySet() ) {
      System.out.print( s + "," + aMap.get( s ) + " " );
    }
    System.out.println( );
  }

  public static void main(String[] args) {
    int A1[] = {0,1,2,3,4,5,6,7,8,9,2,4,6,10,10,10,3,2,1,0};
    int A2[] = {0,1,2,3,4,5,0,7,8,9,2,4,0,10,10,10};
    int subseq1[] = {2,4,6};
    int subseq2[] = {2,10,6};
    int subseq3[] = {10};
    int subseq5[] = {0,10};
    assert( 3 == minSubSeqCover( A1, subseq1 ) );
    assert( Integer.MAX_VALUE == minSubSeqCover( A2, subseq1 ) );
    assert( Integer.MAX_VALUE == minSubSeqCover( A1, subseq2 ) );
    assert( 1 == minSubSeqCover( A1, subseq3 ) );
    int A3[] = {0,1,2,3,4,5,6,7,8,9,2,4,6,10,10,10,3,2,1,0};
    int subseq4[] = {0,2,9,4,6};
    assert( 13 == minSubSeqCover( A3, subseq4 ) );
    assert( 14 == minSubSeqCover( A1, subseq5 ) );

  }

  // @include
  public static int minSubSeqCover(int[] A, int[] Q) {
    Map<Integer,Integer> K = new HashMap<Integer,Integer>();
    Map<Integer,Integer> D = new HashMap<Integer,Integer>();

    for (int i = 0; i < Q.length; ++i) {
      K.put(Q[i], i);
      D.put(Q[i], Integer.MAX_VALUE);
    }

    int optimum = Integer.MAX_VALUE;
    Map<Integer,Integer> L = new HashMap<Integer,Integer>();

    for (int i = 0; i < A.length; ++i) {
      if (!K.containsKey(A[i])) {
        continue;
      }

      if (K.get(A[i]) == 0) { // first one, no predecessor
        D.put(A[i], 1); // base condition
      } else {
        int predecessor = Q[K.get(A[i]) - 1];
        int predLastOccurrence = L.containsKey(predecessor) ?
          L.get(predecessor) : Integer.MIN_VALUE;
        int predBest = D.get(predecessor);
        int update =
          (L.containsKey(predecessor) && predBest != Integer.MAX_VALUE) ?
          i - predLastOccurrence + predBest : Integer.MAX_VALUE;

        D.put(A[i], update);
      }
      L.put(A[i], i); // update the most recent occurrence
      if (K.get(A[i]) == Q.length - 1) {
        optimum = Math.min(optimum, D.get(A[i]));
      }
    }
    return optimum;
  }
  // @exclude
}
