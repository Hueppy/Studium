FILENAME = "Studinamen.txt"


class Student:
    def __init__(self, id, surname, firstname):
        self.id = id
        self.surname = surname
        self.firstname = firstname

    def get_key(self):
        return self.surname

    def __eq__(self, other):
        return isinstance(other, Student) and self.id == other.id and self.surname == other.surname and self.firstname == other.firstname

    def __repr__(self):
        return "Student ({}, {}, {})".format(self.id, self.surname, self.firstname)



def load(filename):
    """Lädt die Daten aus der Datei"""
    result = list()
    try:
        file = open(filename, mode="r")
        for line in file:
            if line.strip() != "":
                student = Student(*line.strip().split(";"))
                result.append(student)
        file.close()
    except:
        pass
    return result