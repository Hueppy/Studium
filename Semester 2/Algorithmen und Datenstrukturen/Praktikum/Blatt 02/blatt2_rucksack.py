import time


class Item:
    def __init__(self, gewicht, wert):
        self.gewicht = gewicht
        self.wert = wert


def rucksack(items, c):
    n = len(items) - 1
    f = [[0 for x in range(c + 1)] for y in range(n + 1)]
    calls = 0
    count = 0

    for rk in range(c + 1):
        if (rk < items[n].gewicht):
            f[n][rk] = 0
        else:
            f[n][rk] = items[n].wert

    for i in range(n - 1, -1, -1):
        for rk in range(c + 1):
            count = count + 1
            if (rk < items[i].gewicht):
                f[i][rk] = f[i+1][rk]
            else:
                calls = calls + 1
                f[i][rk] = max(
                    f[i+1][rk],
                    f[i+1][rk - items[i].gewicht] + items[i].wert
                )

    return (f[0][c], calls, count)

def rucksack_back(items, i, rest):
    if (i + 1 == len(items)):
        if rest < items[i].gewicht:
            return (0, 0)
        else:
            return (items[i].wert, 0)
    else:
        if rest < items[i].gewicht:
            # pass Objekt i nicht in den Rucksack?
            # verssuche naechstes Objekt
            return rucksack_back(items, i + 1, rest)
        else:
            (a_wert, a_calls) = rucksack_back(items, i + 1, rest)
            (b_wert, b_calls) = rucksack_back(items, i + 1, rest - items[i].gewicht)
            return (max(a_wert, b_wert + items[i].wert), a_calls + b_calls + 1);


items1 = [
    Item(2, 6),
    Item(2, 3),
    Item(6, 5),
    Item(5, 4),
    Item(4, 6),
]
items2 = [
    Item(2, 10),
    Item(10, 3),
    Item(7, 1),
    Item(9, 9),
    Item(2, 5),
    Item(2, 8),
    Item(5, 2),
    Item(10, 5),
    Item(8, 4),
    Item(8, 5),
    Item(6, 10),
    Item(3, 3),
    Item(6, 8),
    Item(3, 2),
    Item(6, 8),
    Item(3, 4),
    Item(8, 4),
    Item(4, 10),
    Item(7, 9),
    Item(4, 8)
]
items3 = [
    Item(6, 1),
    Item(9, 1),
    Item(4, 9),
    Item(4, 4),
    Item(3, 2),
    Item(7, 10),
    Item(9, 5),
    Item(10, 1),
    Item(8, 5),
    Item(4, 4),
    Item(6, 6),
    Item(1, 3),
    Item(4, 7),
    Item(3, 4),
    Item(2, 6),
    Item(9, 1),
    Item(9, 1),
    Item(10, 4),
    Item(7, 2),
    Item(9, 2),
    Item(1, 5),
    Item(3, 6),
    Item(8, 5),
    Item(2, 6),
    Item(9, 8),
    Item(4, 7),
    Item(10, 3),
    Item(9, 5),
    Item(2, 5),
    Item(4, 8),
    Item(3, 1),
    Item(5, 2),
    Item(3, 1),
    Item(6, 10),
    Item(7, 1),
    Item(2, 9),
    Item(10, 3),
    Item(6, 9),
    Item(3, 10),
    Item(9, 4),
    Item(4, 10),
    Item(4, 1),
    Item(5, 3),
    Item(7, 3),
    Item(4, 10),
    Item(3, 7),
    Item(10, 3),
    Item(8, 7),
    Item(6, 4),
    Item(8, 7),
    Item(1, 4),
    Item(9, 1),
    Item(3, 6),
    Item(3, 4),
    Item(5, 10),
    Item(5, 2),
    Item(2, 4),
    Item(6, 4),
    Item(9, 3),
    Item(1, 10),
    Item(4, 2),
    Item(5, 5),
    Item(1, 9),
    Item(6, 1),
    Item(6, 3),
    Item(6, 8),
    Item(8, 4),
    Item(7, 7),
    Item(3, 1),
    Item(8, 1),
    Item(1, 6),
    Item(10, 4),
    Item(3, 5),
    Item(4, 6),
    Item(4, 2),
    Item(3, 4),
    Item(9, 9),
    Item(4, 9),
    Item(7, 10),
    Item(5, 5),
    Item(1, 2),
    Item(4, 3),
    Item(9, 3),
    Item(8, 6),
    Item(1, 9),
    Item(7, 3),
    Item(7, 9),
    Item(4, 6),
    Item(3, 5),
    Item(2, 2),
    Item(6, 1),
    Item(3, 7),
    Item(9, 5),
    Item(6, 4),
    Item(3, 6),
    Item(2, 6),
    Item(3, 3),
    Item(6, 5),
    Item(10, 6),
    Item(8, 6)
]

start = time.time()
(wert, calls, count) = rucksack(items3, 10)
stop = time.time()

print("Algorithmus I")
print("Maximaler Wert: ", wert)
print("Schleifendurchläufe: ", count)
print("max() Aufrufe: ", calls)
print("Zeit in Sekunden: ", stop - start)

start = time.time()
(wert, calls) = rucksack_back(items3, 0, 10)
stop = time.time()

print("Algorithmus II - Backtracking")
print("Maximaler Wert: ", wert)
print("max() Aufrufe: ", calls)
print("Zeit in Sekunden: ", stop - start)