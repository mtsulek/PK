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

double getOneDimDistance(double x0, double x1, double boxXorY);
class Particle{
private:
	Coordinates _coordinate;
	Velocity _velocity;
	Size _size;
public:
	Particle(double x, double y, double vx, double vy, double mass, double radius);
	double getTimeTOColision(struct Coordinates coordinate, struct Velocity velocity, struct Size size, double boxX, double boxY);
	double distanceBetweenParticles(struct Coordinates coordinate, double boxX=800.0, double boxY=600.0);
	// double oneDimDistance(double x0, double x1, double boxX);
	void ramdomizePosition(double min, double max);
	void setVelocity(double vx, double vy);
	void setPosition(double x, double y);
	Coordinates whereAmI();
	Size howBigAmI();
	Velocity howFastAmI();
};

#endif
