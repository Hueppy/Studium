wort = "test"

def scopes():
    wort = "scopes"

    def do_local():
        wort = "local"
        print("in do-local: " + wort + " wort")

    def do_nonlocal():
        nonlocal wort
        wort = "nonlocal"
        print("in do-nonlocal: " + wort + " wort")

    def do_global():
        global wort
        wort = "global"
        print("in do-global: " + wort + " wort")
        pass

    print("in scopes: " + wort + " wort")
    do_local()
    print("in scopes: " + wort + " wort")
    do_nonlocal()
    print("in scopes: " + wort + " wort")
    do_global()
    print("in scopes: " + wort + " wort")

print("im Hauptprogramm: " + wort + " wort")
scopes()
print("im Hauptprogramm: " + wort + " wort")
