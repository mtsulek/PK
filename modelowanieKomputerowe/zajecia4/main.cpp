#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

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

void rysujwykres(ALLEGRO_BITMAP *histogram, double *x, double *y, int n, ALLEGRO_FONT *czcionka, char const *tytul){
    int rx=al_get_bitmap_width(histogram);
    int ry=al_get_bitmap_height(histogram);
    double bok=0.1;
    al_set_target_bitmap(histogram);
    al_clear_to_color(al_map_rgb(255,255,255));
    ALLEGRO_COLOR czarny=al_map_rgb(0,0,0);
    ALLEGRO_COLOR czerwony=al_map_rgb(255,0,0);
    al_draw_line(bok*rx,(1.0-bok)*ry,(1.0-bok)*rx,(1.0-bok)*ry,czarny,1.0);
    al_draw_line(bok*rx,(1.0-bok)*ry,bok*rx,bok*ry,czarny,1.0);
    al_draw_line(bok*rx,bok*ry,(1.0-bok)*rx,bok*ry,czarny,1.0);
    al_draw_line((1.0-bok)*rx,(1.0-bok)*ry,(1.0-bok)*rx,bok*ry,czarny,1.0);
    al_draw_text(czcionka,czerwony,rx/2.0,0.5*bok*ry,ALLEGRO_ALIGN_CENTER,tytul);
    al_draw_text(czcionka,czerwony,bok*rx/2.0,0.5*ry,ALLEGRO_ALIGN_CENTER,"Y");
    al_draw_text(czcionka,czerwony,rx/2.0,ry-0.5*bok*ry,ALLEGRO_ALIGN_CENTER,"X");
}

void rysujdeske(ALLEGRO_BITMAP *bitmapa,int *drogakulki, int *danehist, int rz, int gx, int gy,  ALLEGRO_FONT *czcionka, char const *tytul){
    int rx=al_get_bitmap_width(bitmapa);
    int ry=al_get_bitmap_height(bitmapa);
    al_set_target_bitmap(bitmapa);
    al_clear_to_color(al_map_rgb(255,255,255));
    ALLEGRO_COLOR czarny=al_map_rgb(0,0,0);
    ALLEGRO_COLOR czerwony=al_map_rgb(255,0,0);
    ALLEGRO_COLOR niebieski=al_map_rgb(0,0,255);
    al_draw_text(czcionka,czerwony,rx/2.0,0.1*ry,ALLEGRO_ALIGN_CENTER,tytul);
    double xekran,yekran;

    for(int j=0;j<rz;j++){
        al_draw_filled_rectangle((j+1)*rx/(rz+1.0)-5,ry-danehist[j],(j+1)*rx/(rz+1.0)+5,ry,niebieski);
    }

    for(int i=1;i<=rz;i++)
        for(int j=1;j<=i;j++){
            xekran=j*rx/(rz+1.0);
            yekran=i*ry/(rz+1.0);
            al_draw_filled_circle(xekran,yekran,5,czarny);
        }
        for(int i=1;i<=rz;i++){
        xekran=(drogakulki[i-1]+1)*rx/(rz+1.0);
        yekran=i*ry/(rz+1.0);
        al_draw_filled_circle(xekran,yekran,18,czerwony);
        }
}

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

            rysujdeske(bitmapka, droga, danehist,rz,j,rz,czcionka,"Nazywam się Diego.");
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
