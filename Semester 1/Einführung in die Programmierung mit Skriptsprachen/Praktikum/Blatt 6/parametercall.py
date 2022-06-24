vint = 7
vstr = "Hallo Welt"
vlist = [1, 3, 6]

def modifyInt(x):
    x = 3

def modifyString(x):
    x = x + "a"

def modifyList(x):
    x[2] = 2

print("Integer vorher: ", vint)
modifyInt(vint)
print("Integer nachher: ", vint)

print("String vorher: ", vstr)
modifyString(vstr)
print("String nachher: ", vstr)

print("Liste vorher: ", vlist)
modifyList(vlist)
print("Liste nachher: ", vlist)

