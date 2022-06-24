class Münze:
    def __init__(self, wert, anzahl):
        self.wert = wert
        self.anzahl = anzahl

    def __str__(self):
        return "({}, {})".format(self.wert, self.anzahl)

    def __repr__(self):
        return self.__str__()

def wechselgeld(muenzen, wert):
    ausgabe = []

    for m in muenzen:
        am = Münze(m.wert, 0)
        ausgabe.append(am)

        while (m.anzahl > 0) and (wert >= m.wert):
            am.anzahl += 1
            m.anzahl -= 1
            wert -= m.wert

    if wert == 0:
        return ausgabe
    else:
        for m in muenzen:
            for am in ausgabe:
                if (m.wert == am.wert):
                    m.anzahl += am.anzahl

        return "Geldwechseln nicht möglich"


print(wechselgeld([Münze(10, 1), Münze(2, 6), Münze(1, 10)], 12))
print(wechselgeld([Münze(50, 1), Münze(20, 6), Münze(10, 10), Münze(5, 4), Münze(2, 3), Münze(1, 2)], 69))

print(wechselgeld([Münze(50, 1), Münze(20, 3), Münze(2, 10)], 60))
print(wechselgeld([Münze(20, 3), Münze(19, 2), Münze(3, 1), Münze(2, 10)], 42))


muenzen = []
n = int(input("Anzahl der Münzen: "))
for i in range(n):
    print("Münze ", i + 1)
    muenzen.append(
        Münze(
            int(input("Wert: ")),
            int(input("Anzahl: "))
        )
    )

while 1:
    summe = int(input("Zu zahlende Summe: "))
    betrag = int(input("Bezahlter Betrag: "))

    print(wechselgeld(muenzen, betrag - summe))

