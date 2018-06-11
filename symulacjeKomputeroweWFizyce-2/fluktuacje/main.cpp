#include <allegro5/allegro.h> 
#include <allegro5/allegro_primitives.h> 
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 
int main(int argc, char **argv) 
{ 
    al_init(); 
    al_install_keyboard(); 
    al_install_mouse(); 
    al_init_primitives_addon(); 
    ALLEGRO_DISPLAY *display=al_create_display(800, 600); 
    bool redraw=true; 
    const float FPS=10000; 
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS); 
    al_start_timer(timer); 
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue(); 
    al_register_event_source(event_queue, 
    al_get_display_event_source(display)); 
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); 
    const int N=800; 
    short int spiny[N]; 
    for(int i=0;i<N;i++)spiny[i]=-1+2*(rand()%2); 
    ALLEGRO_COLOR niebieski=al_map_rgb(0,0,255); 
    ALLEGRO_COLOR czerwony=al_map_rgb(255,0,0); 
    int losowyspin; 
    double deltaE; 
    double T=1.0; 
    double k=1.0; 
    double expB; 
    double liczbalosowa; 
    double M,Esr; 
    int licznik=0; 
    double pole=-0.1; 
    fprintf(stdout,"M\t\tE\n"); 
    while(1){ 
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
            losowyspin=rand()%N; 
            if(losowyspin==0)deltaE=2.0*spiny[0]*(spiny[N-1]+spiny[1]); 
            else if(losowyspin==N-1)deltaE=2.0*spiny[N-1]*(spiny[N-2]+spiny[0]); 
            else deltaE=2.0*spiny[losowyspin]*(spiny[losowyspin-1]+spiny[losowyspin+1]); 
            deltaE+=2.0*pole*spiny[losowyspin]; 
            if(deltaE<0.0){ 
                spiny[losowyspin]*=-1; 
            }else{ 
                expB=exp(-deltaE/(k*T)); 
                liczbalosowa=(double)(rand()%RAND_MAX)/((double)RAND_MAX); 
                if(liczbalosowa < expB)spiny[losowyspin]*=-1; 
            } 
            if(licznik++%100==0){ 
                M=0.0; 
                for(int i=0;i<N;i++)M+=spiny[i]/(double)N; 
                Esr=0.0; 
                for(int i=1;i<N-1;i++)Esr+=-spiny[i]*(spiny[i-1]+spiny[i+1]); 
                Esr+=-spiny[0]*(spiny[N-1]+spiny[1]); 
                Esr+=-spiny[N-1]*(spiny[N-2]+spiny[0]);
                Esr/=(2.0*N); 
                fprintf(stdout,"%lf\t%lf\n",M,Esr); 
            } 
            for(int i=0;i<N;i++){ 
                if(spiny[i]==-1){
                    al_draw_arc(400,300,250,i*2.0*M_PI/(double)N,2.0*M_PI/(double)N,niebieski,50); 
                }else{
                    al_draw_arc(400,300,250,i*2.0*M_PI/(double)N,2.0*M_PI/(double)N,czerwony,50); 
                }
            } 
            al_flip_display(); 
        }
    } 
    al_destroy_timer(timer); 
    al_destroy_display(display); 
    al_destroy_event_queue(event_queue); 
    return 0; 
} 
