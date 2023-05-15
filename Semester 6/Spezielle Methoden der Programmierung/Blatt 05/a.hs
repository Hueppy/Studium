xor True  y = not y
xor False y = y

testXor = (xor False False == False)
       && (xor False True  == True)
       && (xor True  False == True)
       && (xor True  True  == False)

fac 0 = 1
fac n = n * fac (n - 1)