#include "Particle.h"

/**
 * Construct Particle; Sets Particle parameters to new ones
 * @param x
 * @param y
 * @param vx
 * @param vy
 * @param mass
 * @param radius
 */
Particle::Particle(double x, double y, double vx, double vy, double mass,double radius){
	this->_velocity.vx = vx;
	this->_velocity.vy = vy;
	this->_size.mass = mass;
	this->_size.radius = radius;
	this->_coordinate.x = x;
	this->_coordinate.y = y;
}


double getOneDimDistance(double x0, double x1, double boxXorY)
{
    x0 = x0 - (double)floor(x0 / boxXorY) * boxXorY;
    double dx = x0 - x1;
    dx = dx - (double)nearbyint(dx/boxXorY) * boxXorY;
    return (dx);
}

/**
 * Returns distance between this-> Particle and another particular particles
 * @param coordinate
 * @return
 */
double Particle::distanceBetweenParticles(struct Coordinates coordinate, double boxX, double boxY){
	//double dx = _coordinate.x - coordinate.x;
	//double dy = _coordinate.y - coordinate.y;
	double dx = getOneDimDistance(this->_coordinate.x, coordinate.x, boxX);
	double dy = getOneDimDistance(this->_coordinate.y, coordinate.y, boxY);
	return (sqrt(dx * dx + dy * dy));
}

// double Particle::oneDimDistance(double x0, double x1, double boxXorY)
// {
//     x0 = x0 - floor(x0 / boxXorY) * boxXorY;
//     double dx = x0 - x1;
//     dx = dx - nearbyint(dx/boxXorY) * boxXorY;
//     return (dx);
// }

/**
 * Generate Random position between min and max and sets as Particle coordinate
 * @param min
 * @param max
 */
void Particle::ramdomizePosition(double min, double max){
	int value = ((max - min) + 1) + min;
	double x = rand() % value;
	double y = rand() % value;
	this->_coordinate.x = x;
	this->_coordinate.y = y;
}

/**
 * Returns velocity of particle
 * @return
 */
Velocity Particle::howFastAmI(){
	return _velocity;
}

/**
 * Returns position of particle
 * @return
 */
Coordinates Particle::whereAmI(){
	return _coordinate;
}

/**
 * Returns position of particle
 * @return
 */
Size Particle::howBigAmI(){
	return _size;
}

/**
 * Sets new velocity of particular particle
 * @param vx
 * @param vy
 */
void Particle::setVelocity(double vx, double vy){
	this->_velocity.vx = vx;
	this->_velocity.vy = vy;
}

/**
 * Sets new position of particular particle
 * @param x
 * @param y
 */
void Particle::setPosition(double x, double y){
	this->_coordinate.x = x;
	this->_coordinate.y = y;
}

double Particle::getTimeTOColision(struct Coordinates coordinate, struct Velocity velocity, struct Size size, double boxX, double boxY){
	double dradius = this->_size.radius + size.radius;
	double rij = distanceBetweenParticles(coordinate);
	
	double drx = getOneDimDistance(coordinate.x, this->_coordinate.x, boxX);
	double dry = getOneDimDistance(coordinate.y, this->_coordinate.y, boxY);

	double dvx = this->_velocity.vx - velocity.vx;
	double dvy = this->_velocity.vy - velocity.vy;
	double bij = drx * dvx + dry * dvy;
	double vij = sqrt(dvx * dvx + dvy * dvy);
	double tij = 0.0;
	dradius *= dradius;
	if (bij * bij - vij * vij * (rij * rij - dradius) < 0.0)
	{
		tij = 10e10;
	}
	else
	{
		tij = (-bij - sqrt(bij * bij - vij * vij * (rij * rij - dradius)))
				/ (vij * vij);
	}
	if (tij < 0.0)
	{
		tij = 10e10;
	}

	return (tij);
}

