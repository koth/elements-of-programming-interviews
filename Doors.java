public class Doors {
  // @include
  static boolean isOpen(int i) {
    double di = (double)i;
    double sqrtdi = Math.sqrt(di);
    int sqrti = (int)sqrtdi;
    return (sqrti * sqrti == i);
  }
  // @exclude

  public static void test(int i) {
    System.out.println("Door " + i + " is " + ( isOpen( i ) ? "" : "not " ) + "open" );
  }

  public static void main(String args[]) {
    for ( int i = 0 ; i < 100; i++ ) {
      test(i);
    }
  }
}

