#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "vector"
#include "Particle.h"
using namespace std;

class Allegro{
private:
public:
    Allegro();
    int Draw(int x, int y, vector<Particle> particleContainer, int ( * simulationPointer)(vector<Particle>));
};

#endif
