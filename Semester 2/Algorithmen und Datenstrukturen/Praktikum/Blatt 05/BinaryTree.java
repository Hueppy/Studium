package uebungsblatt5;

public class BinaryTree<T> {
  private BinaryTree<T> _left;
  private T _value;
  private BinaryTree<T> _right;

  public BinaryTree(BinaryTree<T> left, T value, BinaryTree<T> right) {
    this._left = left;
    this._value = value;
    this._right = right;
  }

  public static <T> boolean isEmpty(BinaryTree<T> tree) {
    return tree == null;
  }

  public static <T> BinaryTree<T> left(BinaryTree<T> tree) {
    return tree._left;
  }

  public static <T> BinaryTree<T> right(BinaryTree<T> tree) {
    return tree._right;
  }

  public static <T> T value(BinaryTree<T> tree) {
    if (tree == null) {
      return null;
    } else {
      return tree._value;
    }
  }
}
