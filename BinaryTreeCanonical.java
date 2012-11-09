import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.LinkedList;
import java.util.Map;
import java.util.HashMap;

public class BinaryTreeCanonical {

  static void p(String s) { System.out.println(s); }
  static int recCount = 0;

  // @include
  static class BinaryTreeNode {
    int key;
    String name;
    BinaryTreeNode left, right;
    Integer cachedHash;

    public BinaryTreeNode(int k, String s, BinaryTreeNode l, BinaryTreeNode r) {
      this.key = k;
      this.name = s;
      this.left = l;
      this.right = r;
      this.cachedHash = null;
    }

    @Override
    public int hashCode() {
      System.out.println("Calling overridden hashCode");
      Integer result;
      result = this.cachedHash;
      if (result != null) {
        // @exclude
        p("result from cache:" + result );
        // @include
        return result;
      }

      int x = 3 * key, y = 5;
      if (this.left != null) {
        y *= this.left.hashCode();
      }
      int z = 7;
      if (this.right != null) {
        z *= this.right.hashCode();
      }
      result = x + y + z;
      this.cachedHash = result;
      // @exclude
      p(name + " hashed to " + result );
      // @include
      return result;
    }

    @Override
    public boolean equals(Object o) {
      if (o == this) {
       return true;
      }
      if (!(o instanceof BinaryTreeNode)) {
        return false;
      }
      BinaryTreeNode n = (BinaryTreeNode)o;

      // @exclude
      p("This is " + this.toString() );
      p("n is " + n.toString() );
      // @include
      boolean result = false;
      if (n == null) {
        result = false;
      } else if (key != n.key) {
        result = false;
      } else {
        // Assuming that equals is called on nodes
        // where children are already in canonical form
        result = (left == n.left && right == n.right);
      }
      // @exclude
      p("result is "  + result);
      // @include
      return result;
    }

    // @exclude
    void print() {
      print("");
    }

    void print(String s) {
      System.out.println( s + "\t" + this.toString() );
    }

    @Override
    public String toString() {
      return "Name:" + name + "---" + new Integer( key ).toString() + "\n\t"
      	+ ( (left != null ) ? left.toString() : "l:null" ) + "\n\t"
        + ( (right != null) ? right.toString() : "r:null" ) ;
    }
  }

  static Map<Object, Integer> nodeToHashCache =
      new HashMap<Object, Integer>();

  // @include
  static Map<BinaryTreeNode, BinaryTreeNode> nodeToCanonicalNode =
    new HashMap<BinaryTreeNode, BinaryTreeNode>();

  static BinaryTreeNode getCanonical(BinaryTreeNode n) {
    BinaryTreeNode lc = (n.left == null) ? null : getCanonical(n.left);
    BinaryTreeNode rc = (n.right == null) ? null : getCanonical(n.right);
    BinaryTreeNode nc = new BinaryTreeNode(n.key, n.name, lc, rc);
    BinaryTreeNode result = null;

    if (nodeToCanonicalNode.containsKey(nc)) {
      result = nodeToCanonicalNode.get(nc);
      // @exclude
      p("check to see if " + nc.name + " was present---YES");
      // @include
    } else {
      // @exclude
      // nodeToHashCache.put( (Object) nc, new Integer( nc.hashCode() ) );
      // @include
      nodeToCanonicalNode.put(nc, nc);
      // @exclude
      p("check to see if " + nc.name + " was present---NO");
      // @include
      result = nc;
    }
    return result;
  }
  // @exclude

  static public void main( String [] args ) {

    BinaryTreeNode a = new BinaryTreeNode( 1, "a", null, null );
    BinaryTreeNode b = new BinaryTreeNode( 2, "b", null, null );
    BinaryTreeNode c = new BinaryTreeNode( 3, "c", null, null );
    BinaryTreeNode d = new BinaryTreeNode( 2, "d", null, null );
    BinaryTreeNode e = new BinaryTreeNode( 3, "e", null, null );
    BinaryTreeNode f = new BinaryTreeNode( 1, "f", null, null );

    BinaryTreeNode bDup = new BinaryTreeNode( 2, "bdup", null, null );
    Set<BinaryTreeNode> aSet = new HashSet<BinaryTreeNode>();
    aSet.add( b );
    if ( !aSet.contains( bDup ) ) {
      p("problem with lookup");
    }

    a.left = b;
    a.right = c;
    d.left = b;
    d.right = e;
    f.left = b;
    f.right = c;

    System.out.println("a == f ? " + a.equals( f ) );
    BinaryTreeNode t1 = getCanonical(a);
    BinaryTreeNode t2 = getCanonical(d);
    t1.print( "t1" );
    t2.print( "t2" );
    p("-----");

    List<BinaryTreeNode> Alist = new LinkedList<BinaryTreeNode>();
    Alist.add( a );
    Alist.add( b );
    Alist.add( c );
    Alist.add( d );
    Alist.add( e );
    Alist.add( f );

    List<BinaryTreeNode> Blist = new LinkedList<BinaryTreeNode>();
    for ( BinaryTreeNode n : Alist ) {
      BinaryTreeNode cn = getCanonical( n );
      cn.print();
      Blist.add( cn );
    }
    p("nodeToCanonicalNode hash size:" + nodeToCanonicalNode.size() );
    // */
  }
}
