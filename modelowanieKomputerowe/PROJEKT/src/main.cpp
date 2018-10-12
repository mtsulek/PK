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
    double dt = 0.000001;
        while (true){
        // al_clear_to_color(al_map_rgb(0,0,0));
        for(int j=0; j<particle.size(); j++){
            double velocityX = particle[j].howFastAmI().vx;
            double velocityY = particle[j].howFastAmI().vy;
            cout << velocityX << velocityY << endl;
            double posX = particle[j].whereAmI().x;
            double posY = particle[j].whereAmI().y;
            particle[j].setPosition(posX + velocityX * dt, posY + velocityY * dt);
            al_draw_filled_circle(particle[j].whereAmI().x ,particle[j].whereAmI().y, particle[j].howBigAmI().radius, al_map_rgb(0,255,0));
            al_flip_display();
        }
    }
}
// Create pointer to simulation function
typedef int ( * simulationPointer)(vector<Particle>);
// Allocate function adress to pointer 
simulationPointer simulation = simulationFunction;

/**
 * Check if Particle can fit between other particles if not -> re-roll position
 * @param particle
 * @param &particleContainer
 * @param numberOfParticles
 */
// void ifParticleFits(int particle, vector<Particle> &particleContainer, int numberOfParticles){
//     for(int iteration = 0; iteration < numberOfParticles; iteration++){
//         bool conflict = true;
//         if(particle != iteration){
//             while (conflict == true){
//                 particleContainer[particle].ramdomizePosition(0, 500);
//                 double distanceOfTwo = particleContainer[particle].distanceBetweenParticles(particleContainer[iteration].whereAmI());
//                 double radiusOfTwo = (particleContainer[particle].howBigAmI().radius + particleContainer[iteration].howBigAmI().radius);
//                 if(distanceOfTwo > radiusOfTwo){
//                     conflict = false;
//                 } else {
//                     conflict = true;
//                 }
//             }
//         }
//     }
// }
bool positionAllowed(int particle, vector<Particle> &particleContainer, int numberOfParticles){
    for(int iteration = 0; iteration < numberOfParticles; iteration++){
        if(particle != iteration){
            double distanceOfTwo = particleContainer[particle].distanceBetweenParticles(particleContainer[iteration].whereAmI());
            double radiusOfTwo = (particleContainer[particle].howBigAmI().radius + particleContainer[iteration].howBigAmI().radius);
            if(distanceOfTwo < radiusOfTwo){
            return false;
            }
        }
    }
    return true;
}

int main(){
    /**
     * Time dependent rand and initiation of particle class vector
     */
    srand(time(NULL));
    srand48(time(NULL));
    vector<Particle> particleContainer;

    /**
     * Create no. Particles classes
     */
    int numberOfParticles = 1000;
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        Particle Particle(1.0, 1.0, 1.0, 1.0, 1.0, 5.0);
        particleContainer.push_back(Particle);
    }
    cout << sizeof(particleContainer) << "tutaj";

    /**
     * start positions for autocorelation
     */
    vector<Coordinates> zeroPositions;

    /**
     * Loop for rand position and Boltzman velocity of each Particle
     */
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        particleContainer[iterator].ramdomizePosition(0, 500);
        double vx;
        double vy;
        double u2 = drand48();
        double u1 = drand48();
        double g1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
        double g2 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);
        int multiplier = 0.01;
        vx = (g1 / 0.04) * multiplier;
        vy = (g2 / 0.04) * multiplier;
        while (positionAllowed(iterator, particleContainer, numberOfParticles) == false){
            particleContainer[iterator].ramdomizePosition(0, 500);
            particleContainer[iterator].setVelocity(vx, vy);
        }
        cout << vx << vy << endl;
        zeroPositions.push_back(particleContainer[iterator].whereAmI());
    }


    /**
     * Initiate drawing class and launch simulation function
     */
    Allegro canvas;
    canvas.Draw(800, 600, particleContainer, simulation);
}
