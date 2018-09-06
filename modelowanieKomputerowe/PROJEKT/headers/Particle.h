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
        }

        double distanceBetweenParticles(struct Coordinates coordinate){
            // Returns distance between this-> Particle and another particular particles
        }

        void ramdomizePosition(double min, double max){
            // Generate Random position between min and max and sets as Particle coordinate
        }

        Coordinates whereAmI(){
            // Returns position of particle
        }

        Size howBigAmI(){
            // Returns position of particle
        }

        void setVelocity(double vx, double vy){
            // Sets new velocity of particular particle
        }

        void setPosition(double x, double y){
            // Sets new position of particular particle
        }
};