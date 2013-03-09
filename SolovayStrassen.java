import java.math.BigInteger;
import java.util.Random;

public class SolovayStrassen {
  // constants used in computation of Jacobi symbol
  static final BigInteger TWO = new BigInteger( "2" );
  static final BigInteger THREE = TWO.add(BigInteger.ONE);
  static final BigInteger FOUR = TWO.add(TWO);
  static final BigInteger SEVEN = FOUR.add(THREE);
  static final BigInteger EIGHT = FOUR.add(FOUR);

  // @include
  static int Jacobi(BigInteger m, BigInteger n) {
    if (m.compareTo(n) >= 0) {
      m = m.mod(n);
      return Jacobi(m, n);
    }
    if (n.equals(BigInteger.ONE) || m.equals(BigInteger.ONE)) {
      return 1;
    }
    if (m.equals(BigInteger.ZERO)) {
      return 0;
    }

    int twoCount = 0;
    while (m.mod(TWO) == BigInteger.ZERO) {
      twoCount++;
      m = m.divide(TWO);
    }
    int J2n = n.mod(EIGHT).equals(BigInteger.ONE) ||
              n.mod(EIGHT).equals(SEVEN) ? 1 : -1;
    int rule8multiplier = (twoCount % 2 == 0) ? 1 : J2n;

    int tmp = Jacobi(n, m);
    int rule6multiplier = n.mod(FOUR).equals(BigInteger.ONE) ||
                          m.mod(FOUR).equals(BigInteger.ONE) ? 1 : -1;

    return tmp * rule6multiplier * rule8multiplier;
  }

  static int eulerCriterion(BigInteger p, BigInteger a) {
    BigInteger exponent = (p.subtract(BigInteger.ONE)).divide(TWO);
    BigInteger x =  a.modPow(exponent, p);
    if (x.equals(BigInteger.ZERO) || x.equals(BigInteger.ONE)) {
      return x.intValue();
    }
    BigInteger y = x.add(BigInteger.ONE).mod(p);
    return (y.equals(BigInteger.ZERO)) ? -1 : 2;
  }
  // @exclude

  public static void main( String[] arg ) {
    Random r = new Random();
    final int numberOfTests = 256;
    final int numBits = 512;
    boolean isPrime = true;
    BigInteger f0 = BigInteger.probablePrime(numBits, r);
    BigInteger f1 = BigInteger.probablePrime(numBits/2, r);
    f1 = f1.equals(TWO) ? THREE : f1;
    BigInteger f2 = BigInteger.probablePrime(numBits/2, r);
    f2 = f2.equals(TWO) ? THREE : f2;
    BigInteger p = f1.multiply( f2 );
    // BigInteger p = f0;
    for ( int i = 0; i < numberOfTests; i++ ) {
      BigInteger rBig = new BigInteger( numBits, r );
      int ec = eulerCriterion( p, rBig );
      int js = Jacobi( rBig, p );
      if ( ec != js ) {
        isPrime = false;
        break;
      }
    }
    System.out.println(p.toString() +
        ( (isPrime) ? " probably is" : " is definitely not" ) +
        " a prime:" );
  }
}
