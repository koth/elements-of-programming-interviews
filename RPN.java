import java.util.List;
import java.util.Stack;
import java.util.LinkedList;

public class RPN {

  static void p(String s) { System.out.println(s); }

  // @include
  static boolean isOperator(char c) {
    return (c == '*' || c == '+' || c == '-' || c == '/');
  }

  public static int eval(String s) {
     Stack<Integer> evalStack = new Stack<Integer>();
     int offset = 0, length = s.length();

     while (offset < length) {
       char c;
       while (offset < length && isOperator(c = s.charAt(offset))) {
         Integer x, y;
         x = evalStack.pop();
         y = evalStack.pop();
         switch (c) {
           case '*':
             evalStack.push(x * y); break;
           case '+':
             evalStack.push(x + y); break;
           case '/':
             evalStack.push(x / y); break;
           case '-':
             evalStack.push(x - y); break;
           default:
             break;
         }
         ++offset;
       }

       if (offset >= length)
         break;

       int numIndex = offset;
       while (Character.isDigit(s.charAt(offset)))
         ++offset;
       
       Integer tmp = Integer.parseInt(s.substring(numIndex, offset));
       // Detect negative number
       if (s.charAt(offset) == '-') {
         tmp = -tmp;
         ++offset;
       }
       if (s.charAt(offset) == ',') {
         ++offset;
       }
       evalStack.push(tmp);
     }
     return evalStack.pop();
  }
  // @exclude

  static public void main(String [] args) {
    System.out.println(eval("2,10-,/"));
    assert (-5 == eval("2,10-,/"));
    System.out.println(eval("10,2+"));
    assert (12 == eval("10,2+"));
    System.out.println(eval("1,2+3,4*+"));
    assert (15 == eval("1,2+3,4*+"));
    System.out.println(eval("1,2,3,4,5+*++3,4*+"));
    assert (42 == eval("1,2,3,4,5+*++3,4*+"));
  }
}

