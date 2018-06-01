#include <allegro5/allegro.h> 
#include <allegro5/allegro_primitives.h> 
#include <cmath>

// RÓWNANIE RÓŻNICZKOWE
double fx(double x, double y, double vx, double vy, double t){
    return vx;
}
double fy(double x, double y, double vx, double vy, double t){
    return vy;
}
double gx(double x, double y, double vx, double vy, double t){
    double pierwiastek = sqrt(x*x + y*y);
    return -x/(pierwiastek*pierwiastek*pierwiastek) + 1*cos(10 * t);
}
double gy(double x, double y, double vx, double vy, double t){
        double pierwiastek = sqrt(x*x + y*y);
        return -y/(pierwiastek*pierwiastek*pierwiastek + 1*cos(10 * t));
}

// MAIN
int main(int argc, char **argv) 
{ 
    al_init(); 
    al_install_keyboard(); 
    al_install_mouse(); 
    al_init_primitives_addon(); 
    ALLEGRO_DISPLAY *display=al_create_display(800, 600); 
    bool redraw=true; 
    const float FPS=600; 
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS); 
    al_start_timer(timer); 
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue(); 
    al_register_event_source(event_queue, 
    al_get_display_event_source(display)); 
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); 

    // PROG 

    // promien planety
    double promienPlanety = 0.667;
    // old od srodka
    double odl;
    // zmiana czasu i czas
    double t = 0;
    double dt = 0.01;
    // 
    double kx[4], ky[4], lx[4], ly[4];
    // zmienne
    double x, y, vx, vy;
    // zmienne początkowe
    double x0 = 0, y0 = 1, vx0 = 1, vy0 = 0;
    // aplikacja warunków początkowych
    x = x0, y = y0, vx = vx0, vy = vy0;




    // END PROG

    while(1) { 
        ALLEGRO_EVENT ev; 
        al_wait_for_event(event_queue,&ev); 
        if(ev.type==ALLEGRO_EVENT_TIMER){ 
            redraw=true; 
        } else if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE) { 
            break; 
        } 
        if(redraw && al_is_event_queue_empty(event_queue)){ 
        redraw = false; 

        // LOOP PROG

        kx[0] = fx(x, y, vx, vy, t);
        ky[0] = fy(x, y, vx, vy, t);
        lx[0] = gx(x, y, vx, vy, t);
        ly[0] = gy(x, y, vx, vy, t);

        kx[1] = fx(x+0.5*dt*kx[0], y+0.5*dt*ky[0], vx+0.5*dt*lx[0], vy+0.5*dt*ly[0], t+0.5*dt);
        ky[1] = fy(x+0.5*dt*kx[0], y+0.5*dt*ky[0], vx+0.5*dt*lx[0], vy+0.5*dt*ly[0], t+0.5*dt);
        lx[1] = gx(x+0.5*dt*kx[0], y+0.5*dt*ky[0], vx+0.5*dt*lx[0], vy+0.5*dt*ly[0], t+0.5*dt);
        ly[1] = gy(x+0.5*dt*kx[0], y+0.5*dt*ky[0], vx+0.5*dt*lx[0], vy+0.5*dt*ly[0], t+0.5*dt);

        kx[2] = fx(x+0.5*dt*kx[1], y+0.5*dt*ky[1], vx+0.5*dt*lx[1], vy+0.5*dt*ly[1], t+0.5*dt);
        ky[2] = fy(x+0.5*dt*kx[1], y+0.5*dt*ky[1], vx+0.5*dt*lx[1], vy+0.5*dt*ly[1], t+0.5*dt);
        lx[2] = gx(x+0.5*dt*kx[1], y+0.5*dt*ky[1], vx+0.5*dt*lx[1], vy+0.5*dt*ly[1], t+0.5*dt);
        ly[2] = gy(x+0.5*dt*kx[1], y+0.5*dt*ky[1], vx+0.5*dt*lx[1], vy+0.5*dt*ly[1], t+0.5*dt);

        kx[3] = fx(x+dt*kx[2], y+dt*ky[2], vx+dt*lx[2], vy+dt*ly[2], t+dt);
        ky[3] = fy(x+dt*kx[2], y+dt*ky[2], vx+dt*lx[2], vy+dt*ly[2], t+dt);
        lx[3] = gx(x+dt*kx[2], y+dt*ky[2], vx+dt*lx[2], vy+dt*ly[2], t+dt);
        ly[3] = gy(x+dt*kx[2], y+dt*ky[2], vx+dt*lx[2], vy+dt*ly[2], t+dt);

        x = x+dt/6*(kx[0]+ 2*kx[1]+ 2*kx[2]+ kx[3]);
        y = y+dt/6*(ky[0]+ 2*ky[1]+ 2*ky[2]+ ky[3]);
        vx = vx+dt/6*(lx[0]+ 2*lx[1]+ 2*lx[2]+ lx[3]);
        vy = vy+dt/6*(ly[0]+ 2*ly[1]+ 2*ly[2]+ ly[3]);

        t += dt;
        odl = sqrt(x*x + y*y);
        if (odl <= promienPlanety){
            // x = x-dt/6*(kx[0]+ 2*kx[1]+ 2*kx[2]+ kx[3]);
            // y = y-dt/6*(ky[0]+ 2*ky[1]+ 2*ky[2]+ ky[3]);
            vx = -vx;
            // vy = -vy;
        }
        // END LOOP PROG

        al_clear_to_color(al_map_rgb(0,0,50)); 
        // planeta
        al_draw_filled_circle(400,300,150*promienPlanety,al_map_rgb(0,255,100)); 
        // pocisk
        al_draw_filled_circle(400+x*150, 300+y*150 ,10,al_map_rgb(255,0,0)); 

        al_flip_display(); 
        } 
    } 
    al_destroy_timer(timer); 
    al_destroy_display(display); 
    al_destroy_event_queue(event_queue); 
    return 0; 
} 