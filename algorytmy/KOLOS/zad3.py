def InterpolacjaSzukaj(tablica, n, x):
    dol = 0
    gora = (n - 1)
    babelkuj(tablica)

    while dol <= gora and x >= tablica[dol] and x <= tablica[gora]:
        pos  = dol + int(((float(gora - dol) /
            ( tablica[gora] - tablica[dol])) * ( x - tablica[dol])))
        if tablica[pos] == x:
            return pos
        if tablica[pos] < x:
            dol = pos + 1;
        else:
            gora = pos - 1;
    return -1

def babelkuj(lista):
    dlugoscListy = len(lista)
    for i in range(dlugoscListy):
        for j in range(0, dlugoscListy-i-1):
            if lista[j] > lista[j+1] :
                lista[j], lista[j+1] = lista[j+1], lista[j]

tablica = [10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47]
n = len(tablica)
x = 18 
index = InterpolacjaSzukaj(tablica, n, x)
if index != -1:
    print ("Znalazłem tutaaaaj:",index)
else:
    print ("NIE umiem!")