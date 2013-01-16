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
    BinaryTreeNode left, right;
    Integer cachedHash;

    public BinaryTreeNode(int k, BinaryTreeNode l, BinaryTreeNode r) {
      this.key = k;
      this.left = l;
      this.right = r;
      this.cachedHash = null;
    }

    @Override
    public int hashCode() {
      // @exclude
      System.out.println("Calling overridden hashCode");
      // @include
      if (this.cachedHash != null) {
        // @exclude
        p("result from cache:" + this.cachedHash);
        // @include
        return this.cachedHash;
      }

      int x = 3 * key;
      int y = this.left == null ? 5 : 5 * this.left.hashCode();
      int z = this.right == null ? 7 : 7 * this.right.hashCode();
      this.cachedHash = x + y + z;
      return this.cachedHash;
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

      if (n == null || key != n.key) {
        return false;
      }
      // @exclude
      p("result is "  + (left == n.left && right == n.right));
      // @include
      // Assuming that equals is called on nodes
      // where children are already in canonical form
      return (left == n.left && right == n.right);
    }
  }

  // @exclude

  static Map<Object, Integer> nodeToHashCache = new HashMap<Object, Integer>();

  // @include
  static Map<BinaryTreeNode, BinaryTreeNode> nodeToCanonicalNode =
    new HashMap<BinaryTreeNode, BinaryTreeNode>();

  static BinaryTreeNode getCanonical(BinaryTreeNode n) {
    BinaryTreeNode lc = (n.left == null) ? null : getCanonical(n.left);
    BinaryTreeNode rc = (n.right == null) ? null : getCanonical(n.right);
    BinaryTreeNode nc = new BinaryTreeNode(n.key, lc, rc);

    if (nodeToCanonicalNode.containsKey(nc)) {
      return nodeToCanonicalNode.get(nc);
    }
    // @exclude
    // nodeToHashCache.put( (Object) nc, new Integer( nc.hashCode() ) );
    // @include
    nodeToCanonicalNode.put(nc, nc);
    return nc;
  }
  // @exclude

  static public void main( String [] args ) {

    BinaryTreeNode a = new BinaryTreeNode( 1, null, null );
    BinaryTreeNode b = new BinaryTreeNode( 2, null, null );
    BinaryTreeNode c = new BinaryTreeNode( 3, null, null );
    BinaryTreeNode d = new BinaryTreeNode( 2, null, null );
    BinaryTreeNode e = new BinaryTreeNode( 3, null, null );
    BinaryTreeNode f = new BinaryTreeNode( 1, null, null );

    BinaryTreeNode bDup = new BinaryTreeNode( 2, null, null );
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
      Blist.add( cn );
    }
    p("nodeToCanonicalNode hash size:" + nodeToCanonicalNode.size() );
    // */
  }
}
