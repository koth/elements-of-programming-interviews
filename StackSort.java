import java.util.LinkedList;

public class StackSort {

  // @include
  static Integer pop(LinkedList<Integer> stack) {
    return stack.removeLast();
  }

  static void push(LinkedList<Integer> stack, Integer e) {
    stack.addLast(e);
    return;
  }

  static boolean isEmpty(LinkedList<Integer> stack) {
    return (stack.isEmpty() == true);
  }

  static Integer peek(LinkedList<Integer> stack) {
    return stack.getLast();
  }

  static void insert(LinkedList<Integer> stack, Integer e) {
    if (!isEmpty(stack) && peek(stack) < e) {
      Integer f = pop(stack);
      insert(stack, e);
      push(stack, f);
    } else {
      push(stack, e);
    }
  }

  static void sort(LinkedList<Integer> stack) {
    if (!isEmpty(stack)) {
      Integer e = pop(stack);
      sort(stack);
      insert(stack, e);
    }
  }
  // @exclude

  static void print(LinkedList<Integer> stack ) {
    for ( Integer e : stack ) {
      System.out.print("\t" + e );
    }
    System.out.println();
  }

  public static void main( String [] args ) {
    LinkedList<Integer> stack = new LinkedList<Integer>();
    stack.addLast(1);
    stack.addLast(3);
    stack.addLast(0);
    stack.addLast(3);
    stack.addLast(1);
    stack.addLast(7);
    stack.addLast(-1);
    System.out.println("Before sorting:");
    print(stack);
    System.out.println("After sorting:");
    sort(stack);
    print(stack);
  }
}
