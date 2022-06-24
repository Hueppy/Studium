import time

from student import *


class Node:
    """Knoten in der verktetteten Liste"""
    def __init__(self, value):
        self.value = value
        self.next = None

    def set_next(self, next):
        self.next = next

    def get_next(self):
        return self.next

    def get_value(self):
        return self.value


class LinkedList:
    """Verkettete Liste"""
    def __init__(self):
        self.head = None

    def add(self, value):
        """Wert zu der verketteten Liste hinzufügen"""
        new = Node(value)
        node = self.head
        if node is None:
            self.head = new
            return None

        next = node.get_next()
        while next is not None:
            node = next
            next = node.get_next()

        node.set_next(new)

    def remove(self, value):
        """Wert aus der verketteten Liste löschen"""
        prev = self.head
        if prev is None or prev.get_value() == value:
            self.head = None
            return

        node = prev.get_next()
        while node is not None and node.get_value() != value:
            prev = node
            node = node.get_next()

        if node is not None:
            prev.set_next(node.get_next())

    def get_head(self):
        """Kopf der verketteten Liste"""
        return self.head


class Hashtable:
    def __init__(self, count):
        self.count = count
        self.buckets = [None] * count

    def hash(self, value):
        """Hashfunktion der Liste"""
        hash = 0
        for c in value.get_key():
            hash += ord(c)
        return hash % self.count

    def add(self, value):
        """Wert zu der Liste hinzufügen"""
        hash = self.hash(value)
        if self.buckets[hash] is None:
            self.buckets[hash] = LinkedList()

        self.buckets[hash].add(value)

    def remove(self, value):
        """Wert aus der Liste entfernen"""
        hash = self.hash(value)
        list = self.buckets[hash]
        if list is not None:
            dele = list.remove
            dele(value)


def save(hashtable, filename):
    """Speichert die Daten in der Datei"""
    try:
        f = open(filename, mode="w")
        for bucket in hashtable.buckets:
            if bucket is not None:
                node = bucket.get_head()
                while node is not None:
                    student = node.get_value()
                    f.write("{};{};{}\n".format(student.id, student.surname, student.firstname))
                    node = node.get_next()
        f.close()
    except:
        print("Datei konnte nicht gespeichert werden")


def add(hashtable):
    """Hinzufügen eines Students zur Hashtabelle"""
    id = input("Id: ")
    surname = input("Nachname: ")
    firstname = input("Vorname: ")
    student = Student(id, surname, firstname)

    hashtable.add(student)


def remove(hashtable):
    """Entfernen eines Studentens aus der Hashtabelle"""
    id = input("Id: ")
    surname = input("Nachname: ")
    firstname = input("Vorname: ")
    student = Student(id, surname, firstname)

    hashtable.remove(student)


def print_table(hashtable):
    """Ausgabe der Hashtabelle"""
    for bucket in hashtable.buckets:
        if isinstance(bucket, LinkedList):
            node = bucket.get_head()
            while node is not None:
                print(node.get_value())
                node = node.get_next()
    print()


def change_lastname(hashtable):
    """Ändern des Nachnames eines Students"""
    id = input("Id: ")
    surname = input("Nachname: ")
    firstname = input("Vorname: ")
    student = Student(id, surname, firstname)

    # Entferne den Student
    hashtable.remove(student)
    print(student)
    surname = input("Neuer Nachname: ")
    student.surname = surname
    # Füge den Student wieder hinzu
    hashtable.add(student)


students = load(FILENAME)
hashtable = Hashtable(53)

start = time.time()
for student in students:
    hashtable.add(student)
stop = time.time()
print(stop - start)

last = students[-1]
start = time.time()
hashtable.remove(last)
stop = time.time()
print(stop - start)

menu = {
    "a": (lambda: add(hashtable)),
    "r": (lambda: remove(hashtable)),
    "c": (lambda: change_lastname(hashtable)),
    "p": (lambda: print_table(hashtable)),
    "s": (lambda: save(hashtable, FILENAME))
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
