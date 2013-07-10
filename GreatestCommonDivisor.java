import java.math.BigInteger;

public class GreatestCommonDivisor {

  // @include
  private static boolean isOdd(BigInteger x) {
    return x.testBit(0);
  }

  private static boolean isEven(BigInteger x) {
    return !isOdd(x);
  }

  public static BigInteger GCD(BigInteger x, BigInteger y) {
    if (x.equals(BigInteger.ZERO)) {
      return y;
    } else if (y.equals(BigInteger.ZERO)) {
      return x;
    } else if (isEven(x) && isEven(y)) {
      x = x.shiftRight(1);
      y = y.shiftRight(1);
      return GCD(x, y).shiftLeft(1);
    } else if (isOdd(x) && isEven(y)) {
      return GCD(x, y.shiftRight(1));
    } else if (isOdd(y) && isEven(x)) {
      return GCD(y, x.shiftRight(1));
    } else if (x.compareTo(y) <= 0) {
      return GCD(x, y.subtract(x));
    } else {
      return GCD(y, x.subtract(y));
    }
  }
  // @exclude

  public static void main( String [] args ) {
    BigInteger r1 = GCD( new BigInteger("12"), new BigInteger("18") );
    System.out.println("GCD of 12 and 18 is " + r1 );
    BigInteger r2 = GCD(
      new BigInteger("12121212121212121212121212121212121212")
         .multiply(new BigInteger("181818181818181818181818181818181818183") ),
         new BigInteger("121212121212121212121212121212121212120") );
    System.out.println("GCD is " + r2 );
  }
}
