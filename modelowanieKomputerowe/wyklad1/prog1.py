import time
import random
import threading
import sys
import matplotlib.pyplot as plt
import math
noParticle = 10
globalParticle = []

class czastka (threading.Thread):
    def __init__(self, threadID, counter, x, y):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.counter = counter
        self.stopped = False
        self.coordinateX = x
        self.coordinateY = y
        self.name = 'electrons'

    def giveParticleFormationForParticles(self, listOfParticles, count):
        for particle in listOfParticles:
            particle.coordinateOfParticle(self, 10, 11)

def createParticles(count, rand):
    particles = list(range(0,count))
    for particle in range(0,count):
        try:
            particles[particle] = czastka(particle, particle, random.randint(0,rand), random.randint(0,rand))
            globalParticle.append(particles[particle])
        except: 
            print('Error - cant create particle')
            raise     

class canvas(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.stopped = False
        self.name = 'electrons'

    def createCanvas(self, sizeX, sizeY):
        plt.title('Particles')
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.grid(True)
        plt.xlim(sizeX)
        plt.ylim(0,sizeY)

        cooX = []
        cooY = []
        for particle in globalParticle:
            cooX.append(particle.coordinateX)
            cooY.append(particle.coordinateY)

        plt.plot(cooX, cooY,'ro', color="blue", label = globalParticle[0].name)
        plt.legend()

    def showCanvas(self):
        plt.show()



createParticles(1000, 100)
canvas().createCanvas(100,100)
canvas().showCanvas()

# createCanvas(100,100)
