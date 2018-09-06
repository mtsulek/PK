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

/**
 * Returns distance between this-> Particle and another particular particles
 * @param coordinate
 * @return
 */
double Particle::distanceBetweenParticles(struct Coordinates coordinate){
	double dx = _coordinate.x - coordinate.x;
	double dy = _coordinate.y - coordinate.y;
	return sqrt(dx * dx + dy * dy);
}

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
