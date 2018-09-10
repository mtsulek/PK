#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "vector"
#include <time.h>

using namespace std;
// #include "Particle.h"
#include "Allegro.h"

/**
 * Simulation "jobs" to be done
 * @param vector of Particle classes
 */
int simulationFunction(vector<Particle> particle){
    for(int j=0; j<particle.size(); j++){
        al_draw_filled_circle(particle[j].whereAmI().x ,particle[j].whereAmI().y, particle[j].howBigAmI().radius, al_map_rgb(0,255,0));
    }
}

// Create pointer to simulation function
typedef int ( * simulationPointer)(vector<Particle>);
// Allocate function adress to pointer 
simulationPointer simulation = simulationFunction;

/**
 * Check if Particle can fit between other particles if not -> re-roll position
 * @param particle
 * @param particleContainer POINTER????
 * @param numberOfParticles
 */
void ifParticleFits(int particle, vector<Particle> &particleContainer, int numberOfParticles){
    for(int iteration = 0; iteration < numberOfParticles; iteration++){
        bool conflict = true;
        if(particle != iteration){
            while (conflict == true){
                particleContainer[particle].ramdomizePosition(0, 500);
                double distanceOfTwo = particleContainer[particle].distanceBetweenParticles(particleContainer[iteration].whereAmI());
                double radiusOfTwo = (particleContainer[particle].howBigAmI().radius + particleContainer[iteration].howBigAmI().radius);
                if(distanceOfTwo > radiusOfTwo){
                    conflict = false;
                } else {
                    conflict = true;
                }
            }
        }
    }
}

int main(){
    /**
     * Time dependent rand and initiation of particle class vector
     */
    srand(time(NULL));
    vector<Particle> particleContainer;

    /**
     * Create no. Particles classes
     */
    int numberOfParticles = 200;
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        Particle Particle(1.0, 1.0, 1.0, 1.0, 1.0, 5.0);
        particleContainer.push_back(Particle);
    }

    cout << sizeof(particleContainer) << "tutaj";

    /**
     * Loop for rand position of each Particle
     */
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        ifParticleFits(iterator, particleContainer, numberOfParticles);
    }

    /**
     * Initiate drawing class and launch simulation function
     */
    Allegro canvas;
    canvas.Draw(800, 600, particleContainer, simulation);
}
