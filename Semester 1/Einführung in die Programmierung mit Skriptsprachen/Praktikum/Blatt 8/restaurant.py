from os.path import isfile


def query_list(list, value, callback):
    for i, v in enumerate(list):
        print("[{}] {}".format(i + 1, value(v)))

    try:
        index = int(input()) - 1
    except:
        return

    if 0 <= index < len(list):
        callback(index)
    else:
        print('Ungültige Nummer')


def query_category(list, callback):
    query_list(list, lambda c: c, callback)


def query_menu(list, callback):
    query_list(list, lambda m: m.name, callback)


class Meal:
    def __init__(self, name, category, price):
        self.name = name;
        self.category = category
        self.price = price


class Action:
    def execute(self, menu):
        pass

    def get_key(self):
        pass

    def get_description(self):
        pass


class ShowAction(Action):
    def __init__(self, categories):
        self._categories = categories

    def execute(self, menu):
        prev_category = str()
        for m in sorted(menu, key=lambda m: self._categories.index(m.category)):
            if prev_category != m.category:
                prev_category = m.category
                print("\n## {} ##".format(prev_category))

            print("{} = {}".format(m.name, m.price))

    def get_key(self):
        return "a"

    def get_description(self):
        return "Speisekarte anzeigen"


class AddAction(Action):
    def __init__(self, categories):
        self._categories = categories

    def execute(self, menu):
        print("Hinweis: Eine leerer Name bricht den Vorgang ab")
        name = input("Name des Gerichts: ")
        if name != str():
            price = input("Preis des Gerichts: ")

            for i, c in enumerate(self._categories):
                print("[{}] {}".format(i + 1, c))
            category = int(input("Nummer der Kategorie: ")) - 1
            if 0 <= category < len(self._categories):
                menu.append(Meal(name, self._categories[category], price))
            else:
                print('Ungültige Kategorie')

    def get_key(self):
        return "n"

    def get_description(self):
        return "neues Gericht hinzufügen"


class DeleteAction(Action):
    def execute(self, menu):
        query_menu(menu, lambda i: menu.pop(i))

    def get_key(self):
        return "l"

    def get_description(self):
        return "Gericht löschen"


class ChangeCategoryAction(Action):
    def __init__(self, categories):
        self._categories = categories

    def execute(self, menu):
        def get_callback(meal):
            def callback(i):
                meal.category = self._categories[i]

            return callback

        query_menu(menu, lambda i: query_category(self._categories, get_callback(menu[i])))

    def get_key(self):
        return "k"

    def get_description(self):
        return "Kategorie ändern"


class MenuLoader:
    def load(self, menu):
        pass


class FileMenuLoader(MenuLoader):
    def __init__(self, filename):
        self._filename = filename

    def load(self, menu):
        menu.clear()

        if isfile(self._filename):
            f = open(filename, mode="r")
            for l in f:
                d = l.strip().split(";")
                menu.append(Meal(*d))
            f.close()


class MenuSaver:
    def save(self, menu):
        pass


class FileMenuSaver(MenuSaver):
    def __init__(self, filename):
        self._filename = filename

    def save(self, menu):
        f = open(self._filename, mode="w")
        for meal in menu:
            f.write("{};{};{}\n".format(meal.name, meal.category, meal.price))
        f.close()


class Restaurant:
    def __init__(self, actions, loader, saver):
        self._actions = actions
        self._loader = loader
        self._saver = saver
        self._menu = list()

    def _print_actions(self):
        for action in self._actions:
            print("{} = {}".format(action.get_key(), action.get_description()))
        print("e = Programmende")

    def _execute_action(self, key):
        for action in self._actions:
            if (action.get_key() == key):
                action.execute(self._menu)

    def run(self):
        self._loader.load(self._menu)
        option = str()
        while option != "e":
            print()
            self._print_actions()
            print()
            option = input().lower()
            print()
            self._execute_action(option)
        self._saver.save(self._menu)


categories = ["Vorspeise", "Hauptspeise", "Nachspeise", "Getränk"]

default_filename = "speisekarte.txt"
filename = input("Dateiname <{}>: ".format(default_filename))
if filename == "":
    filename = default_filename

restaurant = Restaurant(
    [ShowAction(categories), AddAction(categories), DeleteAction(), ChangeCategoryAction(categories)],
    FileMenuLoader(filename),
    FileMenuSaver(filename))

restaurant.run()
