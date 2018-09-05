#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "vector"
#include <time.h>

using namespace std;

class Particle{
    private:
        struct Coordinates{
            double x;
            double y;
        };
        Coordinates _coordinate;

        struct Velocity{
            double vx;
            double vy;
        };
        Velocity _velocity;

        struct Size{
            double mass;
            double radius;
        };
        Size _size;

    public:
        Particle(double x, double y, double vx, double vy, double mass, double radius){
            // Construct Particle; Sets Particle parameters to new ones
            this-> _velocity.vx = vx;
            this-> _velocity.vy = vy;
            this-> _size.mass = mass;
            this-> _size.radius = radius;
            this-> _coordinate.x = x;
            this-> _coordinate.y = y;
        }

        double distanceBetweenParticles(struct Coordinates coordinate){
            // Returns distance between this-> Particle and another particular particles
            double dx = coordinate.x - _coordinate.x;
            double dy = coordinate.y - _coordinate.y;
            return sqrt(dx*dx+dy*dy);
        }

        void ramdomizePosition(double min, double max){
            // Generate Random position between min and max and sets as Particle coordinate
            int value = ((max - min) + 1) + min;
            double x = rand() % value;
            double y = rand() % value;
            this-> _coordinate.x = x;
            this-> _coordinate.y = y;
        }

        Coordinates whereAmI(){
            // Returns position of particle
            return _coordinate;
        }

        double howBigAmI(){
            // Returns position of particle
            return _size.radius;
        }

        void setVelocity(double vx, double vy){
            // Sets new velocity of particular particle
            this-> _velocity.vx = vx;
            this-> _velocity.vy = vy;
        }

        void setPosition(double x, double y){
            // Sets new position of particular particle
            this-> _coordinate.x = x;
            this-> _coordinate.y = y;
        }
};

int main(){
    
    // Obvious
    srand(time(NULL));
    vector<Particle> particleContainer;

    // Create no. particles
    int numberOfParticles = 10;
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        Particle Particle(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
        particleContainer.push_back(Particle);
    }

    // Give random position to each particle
    for(int particle = 0; particle < particleContainer.size(); particle++){
        particleContainer[particle].ramdomizePosition(10, 10);
        
        // Check if particles can fit
        for(int iterator = particle; iterator < particleContainer.size(); iterator++){
            if(particleContainer[particle].distanceBetweenParticles(particleContainer[iterator+1].whereAmI()) < (particleContainer[particle].howBigAmI() + particleContainer[iterator].howBigAmI())){
                cout << "Nie mieszczę się! \n";
            } else {
                cout << "Wejszłem! \n";
            }
            // TO BE CONTINUED!!!
        }

        particleContainer[particle].whereAmI();
    }

    // Measure distance between particle 
    cout << particleContainer[0].distanceBetweenParticles(particleContainer[1].whereAmI()) << endl;
    cout << (particleContainer[0].howBigAmI() + particleContainer[1].howBigAmI()) << endl;

}