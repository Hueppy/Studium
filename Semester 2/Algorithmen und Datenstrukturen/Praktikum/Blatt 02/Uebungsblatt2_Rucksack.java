public class Uebungsblatt2_Rucksack {
    private static class Item {
        private int gewicht;
        private int wert;

        public Item(int gewicht, int wert) {
            this.gewicht = gewicht;
            this.wert = wert;
        }

        public int getGewicht() {
            return gewicht;
        }

        public int getWert() {
            return wert;
        }
    }

    private static class Rucksack {
        private int wert = 0;
        private int maxCalls = 0;
        private int loopCount = 0;

        private Rucksack() {
        }

        private static Rucksack run(Item[] items, int c) {
            final Rucksack result = new Rucksack();

            final int n = items.length - 1;
            final int[][] f = new int[n + 1][c + 1];

            for (int rk = 0; rk <= c; rk++) {
                if (rk < items[n].getGewicht()) {
                    f[n][rk] = 0;
                } else {
                    f[n][rk] = items[n].getWert();
                }
            }

            for (int i = n - 1; i >= 0; i--) {
                for (int rk = 0; rk <= c; rk++) {
                    result.loopCount++;
                    if (rk < items[i].getGewicht()) {
                        f[i][rk] = f[i + 1][rk];
                    } else {
                        result.maxCalls++;
                        f[i][rk] = Math.max(
                                f[i + 1][rk],
                                f[i + 1][rk - items[i].getGewicht()] + items[i].getWert()
                        );
                    }
                }
            }

            result.wert = f[0][c];
            return result;
        }

        public int getWert() {
            return wert;
        }

        public int getMaxCalls() {
            return maxCalls;
        }

        public int getLoopCount() {
            return loopCount;
        }
    }

    private static class RucksackBack {
        private int wert = 0;
        private int calls = 0;

        private RucksackBack(int wert, int calls) {
            this.wert = wert;
            this.calls = calls;
        }

        public int getWert() {
            return wert;
        }

        public int getCalls() {
            return calls;
        }

        public static RucksackBack run(Item[] items, int i, int rest) {
            if (i + 1 == items.length) {
                if (rest < items[i].getGewicht()) {
                    return new RucksackBack(0, 0);
                } else {
                    return new RucksackBack(items[i].getWert(), 0);
                }
            } else {
                if (rest < items[i].getGewicht()) {
                    return run(items, i + 1, rest);
                } else {
                    RucksackBack a = run(items, i + 1, rest);
                    RucksackBack b = run(items, i + 1, rest - items[i].getGewicht());
                    return new RucksackBack(
                            Math.max(a.wert, b.wert + items[i].getWert()),
                            a.calls + b.calls + 1
                    );
                }
            }

        }
    }

    public static void main(String[] args) {
        final Item[] items1 = new Item[]{
                new Item(2, 6),
                new Item(2, 3),
                new Item(6, 5),
                new Item(5, 4),
                new Item(4, 6),
        };
        final Item[] items2 = new Item[]{
                new Item(2, 10),
                new Item(10, 3),
                new Item(7, 1),
                new Item(9, 9),
                new Item(2, 5),
                new Item(2, 8),
                new Item(5, 2),
                new Item(10, 5),
                new Item(8, 4),
                new Item(8, 5),
                new Item(6, 10),
                new Item(3, 3),
                new Item(6, 8),
                new Item(3, 2),
                new Item(6, 8),
                new Item(3, 4),
                new Item(8, 4),
                new Item(4, 10),
                new Item(7, 9),
                new Item(4, 8)
        };
        final Item[] items3 = new Item[]{
                new Item(6, 1),
                new Item(9, 1),
                new Item(4, 9),
                new Item(4, 4),
                new Item(3, 2),
                new Item(7, 10),
                new Item(9, 5),
                new Item(10, 1),
                new Item(8, 5),
                new Item(4, 4),
                new Item(6, 6),
                new Item(1, 3),
                new Item(4, 7),
                new Item(3, 4),
                new Item(2, 6),
                new Item(9, 1),
                new Item(9, 1),
                new Item(10, 4),
                new Item(7, 2),
                new Item(9, 2),
                new Item(1, 5),
                new Item(3, 6),
                new Item(8, 5),
                new Item(2, 6),
                new Item(9, 8),
                new Item(4, 7),
                new Item(10, 3),
                new Item(9, 5),
                new Item(2, 5),
                new Item(4, 8),
                new Item(3, 1),
                new Item(5, 2),
                new Item(3, 1),
                new Item(6, 10),
                new Item(7, 1),
                new Item(2, 9),
                new Item(10, 3),
                new Item(6, 9),
                new Item(3, 10),
                new Item(9, 4),
                new Item(4, 10),
                new Item(4, 1),
                new Item(5, 3),
                new Item(7, 3),
                new Item(4, 10),
                new Item(3, 7),
                new Item(10, 3),
                new Item(8, 7),
                new Item(6, 4),
                new Item(8, 7),
                new Item(1, 4),
                new Item(9, 1),
                new Item(3, 6),
                new Item(3, 4),
                new Item(5, 10),
                new Item(5, 2),
                new Item(2, 4),
                new Item(6, 4),
                new Item(9, 3),
                new Item(1, 10),
                new Item(4, 2),
                new Item(5, 5),
                new Item(1, 9),
                new Item(6, 1),
                new Item(6, 3),
                new Item(6, 8),
                new Item(8, 4),
                new Item(7, 7),
                new Item(3, 1),
                new Item(8, 1),
                new Item(1, 6),
                new Item(10, 4),
                new Item(3, 5),
                new Item(4, 6),
                new Item(4, 2),
                new Item(3, 4),
                new Item(9, 9),
                new Item(4, 9),
                new Item(7, 10),
                new Item(5, 5),
                new Item(1, 2),
                new Item(4, 3),
                new Item(9, 3),
                new Item(8, 6),
                new Item(1, 9),
                new Item(7, 3),
                new Item(7, 9),
                new Item(4, 6),
                new Item(3, 5),
                new Item(2, 2),
                new Item(6, 1),
                new Item(3, 7),
                new Item(9, 5),
                new Item(6, 4),
                new Item(3, 6),
                new Item(2, 6),
                new Item(3, 3),
                new Item(6, 5),
                new Item(10, 6),
                new Item(8, 6)
        };

        long start = System.nanoTime();
        Rucksack r = Rucksack.run(items3, 10);
        long finish = System.nanoTime();
        double timeElapsed = (finish - start) / 1_000_000_000f;
        System.out.println("Alogrithmus I");
        System.out.printf("Maximaler Wert: %d\n", r.getWert());
        System.out.printf("Schleifendurchläufe: %d\n", r.getLoopCount());
        System.out.printf("max() Aufrufe: %d\n", r.getMaxCalls());
        System.out.printf("Zeit in Sekunden: %f\n", timeElapsed);

        start = System.nanoTime();
        RucksackBack rb = RucksackBack.run(items3, 0, 10);
        finish = System.nanoTime();
        timeElapsed = (finish - start) / 1_000_000_000f;
        System.out.println("Alogrithmus II - Backtracking");
        System.out.printf("Maximaler Wert: %d\n", rb.getWert());
        System.out.printf("max() Aufrufe: %d\n", rb.getCalls());
        System.out.printf("Zeit in Sekunden: %f\n", timeElapsed);
    }
}
