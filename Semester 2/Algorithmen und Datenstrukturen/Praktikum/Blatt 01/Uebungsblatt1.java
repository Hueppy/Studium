import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Timer;
import java.util.stream.Collectors;

public class Uebungsblatt1 {
    private static class MaxTeilsumme {
        List<Integer> set;
        int firstIndex;
        int lastIndex;
        int sum;
        long additions;

        private MaxTeilsumme(List<Integer> set) {
            this.set = set;
            this.sum = Integer.MIN_VALUE;
            this.additions = 0;
        }

        public static MaxTeilsumme calculate(List<Integer> set) {
            final MaxTeilsumme result = new MaxTeilsumme(set);
            final int length = set.size();

            for (int i = 0; i < length; i++) {
                for (int j = i; j < length; j++) {
                    int sum = 0;
                    for (int k = i; k <= j; k++) {
                        sum += set.get(k);
                        result.additions++;
                    }
                    if (sum > result.sum) {
                        result.sum = sum;
                        result.firstIndex = i;
                        result.lastIndex = j;
                    }
                }
            }

            return result;
        }

        public List<Integer> getSet() {
            return set;
        }

        public int getFirstIndex() {
            return firstIndex;
        }

        public int getLastIndex() {
            return lastIndex;
        }

        public int getSum() {
            return sum;
        }

        public long getAdditions() {
            return additions;
        }
    }

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        System.out.print("Dateiname: ");
        final String filename = sc.next();

        System.out.println(Path.of(filename).toAbsolutePath().toString());

        List<Integer> set;
        try (BufferedReader file = new BufferedReader(new FileReader(filename))) {
            set = file.lines().map((s) -> Integer.parseInt(s)).collect(Collectors.toList());
        }

        long start = System.nanoTime();
        MaxTeilsumme result = MaxTeilsumme.calculate(set);// ...
        long finish = System.nanoTime();
        double timeElapsed = (finish - start) / 1_000_000_000f;
        System.out.printf("Max. Teilsumme: %d\n", result.getSum());
        System.out.printf("Erster Index: %d\n", result.getFirstIndex());
        System.out.printf("Letzer Index: %d\n", result.getLastIndex());
        System.out.printf("Zeit in Sekunden: %f\n", timeElapsed);
        System.out.printf("Additionen: %d\n", result.getAdditions());
    }
}
