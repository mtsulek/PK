#include <allegro5/color.h>
#include <bits/stdint-uintn.h>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <thread>
#include <future>
#include <fstream>
#include <exception>

#define OK 1
#define ERROR -1
#define DEBUG 1

//const double kBoltzmann = 1.380658e-23;
const double kBoltzmann = 1.0;

using namespace std;

template<class T> T find_max(T* data, uint64_t size);
template<class T> T find_min(T* data, uint64_t size);
template<class T> T find_max(vector<T> *data);
template<class T> T find_min(vector<T> *data);
template<class T> T find_delta(vector<T> *data);
template<class T> T find_sum(vector<T> &data);
template<class T> T find_average(vector<T> &data);

int find_is_in_range(double value, double centrum, double delta);
int find_is_in_range(double value, double centrum, double left, double right);

int save_to_file(std::string filename, std::string data);

struct particle
{
	particle(double x, double y, double r, double vx = 0.0, double vy = 0.0,
			double maxVelocity = 0.0, uint64_t nr = 0);
	double pos[2];
	double vel[2];
	double maxVelocity;
	double r;
	double m;
	double t;
	double tlc;
	uint64_t nr;
	ALLEGRO_COLOR color;

	int set_mass(double m);
	int set_r(double r);
	int set_pos(double x, double y);
	int set_vel(double vx, double vy);
	int set_maxVelocity(double maxVelocity);

	int step(double dt = 1.0);

	double get_distance(particle *to_particle, double box_x = 0.0,
			double box_y = 0.0);
	double get_velocity(void);

	double get_time_to_collision(particle *to_particle, double box_x = 0.0,
			double box_y = 0.0);
	std::string get_info(void);
};

struct part_particles
{
	part_particles(particle part, uint64_t nr);
	particle part;
	uint64_t nr;
};

struct s_pair
{
	s_pair(uint64_t a, uint64_t b, double dt);
	uint64_t a;
	uint64_t b;
	double dt;
};

struct particle_zero_time
{
	particle_zero_time(particle *particle);
	uint64_t nr;
	double pos[2];
	double vel[2];
	double maxVelocity;
	double r;
	double m;
	double velxy;
};

double get_distance_1d(double x0, double x1, double box_x);

double get_distance_2d(particle *p0, particle *p1, double box_x, double box_y);
double get_distance_2d(double x0, double y0, double x1, double y1, double box_x,
		double box_y);

int zderzenie(particle *cz0, particle *cz1, double box_x = 0.0, double box_y =
		0.0);

class ClassSiec
{
public:
	ClassSiec(void);
	ClassSiec(double dt, double box_x = 800.0, double box_y = 600.0);
	virtual ~ClassSiec(void);

	int add_particle(double x, double y, double r, double vx = 0.0, double vy =
			0.0, double maxVelocity = 0.0);

	int create_random(double r_min, double r_max, double density, double precision = 0.01);
//	int check_is_forbidden_position(particle *for_particle);
	int check_is_allowed_position(double x, double y, double r);

	int set_random_velocity(double multiplier = 1.0);
	int set_random_size(double min, double max);
	int set_mass_to_radius(double ratio = 1.0);
	int set_mass_to_area(double ratio = 1.0);
	int set_mass_all(double mass = 1.0);

	int set_momentum_to_zero(double Ekpoz_t, double precision = 0.001);

	int set_particles_zero_time(void);

	int set_dt(double dt);

	uint64_t get_particles_len(void);
	int get_particle(uint64_t nr, particle *here);
	s_pair get_next_collision_particle_number(void);
	double get_next_collision_particles(vector<s_pair> *ptr);

	float get_time(void);
	float get_temperature(void);
	float get_density(void);
	float get_density_real(void);
	float get_packing_ratio(void);
	double get_kinetic_energy(void);
	uint64_t get_number_of_particles_in_radius(double r, double dr,
			particle *for_particle);
	uint64_t get_number_of_particles_in_radius(double r, double dr);

	float get_radial_distribution_function(double r, double dr,
			particle *for_particle, uint64_t prec = 100);
	float get_radial_distribution_function(double r, double dr);
	float get_radial_distribution_function_theoretical(void);

	float get_state_space_Boublik(void);
	float get_state_space_Handerson(void);
	float get_state_space_Solan(void);

	float get_Velocity_Autocorrelation_Function(void);
	float get_diffusivity(void);

	double get_diffusitivity_delta(void);
	double get_Velocity_Autocorrelation_Function_delta(void);
	double get_diffusitivity_delta_ratio(void);
	double get_Velocity_Autocorrelation_Function_delta_ratio(void);

	double get_box_x(void);
	double get_box_y(void);

	double get_min_radius(void);
	double get_max_radius(void);

	void convert_to_box(double *x, double *y);

	std::string get_box_info(std::string sep = "\t");
	std::string get_box_info_title(std::string sep = "\t");
	std::string get_box_info_raw(std::string sep = "\t");
	std::string get_RDF_r(double r, double dr, uint64_t prec = 100,
			std::string sep = " ");
	std::string get_RDF_r(uint64_t prec = 100, std::string sep = " ");
	std::string get_static_parameters_info(std::string sep = "\n");
	std::string get_static_parameters_title(std::string sep = "\t");
	std::string get_static_parameters_raw(std::string sep = "\t");

	int save_RDF(uint64_t prec = 100, std::string sep = " ");
	void save_RDF_to_array(vector<double> *array, uint64_t prec = 100);

	int fix_position(void);
	int init(std::string filename);
	int insert_to_file(std::string data);
	int flush_file(void);
	int close_file(void);
	int step_all(int debug = 0);

	vector<particle> particles;
	vector<particle_zero_time> particles_zero_time;
	vector<double> current_RDF;
	double distancex;
	double distancey;
	double distance;
	double box_x;
	double box_y;
private:
	double global_time;
	double dt;
	double temperature;
	double diffusivity;
	double previous_collision_dt;
	double VAF_Dnorm;

	std::string filename;
	std::fstream file;

	vector<double> diffusivity_vector;
	vector<double> Velocity_Autocorrelation_Function_vector;

};

void thread_RDF(ClassSiec *siec, uint64_t c1, double prec = 100.0);
