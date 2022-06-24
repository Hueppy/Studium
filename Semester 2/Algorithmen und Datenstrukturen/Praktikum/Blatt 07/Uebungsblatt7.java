import java.sql.SQLOutput;
import java.util.Queue;
import java.util.Scanner;

public class Uebungsblatt7 {
    public static class LinkedList<T> {
        public class Node {
            private final T value;
            private Node next;

            public Node(T value) {
                this.value = value;
            }

            public Node getNext() {
                return next;
            }

            public void setNext(Node next) {
                this.next = next;
            }

            public T getValue() {
                return value;
            }
        }

        private Node head;

        public Node getHead() {
            return head;
        }

        public void setHead(Node head) {
            this.head = head;
        }
    }

    public static class Stack<T> extends LinkedList<T> {
        public void push(T value) {
            Node n = new Node(value);
            n.setNext(getHead());
            setHead(n);
        }

        public T pop() {
            Node n = getHead();
            if (n == null) {
                return null;
            }

            setHead(n.getNext());
            return n.getValue();
        }

        public T top() {
            Node n = getHead();
            if (n == null) {
                return null;
            }

            return n.getValue();
        }

        public boolean isEmpty() {
            return getHead() == null;
        }
    }

    public static class Queue<T> {
        private final Object[] buffer;
        private int front;
        private int back;
        private boolean full;

        public Queue(int length) {
            this.buffer = new Object[length];
            front = 0;
            back = 0;
        }

        public void enqueue(T value) {
            if (full) {
                return;
            }

            buffer[back] = value;
            back = (back + 1) % buffer.length;
            if (back == front) {
                full = true;
            }
        }

        public T dequeue() {
            Object value = buffer[front];
            if (full && front == back) {
                full = false;
            }
            front = (front + 1) % buffer.length;
            return (T)value;
        }

        public boolean isEmpty() {
            return !full && front == back;
        }
    }

    public static void print(LinkedList<String> list) {
        LinkedList<String>.Node n = list.getHead();
        while (n != null) {
            System.out.println(n.getValue());
            n = n.getNext();
        }
    }

    public static void mainStack() {
        Stack<String> stack = new Stack<>();

        Scanner sc = new Scanner(System.in);
        String query;
        do {
            System.out.println("<A> Element einfügen");
            System.out.println("<E> Element entfernen");
            System.out.println("<T> Element ausgeben");
            System.out.println("<O> Elemente ausgeben");
            System.out.println("<L> Ist Stack leer?");
            System.out.println("<Q> Beenden");

            query = sc.next().toLowerCase();

            if (query.startsWith("a")) {
                System.out.print("Element: ");
                stack.push(sc.next());
            } else if (query.startsWith("e")) {
                System.out.print("Element: ");
                System.out.println(stack.pop());
            } else if (query.startsWith("t")) {
                System.out.print("Element: ");
                System.out.println(stack.top());
            } else if (query.startsWith("o")) {
                print(stack);
            } else if (query.startsWith("l")) {
                System.out.println(stack.isEmpty());
            }

        } while (!query.startsWith("q"));
    }

    public static void print(Queue<String> queue) {
        if (queue.front < queue.back) {
            for (int i = queue.front; i < queue.back; i++) {
                System.out.println(queue.buffer[i]);
            }
        } else {
            for (int i = queue.front; i < queue.buffer.length; i++) {
                System.out.println(queue.buffer[i]);
            }
            for (int i = 0; i < queue.back; i++) {
                System.out.println(queue.buffer[i]);
            }
        }
    }

    public static void mainQueue() {
        Queue<String> queue = new Queue<>(10);

        Scanner sc = new Scanner(System.in);
        String query;
        do {
            System.out.println("<A> Element einfügen");
            System.out.println("<E> Element entfernen");
            System.out.println("<O> Elemente ausgeben");
            System.out.println("<L> Ist Queue leer?");
            System.out.println("<Q> Beenden");

            query = sc.next().toLowerCase();

            if (query.startsWith("a")) {
                System.out.print("Element: ");
                queue.enqueue(sc.next());
            } else if (query.startsWith("e")) {
                System.out.print("Element: ");
                System.out.println(queue.dequeue());
            } else if (query.startsWith("o")) {
                print(queue);
            } else if (query.startsWith("l")) {
                System.out.println(queue.isEmpty());
            }

        } while (!query.startsWith("q"));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("<S> Stack");
        System.out.println("<Q> Queue");

        String query = sc.next().toLowerCase();

        if (query.startsWith("s")) {
            mainStack();
        } else if (query.startsWith("q")) {
            mainQueue();
        }
    }
}
