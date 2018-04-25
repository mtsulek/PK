lista = [1, 654654, 4543, 4534777, -5643, 0, 554]

funckja babelkuj(lista):
    dlListy = dlugosc(lista) - 2
    czyNiePosortowane = True

    poki czyNiePosortowane:
        dla element w przedzial(0, dlListy):
            czyNiePosortowane = False

            jezeli lista[element] > lista[element + 1]:
                hold = lista[element + 1]
                lista[element + 1] = lista[element]
                lista[element] = hold
                print(lista)
                czyNiePosortowane = True

    zwroc lista

print(babelkuj(lista))