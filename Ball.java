public class Ball {

  public static final int N = 1000;
  public static int cache[][] = new int[N][N];

  // @include
  public static int maxHeight(int c, int d) {
    if (d == 0) {
      return 0;
    } else if (c == 1) {
      return d;
    } else {
      if (cache[c][d] == -1) {
        cache[c][d] = maxHeight(c, d - 1) + maxHeight(c - 1, d - 1) + 1;
      }
      return cache[c][d];
    }
  }
  // @exclude

  public static void clearCache() {
    for (int i = 0 ; i < cache.length; ++i) {
      for (int j = 0 ; j < cache[i].length; ++j) {
        cache[i][j] = -1;
      }
    }
  }

  public static int testMaxHeight( int B, int D ) {
    clearCache();
    int result = -1;
    System.out.println("test: B = " + B + ", D = " + D + " max height = " + (result = maxHeight( B, D ) ) );
    return result;
  }


  public static void main(String [] args) {
    testMaxHeight( 1, 10 );
    testMaxHeight( 2, 1 );
    testMaxHeight( 2, 2 );
    testMaxHeight( 2, 3 );
    testMaxHeight( 2, 4 );
    testMaxHeight( 2, 5 );
    testMaxHeight( 3, 2 );
    testMaxHeight( 100, 2 );
    testMaxHeight( 3, 5 );
    testMaxHeight( 8, 11 );
    for ( int i = 0 ; i < 100; i++ ) {
      if ( testMaxHeight( 3, i ) >= 100 ) {
        System.out.println("Success with " + i + " drops");
        break;
      }
    }
  }
}
