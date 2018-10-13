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
double rozmiarpudlax = 25.0;
double rozmiarpudlay = 25.0;

int nint(double a)
{
    int b;
    double a2 = a;
    if (a2 < 0)
        b = (int)(a2 - 0.5);
    else
        b = (int)(a2 + 0.5);
    return b;
}

typedef struct czasteczka
{
    double x, y;
    double vx, vy;
    double vx0, vy0;
    double r;
    double m;
} czasteczka;

double odleglosc(czasteczka *c, int i, int j)
{
    double x1 = c[i].x;
    double y1 = c[i].y;
    double x2 = c[j].x;
    double y2 = c[j].y;
    double dx = x2 - x1;
    dx = dx - nint(dx / rozmiarpudlax) * rozmiarpudlax;
    double dy = y2 - y1;
    dy = dy - nint(dy / rozmiarpudlay) * rozmiarpudlay;
    return sqrt(dx * dx + dy * dy);
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
    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    bool redraw = true;
    const float FPS = 10;
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    srand(time(NULL));


    const int liczbaczast = 100;
    czasteczka *czasteczki = new czasteczka[liczbaczast];
    double u1, u2, g1, g2;
    int biezczast = 0;

    double max = 25;
    double min = 25;

	int value = ((max - min) + 1) + min;
	// double x = rand() % value;
	// double y = rand() % value;

    for (int i = 0; i < liczbaczast; i++)
        {
            czasteczki[biezczast].r = 0.5;
            czasteczki[biezczast].m = 1.0;
            bool positionAllowed = false;
            while (positionAllowed == false){
                czasteczki[biezczast].x = rand() % value;;
                czasteczki[biezczast].y = rand() % value;;
                for(int iteration = 0; iteration < liczbaczast; iteration++){
                    if(liczbaczast != iteration){
                        double distanceOfTwo = odleglosc(czasteczki, liczbaczast, iteration);
                        double radiusOfTwo = czasteczki[liczbaczast].r + czasteczki[iteration].r;
                        if(distanceOfTwo < radiusOfTwo){
                        // return false;
                        positionAllowed = false;
                        }
                    }
                }
                // return true;
                positionAllowed =true;

            }



            double u2 = drand48();
            double u1 = drand48();
            double g1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
            double g2 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);
            double multiplier = 0.01;
            czasteczki[biezczast].vx0 = (g1 / 0.04) * multiplier;
            czasteczki[biezczast].vy0 = (g2 / 0.04) * multiplier;
            czasteczki[biezczast].vx = czasteczki[biezczast].vx0;
            czasteczki[biezczast].vy = czasteczki[biezczast].vy0;
            biezczast++;
        }
    double t = 0.0;
    double **tij;
    tij = (double **)malloc(liczbaczast * sizeof(double *));
    for (int i = 0; i < liczbaczast; i++)
        tij[i] = (double *)malloc(liczbaczast * sizeof(double));
    for (int i = 0; i < liczbaczast; i++)
        for (int j = 0; j < liczbaczast; j++)
            tij[i][j] = 10e10;
    for (;;)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            double drx, dry, dvx, dvy, bij, vij, rij;
            for (int i = 0; i < liczbaczast; i++)
                for (int j = i + 1; j < liczbaczast; j++)
                {
                    drx = czasteczki[j].x - czasteczki[i].x;
                    drx = drx - nint(drx / rozmiarpudlax) * rozmiarpudlax;
                    dry = czasteczki[j].y - czasteczki[i].y;
                    dry = dry - nint(dry / rozmiarpudlay) * rozmiarpudlay;
                    dvx = czasteczki[j].vx - czasteczki[i].vx;
                    dvy = czasteczki[j].vy - czasteczki[i].vy;
                    bij = drx * dvx + dry * dvy;
                    vij = sqrt(dvx * dvx + dvy * dvy);
                    rij = odleglosc(czasteczki, i, j);
                    if (bij * bij - vij * vij * (rij * rij - 1.0) < 0.0)
                        tij[i][j] = 10e10;
                    else
                        tij[i][j] = (-bij - sqrt(bij * bij - vij * vij * (rij * rij - 1.0))) / (vij * vij);
                    if (tij[i][j] < 0.0)
                        tij[i][j] = 10e10;
                }
            double tmin;
            tmin = 10e10;
            int ktorai = 0, ktoraj = 1;
            for (int i = 0; i < liczbaczast; i++)
                for (int j = i + 1; j < liczbaczast; j++)
                {
                    if (tij[i][j] < tmin && tij[i][j] >= 0.0)
                    {
                        tmin = tij[i][j];
                        ktorai = i;
                        ktoraj = j;
                    }
                }
            for (int i = 0; i < liczbaczast; i++)
            {
                czasteczki[i].x += czasteczki[i].vx * tmin;
                czasteczki[i].y += czasteczki[i].vy * tmin;
            }
            drx = czasteczki[ktoraj].x - czasteczki[ktorai].x;
            drx = drx - nint(drx / rozmiarpudlax) * rozmiarpudlax;
            dry = czasteczki[ktoraj].y - czasteczki[ktorai].y;
            dry = dry - nint(dry / rozmiarpudlay) * rozmiarpudlay;
            dvx = czasteczki[ktoraj].vx - czasteczki[ktorai].vx;
            dvy = czasteczki[ktoraj].vy - czasteczki[ktorai].vy;
            bij = drx * dvx + dry * dvy;
            czasteczki[ktorai].vx += bij * drx;
            czasteczki[ktorai].vy += bij * dry;
            czasteczki[ktoraj].vx -= bij * drx;
            czasteczki[ktoraj].vy -= bij * dry;
            t += tmin;
            cout << t << endl;
            double wspx, wspy;
            for (int j = 0; j < liczbaczast; j++)
            {
                wspx = czasteczki[j].x - nint(czasteczki[j].x / rozmiarpudlax) * rozmiarpudlax;
                wspy = czasteczki[j].y - nint(czasteczki[j].y / rozmiarpudlay) * rozmiarpudlay;
                al_draw_filled_circle(wspx * 20 + 400, wspy * 20 + 300, czasteczki[j].r * 20, al_map_rgb(0, 255, 0));
            }
            wspx = czasteczki[ktorai].x - nint(czasteczki[ktorai].x / rozmiarpudlax) * rozmiarpudlax;
            wspy = czasteczki[ktorai].y - nint(czasteczki[ktorai].y / rozmiarpudlay) * rozmiarpudlay;
            al_draw_filled_circle(wspx * 20 + 400, wspy * 20 + 300, czasteczki[ktorai].r * 20, al_map_rgb(255, 0, 0));
            wspx = czasteczki[ktoraj].x - nint(czasteczki[ktoraj].x / rozmiarpudlax) * rozmiarpudlax;
            wspy = czasteczki[ktoraj].y - nint(czasteczki[ktoraj].y / rozmiarpudlay) * rozmiarpudlay;
            al_draw_filled_circle(wspx * 20 + 400, wspy * 20 + 300, czasteczki[ktoraj].r * 20, al_map_rgb(255, 0, 0));
            for (int j = 0; j < liczbaczast; j++)
            {
                wspx = czasteczki[j].x - nint(czasteczki[j].x / rozmiarpudlax) * rozmiarpudlax;
                wspy = czasteczki[j].y - nint(czasteczki[j].y / rozmiarpudlay) * rozmiarpudlay;
                al_draw_line(wspx * 20 + 400, wspy * 20 + 300, wspx * 20 + 400 + czasteczki[j].vx,
                             wspy * 20 + 300 + czasteczki[j].vy, al_map_rgb(255, 255, 255), 1);
            }
            al_flip_display();
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}