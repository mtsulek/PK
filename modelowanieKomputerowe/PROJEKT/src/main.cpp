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
#include "Particle.h"

/**
 * Simulation "jobs" to be done
 * @param vector of Particle classes
 */
int simulationFunction(vector<Particle> particle){
    for(int j=0; j<particle.size(); j++){
        al_draw_filled_circle(particle[j].whereAmI().x ,particle[j].whereAmI().y, particle[j].howBigAmI().radius, al_map_rgb(0,255,0));
    }
}

// Create pointer to simulation function
typedef int ( * simulationPointer)(vector<Particle>);
// Allocate function adress to pointer 
simulationPointer simulation = simulationFunction;


/**
 * Class for canvas drawing and simulation
 */
class Allegro{
    private:
    public:
        Allegro(){
            al_init();
            al_install_keyboard();
            al_install_mouse();
            al_init_primitives_addon();
            al_init_font_addon();
            al_init_ttf_addon();
            al_init_image_addon();
        }

        /**
         * Takes size of box and start simulation function
         * @param x
         * @param y
         * @param particleContainer
         */
        int Draw(int x, int y, vector<Particle> particleContainer){
            ALLEGRO_DISPLAY *display=al_create_display(800, 600);
            bool redraw=true;
            const float FPS=1;
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
                    int result = simulation(particleContainer);

                    al_flip_display();
                }
            }
            al_destroy_timer(timer);
            al_destroy_display(display);
            al_destroy_event_queue(event_queue);
            return 0;
        }
};

/**
 * Check if Particle can fit between other particles if not -> re-roll position
 * @param particle
 * @param particleContainer POINTER????
 * @param numberOfParticles
 */
void ifParticleFits(int particle, vector<Particle> particleContainer, int numberOfParticles){
    for(int iteration = 0; iteration < numberOfParticles; iteration++){
        bool conflict = true;
        if(particle != iteration){
            cout << iteration << endl;
            while (conflict == true){
                particleContainer[particle].ramdomizePosition(0, 500);
                double distanceOfTwo = particleContainer[particle].distanceBetweenParticles(particleContainer[iteration].whereAmI());
                double radiusOfTwo = (particleContainer[particle].howBigAmI().radius + particleContainer[iteration].howBigAmI().radius);
                if(distanceOfTwo > radiusOfTwo){
                    cout << distanceOfTwo << endl << particleContainer[iteration].whereAmI().x << ", " <<particleContainer[iteration].whereAmI().y << endl;
                    conflict = false;
                } else {
                    conflict = true;
                }
            }
        }
    }
    particleContainer[2].ramdomizePosition(0, 500);
}

int main(){
    /**
     * Time dependent rand and initiation of particle class vector
     */
    srand(time(NULL));
    vector<Particle> particleContainer;

    /**
     * Create no. Particles classes
     */
    int numberOfParticles = 45;
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        Particle Particle(1.0, 1.0, 1.0, 1.0, 1.0, 5.0);
        particleContainer.push_back(Particle);
    }

    /**
     * Loop for rand position of each Particle
     */
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        ifParticleFits(iterator, particleContainer, 45);
    }

    particleContainer[0].ramdomizePosition(0, 500);

    /**
     * Initiate drawing class and launch simulation function
     */
    Allegro canvas;
    canvas.Draw(800, 600, particleContainer);
}
