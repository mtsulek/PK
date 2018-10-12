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
// int simulationFunction(vector<Particle> particle){
//     double dt = 0.000001;
//         while (true){
//         // al_clear_to_color(al_map_rgb(0,0,0));
      
//             al_flip_display();
//         }
//     }
// }
// Create pointer to simulation function
// typedef int ( * simulationPointer)(vector<Particle>);
// // Allocate function adress to pointer 
// simulationPointer simulation = simulationFunction;

bool zderzenie(vector<Particle> &particleContainer, int czastkaI, int czastkaJ, double boxX, double boxY){
	double tmp[4];
    double tempr[4];
	double Mp = particleContainer[czastkaI].howBigAmI().mass + particleContainer[czastkaJ].howBigAmI().mass;

	double dx01 = getOneDimDistance(particleContainer[czastkaI].whereAmI().x, particleContainer[czastkaJ].whereAmI().x, boxX);
	double dy01 = getOneDimDistance(particleContainer[czastkaI].whereAmI().y, particleContainer[czastkaJ].whereAmI().y, boxY);
	double dx10 = -dx01;
	double dy10 = -dy01;
	double odl01 = particleContainer[czastkaI].distanceBetweenParticles(particleContainer[czastkaJ].whereAmI(), boxX, boxY);
	odl01 *= odl01;

	double dvx01 = particleContainer[czastkaI].howFastAmI().vx - particleContainer[czastkaJ].howFastAmI().vx;
	double dvy01 = particleContainer[czastkaI].howFastAmI().vy - particleContainer[czastkaJ].howFastAmI().vy;

	tmp[0] = 2.0 * particleContainer[czastkaJ].howBigAmI().mass / Mp * (dvx01 * dx01 + dvy01 * dy01) * dx01 / odl01;
	tmp[1] = 2.0 * particleContainer[czastkaJ].howBigAmI().mass / Mp * (dvx01 * dx01 + dvy01 * dy01) * dy01 / odl01;
	tmp[2] = 2.0 * particleContainer[czastkaI].howBigAmI().mass / Mp * (-dvx01 * dx10 - dvy01 * dy10) * dx10 / odl01;
	tmp[3] = 2.0 * particleContainer[czastkaI].howBigAmI().mass / Mp * (-dvx01 * dx10 - dvy01 * dy10) * dy10 / odl01;

    tempr[0] = particleContainer[czastkaI].howFastAmI().vx - tmp[0];
	tempr[1] = particleContainer[czastkaI].howFastAmI().vy - tmp[1];
	tempr[2] = particleContainer[czastkaJ].howFastAmI().vx - tmp[2];
	tempr[3] = particleContainer[czastkaJ].howFastAmI().vy - tmp[3];

    particleContainer[czastkaI].setVelocity(tempr[0], tempr[1]);
    particleContainer[czastkaJ].setVelocity(tempr[2], tempr[3]);

	// ALLEGRO_COLOR zielony = al_map_rgb(0, 255, 0);
	// cz0->color = zielony;
	// cz1->color = zielony;
	// cz0->tlc = 0.0;
	// cz1->tlc = 0.0;

	return true;
}


/**
 * Check if Particle can fit between other particles if not -> re-roll position
 * @param particle
 * @param &particleContainer
 * @param numberOfParticles
 */
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
    int numberOfParticles = 2;
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        Particle Particle(1.0, 1.0, 1.0, 1.0, 1.0, 10.0);
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
        double multiplier = 0.01;
        vx = (g1 / 0.04) * multiplier;
        vy = (g2 / 0.04) * multiplier;
        while (positionAllowed(iterator, particleContainer, numberOfParticles) == false){
            particleContainer[iterator].ramdomizePosition(0, 500);
        }
        particleContainer[iterator].setVelocity(vx, vy);
        cout << vx << vy << endl;
        zeroPositions.push_back(particleContainer[iterator].whereAmI());
    }

    double dt = 6;
    /**
     * Initiate drawing class and launch simulation function
     */
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    int boxX = 800;
    int boxY = 600;
                int czastaI = 0;
                int czastaJ = 1;
                particleContainer[czastaI].setPosition(150, 150);
                particleContainer[czastaJ].setPosition(150, 300);
    ALLEGRO_DISPLAY *display=al_create_display(boxX, boxY);
    bool redraw=true;
    const float FPS=200;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    for(;;){
        ALLEGRO_EVENT ev;   
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_TIMER){
            redraw=true;
        } else if (ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));

            // Takes simulation function
            for(int j=0; j<particleContainer.size(); j++){
                // Get time to colision
                // pairs->clear();
                int czastaI = 0;
                int czastaJ = 1;

                particleContainer[czastaI].setVelocity(0, 3);
                particleContainer[czastaJ].setVelocity(0, 0);
                double dt = 1;
                // s_pair ret_pair(0,0, dt);
                // for (uint64_t c0 = 0; c0 < (particleContainer.size() - 1); c0++)
                // {
                //     for (uint64_t c1 = (c0 + 1); c1 < particleContainer.size(); c1++)
                //     {
                //         if (!(c1 == c0))
                //         {
                //             double tmp_dt = particleContainer[c0].getTimeTOColision(particleContainer[c1].whereAmI(),particleContainer[c1].howFastAmI(),particleContainer[c1].howBigAmI(), boxX, boxY);
                //             if (tmp_dt<dt)
                //             {
                //                 dt = tmp_dt;
                //                 czastaI = c0;
                //                 czastaJ = c1;
                //             }
                //             // pairs->push_back(s_pair(c0, c1, tmp_dt));
                //         }
                //     }
                // }

                zderzenie(particleContainer, czastaI, czastaJ, boxX, boxY);
                

                // velocity counting 
                double velocityX = particleContainer[j].howFastAmI().vx;
                double velocityY = particleContainer[j].howFastAmI().vy;
                cout << velocityX << velocityY << endl;
                double posX = particleContainer[j].whereAmI().x;
                double posY = particleContainer[j].whereAmI().y;

                // Nint
                double x = posX + velocityX * dt;
                x = boxX + (x - boxX * ceil(x/boxX));

                double y = posY + velocityY * dt;
                y = boxY + (y - boxY * ceil(y/boxY));

                particleContainer[j].setPosition(x,y);



                al_draw_filled_circle(particleContainer[j].whereAmI().x ,particleContainer[j].whereAmI().y, particleContainer[j].howBigAmI().radius, al_map_rgb(0,255,0));
            }

            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}

