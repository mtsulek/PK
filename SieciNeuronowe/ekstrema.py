import parser
import matplotlib.pyplot as plt
import math
from operator import itemgetter
from mpl_toolkits import mplot3d

# FUNKCJE
def RozwiążRownanie(rownanie, x ,y, z):
    wynik = parser.expr(rownanie).compile() 
    return eval(wynik)

# STAŁE
x0, xk = 0, 3
y0, yk = 1, 2
rownanie = "math.sin(x) + math.cos(y)"
# SZUKANE
paraPunktow = []

for x in range(x0, xk+1):
    for y in range(y0, yk+1):
        paraPunktow.append([x, y, RozwiążRownanie(rownanie, x, y, 1)])

print(sorted(paraPunktow, key=itemgetter(2))[0])

# RYSOWANIE
xList = []
yList = []
zList = []

for i in range(0, len(paraPunktow)):
    xList.append(paraPunktow[i][0])
    yList.append(paraPunktow[i][1])
    zList.append(paraPunktow[i][2])


ax = plt.axes(projection='3d')
ax.plot_trisurf(xList, yList, zList, cmap='viridis', linewidth=0.5)
ax.set_title('surface');

plt.show(ax)