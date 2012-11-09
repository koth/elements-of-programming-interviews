import java.util.Random;

public class TailCoin {
  public static void main( String [] args ) {
    int numTrials = (args.length > 0) ? new Integer( args[0] ) : 10;
    int N = (args.length > 1) ? new Integer( args[1] ) : 10;
    int numFails = 0;
    double bias = 0.4;
    if ( args.length > 0 ) {
      numTrials = new Integer( args[0] );
    }
    if ( args.length > 1 ) {
      N = new Integer( args[1] );
    }
    // @include
  Random r = new Random();
  for (int i = 0; i < numTrials; ++i) {
    int sum = 0;
    for (int j = 0; j < N; ++j) {
      sum += (r.nextDouble() < bias) ? 1 : 0;
    }
    if (sum >= N / 2) {
      ++numFails;
    }
  }
  // @exclude
    System.out.println("fails:trials\t=\t"
        + numFails
        + ":" + numTrials
        + "\n\tratio\t=\t"
        + ( (double) numFails/(double) numTrials) );
  }
}
