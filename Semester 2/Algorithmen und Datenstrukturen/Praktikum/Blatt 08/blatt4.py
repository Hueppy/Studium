import time

from student import *


class Hashtable:
    def __init__(self, n):
        self.empty = "empty"
        self.removed = "removed"
        self.n = n
        self.buckets = [self.empty] * n

    def query(self, hash, callback):
        """Hilfsfunktion um die Hashtable nach dem Sondierungsprinzip abzufragen"""
        i = 0
        index = hash
        while i < self.n and not callback(self.buckets[index]):
            i += 1
            index = (hash + (i * i)) % self.n
        if i < self.n:
            return index
        else:
            return self.n

    def add(self, item):
        """Fügt das übergebene Item der Hashtable hinzu"""
        index = self.query(self.hash(item.get_key()), lambda x: x == self.empty or x == self.removed)
        if index < self.n:
            self.buckets[index] = item
            return True
        else:
            return False

    def remove(self, item):
        """Entfernt das übergebene Item aus der Hashtabelle"""
        return self.remove_by_key(item.get_key())

    def remove_by_key(self, key):
        """Entfernt das Item mit dem übergebenen Schlüssel aus der Hashtabelle"""
        index = self.query(self.hash(key), lambda x: x == self.empty or (x != self.removed and x.get_key() == key))
        if index < self.n and self.buckets[index] != self.empty:
            self.buckets[index] = self.removed
            return True
        else:
            return False

    def hash(self, s):
        """Implementierung des Hashverfahrens"""
        sum = 0
        for c in s:
            sum += ord(c)
        return sum % self.n

    def clear(self):
        """Leert die Hashtabelle"""
        for i in range(self.n):
            self.buckets[i] = self.empty

    def get_by_key(self, key):
        """Holt das Item mit dem übergebenen Schlüssel aus der Hashtabelle"""
        index = self.query(self.hash(key), lambda x: x == self.empty or (x != self.removed and x.get_key() == key))
        if index < self.n:
            return self.buckets[index]
        else:
            return None


def save(hashtable, filename):
    """Speichert die Daten in der Datei"""
    try:
        f = open(filename, mode="w")
        for student in hashtable.buckets:
            if isinstance(student, Student):
                f.write("{};{};{}\n".format(student.id, student.surname, student.firstname))
        f.close()
    except:
        print("Datei konnte nicht gespeichert werden")

def add(hashtable):
    """Hinzufügen eines Students zur Hashtabelle"""
    id = input("Id: ")
    surname = input("Nachname: ")
    firstname = input("Vorname: ")
    student = Student(id, surname, firstname)

    if not hashtable.add(student):
        print("Einfügen nicht möglich")


def remove(hashtable):
    """Entfernen eines Studentens aus der Hashtabelle"""
    lastname = input("Nachname: ")
    if not hashtable.remove_by_key(lastname):
        print("Datensatz nicht gefunden")


def print_table(hashtable):
    """Ausgabe der Hashtabelle"""
    for n in hashtable.buckets:
        print(n)
    print()


def change_lastname(hashtable):
    """Ändern des Nachnames eines Students"""
    lastname = input("Alter Nachname: ")
    student = hashtable.get_by_key(lastname)
    if isinstance(student, Student):
        # Entferne den Student
        hashtable.remove(student)
        print(student)
        surname = input("Neuer Nachname: ")
        # Ändere den Nachname
        student.surname = surname
        # Füge den Student wieder hinzu
        hashtable.add(student)
    else:
        print("Datensatz nicht gefunden")


students = load(FILENAME)
table = Hashtable(100)

start = time.time()
for student in students:
    table.add(student)
stop = time.time()
print(stop - start)

last = students[-1]
start = time.time()
table.remove(last)
stop = time.time()
print(stop - start)

menu = {
    "a": (lambda: add(table)),
    "r": (lambda: remove(table)),
    "c": (lambda: change_lastname(table)),
    "p": (lambda: print_table(table)),
    "s": (lambda: save(table, FILENAME))
}

once = True
while once or query != "":
    once = False
    print("<a> - Student hinzufügen")
    print("<r> - Student entfernen")
    print("<c> - Nachnamen ändern")
    print("<p> - Ausgabe")
    print("<s> - Speichern")
    query = input()

    if query in menu:
        menu[query.lower()]()
