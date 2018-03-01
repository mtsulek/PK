
'Tworzenie macierzy'
  m1 = ones(4)*2
  m2 = ones(4)*3

'Sposób mnożenia macierzy'
  'Mnozenie macierzy'
  M = m1*m2
  'Mnożenie wartości z macierzy (tablicowe)'
  M2 = m1.*m2

'Potęgowanie macierzowe'
  M3 = m1^2
  'Potęgowanie macierzy tablicowo'
  M3 = m1^2

'funckja size(x)'
  'Wypisuje wektor dwuelementowy'
  size(m1)

'Przypisywanie do wektora'
  

'clc - czysci konsolę, trzeba wpisać w konsoli'
'clf - cos robi'
'clear x - usuwa daną zmienną z pamięci'
'clear - czysci przestrzen roboczą ze wszystkich zmiennych'
'help eye, help help, doc eye -podpowiedzi'

'macierze losowe o takich samych wymiarach'
  m3 = rand(2,2)
  m4 = rand(2,2)

'szukanie wiekszych w danej macierzy niz 0.5'
  index = find(m3 > 0.5)
  cpm3 = m3
  cpm3(index) = 5

'szukanie i zamiana na 0'
  index2 = find(m3 > m4)
  cpm3a = cpm3
  cpm3a(index) = 0 

'cpm3a(find(m3 > m4)) = 0 jednoliniowiec'

'Funkcyjne rzeczy'
function c = pitagoras(a,b)
 sqrt(a^2 + b^2)
end

pitagoras(1,2)

x = 0:pi/20:2*pi;
y = cos(x)
plot(x,y)
hold on
x = sin(x)
plot(x,y)