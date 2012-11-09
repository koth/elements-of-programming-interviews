import java.util.List;
import java.util.ArrayList;

public class Hanoi {

  static final int n = 4;
  static final int numPegs = 3;
  static int count = 0;

  static List<ArrayList<Integer>> P =
    new ArrayList<ArrayList<Integer>>(numPegs);

  static void print() {
    System.out.print("Stack 0:");
    printStack(P.get(0));
    System.out.print("Stack 1:");
    printStack(P.get(1));
    System.out.print("Stack 2:");
    printStack(P.get(2));
  }

  static void printStack(List<Integer> p) {
    for (Integer i : p) {
      System.out.print("\t" + i);
    }
    System.out.println();
  }

  static void push(List<Integer> peg, Integer d) {
    peg.add(d);
  }

  static int pop(List<Integer> peg) {
    return peg.remove(peg.size() - 1);
  }

  // @include
  static void move(int from, int to) {
    ++count;
    System.out.println("Move " + from + " to " + to);
    push(P.get(to), pop(P.get(from)));
  }

  static void transfer(int number, int from, int to, int using) {
    if (number > 0) {
      transfer(number - 1, from, using, to);
      move(from, to);
      transfer(number - 1, using, to, from);
    }
  }
  // @exclude


  public static void main (String args[]) {
    P.add(0, new ArrayList<Integer>(n));
    P.add(1, new ArrayList<Integer>(n));
    P.add(2, new ArrayList<Integer>(n));

    for (int i = 0 ; i < n; ++i) {
      P.get(0).add(n - 1 - i);
    }

    System.out.println("Initial configuration:");
    print();
    System.out.println("-----");
    transfer(n, 0, 1, 2);
    System.out.println("Total number of moves: " + count);
    System.exit(0);
  }
}
