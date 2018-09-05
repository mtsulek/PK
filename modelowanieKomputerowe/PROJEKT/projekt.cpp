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

class Allegro{
    private:

    public:
        Allegro(){
            // Initialization
            al_init();
            al_install_keyboard();
            al_install_mouse();
            al_init_primitives_addon();
            al_init_font_addon();
            al_init_ttf_addon();
            al_init_image_addon();
        }

        int Draw(int x, int y, vector<Particle> particle){
            // Takes size of box and start simulation function
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
                    simulationFunction(particle);

                    al_flip_display();
                }
            }
            al_destroy_timer(timer);
            al_destroy_display(display);
            al_destroy_event_queue(event_queue);
            return 0;
        }

        void simulationFunction(vector<Particle> particle){
            for(int j=0; j<particle.size(); j++){
                al_draw_filled_circle(particle[j].whereAmI().x*20+50 ,particle[j].whereAmI().y*20+50, particle[j].howBigAmI().radius, al_map_rgb(0,255,0));
            }
        }
};

int main(){
    
    // Obvious
    srand(time(NULL));
    vector<Particle> particleContainer;

    // Create no. particles
    int numberOfParticles = 45;
    for(int iterator = 0; iterator < numberOfParticles; iterator++){
        Particle Particle(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
        particleContainer.push_back(Particle);
    }

    // Give random position to each particle
    for(int particle = 0; particle < particleContainer.size(); particle++){
        particleContainer[particle].ramdomizePosition(0, 25);
        
        // Check if particles can fit
        for(int iterator = particle; iterator < particleContainer.size(); iterator++){
            double distanceOfTwo = particleContainer[particle].distanceBetweenParticles(particleContainer[iterator+1].whereAmI());
            double radiusOfTwo = (particleContainer[particle].howBigAmI().radius + particleContainer[iterator].howBigAmI().radius);
            if(distanceOfTwo < radiusOfTwo){
                cout << "Nie mieszczę się! \n";
                // HERE REROLL POSITION
            } else {
                cout << "Wejszłem! \n";
            }
            // TO BE CONTINUED!!!
        }
    }

    // Measure distance between particle 
    cout << particleContainer[0].distanceBetweenParticles(particleContainer[1].whereAmI()) << endl;
    cout << (particleContainer[0].howBigAmI().radius + particleContainer[1].howBigAmI().radius) << endl;

    // Initiate drawing class and launch simulation function
    Allegro simulation;
    simulation.Draw(800, 600, particleContainer);
}