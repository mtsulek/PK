#include <stdio.h> 
#include <stdlib.h> 
#include <allegro5/allegro.h> 
#include <allegro5/allegro_primitives.h> 


int main(int argc, char **argv) 
{ 
  al_init(); 
  al_init_primitives_addon(); 
  al_install_keyboard(); 
  al_install_mouse(); 
  ALLEGRO_DISPLAY *display=al_create_display(800, 600); 
  al_set_window_title(display,"Okienko"); 
  ALLEGRO_KEYBOARD_STATE klawiatura; 
  while(!al_key_down( &klawiatura, ALLEGRO_KEY_ESCAPE)) 
  { 
  al_get_keyboard_state(&klawiatura); 
  al_clear_to_color(al_map_rgb(0,0,0)); 
  al_draw_filled_circle(400, 300,100, al_map_rgb(255,255,255)); 
  al_flip_display(); 
  } 
  al_destroy_display(display); 
  return 0; 
} 