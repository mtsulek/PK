#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
using namespace std;

typedef struct czasteczka{
    double x, y, vx, vy, m, r;
}czasteczka;

double odleglosc(czasteczka *c, int i, int j){
    double dx = c[i].x - c[j].x;
    double dy = c[i].y - c[j].y;
    return sqrt(dx * dx + dy * dy);
}

//
int main(int argc, char **argv)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    ALLEGRO_DISPLAY *display=al_create_display(800, 600);
    ALLEGRO_BITMAP *bitmapka=al_create_bitmap(800,600);
    bool redraw=true;
    const float FPS=60;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    srand(time(NULL));
    const int n=600;
    double *wspx=(double *)malloc(n*sizeof(double));
    double *wspy=(double *)malloc(n*sizeof(double));
    int licznik=0;

    // 
    double dt = 0.1; 
    czasteczka czasteczki[2];
    czasteczki[0].m =   1;
    czasteczki[0].r =   50;
    czasteczki[0].x =   0;
    czasteczki[0].y =   200;
    czasteczki[0].vx =  14;
    czasteczki[0].vy =  0;

    czasteczki[1].m =   1;
    czasteczki[1].r =   50;
    czasteczki[1].x =   800;
    czasteczki[1].y =   220;
    czasteczki[1].vx =  -14;
    czasteczki[1].vy =  0;
    // 

    for(;;){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_TIMER){
            redraw=true;
        }else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            // 
            al_draw_filled_circle(czasteczki[0].x, czasteczki[0].y,  czasteczki[0].r, al_map_rgb(0, 200, 244));
            al_draw_filled_circle(czasteczki[1].x, czasteczki[1].y,  czasteczki[1].r, al_map_rgb(244, 200, 0));

            if (odleglosc(czasteczki, 0, 1) <= czasteczki[0].r + czasteczki[1].r){

                double tmp[4];

                tmp[0] = czasteczki[0].vx - 2*czasteczki[1].m/(czasteczki[0].m + czasteczki[1].m)
                                *((czasteczki[0].vx - czasteczki[1].vx) * (czasteczki[0].x - czasteczki[1].x)
                                + (czasteczki[0].vy - czasteczki[1].vy) * (czasteczki[0].y - czasteczki[1].y)
                                )*(czasteczki[0].x - czasteczki[1].x) / odleglosc(czasteczki, 0, 1)
                                /  odleglosc(czasteczki, 0, 1);

                tmp[1] = czasteczki[0].vy - 2*czasteczki[1].m/(czasteczki[0].m + czasteczki[1].m)
                                *((czasteczki[0].vx - czasteczki[1].vx) * (czasteczki[0].x - czasteczki[1].x)
                                + (czasteczki[0].vy - czasteczki[1].vy) * (czasteczki[0].y - czasteczki[1].y)
                                )*(czasteczki[0].y - czasteczki[1].y) / odleglosc(czasteczki, 0, 1)
                                /  odleglosc(czasteczki, 0, 1);

                tmp[2] = czasteczki[1].vx - 2*czasteczki[0].m/(czasteczki[1].m + czasteczki[0].m)
                                *((czasteczki[1].vx - czasteczki[0].vx) * (czasteczki[1].x - czasteczki[0].x)
                                + (czasteczki[1].vy - czasteczki[0].vy) * (czasteczki[1].y - czasteczki[0].y)
                                )*(czasteczki[1].x - czasteczki[0].x) / odleglosc(czasteczki, 0, 1)
                                /  odleglosc(czasteczki, 0, 1);

                tmp[3] = czasteczki[1].vy - 2*czasteczki[0].m/(czasteczki[1].m + czasteczki[0].m)
                                *((czasteczki[1].vx - czasteczki[0].vx) * (czasteczki[1].x - czasteczki[0].x)
                                + (czasteczki[1].vy - czasteczki[0].vy) * (czasteczki[1].y - czasteczki[0].y)
                                )*(czasteczki[1].y - czasteczki[0].y) / odleglosc(czasteczki, 0, 1)
                                /  odleglosc(czasteczki, 0, 1);





                czasteczki[0].vx = tmp[1];
                czasteczki[0].vy = tmp[0];
                czasteczki[1].vx = tmp[3];
                czasteczki[1].vy = tmp[2];
            }



            czasteczki[0].x = czasteczki[0].x + czasteczki[0].vx * dt;
            czasteczki[0].y = czasteczki[0].y + czasteczki[0].vy * dt;
            czasteczki[1].x = czasteczki[1].x + czasteczki[1].vx * dt;
            czasteczki[1].y = czasteczki[1].y + czasteczki[1].vy * dt;

            // 
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(bitmapka,0,0,0);
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}