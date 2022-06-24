from os.path import isfile
import json

FILENAME = 'menu.json'

if isfile(FILENAME):
    menu = json.load(open(FILENAME))
else:
    menu = dict()

option = str()
while option != 'e':
    print("""
a = Speisekarte anzeigen
n = neues Gericht hinzufügen
e = Programmende
""")

    option = input().lower()
    print()

    if option == 'a':
        for k, v in menu.items():
            print(k, '=', v)
    elif option == 'n':
        print('Hinweis: Eine leerer Name bricht den Vorgang ab')
        name = input('Name des Gerichts: ')
        if name != str():
            price = input('Preis des Gerichts: ')
            menu[name] = price
    print()

json.dump(menu, open(FILENAME, 'w'))