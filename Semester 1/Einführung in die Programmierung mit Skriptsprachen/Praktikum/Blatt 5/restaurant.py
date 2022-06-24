from os.path import isfile
import json

FILENAME = 'menu.json'

if isfile(FILENAME):
    menu = json.load(open(FILENAME))
else:
    menu = dict()

def show_menu():
    for k, v in menu.items():
        print(k, '=', v)

def add_menu():
    print('Hinweis: Eine leerer Name bricht den Vorgang ab')
    name = input('Name des Gerichts: ')
    if name != str():
        price = input('Preis des Gerichts: ')
        menu[name] = price

def delete_menu():
    keys = list(menu)

    for i, k in enumerate(keys):
        print(i + 1, k)

    index = int(input('Nummer des Gerichts: ')) - 1
    if 0 <= index < len(keys):
        menu.pop(keys[index])
    else:
        print('Ungültiges Gericht')

option = str()
while option != 'e':
    print("""
a = Speisekarte anzeigen
n = neues Gericht hinzufügen
l = Gericht löschen
e = Programmende
""")

    option = input().lower()
    print()
    if option == 'a':
        show_menu()
    elif option == 'n':
        add_menu()
    elif option == 'l':
        delete_menu()
    print()

json.dump(menu, open(FILENAME, 'w'))