def power(i, x=2):
    if (i < 0):
        return 1 / power(-i, x)
    elif (i == 0):
        return 1
    else:
        return x * power(i-1, x)


print(power(4))
print(power(2, 12))
print(power(-1, 2))