#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro5.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>

#include <thread>
#include <string>

#include "ClassSiec.h"

using namespace std;

template<class T> T find_max(vector<T> &data);
template<class T> T find_min(vector<T> &data);
template<class T> T find_max_ignore_inf(vector<T> &data);
template<class T> T find_min_ignore_inf(vector<T> &data);

uint64_t licznik = 0;

void thread_siec(ClassSiec *siec, int *debug, int *th_run,
		double *stability_time, double *stability_time_full,
		std::string *info_text);
void pend_event(ClassSiec *siec, int *th_run, bool *redraw,
		ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT *ev);
void thread_draw(ClassSiec *siec, int *th_run, bool *redraw,
		ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap_box,
		std::string *info);
int draw_all(ClassSiec *siec, ALLEGRO_BITMAP *bitmap);

int main(int argc, char **argv)
{

	int Nx = 50;
	int Ny = 50;
	int windowx = 600;
	int windowy = 600;
	double rdf_norma = 10.0;

	licznik = 0;
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	ALLEGRO_DISPLAY *display = al_create_display(windowx, windowy);
	ALLEGRO_BITMAP *bitmap_box = al_create_bitmap(windowx, windowy);

	bool redraw = true;
	const float FPS = 1.0;

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	al_start_timer(timer);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	srand(time(NULL));
	srand48(time(NULL));

	ClassSiec siec(0.1, Nx, Ny);

	siec.create_random(0.5, 0.5, 0.2, 0.00001);
	siec.set_mass_all(1.0);
	siec.set_random_velocity();
	siec.fix_position();
	siec.set_momentum_to_zero(3.0);
	siec.set_particles_zero_time();
	siec.init("dane_gestosc_0_01.Day");
	draw_all(&siec, bitmap_box);
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(bitmap_box, 0.0, 0.0, 0);
	al_save_bitmap("uklad_gestosc_0_01.png", bitmap_box);
	int th_run = 1;
	double stability_time = 1000.0;
	double stability_time_full = 1000.0;

	ALLEGRO_EVENT ev;
	std::string info_text = "...";
	int debug = 1;
	thread th_siec = thread(thread_siec, &siec, &debug, &th_run,
			&stability_time, &stability_time_full, &info_text);
	thread th_pend = thread(pend_event, &siec, &th_run, &redraw, event_queue,
			&ev);
	thread th_draw = thread(thread_draw, &siec, &th_run, &redraw, display,
			bitmap_box, &info_text);

	cout << "JOIN THREAD PEND\n";
	if (th_pend.joinable())
	{
		th_pend.join();
	}
	cout << "JOIN THREAD SIEC\n";
	if (th_siec.joinable())
	{
		th_siec.join();
	}
	cout << "JOIN THREAD DRAW\n";
	if (th_draw.joinable())
	{
		th_draw.join();
	}
	cout << "END ALL THREADS\n";
	cout << "Start saving RDF...\n";

	vector<double> tmp_arry;
	tmp_arry.clear();
	siec.flush_file();

	cout << "Prepare array...\n";
	tmp_arry.reserve(100);
	for (uint8_t c0 = 0; c0 < 100; c0++)
	{
		tmp_arry.emplace_back(0.0);
	}
	cout << "RDF...\n";
	for (uint8_t c0 = 0; c0 < rdf_norma; c0++)
	{
		cout << to_string(c0) << '\n';
		siec.save_RDF_to_array(&tmp_arry);
		siec.step_all(2);
	}
	cout << "Normalizing RDF...\n";
	for (uint8_t c0 = 0; c0 < 100; c0++)
	{
		tmp_arry[c0] /= rdf_norma;
	}
	cout << "Flush static parameters...\n";
	siec.insert_to_file(siec.get_static_parameters_info("\n"));
	cout << "Finding peak RDF...\n";
	double max_peak = find_max_ignore_inf(tmp_arry);
	double min_peak = find_min_ignore_inf(tmp_arry);

	std::stringstream stream;

	stream << "Max peak: " << max_peak << '\n' << "Min peak: " << min_peak
			<< "\n\n";

	cout << "Prepare RDF to save...\n";
	cout << stream.str();
	double tmp_step = (siec.get_min_radius() * 2.0 * 10.0) / 100.0;
	for (uint8_t c0 = 0; c0 < 100; c0++)
	{
		stream << c0 * tmp_step << ',' << tmp_arry[c0] << ';';
	}
	cout << "Saving RDF to file...\n";
	siec.insert_to_file(stream.str());
	cout << "Closing file" << "\n";
	siec.close_file();

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return (0);
}

void thread_siec(ClassSiec *siec, int *debug, int *th_run,
		double *stability_time, double *stability_time_full,
		std::string *info_text)
{
	while (*th_run == 1)
	{
		siec->step_all(*debug);
		*info_text = "Time to end: "
				+ to_string(*stability_time - siec->get_time());
		if ((*stability_time == *stability_time_full)
				&& find_is_in_range(
						siec->get_Velocity_Autocorrelation_Function(), 0.0,
						0.01))
		{

			if (siec->get_Velocity_Autocorrelation_Function_delta() < 0.005)
			{
				if (siec->get_diffusitivity_delta() < 0.0005)
				{
					*stability_time = 2.0 * siec->get_time();
					siec->flush_file();
				}
			}
		}
		if (siec->get_time() > *stability_time)
		{
			if (siec->get_diffusitivity_delta() < 0.0001)
			{
				*th_run = 0;
				break;
			}
		}
	}
	cout << "END THREAD SIEC\n";
}

void pend_event(ClassSiec *siec, int *th_run, bool *redraw,
		ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT *ev)
{
	while (*th_run == 1)
	{
		al_wait_for_event(event_queue, ev);
		if (ev->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			*th_run = 0;
		}
		else if (ev->type == ALLEGRO_EVENT_TIMER)
		{
			*redraw = true;
		}
	}
	cout << "END THREAD PEND\n";

}

void thread_draw(ClassSiec *siec, int *th_run, bool *redraw,
		ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bitmap_box, std::string *info)
{
	while (*th_run)
	{
		if (*redraw == true)
		{
			draw_all(siec, bitmap_box);
			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(bitmap_box, 0.0, 0.0, 0);
			al_flip_display();
		}
	}
	cout << "END THREAD DRAW\n";
}

/**
 * Draw all particles
 * @param siec
 * @param bitmap
 * @return
 */
int draw_all(ClassSiec *siec, ALLEGRO_BITMAP *bitmap)
{
	try
	{
		al_set_target_bitmap(bitmap);
		ALLEGRO_COLOR czerwony = al_map_rgb(255, 0, 0);
		ALLEGRO_COLOR niebieski = al_map_rgb(0, 0, 255);
		double skala = 1.0;
		double skalax = al_get_display_width(al_get_current_display())
				/ siec->get_box_x();
		double skalay = al_get_display_height(al_get_current_display())
				/ siec->get_box_y();

		double x = 0.0;
		double y = 0.0;

		al_clear_to_color(al_map_rgb(0, 0, 0));
		particle *ptr = &siec->particles[0];
		for (uint64_t c0 = 0; c0 < siec->get_particles_len(); c0++)
		{
			x = ptr->pos[0] * skalax;
			y = ptr->pos[1] * skalay;

//		al_draw_filled_circle(x, y, ptr->r * skalar, ptr->color);
			al_draw_filled_ellipse(x, y, ptr->r * skalax, ptr->r * skalay,
					ptr->color);
			al_draw_line(x, y, (x + ptr->vel[0]) * skala,
					(y + ptr->vel[1]) * skala, niebieski, 1.0);
			ptr++;
		}
	} catch (exception & e)
	{
		return (ERROR);
	}
	return (OK);
}

template<class T> T find_max(vector<T> &data)
{
	T result = data[0];
	for (uint64_t c0 = 1; c0 < data.size(); c0++)
	{
		if (result < data[c0])
		{
			result = data[c0];
		}
	}
	return (result);
}

template<class T> T find_max_ignore_inf(vector<T> &data)
{
	T result = data[0];
	uint64_t c0 = 0;
	T inf = std::numeric_limits<T>::infinity();
	while (abs(data[c0]) == inf)
	{
		result = data[c0];
		c0++;
	}
	for (uint64_t c0 = 1; c0 < data.size(); c0++)
	{
		if (abs(data[c0]) != inf)
		{
			if (result < data[c0])
			{
				result = data[c0];
			}
		}
	}
	return (result);
}

template<class T> T find_min_ignore_inf(vector<T> &data)
{
	T result = data[0];
	uint64_t c0 = 0;
	T inf = std::numeric_limits<T>::infinity();
	while (abs(data[c0]) == inf)
	{
		result = data[c0];
		c0++;
	}
	for (uint64_t c0 = 1; c0 < data.size(); c0++)
	{
		if (abs(data[c0]) != inf)
		{
			if (result > data[c0])
			{
				result = data[c0];
			}
		}
	}
	return (result);
}

template<class T> T find_min(vector<T> &data)
{
	T result = data[0];
	for (uint64_t c0 = 1; c0 < data.size(); c0++)
	{
		if (result > data[c0])
		{
			result = data[c0];
		}
	}
	return (result);
}
