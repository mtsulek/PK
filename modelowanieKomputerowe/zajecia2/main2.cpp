#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>


double findmin(double *x, int n){
    double wynik = x[0];
    for(int i = 0; i < n; i++){
        if (x[i] < wynik) wynik = x[i];
    }
    return wynik;
}

double findmax(double *x, int n){
    double wynik = x[0];
    for(int i = 0; i < n; i++){
        if (x[i] < wynik) wynik = x[i];
    }
    return wynik;
}

void rysujwykres(ALLEGRO_BITMAP *bitmapa,double *x,double *y,int n,
ALLEGRO_FONT *czcionka, char const *tytul){
    int rx = al_get_bitmap_width(bitmapa);
    int ry = al_get_bitmap_height(bitmapa);
    double bok = 0.1;
    al_set_target_bitmap(bitmapa);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    ALLEGRO_COLOR czarny = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR czerwony = al_map_rgb(255, 0, 0);
    al_draw_line(bok * rx, (1.0-bok) * ry, (1.0-bok) * rx, (1.0-bok) * ry, czarny, 1.0);
    al_draw_line(bok * rx, (1.0-bok) * ry, bok*rx, bok*ry, czarny, 1.0);
    al_draw_line((1.0-bok) * rx, (1.0-bok) * ry, (1.0-bok)*rx, bok*ry, czarny, 1.0);
    al_draw_line(bok * rx, bok * ry, (1-bok) * rx, bok * ry, czarny, 1.0);
    al_draw_text(czcionka, czerwony, rx/2, 0.5 * bok * ry, ALLEGRO_ALIGN_CENTER, tytul);
    al_draw_text(czcionka, czerwony, rx/2 * bok, 0.5 * ry, ALLEGRO_ALIGN_CENTER, "y");
    al_draw_text(czcionka, czerwony, rx/2, ry - bok * ry / 2, ALLEGRO_ALIGN_CENTER, "x");

    double xmin = findmin(x, n), xmax = findmax(x, n), ymin = findmin(y, n), ymax = findmax(x, n);
    double xekran, yekran, xekran2, yekran2;

    for(int i = 0; i < n; i++){
        xekran = (rx-2.0*bok*rx) * (x[i]-xmin) / (xmax-xmin);
        xekran = ry - (bok*ry+(ry-2.0*bok*ry)*(y[i]-ymin)/(ymax-ymin));
        al_draw_filled_circle(xekran, yekran, 2, czerwony);
    }


    for(int i = 0; i < n-1; i++){
        xekran = (rx-2.0*bok*rx) * (x[i]-xmin) / (xmax-xmin);
        xekran = ry - (bok*ry+(ry-2.0*bok*ry)*(y[i]-ymin)/(ymax-ymin));
        xekran2 = bok * rx + (rx - 2.0 * bok * rx) * (x[i+1] - xmin)/ (xmax - xmin);
        yekran2 = ry - (bok * ry+(ry - 2.0 * bok * ry) * (y[i+1]-ymin)/(ymax-ymin));

        al_draw_line(xekran, yekran, xekran2, yekran2, czarny, 1);
    }

}


int main(int argc, char **argv){
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    ALLEGRO_FONT *czcionka = al_load_ttf_font("./czcionka.ttf", 16, 0);
    ALLEGRO_BITMAP *bitmapka = al_create_bitmap(800,600); 
    // rysujwykres();
    bool redraw = true;
    const float FPS = 60;
    ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);
    al_start_timer(timer);
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    al_register_event_source(event_queue,
    al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    double *danex,*daney,n=100; 
    double x, y, x0 = 0.0, y0 = 0.0, vx, vy, vx0 = 155.0, vy0 = -199.0;

    x = x0;
    y = y0;
    vx = vx0;
    vy = -vy0;
    double dt = 0.05;
    double g = 100.0, m = 1.0;
    double B = 0.1;

    danex = (double *)malloc(n*sizeof(double));
    daney = (double *)malloc(n*sizeof(double));

    for(int i = 0; i < n; i++){
        danex[i]=rand()%RAND_MAX;
        danex[i]=rand()%RAND_MAX;
    }


    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        if (redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_clear_to_color(al_map_rgb(35, 15, 0));

            vx = vx - dt * B;
            vy = vy - dt * m * (g + B * vy);
            x = x + vx * dt;
            y = y + vy * dt;

            if (y < -300){
                y = -300;
                vy = -vy;
                vx = vx -(vx * B*1);
            }

            if (y > 300){
                vy = -vy;
            }

            if (x > 800){
                vx = -vx;
            }
            
            if (x < 0){
                vx = -vx;
            }

            if ((vx < 1 && vx > 0) || (vx > -1 && vx < 0)){
                vx = 0; break;
            }

            al_draw_filled_circle(x, 300-y, 10, al_map_rgb(255, 200, 255));
            al_draw_text(czcionka, al_map_rgb(255,0,0), 400, 300, ALLEGRO_ALIGN_CENTER, "Pilka xD");
            al_flip_display();
        }
    }

    rysujwykres(bitmapka,danex,daney,n,czcionka,"Tytul");
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(bitmapka,0,0,0);
    al_flip_display();
    sleep(10);

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}