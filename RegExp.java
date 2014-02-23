public class RegExp {

  // @include
  static boolean match(String r, String s) {
    if (r.charAt(0) == '^') {
      return matchHere(r.substring(1), s);
    }

    for (int i = 0; i < s.length(); ++i) {
      if (matchHere(r, s.substring(i))) {
        return true;
      }
    }
    return false;
  }

  static boolean matchHere(String r, String s) {
    if (r.length() == 0) {
      return true;
    }

    if (r.length() >= 2 && r.charAt(1) == '*') {
      return matchStar(r.charAt(0), r.substring(2), s);
    }

    if (r.charAt(0) == '$' && r.length() == 1) {
      return (s.length() == 0);
    }

    if (s.length() > 0 && (r.charAt(0) == '.' || r.charAt(0) == s.charAt(0))) {
      return matchHere(r.substring(1), s.substring(1));
    }
    return false;
  }

  static long counter;
  static boolean matchStar(char c, String r, String s) {
    counter++; 
    for (int i = 0; i < s.length() && (s.charAt(i++) == c || c == '.'); ++i) {
      if (matchHere(r, s.substring(i))) {
        return true;
      }
    }
    return false;
  }
  // @exclude

  public static void main( String [] args ) {
 
    for (int i = 1 ; i < 100; i++ ) {
      String s = "a.*";
			String t = "";
			for ( int j = 0 ; j < i; j++ ) {
			   s += "a.*";
				 t += "ab";
			}
			assert( !match( s, t ) );
      System.out.println("s = " + s + " t = " + t );
      System.out.println("iteration = " + i );
      System.out.println("counter = " + counter );
      counter = 0;
    }

   assert( match( ".", "a") );
    assert( match( "a", "a") );
    assert( !match( "a", "b") );
    assert( match( "a.9", "aW9") );
    assert( !match( "a.9", "aW19") );
    assert( match( "^a.9", "aW9") );
    assert( !match( "^a.9", "baW19") );
    assert( match( ".*", "a"));
    // assert( match( ".*", "")); // this one will fail, use System.out.println to show it
    assert( match( ".*",  "asdsdsa"));
    assert( match( "9$" , "xxxxW19" ) );

    assert( match( ".*a", "ba") );

    assert( match( ".*a", "ba") );
    // assert( match( "^a.*9$", "axxxxW19") );

    // assert( match( "^a.*W19$", "axxxxW19") );
    assert( match( ".*a.*W19", "axxxxW19123") );
    assert( !match( ".*b.*W19", "axxxxW19123") );
    assert( match( "n.*", "n") );
    assert( match( "a*n.*", "an") );
    assert( match( "a*n.*", "ana") );
    assert( match( "a*n.*W19", "anaxxxxW19123") );
    assert( match( ".*a*n.*W19", "asdaaadnanaxxxxW19123") );
    assert( match( ".*.*.a*n.*W19", "asdaaadnanaxxxxW19123") );
  }
}
