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
typedef struct predkosc 
{ 
    double vx,vy; 
}predkosc; 
int main(int argc, char **argv) 
{ 
 al_init(); 
 al_install_keyboard(); 
 al_install_mouse(); 
 al_init_primitives_addon(); 
 const int N=100; 
 predkosc v[N]; 
 predkosc v0[N]; 
 for(int i=0;i<N;i++) 
 { 
     double u1=(double)(1+rand()%RAND_MAX)/(1+(double)RAND_MAX); 
     double u2=(double)(1+rand()%RAND_MAX)/(1+(double)RAND_MAX); 
     double g1=sqrt(-2.0*log(u1))*cos(2.0*M_PI*u2);
     double g2=sqrt(-2.0*log(u1))*sin(2.0*M_PI*u2);
     v[i].vx=g1; 
     v[i].vy=g2; 
 } 
 double Ek; 
 double m=1.0; 
 Ek=0.0; 
  for(int i=0;i<N;i++) 
 { 
     Ek+=0.5*m*(v[i].vx*v[i].vx+v[i].vy*v[i].vy); 
 } 
 Ek/=(double)N; 
 cout<<Ek<<endl; 
 double Ekpoz=0.5; 
 for(int i=0;i<N;i++) 
 { 
     v[i].vx*=sqrt(Ekpoz/Ek); 
     v[i].vy*=sqrt(Ekpoz/Ek); 
  } 
 Ek=0.0; 
 for(int i=0;i<N;i++) 
 { 
     Ek+=0.5*m*(v[i].vx*v[i].vx+v[i].vy*v[i].vy); 
 } 
  Ek/=(double)N; 
  cout<<Ek<<endl; 
  for(int i=0;i<N;i++) 
 { 
     v0[i].vx=v[i].vx; 
     v0[i].vy=v[i].vy; 
 } 
 ALLEGRO_DISPLAY *display=al_create_display(800, 600); 
 bool redraw=true; 
 const float FPS=50; 
 ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS); 
 al_start_timer(timer); 
 ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue(); 
 al_register_event_source(event_queue, al_get_display_event_source(display)); 
 al_register_event_source(event_queue, al_get_timer_event_source(timer)); 
 double dt=0.01,t=0.0; 
 double vacf=0.0; 
 cout<<"VACF:"<<endl; 
 FILE *plik=fopen("wynik.txt","w"); 
 while(1) 
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
 vacf=0.0; 
 for(int i=0;i<N;i++) 
 { 
     vacf+=v0[i].vx*v[i].vx+v0[i].vy*v[i].vy; 
 } 
 double vacfnorm=0.0; 
 for(int i=0;i<N;i++) 
 { 
     vacfnorm+=v0[i].vx*v0[i].vx+v0[i].vy*v0[i].vy;
 } 
 vacf/=vacfnorm; 
 cout<<vacf<<endl; 
 fprintf(plik,"%lf\t%lf\n",t,vacf); 
 for(int i=0;i<N;i++) 
 { 
     double u1=(double)(1+rand()%RAND_MAX)/(1+(double)RAND_MAX); 
     double u2=(double)(1+rand()%RAND_MAX)/(1+(double)RAND_MAX); 
     double g1=sqrt(-2.0*log(u1))*cos(2.0*M_PI*u2)*
0.1; 
     double g2=sqrt(-2.0*log(u1))*sin(2.0*M_PI*u2)*
0.1; 
     v[i].vx+=g1; 
     v[i].vy+=g2; 
 } 
 Ek=0.0; 
 for(int i=0;i<N;i++) 
 { 
     Ek+=0.5*m*(v[i].vx*v[i].vx+v[i].vy*v[i].vy); 
 } 
 Ek/=(double)N; 
 for(int i=0;i<N;i++) 
 { 
     v[i].vx*=sqrt(Ekpoz/Ek); 
     v[i].vy*=sqrt(Ekpoz/Ek); 
  } 
 t+=dt; 
 for(int j=0;j<N;j++) 
 { 
al_draw_filled_rectangle(200,5*j,200+50.0*v0[j].vx,
5*j+3,al_map_rgb(0,0,255)); 
al_draw_filled_rectangle(600,5*j,600+50.0*v0[j].vy,
5*j+3,al_map_rgb(0,0,255)); 
al_draw_filled_rectangle(200,5*j,200+50.0*v[j].vx,5
*j+3,al_map_rgb(255,0,0)); 
al_draw_filled_rectangle(600,5*j,600+50.0*v[j].vy,5
*j+3,al_map_rgb(255,0,0)); 
 } 
 al_flip_display(); 
 } 
 } 
 fclose(plik); 
 al_destroy_timer(timer); 
 al_destroy_display(display); 
 al_destroy_event_queue(event_queue); 
 return 0; 
} 