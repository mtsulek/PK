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
    double x, y;  
    double vx, vy;  
    double vx0, vy0;
    double m;  
    double r;  
}czasteczka;  

double  odleglosc(czasteczka  *c, int  i, int  j) { 
    double x1 = c[i].x;  
    double y1 = c[i].y;  
    double x2 = c[j].x;  
    double y2 = c[j].y;  
    double dx = x2-x1;  
    double dy = y2-y1;  
    return sqrt(dx*dx+dy*dy);  
} 

double xponasznint(double x,  double boxsize) { 
    return x-floor(x/boxsize+0.5)*boxsize;  
} 


int main(int argc,  char **argv){ 
    al_init();  
    al_install_keyboard();  
    al_install_mouse();  
    al_init_primitives_addon();  
    al_init_font_addon();  
    al_init_ttf_addon();  
    al_init_image_addon();  
    ALLEGRO_DISPLAY *display = al_create_display(800,  600);  
    bool redraw = true;  
    const float FPS = 1;  
    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);  
    al_start_timer(timer);  
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();  
    al_register_event_source(event_queue,  al_get_display_event_source(display));  
    al_register_event_source(event_queue,  al_get_timer_event_source(timer));  
    srand(time(NULL));  

    // STAŁE I DANE

    const int ilewrzedzie = 5;  
    double promienCzastek = 15;
    const int liczbaczast = ilewrzedzie*ilewrzedzie;  
    czasteczka *czasteczki = new czasteczka[liczbaczast];  
    double romiarpudlax = 500.0, romiarpudlay = 500.0;  
    double u1, u2, g1, g2;  
    int biezczast = 0;  
    for(int i = 0; i<ilewrzedzie; i++) 
        for(int j = 0; j<ilewrzedzie; j++){ 
            czasteczki[biezczast].r = promienCzastek;  
            czasteczki[biezczast].m = czasteczki[biezczast].r*czasteczki[biezczast].r*0.1;  
            czasteczki[biezczast].x = 30.0*i;  
            czasteczki[biezczast].y = 30.0*j;  
            u1 = 1.0*(rand()%RAND_MAX)/((double)RAND_MAX);  
            u2 = 1.0*(rand()%RAND_MAX)/((double)RAND_MAX);  
            g1 = sqrt(-2.0*log(u1))*cos(2.0*M_PI*u2);  
            g2 = sqrt(-2.0*log(u1))*sin(2.0*M_PI*u2);  
            czasteczki[biezczast].vx = g1/0.01;  
            czasteczki[biezczast].vy = g2/0.01;  

            czasteczki[biezczast].vy0 = czasteczki[biezczast].vx;  
            czasteczki[biezczast].vx0 = czasteczki[biezczast].vy;  
            biezczast++;  
        } 
    double dt = 0.01, t = 0;  
    double odl12, dxij, dxji, dyij, dyji;  
    double Ek;  
    
    //
    double dr = 1.0;
    // czastki na liczbe objetosci
    double rho = ilewrzedzie * ilewrzedzie / romiarpudlax / romiarpudlay;
    // biny, upakowanie i upakowanie z gestoscia
    double n[100], gr[100];
    // ile kulek do powierzchni;
    double eta = M_PI * rho * (promienCzastek * 2 * promienCzastek * 2)* 100 / 4; //10 z promienia a 2 nie wiem skad

    // STAŁE I DANE 
    double **tij;
    for(int i; i < liczbaczast; i++){
        tij[i] = (double *)malloc(liczbaczast*sizeof(double));
    }

    for(int i; i < liczbaczast; i++){
        for(int j; j < liczbaczast; j++){
            tij[i][j] = 10e10;
        }
    }

    // METODA SYMULACJI DYNAMIKI MOLEKULARNEJ -- STALE
    double drx, dry, dvx, dvy, bij, vij, rij;
    
    for(; ; ){ 
        ALLEGRO_EVENT ev;  
        al_wait_for_event(event_queue, &ev);  
        if(ev.type == ALLEGRO_EVENT_TIMER){ 
            redraw = true;  
        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ 
            break;  
        }

        if(redraw && al_is_event_queue_empty(event_queue)){ 
            redraw  =  false;  

            //PEOGRAM
            al_clear_to_color(al_map_rgb(0, 0, 0));  
            for(int j = 0; j<liczbaczast; j++) 
                al_draw_filled_circle(czasteczki[j].x+50, czasteczki[j].y+50, czasteczki[j].r, al_map_rgb(0, 255, 0));

            // METODA SYMULACJI DYNAMIKI MOLEKULARNEJ -- OBLICZENIA
            for(int i; i < liczbaczast; i++){
                for(int j = i+1; j < liczbaczast; j++){
                    drx = czasteczki[j].x - czasteczki[i].x;
                    dry = czasteczki[j].y - czasteczki[i].y;
                    dvx = czasteczki[j].vx - czasteczki[i].vx;
                    dvy = czasteczki[j].vy - czasteczki[i].vy;

                    bij = drx*dvx + dry*dvy;
                    vij = sqrt(dvx*dvx + dvy*dvy);

                    rij = odleglosc(czasteczki, i, j);
                    if((bij * bij - vij * vij*(rij * rij - 1) < 0)){
                        tij[i][j] = 10e10;
                    }else{
                        tij[i][j] = (-bij - sqrt(bij * bij - vij * vij*(rij * rij - 1)))/(vij * vij);
                    }

                    if(tij[i][j] > 0){

                    }

                }
            }

            double tmin;
            tmin = tij[0][1];
            for(int i; i < liczbaczast; i++){
                for(int j = i+1; j < liczbaczast; j++){
                    if(tij[i][j] < tmin&&tij[i][j] >= 0){
                        tmin = tij[i][j];
                    }
                }
            }

            for(int i = 0; i < liczbaczast; i++){
                tij[i][j] = 10e10;
            }
            



            //Program
            al_flip_display();  
        }
    }

// zrzut danych
    int indeks;

    for(indeks=0; indeks; indeks++){
        n[indeks]=0;
        gr[indeks]=0;
    }

    for(int i = 0; i<liczbaczast; i++){ 
        for(int j = i+1; j<liczbaczast; j++){ 
            odl12 = odleglosc(czasteczki, i, j);
            indeks = odl12/dr;

            if(indeks <= 100){
                n[indeks] += 1;
            }
        }
    }
    for (indeks = 0; indeks <100; indeks++){
        gr[indeks] = n[indeks]/(rho*2*M_PI*(indeks*dr)*dr);
    }
    FILE *plik = fopen("wynik.csv", "w");
    for (indeks=0; indeks<100;indeks++){
        fprintf(plik, "%.5lf\t%.5lf\n", indeks*dr, gr[indeks]);
    }
    //

    al_destroy_timer(timer);  
    al_destroy_display(display);  
    al_destroy_event_queue(event_queue);  
    return 0;  
} 
