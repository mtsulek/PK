#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

typedef struct czasteczka{
    double x,y;
    double vx,vy;
    double vx0,vy0;
    double r;
    double m;
}czasteczka;

double odleglosc(czasteczka *c,int i,int j){
    double x1=c[i].x;
    double y1=c[i].y;
    double x2=c[j].x;
    double y2=c[j].y;
    double dx=x2-x1;
    double dy=y2-y1;
    return sqrt(dx*dx+dy*dy);
}

double xponasznint(double x, double boxsize){
    return x-floor(x/boxsize+0.5)*boxsize;
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
    bool redraw=true;
    const float FPS=1;
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    srand(time(NULL));
    const int ilewrzedzie=5;
    const int liczbaczast=ilewrzedzie*ilewrzedzie;
    czasteczka *czasteczki=new czasteczka[liczbaczast];
    double romiarpudlax=25.0,romiarpudlay=25.0;
    double u1,u2,g1,g2;
    int biezczast=0;
    for(int i=0;i<ilewrzedzie;i++)
    for(int j=0;j<ilewrzedzie;j++){
        czasteczki[biezczast].r=0.5;
        czasteczki[biezczast].m=1.0;
        czasteczki[biezczast].x=2.5*i;
        czasteczki[biezczast].y=4.0*j;
        u1=1.0*(rand()%RAND_MAX)/((double)RAND_MAX);
        u2=1.0*(rand()%RAND_MAX)/((double)RAND_MAX);
        g1=sqrt(-2.0*log(u1))*cos(2.0*M_PI*u2);
        g2=sqrt(-2.0*log(u1))*sin(2.0*M_PI*u2);
        czasteczki[biezczast].vx=g1/0.04;
        czasteczki[biezczast].vy=g2/0.04;//manipulacja temperatury
        biezczast++;
    }
    double dt=0.01, t=0.0;
    double odl12,dxij,dxji,dyij,dyji;
    double dr=1.0;
    double rho=ilewrzedzie*ilewrzedzie/(romiarpudlax*romiarpudlay);
    double eta=M_PI*(10.0*2.0)*(10.0*2.0)*rho/4.0;
    double n[100];
    double gr[100];
    double Ek;
    double **tij;
    tij=(double **)malloc(liczbaczast*sizeof(double *));
    for(int i=0;i<liczbaczast;i++)tij[i]=(double *)malloc(liczbaczast*sizeof(double));
    for(int i=0;i<liczbaczast;i++)
    for(int j=0;j<liczbaczast;j++)tij[i][j]=10e10;

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


            double drx,dry,dvx,dvy,bij,vij,rij;
            for(int i=0;i<liczbaczast;i++){
                for(int j=i+1;j<liczbaczast;j++){
                    drx=czasteczki[j].x-czasteczki[i].x;
                    dry=czasteczki[j].y-czasteczki[i].y;
                    dvx=czasteczki[j].vx-czasteczki[i].vx;
                    dvy=czasteczki[j].vy-czasteczki[i].vy;
                    bij=drx*dvx+dry*dvy;
                    vij=sqrt(dvx*dvx+dvy*dvy);
                    rij=odleglosc(czasteczki,i,j);
                    if(bij*bij-vij*vij*(rij*rij-1.0)<0.0)tij[i][j]=10e10;
                    else
                    tij[i][j]=(-bij-sqrt(bij*bij-vij*vij*(rij*rij-1.0)))/(vij*vij);
                    if(tij[i][j]<0.0)tij[i][j]=10e10;
                }
            }
        double tmin;
        tmin=tij[0][1];
        int ktorai=0,ktoraj=1;

        for(int i=0;i<liczbaczast;i++){
            for(int j=i+1;j<liczbaczast;j++){
                if(tij[i][j]<tmin&&tij[i][j]>=1e-10){
                    tmin=tij[i][j];
                    ktorai=i;
                    ktoraj=j;
                }
            }
        }

        for(int i=0;i<liczbaczast;i++){
            czasteczki[i].x+=czasteczki[i].vx*tmin;
            czasteczki[i].y+=czasteczki[i].vy*tmin;
        }

        drx=czasteczki[ktoraj].x-czasteczki[ktorai].x;
        dry=czasteczki[ktoraj].y-czasteczki[ktorai].y;
        dvx=czasteczki[ktoraj].vx-czasteczki[ktorai].vx;
        dvy=czasteczki[ktoraj].vy-czasteczki[ktorai].vy;
        bij=drx*dvx+dry*dvy;
        czasteczki[ktorai].vx+=bij*drx;
        czasteczki[ktorai].vy+=bij*dry;
        czasteczki[ktoraj].vx-=bij*drx;
        czasteczki[ktoraj].vy-=bij*dry;

        cout<<tmin<<endl;

        for(int j=0;j<liczbaczast;j++){
            al_draw_filled_circle(czasteczki[j].x*20+50,czasteczki[j].y*20+50,20*czasteczki[j].r,al_map_rgb(0,255,0));
            al_draw_line(czasteczki[j].x*20+50, czasteczki[j].y*20+50, czasteczki[j].x*20+50 + 1 *(czasteczki[j].vx) ,czasteczki[j].y*20+50 + 1 * (czasteczki[j].vy) ,al_map_rgb(0,255,0), 1);
        }

        al_draw_filled_circle(czasteczki[ktorai].x*20+50,czasteczki[ktorai].y*20+50,20*czasteczki[ktorai].r,al_map_rgb(255,0,0));
        al_draw_filled_circle(czasteczki[ktoraj].x*20+50,czasteczki[ktoraj].y*20+50,20*czasteczki[ktoraj].r,al_map_rgb(255,0,0));


        al_flip_display();
        }
    }

al_destroy_timer(timer);
al_destroy_display(display);
al_destroy_event_queue(event_queue);
return 0;
}
