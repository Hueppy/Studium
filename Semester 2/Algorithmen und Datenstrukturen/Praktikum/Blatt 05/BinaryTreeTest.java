package uebungsblatt5;

import org.junit.Assert;
import org.junit.Test;
import static org.junit.Assert.*;

public class BinaryTreeTest {
  @Test
  public void testLeft() {
    BinaryTree<Integer> x = new BinaryTree<>(null, 1, null);
    BinaryTree<Integer> y = new BinaryTree<>(null, 2, null);
    Integer value = 3;
    BinaryTree<Integer> tree = new BinaryTree<>(x, value, y);

    Assert.assertEquals(BinaryTree.left(tree), x);
  }

  @Test
  public void testRight() {
    BinaryTree<Integer> x = new BinaryTree<>(null, 1, null);
    BinaryTree<Integer> y = new BinaryTree<>(null, 2, null);
    Integer value = 3;
    BinaryTree<Integer> tree = new BinaryTree<>(x, value, y);

    Assert.assertEquals(BinaryTree.right(tree), y);
  }

  @Test
  public void testValue() {
    BinaryTree<Integer> x = new BinaryTree<>(null, 1, null);
    BinaryTree<Integer> y = new BinaryTree<>(null, 2, null);
    Integer value = 3;
    BinaryTree<Integer> tree = new BinaryTree<>(x, value, y);

    Assert.assertEquals(BinaryTree.value(tree), value);
  }

  @Test
  public void testIsEmptyNull() {
    Assert.assertTrue(BinaryTree.isEmpty(null));
  }

  @Test
  public void testIsEmpty() {
    BinaryTree<Integer> x = new BinaryTree<>(null, 1, null);
    BinaryTree<Integer> y = new BinaryTree<>(null, 2, null);
    Integer value = 3;
    BinaryTree<Integer> tree = new BinaryTree<>(x, value, y);

    Assert.assertFalse(BinaryTree.isEmpty(tree));
  }
}