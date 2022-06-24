package uebungsblatt5;

import java.util.Scanner;
import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.util.function.Function;

public class SearchTree<T extends Comparable<T>> {
  private BinaryTree<T> root;

  public SearchTree() {

  }

  private BinaryTree<T> add(BinaryTree<T> tree, T value) {
    if (BinaryTree.isEmpty(tree)) {
      return new BinaryTree<>(null, value, null);
    }
    int comparison = BinaryTree.value(tree).compareTo(value);
    if (comparison > 0) {
      return new BinaryTree<>(
              add(BinaryTree.left(tree), value),
              BinaryTree.value(tree),
              BinaryTree.right(tree)
      );
    } else if (comparison < 0) {
      return new BinaryTree<>(
              BinaryTree.left(tree),
              BinaryTree.value(tree),
              add(BinaryTree.right(tree), value)
      );
    } else {
      return tree;
    }
  }

  private BinaryTree<T> delete(BinaryTree<T> tree, T value) {
    if (BinaryTree.isEmpty(tree)) {
      return null;
    }
    int comparison = BinaryTree.value(tree).compareTo(value);
    if (comparison > 0) {
      return new BinaryTree<>(
              delete(BinaryTree.left(tree), value),
              BinaryTree.value(tree),
              BinaryTree.right(tree)
      );
    } else if (comparison < 0) {
      return new BinaryTree<>(
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
      return new BinaryTree<T>(
              BinaryTree.left(tree),
              subValue,
              delete(BinaryTree.right(tree), subValue)
      );
    }
  }

  private static String nodeToString(BinaryTree tree, int height) {
    if (tree == null) {
      return "null";
    } else {
      return String.format("(%d, %s)", height, BinaryTree.value(tree));
    }
  }

  private static void output(BinaryTree tree, Integer height) {
    BinaryTree left = BinaryTree.left(tree);
    BinaryTree right = BinaryTree.right(tree);

    System.out.printf("%s : %s, %s\n",
            nodeToString(tree, height),
            nodeToString(left,  height + 1),
            nodeToString(right, height + 1)
    );
  }

  public void preorder(BinaryTree<T> tree, int height, BiConsumer<BinaryTree<T>, Integer> processor) {
    if (BinaryTree.isEmpty(tree)) {
      return;
    }
    processor.accept(tree, height);
    preorder(BinaryTree.left(tree), height + 1, processor);
    preorder(BinaryTree.right(tree), height + 1, processor);
  }

  public void inorder(BinaryTree<T> tree, int height, BiConsumer<BinaryTree<T>, Integer> processor) {
    if (BinaryTree.isEmpty(tree)) {
      return;
    }
    inorder(BinaryTree.left(tree), height + 1, processor);
    processor.accept(tree, height);
    inorder(BinaryTree.right(tree), height + 1, processor);
  }

  public void add(T value) {
    root = add(root, value);
  }

  public void delete(T value) {
    root = delete(root, value);
  }

  public void modify(T oldValue, T newValue) {
    root = add(delete(root, oldValue), newValue);
  }

  public void output() {
    preorder(root, 0, SearchTree::output);
  }

  public void outputInorder() {
    inorder(root, 0, SearchTree::output);
  }

  public static void main(String[] args) {
    SearchTree<Integer> tree = new SearchTree<>();

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
        case "I":
          tree.outputInorder();
          break;
      }
    } while (!query.isBlank());
  }
}
