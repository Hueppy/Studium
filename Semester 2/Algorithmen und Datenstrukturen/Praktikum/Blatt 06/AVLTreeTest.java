package uebeungsblatt6;

import org.junit.Assert;
import org.junit.Test;
import static org.junit.Assert.*;

public class AVLTreeTest {

  @Test
  public void testAdd() {
    AVLTree<Integer> tree = new AVLTree<>();
    tree.add(1);
    tree.add(3);
    tree.add(2);

    Assert.assertEquals(BinaryTree.value(tree.getRoot()), Integer.valueOf(2));
    Assert.assertEquals(BinaryTree.value(BinaryTree.left(tree.getRoot())), Integer.valueOf(1));
    Assert.assertEquals(BinaryTree.value(BinaryTree.right(tree.getRoot())), Integer.valueOf(3));
  }

  @Test
  public void testDelete() {
    AVLTree<Integer> tree = new AVLTree<>();
    tree.add(2);
    tree.add(1);
    tree.add(4);
    tree.add(3);
    tree.delete(1);

    Assert.assertEquals(BinaryTree.value(tree.getRoot()), Integer.valueOf(3));
    Assert.assertEquals(BinaryTree.value(BinaryTree.left(tree.getRoot())), Integer.valueOf(2));
    Assert.assertEquals(BinaryTree.value(BinaryTree.right(tree.getRoot())), Integer.valueOf(4));
  }

  @Test
  public void testModify() {
    AVLTree<Integer> tree = new AVLTree<>();
    tree.add(2);
    tree.add(3);
    tree.modify(3, 1);

    Assert.assertEquals(BinaryTree.value(tree.getRoot()), Integer.valueOf(2));
    Assert.assertEquals(BinaryTree.value(BinaryTree.left(tree.getRoot())), Integer.valueOf(1));
  }
}