#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// FIND IMAGE MAX AND MIN SIZES //
double findmin(double *x,int n){
    double wynik=x[0];
    for(int i=1;i<n;i++)
        if(x[i]<wynik)wynik=x[i];
    return wynik;
}
double findmax(double *x,int n){
    double wynik=x[0];
    for(int i=1;i<n;i++)
        if(x[i]>wynik)wynik=x[i];
    return wynik;
}

// GENERATE AND DRAW BALLS //
void generujkulki(ALLEGRO_BITMAP *bitmapa, double* kulkix, double* kulkiy, int ilekulek, double rkulki){
    int rx=al_get_bitmap_width(bitmapa);
    int ry=al_get_bitmap_height(bitmapa);
    al_set_target_bitmap(bitmapa);
    al_clear_to_color(al_map_rgb(255,255,255));
    ALLEGRO_COLOR czarny=al_map_rgb(0,0,0);
    ALLEGRO_COLOR czerwony=al_map_rgb(255,0,0);
    ALLEGRO_COLOR niebieski=al_map_rgb(0,0,255);
    double xekran,yekran;

    double xmin = findmin(kulkix, ilekulek), xmax = findmax(kulkix, ilekulek);
    double ymin = findmin(kulkiy, ilekulek), ymax = findmax(kulkiy, ilekulek);

    for(int i = 0; i < ilekulek; i++){
        xekran = (xmax - kulkix[i])/(xmax-xmin)*rx;
        yekran = (ymax - kulkix[i])/(ymax-ymin)*ry;
        al_draw_filled_circle(xekran, yekran, rkulki,czerwony);
    }
}



// MAIN //
int main(int argc, char **argv){
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    ALLEGRO_DISPLAY *display=al_create_display(800, 600);
    ALLEGRO_FONT *czcionka=al_load_ttf_font("czcionka.ttf",20,0);
    ALLEGRO_BITMAP *bitmapka=al_create_bitmap(400,600);
    ALLEGRO_BITMAP *histogram=al_create_bitmap(400,600);

    bool redraw=true;
    const float FPS=6;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    srand(time(NULL));

    const int rz=10;

    int licznik[rz][rz];
    int *danehist=(int *)malloc(rz*sizeof(int));
    for(int i=0;i<rz;i++)danehist[i]=0;

    int *droga=(int *)malloc(rz*sizeof(int));
    for(int i=0;i<rz;i++)droga[i]=0;

    int losowa,j;
    for(int i=0;i<rz;i++)for(int k=0;k<rz;k++)licznik[i][k]=0;
    for(int i=0;i<rz;i++)
    for(int j=0;j<rz;j++)
    licznik[i][j]=0;

    int balls=100;

    int ball=0;
    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_TIMER){
            redraw=true;
        }
        else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;  
        }
        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));

            licznik[0][0]++;
            j=0;
            for(int i=1;i<rz;i++){
                losowa=rand()%2;
                if(losowa==1)j++;
                licznik[i][j]++;
                droga[i]=j;
            }
            danehist[j]++;

            ball++;

            generujkulki(bitmapka, , , 1, 15);
            // rysujwykres(bitmapka,danehist,rz,j,rz,czcionka,"Nazywam się Diego...");
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(bitmapka,0,0,0);
            al_draw_bitmap(histogram,400,0,0);
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
