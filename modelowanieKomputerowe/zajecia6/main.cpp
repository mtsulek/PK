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

double findmin(double *x,int n){
    double wynik=x[0];
    for(int i=1;i<n;i++)if(x[i]<wynik)wynik=x[i];
    return wynik;
}
double findmax(double *x,int n){
    double wynik=x[0];
    for(int i=1;i<n;i++)if(x[i]>wynik)wynik=x[i];
    return wynik;
}

int findmin(int *x,int n){
    int wynik=x[0];
    for(int i=1;i<n;i++)if(x[i]<wynik)wynik=x[i];
    return wynik;
}
int findmax(int *x,int n){
    int wynik=x[0];
    for(int i=1;i<n;i++)if(x[i]>wynik)wynik=x[i];
    return wynik;
}

void rysujkulki(ALLEGRO_BITMAP *bitmapa, double *kulkix,double *kulkiy, int
ilekulek, double rkulki){
    int rx=al_get_bitmap_width(bitmapa);
    int ry=al_get_bitmap_height(bitmapa);
    al_set_target_bitmap(bitmapa);
    al_clear_to_color(al_map_rgb(255,255,255));
    ALLEGRO_COLOR czarny=al_map_rgb(0,0,0);
    ALLEGRO_COLOR czerwony=al_map_rgb(255,0,0);
    ALLEGRO_COLOR niebieski=al_map_rgb(0,0,255);
    double xekran,yekran;
    double xmin=findmin(kulkix,ilekulek),xmax=findmax(kulkix,ilekulek),
            ymin=findmin(kulkiy,ilekulek),ymax=findmax(kulkiy,ilekulek);

    double trueskala;
    if (rx < ry) trueskala = rx;
    else trueskala = ry;
    double rkulkiekran = 0.5 * rkulki * trueskala / 30.0;

    for(int i=0;i<ilekulek;i++){
        xekran=(xmax-kulkix[i])/(xmax-xmin)*trueskala;
        yekran=(ymax-kulkiy[i])/(ymax-ymin)*trueskala;
        al_draw_filled_circle(xekran,yekran,rkulki,czerwony);
    }
}




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
    ALLEGRO_FONT *czcionka=al_load_ttf_font("czcionka.ttf",24,0);
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

    double losx, losy;
    double a = 30.0;
    losx = a*(rand()%RAND_MAX)/((double)RAND_MAX);
    losy = a*(rand()%RAND_MAX)/((double)RAND_MAX);
    wspx[0] = losx;
    wspy[0] = losy;
    bool przekrywasie = false;

    // do{
    //     przekrywasie = false;
    //     losx = a*(rand()%RAND_MAX)/((double)RAND_MAX);
    //     losy = a*(rand()%RAND_MAX)/((double)RAND_MAX);

    //     for(int i = 0; i <= licznik; i++){
    //         double odl2 = (wspx[i] - losx) * (wspx[i] - losx)
    //                     + (wspy[i] - losy) * (wspy[i] - losy);
    //         if (odl2 < 1.0){
    //             przekrywasie = true;
    //             break;
    //         }
    //     }
    
    //     if(przekrywasie == false){
    //         licznik++;
    //         wspx[licznik] = losx;
    //         wspy[licznik] = losy;
    //     }

    // }while(licznik < n);


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

            if(licznik < n){
                przekrywasie = false;
                losx = a*(rand()%RAND_MAX)/((double)RAND_MAX);
                losy = a*(rand()%RAND_MAX)/((double)RAND_MAX);

                for(int i = 0; i <= licznik; i++){
                    double odl2 = (wspx[i] - losx) * (wspx[i] - losx)
                                + (wspy[i] - losy) * (wspy[i] - losy);
                    if (odl2 < 1.0){
                        przekrywasie = true;
                        break;
                    }
                }
            
                if(przekrywasie == false){
                    licznik++;
                    wspx[licznik] = losx;
                    wspy[licznik] = losy;
                }

            }

            rysujkulki(bitmapka,wspx,wspy,n,1);
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