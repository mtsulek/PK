#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include "vector"
#include <time.h>

struct Coordinates{
	double x;
	double y;
};

struct Velocity{
	double vx;
	double vy;
};

struct Size{
	double mass;
	double radius;
};

class Particle{
private:
	Coordinates _coordinate;
	Velocity _velocity;
	Size _size;
public:
	Particle(double x, double y, double vx, double vy, double mass, double radius);
	double distanceBetweenParticles(struct Coordinates coordinate);
	void ramdomizePosition(double min, double max);
	Coordinates whereAmI();
	Size howBigAmI();
	Velocity howFastAmI();
	void setVelocity(double vx, double vy);
	void setPosition(double x, double y);
};

#endif
