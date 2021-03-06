#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

typedef struct czasteczka
{
    double x,y;
    double vx,vy;
    double m;
    double r;
}czasteczka;

class czastka
{
private:
    double x,y,vx,vy,m,r;
public:
    czastka():x(0.0),y(0.0),vx(0.0),vy(0.0),m(1.0),r(1.0){}
    czastka(double x,double y,double vx, double vy,double m,double r):x(x),y(y),vx(vx),vy(vy),m(m),r(r){}
    void setvx(double vx){this->vx=vx;}
};

double odleglosc(czasteczka *c, int i,int j)
{
    //dx=dx-nint(dx/rozmiarpx)*rozmiarpx;
    //dy=dx-nint(dy/rozmiarpy)*rozmiarpy;
    double dx=c[i].x-c[j].x;
    double dy=c[i].y-c[j].y;
    return sqrt(dx*dx+dy*dy);
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
 const float FPS=160;
 ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
 al_start_timer(timer);
 ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
 al_register_event_source(event_queue, al_get_display_event_source(display));
 al_register_event_source(event_queue, al_get_timer_event_source(timer));
 srand(time(NULL));

 //czasteczka czasteczki[2];
 const int ilewrzedzie=10;
 const int liczbaczast=ilewrzedzie*ilewrzedzie;
 czasteczka *czasteczki=new czasteczka[liczbaczast];

 double rozmiarpx=500.0,rozmiarpy=500.0;

 double u1,u2,g1,g2;
 int  biezczast=0;
 for(int i=0;i<ilewrzedzie;i++)
 for(int j=0;j<ilewrzedzie;j++)
 {

    czasteczki[biezczast].r=5.0+rand()%10;
    czasteczki[biezczast].m=czasteczki[biezczast].r*czasteczki[biezczast].r*0.1;
    czasteczki[biezczast].x=30.0*i;
    czasteczki[biezczast].y=30.0*j;

    u1=1.0*(rand()%RAND_MAX)/((double)RAND_MAX);
    u2=1.0*(rand()%RAND_MAX)/((double)RAND_MAX);
    g1=sqrt(-2.0*log(u1))*cos(2.0*M_PI*u2);
    g2=sqrt(-2.0*log(u1))*sin(2.0*M_PI*u2);

    czasteczki[biezczast].vx=g1;
    czasteczki[biezczast].vy=g2;
    biezczast++;
 }

 /*
 for(int i=0;i<ilewrzedzie;i++)
 for(int j=0;j<ilewrzedzie;j++)
 {
    czasteczki[i+j*ilewrzedzie].m=1.0;
    czasteczki[i+j*ilewrzedzie].r=10.0;
    czasteczki[i+j*ilewrzedzie].x=0.0;
    czasteczki[i+j*ilewrzedzie].y=400.0;
    czasteczki[i+j*ilewrzedzie].vx=1.0;
    czasteczki[i+j*ilewrzedzie].vy=0.1;
 }*/

double dt=0.2;

 for(;;)
 {
 ALLEGRO_EVENT ev;
 al_wait_for_event(event_queue,&ev);
 if(ev.type==ALLEGRO_EVENT_TIMER)
 {
 redraw=true;
 }
 else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
 {
 break;
 }
 if(redraw && al_is_event_queue_empty(event_queue))
 {
 redraw = false;
 al_clear_to_color(al_map_rgb(0,0,0));

 al_draw_rectangle(50,50,550,550,al_map_rgb(255,0,0),1);

 for(int j=0;j<liczbaczast;j++)
 al_draw_filled_circle(czasteczki[j].x+50,czasteczki[j].y+50,czasteczki[j].r,al_map_rgb(2* rand()%100,2* rand()%100,2* rand()%100));

 for(int i=0;i<liczbaczast;i++)
 {
     czasteczki[i].x=czasteczki[i].x-floor(czasteczki[i].x/rozmiarpx)*rozmiarpx;
     czasteczki[i].y=czasteczki[i].y-floor(czasteczki[i].y/rozmiarpy)*rozmiarpy;
 }

 for(int i=0;i<liczbaczast;i++)
 for(int j=i+1;j<liczbaczast;j++)
 if(odleglosc(czasteczki,i,j)<czasteczki[i].r+czasteczki[j].r)
 {
     double temp[4];
     temp[0]=czasteczki[i].vx-2.0*czasteczki[j].m/(czasteczki[i].m+czasteczki[j].m)*((czasteczki[i].vx-czasteczki[j].vx)*(czasteczki[i].x-czasteczki[j].x)+(czasteczki[i].vy-czasteczki[j].vy)*(czasteczki[i].y-czasteczki[j].y))*(czasteczki[i].x-czasteczki[j].x)/odleglosc(czasteczki,i,j)/odleglosc(czasteczki,i,j);
     temp[1]=czasteczki[i].vy-2.0*czasteczki[j].m/(czasteczki[i].m+czasteczki[j].m)*((czasteczki[i].vx-czasteczki[j].vx)*(czasteczki[i].x-czasteczki[j].x)+(czasteczki[i].vy-czasteczki[j].vy)*(czasteczki[i].y-czasteczki[j].y))*(czasteczki[i].y-czasteczki[j].y)/odleglosc(czasteczki,i,j)/odleglosc(czasteczki,i,j);
     temp[2]=czasteczki[j].vx-2.0*czasteczki[i].m/(czasteczki[i].m+czasteczki[j].m)*((czasteczki[j].vx-czasteczki[i].vx)*(czasteczki[j].x-czasteczki[i].x)+(czasteczki[j].vy-czasteczki[i].vy)*(czasteczki[j].y-czasteczki[i].y))*(czasteczki[j].x-czasteczki[i].x)/odleglosc(czasteczki,i,j)/odleglosc(czasteczki,i,j);
     temp[3]=czasteczki[j].vy-2.0*czasteczki[i].m/(czasteczki[i].m+czasteczki[j].m)*((czasteczki[j].vx-czasteczki[i].vx)*(czasteczki[j].x-czasteczki[i].x)+(czasteczki[j].vy-czasteczki[i].vy)*(czasteczki[j].y-czasteczki[i].y))*(czasteczki[j].y-czasteczki[i].y)/odleglosc(czasteczki,i,j)/odleglosc(czasteczki,i,j);
     czasteczki[i].vx=temp[0];
     czasteczki[i].vy=temp[1];
     czasteczki[j].vx=temp[2];
     czasteczki[j].vy=temp[3];
 }

 for(int j=0;j<liczbaczast;j++)
 {
    czasteczki[j].x=czasteczki[j].x+czasteczki[j].vx*dt;
    czasteczki[j].y=czasteczki[j].y+czasteczki[j].vy*dt;
 }

 al_flip_display();
 }
 }
 al_destroy_timer(timer);
 al_destroy_display(display);
 al_destroy_event_queue(event_queue);
 return 0;
}

