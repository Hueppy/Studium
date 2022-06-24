import math
import time


def maxTeilsumme(a):
    n = len(a)
    maxsumme = -math.inf
    additionen = 0
    von = 0
    bis = 0
    for i in range(0, n):
        for j in range(i, n):
            summe = 0
            for k in range(i, j + 1):
                summe = summe + a[k]
                additionen = additionen + 1
            if summe > maxsumme:
                maxsumme = summe
                von = i
                bis = j
    return (von, bis, maxsumme, additionen)


a = list()
filename = input("Dateiname: ")
file = open(filename, mode='r')
for line in file:
    a.append(int(line))
file.close()

start = time.time()
(von, bis, maxsumme, additionen) = maxTeilsumme(a)
stop = time.time()

print("Max. Teilsumme", maxsumme)
print("Erster Index", von)
print("Letzter Index", bis)
print("Zeit in Sekunden", stop - start)
print("Additionen", additionen)
