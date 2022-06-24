import java.lang.reflect.Array;
import java.util.Arrays;

public class Uebungsblatt2_Damen {
    private enum Feld {
        Frei,
        Konflikt,
        Dame
    }

    private static Feld[][] damenproblem(int n) {
        Feld[][] brett = new Feld[n][n];
        for (int i = 0; i < n; i++) {
            Arrays.fill(brett[i], Feld.Frei);
        }

        platziereDame(brett, n, n);

        return brett;
    }

    private static boolean platziereDame(Feld[][] brett, int n, int dame) {
        for (int i = 0; i < brett.length; i++) {
            for (int j = 0; j < brett[i].length; j++) {
                if (platziereDame(brett, n, dame, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    private static void copyFeld(Feld[][] src, Feld[][] dst) {
        for (int i = 0; i < src.length; i++) {
            for (int j = 0; j < src[i].length; j++) {
                dst[i][j] = src[i][j];
            }
        }
    }

    private static boolean platziereDame(Feld[][] brett, int n, int dame, int zeile, int spalte) {
        if (brett[zeile][spalte] != Feld.Frei) {
            return false;
        }

        Feld[][] neuesBrett = new Feld[n][n];
        copyFeld(brett, neuesBrett);

        for (int i = 0; i < n; i++) {
            if (i != spalte) {
                neuesBrett[zeile][i] = Feld.Konflikt;
            }
            if (i != zeile) {
                neuesBrett[i][spalte] = Feld.Konflikt;
            }
        }


        for (int i = 1; i < Math.min(zeile + 1, spalte + 1); i++) {
            neuesBrett[zeile - i][spalte - i] = Feld.Konflikt;
        }
        for (int i = 1; i < Math.min(zeile + 1, n - spalte); i++) {
            neuesBrett[zeile - i][spalte + i] = Feld.Konflikt;
        }
        for (int i = 1; i < Math.min(n - zeile, spalte + 1); i++) {
            neuesBrett[zeile + i][spalte - i] = Feld.Konflikt;
        }
        for (int i = 1; i < Math.min(n - zeile, n - spalte); i++) {
            neuesBrett[zeile + i][spalte + i] = Feld.Konflikt;
        }

        neuesBrett[zeile][spalte] = Feld.Dame;

        printBrett(neuesBrett);

        if (dame <= 1 || platziereDame(neuesBrett, n, dame - 1)) {
            copyFeld(neuesBrett, brett);
            return true;
        }

        return false;
    }

    private static void printBrett(Feld[][] brett) {
        final char[] numerals = new char[]{'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

        System.out.print("  ");
        for (int j = 0; j < brett[0].length; j++) {
            System.out.print(numerals[j]);
        }
        System.out.println();
        for (int i = 0; i < brett.length; i++) {
            System.out.printf("%s ", numerals[i]);
            for (int j = 0; j < brett[i].length; j++) {
                System.out.print(brett[i][j] == Feld.Dame ? "D" : brett[i][j] == Feld.Konflikt ? "K" : " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public static void main(String[] args) {
        final int n = 10;

        Feld[][] brett = damenproblem(n);
        printBrett(brett);
    }

}
