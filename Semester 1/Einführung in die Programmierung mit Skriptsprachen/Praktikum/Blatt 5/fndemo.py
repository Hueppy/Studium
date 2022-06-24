def fn_with_default(x=3):
    print("Called with", x)

def fn_positional(x, y, z):
    print("Called with", x, y ,z)

def fn_named(x, y, z):
    print("Called with", x, y, z)

def fn_unpacked(x, y, z):
    print("Called with", x, y, z)

def fn_packed(*args):
    print("Called with", args)

fn_with_default()
fn_with_default(7)

fn_positional(1, 2, 3)

fn_named(1, 2, 3)
fn_named(z=1, y=2, x=3)

fn_unpacked(*[1, 2, 3])

fn_packed([1, 2, 3])
fn_packed(1, 2, 3)
