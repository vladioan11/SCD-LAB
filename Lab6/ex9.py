def afiseaza1(x):
    x =2
    print('afisez', x)

def afiseaza2(x):
    x.append(['b', 5])
    print(x)

x=7
afiseaza1(x)
print(x)
lista = ['a', 3]
print("popul este ", lista.pop())
afiseaza2(lista)
print(lista)
