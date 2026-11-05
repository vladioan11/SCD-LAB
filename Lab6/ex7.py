dictionar = {'nume':'Ionut', 5:128,(1,2):'galati'}
print(dictionar)
print(dictionar['nume'])
print(dictionar[5])
print(dictionar[(1,2)])
print(dictionar.keys())
print(dictionar.values())

dictionar['varsta']= 57
dictionar[(1,3)]=18

print (dictionar)
print(len(dictionar))
print ('nume'in dictionar)
if (1, 3) in dictionar:
    print('valoare este ', dictionar[(1, 3)])
