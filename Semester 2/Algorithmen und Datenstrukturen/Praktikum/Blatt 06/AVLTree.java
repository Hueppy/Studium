package uebeungsblatt6;

import java.util.Scanner;
import java.util.function.Consumer;

/** Klasse für den AVL Baum */
public class AVLTree<T extends Comparable> {
  private BinaryTree<T> root;

  public BinaryTree<T> getRoot() {
    return root;
  }

  private static int height(BinaryTree tree) {
    if (tree == null) {
      return -1;
    } else {
      return 1 + Math.max(height(BinaryTree.left(tree)), height(BinaryTree.right(tree)));
    }
  }

  private static int balance(BinaryTree tree) {
    return height(BinaryTree.left(tree)) - height(BinaryTree.right(tree));
  }

  private BinaryTree<T> rotateLeft(BinaryTree<T> parent) {
    BinaryTree<T> left = BinaryTree.left(parent);

    return new BinaryTree<>(
            BinaryTree.left(left),
            BinaryTree.value(left),
            new BinaryTree<>(
                    BinaryTree.right(left),
                    BinaryTree.value(parent),
                    BinaryTree.right(parent)
            )
    );
  }

  private BinaryTree<T> rotateRight(BinaryTree<T> parent) {
    BinaryTree<T> right = BinaryTree.right(parent);

    return new BinaryTree<>(
            new BinaryTree<>(
                    BinaryTree.left(right),
                    BinaryTree.value(parent),
                    BinaryTree.left(parent)
            ),
            BinaryTree.value(right),
            BinaryTree.right(right)
    );
  }

  /** "Normalisiert" den Baum, also führt, wenn nötig, die Rotierung durch */
  private BinaryTree<T> normalize(BinaryTree<T> tree) {
    BinaryTree<T> result = tree;

    int balance = balance(result);

    if (balance > 1) {
      int left_balance = balance(BinaryTree.left(result));
      if (left_balance > 0) {
        result = rotateLeft(result);
      } else {
        result = new BinaryTree<>(
                rotateRight(BinaryTree.left(result)),
                BinaryTree.value(result),
                BinaryTree.right(result)
        );
        result = rotateLeft(result);
      }
    } else if (balance < -1) {
      int right_balance = balance(BinaryTree.left(result));
      if (right_balance < 0) {
        result = rotateRight(result);
      } else {
        result = new BinaryTree<>(
                BinaryTree.left(result),
                BinaryTree.value(result),
                rotateLeft(BinaryTree.right(result))
        );
        result = rotateRight(result);
      }
    }

    return result;
  }

  private BinaryTree<T> add(BinaryTree<T> tree, T value) {
    if (tree == null) {
      return new BinaryTree<>(null, value, null);
    }

    BinaryTree<T> result;

    int comparison = BinaryTree.value(tree).compareTo(value);
    if (comparison > 0) {
      result = new BinaryTree<>(
              add(BinaryTree.left(tree), value),
              BinaryTree.value(tree),
              BinaryTree.right(tree)
      );
    } else if (comparison < 0) {
      result = new BinaryTree<>(
              BinaryTree.left(tree),
              BinaryTree.value(tree),
              add(BinaryTree.right(tree), value)
      );
    } else {
      return tree;
    }

    return normalize(result);
  }

  private BinaryTree<T> delete(BinaryTree<T> tree, T value) {
    if (BinaryTree.isEmpty(tree)) {
      return null;
    }
    int comparison = BinaryTree.value(tree).compareTo(value);
    BinaryTree<T> result;
    if (comparison > 0) {
      result = new BinaryTree<>(
              delete(BinaryTree.left(tree), value),
              BinaryTree.value(tree),
              BinaryTree.right(tree)
      );
    } else if (comparison < 0) {
      result = new BinaryTree<>(
              BinaryTree.left(tree),
              BinaryTree.value(tree),
              delete(BinaryTree.right(tree), value)
      );
    } else {
      if (BinaryTree.isEmpty(BinaryTree.right(tree))
              && BinaryTree.isEmpty(BinaryTree.right(tree))) {
        return null;
      }

      BinaryTree<T> subTree = BinaryTree.right(tree);
      BinaryTree<T> left = BinaryTree.left(subTree);
      while (!BinaryTree.isEmpty(left)) {
        subTree = left;
        left = BinaryTree.left(subTree);
      }

      T subValue = BinaryTree.value(subTree);
      result = new BinaryTree<T>(
              BinaryTree.left(tree),
              subValue,
              delete(BinaryTree.right(tree), subValue)
      );
    }

    return normalize(result);
  }

  public void preorder(BinaryTree<T> tree, Consumer<BinaryTree> processor) {
    if (BinaryTree.isEmpty(tree)) {
      return;
    }
    processor.accept(tree);
    preorder(BinaryTree.left(tree), processor);
    preorder(BinaryTree.right(tree), processor);
  }

  private static String nodeToString(BinaryTree tree) {
    if (tree == null) {
      return "null";
    } else {
      return String.format("%s(%d, %s)", BinaryTree.value(tree), height(tree), balance(tree));
    }
  }

  private static void output(BinaryTree tree) {
    BinaryTree left = BinaryTree.left(tree);
    BinaryTree right = BinaryTree.right(tree);

    System.out.printf("%s : %s, %s\n",
            nodeToString(tree),
            nodeToString(left),
            nodeToString(right)
    );
  }

  public void output() {
    preorder(root, AVLTree::output);
  }

  /** Fügt ein Wert zu dem Baum hinzu */
  public void add(T value) {
    root = add(root, value);
  }

  /** Löscht ein Wert aus dem Baum */
  public void delete(T value) {
    root = delete(root, value);
  }

  /** Ändert den Wert eines Elements im Baum */
  public void modify(T oldValue, T newValue) {
    root = add(delete(root, oldValue), newValue);
  }

  public static void main(String[] args) {
    AVLTree<Integer> tree = new AVLTree<>();

    Scanner sc = new Scanner(System.in);
    String query = "";
    do {
      System.out.println("<E> Wert einfügen");
      System.out.println("<L> Wert löschen");
      System.out.println("<M> Wert modifizieren");
      System.out.println("<A> Baumausgabe");
      System.out.println("<I> Inorder Baumausgabe");

      int value;

      query = sc.next().toUpperCase();
      switch (query) {
        case "E":
          System.out.print("Wert: ");
          value = sc.nextInt();
          tree.add(value);
          break;
        case "L":
          System.out.print("Wert: ");
          value = sc.nextInt();
          tree.delete(value);
          break;
        case "M":
          System.out.print("Alter Wert: ");
          int oldValue = sc.nextInt();
          System.out.print("Neuer Wert: ");
          int newValue = sc.nextInt();
          tree.modify(oldValue, newValue);
          break;
        case "A":
          tree.output();
          break;
      }
    } while (!query.isBlank());
  }

}
