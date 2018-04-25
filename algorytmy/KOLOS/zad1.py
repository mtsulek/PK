def babelkuj(lista):
    dlugoscListy = len(lista)
 
    for i in range(dlugoscListy):
        for j in range(0, dlugoscListy-i-1):
            if lista[j] > lista[j+1] :
                lista[j], lista[j+1] = lista[j+1], lista[j]
 
# SPRAWDZENIE:
lista = [1, 654654, 4543, 4534777, -5643, 0, 554]
babelkuj(lista)
print(lista)
