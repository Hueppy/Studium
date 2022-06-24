from os.path import isfile

DEFAULT_FILENAME = "speisekarte.txt"

menu = list()
categories = ["Vorspeise", "Hauptspeise", "Nachspeise", "Getränk"]


class Meal:
    def __init__(self, name, category, price):
        self.name = name;
        self.category = category
        self.price = price


def load(filename):
    menu.clear()

    if isfile(filename):
        f = open(filename, mode="r")
        for l in f:
            d = l.strip().split(";")
            menu.append(Meal(*d))
        f.close()


def save(filename):
    f = open(filename, mode="w")
    for meal in menu:
        f.write("{};{};{}\n".format(meal.name, meal.category, meal.price))
    f.close()


def show_menu():
    prev_category = str()
    for m in sorted(menu, key=lambda m: categories.index(m.category)):
        if prev_category != m.category:
            prev_category = m.category
            print("\n## {} ##".format(prev_category))

        print("{} = {}".format(m.name, m.price))


def add_menu():
    print("Hinweis: Eine leerer Name bricht den Vorgang ab")
    name = input("Name des Gerichts: ")
    if name != str():
        price = input("Preis des Gerichts: ")

        for i, c in enumerate(categories):
            print("[{}] {}".format(i + 1, c))
        category = int(input("Nummer der Kategorie: ")) - 1
        if 0 <= category < len(categories):
            menu.append(Meal(name, categories[category], price))
        else:
            print('Ungültige Kategorie')


def query_list(list, value, callback):
    for i, v in enumerate(list):
        print("[{}] {}".format(i + 1, value(v)))

    try:
        index = int(input()) - 1
    except:
        return

    if 0 <= index < len(menu):
        callback(index)
    else:
        print('Ungültige Nummer')


def query_category(callback):
    query_list(categories, lambda c: c, callback)


def query_menu(callback):
    query_list(menu, lambda m: m.name, callback)


def delete_menu():
    query_menu(lambda i: menu.pop(i))


def change_category():
    def do(i):
        def set_category(i):
            m.category = categories[i]

        m = menu[i]
        query_category(set_category)

    query_menu(do)


filename = input("Dateiname <{}>: ".format(DEFAULT_FILENAME))
if filename == "":
    filename = DEFAULT_FILENAME

load(filename)

option = str()
switch = {
    'a': show_menu,
    'n': add_menu,
    'l': delete_menu,
    'k': change_category
}

while option != 'e':
    print("""
a = Speisekarte anzeigen
n = neues Gericht hinzufügen
l = Gericht löschen
k = Kategorie ändern
e = Programmende
""")
    option = input().lower()

    print()
    if option in switch:
        switch[option]()
    print()

save(filename)
