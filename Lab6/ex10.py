def suma1(a, b):
    print(a+b)

def suma2(a, b=2):
    print(a+b)

def suma3(a, *valori):
    total =a
    for x in valori:
        total += x
    return total

suma1(2,3)

suma2(5)
suma2(5,5)

suma3(2,3)
print(suma3(2,3,4,5,6,7,8,9))
