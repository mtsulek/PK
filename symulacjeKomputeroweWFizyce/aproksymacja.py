#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plot
import pylab 
# FUNCTIONS:
# SOLVE:
def solve(x1, y1, x2, y2):
    # y1 = a * x1 + b
    # y2 = a * x2 + b

    a = (y2 - y1) / (x2 - x1)
    b = ((x2 * y1)-(x1 * y2)) / (x2 - x1)
    
    return a, b

# DATA:
X = [1,2,3,4,5,6]
Y = [0,-2,2,-4,4,-6]
aprox = []
fitEvery = []
fit = []

# Solve a, b for (len -1)
for i in range(len(X)):
    try:
        aprox.append(solve(X[i], Y[i], X[i+1], Y[i+1]))
    except:
        aprox.append(solve(X[i], Y[i], 0, 0))

# Fit each point
for i in range(len(aprox)):
    fitEvery.append(aprox[i][0] * X[i] + aprox[i][1])

# Fit points
tmpA, tmpB = 0, 0
for i in range(len(aprox)):
    tmpA += aprox[i][0]
    tmpB += aprox[i][1]
tmpA = tmpA / len(X)
tmpB = tmpB / len(X)
print(tmpA, tmpB)
fit.append((tmpA * X[i] + tmpB))
aproximatedX = [X[0], X[-1]]
aproximatedY = [Y[0], fit[0]]

# Aprox
n = len(X)
xySum, xSum, x2Sum, ySum = 0, 0, 0, 0
for i in range(len(aprox)):
    xySum += X[i] * Y[i]
    xSum += X[i]
    ySum += Y[i]
    x2Sum += X[i]* X[i]
# for i in range(len(aprox)):
bigA = (n * xySum - (xSum * ySum)) / ((n * x2Sum) - (xSum * xSum))
bigB = (ySum - (bigA * xSum)) / n
print("Aprox:" + str(bigA) + ", " + str(bigB))

# Get values from parameters:
appvalX = []
appvalY = []
for i in range(100):
    x = i - 50
    y = bigA * x + bigB
    appvalX.append(x)
    appvalY.append(y)

# PLOT
plot.ylim((-6,7))
plot.xlim((0,8))
plot.plot(X, Y, '.', label="Points")
plot.plot(X, fitEvery, label="Fit every near point")
plot.plot(aproximatedX, aproximatedY, label='Aproxim from X[1] to X[-1]')
plot.plot(appvalX, appvalY, label="Aproxim")

pylab.legend(loc='upper left')
plot.show()