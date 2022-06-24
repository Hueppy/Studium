import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Uebungsblatt9 {
    public static class Heap<T extends Comparable<T>> {
        private T[] data;

        public Heap(T[] data) {
            this.data = data;

            int last = getLast();

            for (int i = last / 2; i >= 0; i--){
                heapify(i, data.length - 1);
            }
        }

        private int getLast() {
            int i = 0;

            while (i < data.length && data[i] != null) {
                i++;
            }

            return i - 1;
        }

        private static <T extends Comparable<T>> void swap(T[] data, int i, int j) {
            T temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }

        private void swap(int i, int j) {
            swap(data, i, j);
        }

        private static <T extends Comparable<T>> int compare(T[] data, int i, int j) {
            T a = data[i];
            T b = data[j];

            if (a == null) {
                return 1;
            } else if (b == null) {
                return -1;
            } else {
                return a.compareTo(b);
            }
        }

        private int compare(int i, int j) {
            return compare(data, i, j);
        }

        private static <T extends Comparable<T>> void heapify(T[] data, int low, int high) {
            int i = low;

            int left = 2 * low + 1;
            if (left < high && compare(data, left, i) < 0) {
                i = left;
            }

            int right = left + 1;
            if (right <= high && compare(data, right, i) < 0) {
                i = right;
            }

            if (i != low) {
                swap(data, low, i);
                heapify(data, i, high);
            }
        }

        private void heapify(int low, int high) {
            heapify(data, low, high);
        }

        public void add(T value) {
            int i = getLast() + 1;

            if (i < data.length) {
                data[i] = value;
                int parent = (i - 1) / 2;
                while (i > 0 && compare(i, parent) < 0) {
                    swap(i, parent);
                    i = parent;
                    parent = (i - 1) / 2;
                }
            }
        }

        public void delete() {
            int i = getLast();
            data[0] = data[i];
            data[i] = null;

            heapify(0, data.length - 1);
        }

        public T[] sort() {
            int last = getLast();

            for (int i = last / 2; i >= 0; i--){
                heapify(i, data.length - 1);
            }

            T[] sorted = Arrays.copyOf(data, data.length);

            for (int i = sorted.length - 1; i >= 0; i--) {
                swap(sorted, 0, i);
                heapify(sorted, 0, i);
            }

            return Arrays.copyOfRange(sorted, sorted.length - last - 1, sorted.length);
        }

        public Object[] getData() {
            return data;
        }
    }

    private static Integer[] getNumbers() {
        List<Integer> numbers = new ArrayList<>();

        try {
            FileInputStream file = new FileInputStream("numbers.txt");
            Scanner sc = new Scanner(file);

            while (sc.hasNext()) {
                numbers.add(sc.nextInt());
            }
        } catch (FileNotFoundException e) {
            System.out.println("Datei nicht gefunden");
        }

        return numbers.toArray(new Integer[numbers.size() * 2]);
    }

    public static void main(String[] args) {
        Heap<Integer> heap = new Heap<>(getNumbers());

        Scanner sc = new Scanner(System.in);
        String query = "";

        do {
            System.out.println("e : Einfügen eins Elements in den Heap");
            System.out.println("l : Löschen des kleinsten Elements aus dem Heap");
            System.out.println("s : sortiertes Ausgeben des Heaps (= HeapSort durchführen)");
            System.out.println("a : Ausgeben des Arrays");
            System.out.println("n : erneutes Einlesen der Datei");

            query = sc.next().toLowerCase();
            switch (query) {
                case "e":
                    System.out.print("Zahl: ");
                    int num = sc.nextInt();
                    heap.add(num);
                    break;
                case "l":
                    heap.delete();
                    break;
                case "s":
                    System.out.println(Arrays.toString(heap.sort()));
                    break;
                case "a":
                    System.out.println(Arrays.toString(heap.getData()));
                    break;
                case "n":
                    heap = new Heap<>(getNumbers());
                    break;
            }
        } while (!query.isEmpty());
    }

}
