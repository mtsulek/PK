#include <cmath>
#include "vector"
#include <time.h>

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

        Size howBigAmI(){
            // Returns position of particle
            return _size;
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
