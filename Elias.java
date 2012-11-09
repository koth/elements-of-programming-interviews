import java.util.List;
import java.util.ArrayList;
import java.lang.StringBuffer;

public class Elias {

  // @include
  public static String encode(int [] A) {
    List<String> terms = new ArrayList<String>();
    for (int i : A) {
      String s = Integer.toString(i);
      StringBuffer sb = new StringBuffer();
      for (int j = 0 ; j < s.length() - 1 ;++j) {
        sb.append("0");
      }
      sb.append(s);
      terms.add(sb.toString());
    }

    StringBuffer resultSb = new StringBuffer();
    for (String s : terms) {
      resultSb.append(s);
    }
    return resultSb.toString();
  }

  public static String [] decode(String s) {
    List<String> numbers = new ArrayList<String>();
    int offset = 0;
    while (offset < s.length()) {
      int thisLength = 0;
      while (s.charAt(offset) == '0') {
        ++offset;
        ++thisLength;
      }
      String thisString = s.substring(offset, offset + thisLength + 1);
      offset = offset + thisLength + 1;
      numbers.add(thisString);
    }

    String [] result = new String[numbers.size()];
    numbers.toArray(result);
    return result;
  }
  // @exclude

  static void printStringArray( String [] sa ) {
    for( String s : sa ) {
      System.out.println(s);
    }
  }

  public static void main( String [] args ) {
    String s1 = "0110100011100100";
    String [] d1 = decode(s1);
    System.out.println("Result of decoding " + s1 );
    printStringArray( d1 );
    int [] i1 = new int[d1.length];
    int index = 0;
    for ( String s : d1 )
      i1[index++] = new Integer( s );
    System.out.println("Encoding: " + encode( i1 ) );
  }
}

