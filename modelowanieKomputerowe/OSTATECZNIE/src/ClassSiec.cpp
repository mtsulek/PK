#include "ClassSiec.h"

template<class T> T find_max(T* data, uint64_t size)
{
	T result = data[0];
	for (uint64_t c0 = 1; c0 < size; c0++)
		if (result < data[c0])
			result = data[c0];
	return result;
}

template<class T> T find_min(T* data, uint64_t size)
{
	T result = data[0];
	for (uint64_t c0 = 1; c0 < size; c0++)
	{
		if (result > data[c0])
		{
			result = data[c0];
		}
	}
	return (result);
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

template<class T> T find_delta(vector<T> &data)
{
	T result_min = data[0];
	T result_max = data[0];
	for (uint64_t c0 = 1; c0 < data.size(); c0++)
	{
		if (result_min > data[c0])
		{
			result_min = data[c0];
		}
		if(result_max < data[c0])
		{
			result_max = data[c0];
		}
	}
	return (result_max - result_min);
}

template<class T> T find_sum(vector<T> &data)
{
	T result = data[0];
	for (uint64_t c0 = 1; c0 < data.size(); c0++)
	{
		result += data[c0];
	}
	return (result);
}

template<class T> T find_average(vector<T> &data)
{
	T result = data[0];
	for (uint64_t c0 = 1; c0 < data.size(); c0++)
	{
		result += data[c0];
	}
	return (result/data.size());
}

template<typename Type>
void remove_duplicate(std::vector<Type> vec)
{
	std::sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

template<typename Type>
void remove_duplicate2(std::vector<Type> vec)
{
	std::set<Type> s(vec.begin(), vec.end());
	vec.assign(s.begin(), s.end());
}

int find_is_in_range(double value, double centrum, double delta)
{
	return(!(value >= (centrum + delta) || value <= (centrum - delta)));
}

int find_is_in_range(double value, double centrum, double left, double right)
{
	return(!(value >= (centrum + right) || value <= (centrum - left)));
}

particle::particle(double x, double y, double r, double vx, double vy,
		double maxVelocity, uint64_t nr)
{
	this->pos[0] = x;
	this->pos[1] = y;
	this->vel[0] = vx;
	this->vel[1] = vy;
	this->maxVelocity = maxVelocity;
	this->r = r;
	this->color = al_map_rgb(255, 0, 0);
	this->m = 1.0;
	this->t = 0.0;
	this->tlc = 0.0;
	this->nr = nr;
}

/**
 * Set mass of particle
 * @param m
 * @return
 */
int particle::set_mass(double m)
{
	this->m = m;
	return (OK);
}

/**
 * Set radius of particle
 * @param r
 * @return
 */
int particle::set_r(double r)
{
	this->r = r;
	return (OK);
}

/**
 * Set position of particle
 * @param x
 * @param y
 * @return
 */
int particle::set_pos(double x, double y)
{
	this->pos[0] = x;
	this->pos[1] = y;
	return (OK);
}

/**
 * Set velocity of particle
 * @param vx
 * @param vy
 * @return
 */
int particle::set_vel(double vx, double vy)
{
	this->vel[0] = vx;
	this->vel[1] = vy;
	return (OK);

}

/**
 * Set max velocity of particle
 * @param maxVelocity
 * @bug probably not useful
 * @return
 */
int particle::set_maxVelocity(double maxVelocity)
{
	this->maxVelocity = maxVelocity;
	return (OK);
}

/**
 * Set step dt
 * @param dt
 * @bug not useful
 * @return
 */
int particle::step(double dt)
{
	this->pos[0] += this->vel[0] * dt;
	this->pos[1] += this->vel[1] * dt;
	this->t += dt;
	return (OK);
}

/**
 * Generate zero time particle
 * @param particle
 */
particle_zero_time::particle_zero_time(particle *particle)
{
	this->nr = particle->nr;
	this->pos[0] = particle->pos[0];
	this->pos[1] = particle->pos[1];
	this->vel[0] = particle->vel[0];
	this->vel[1] = particle->vel[1];
	this->maxVelocity = particle->maxVelocity;
	this->r = particle->r;
	this->m = particle->m;
	this->velxy = sqrt(particle->vel[0] * particle->vel[0] + particle->vel[1] * particle->vel[1]);
}

/**
 * Calculate the distance in box
 * @param x0
 * @param x1
 * @param box_x
 * @return
 */
double get_distance_1d(double x0, double x1, double box_x)
{
    x0 = x0 - floor(x0 / box_x) * box_x;
    double dx = x0 - x1;
//    dx = dx - int(round(dx/box_x)) * box_x;
    dx = dx - nearbyint(dx/box_x) * box_x;

    return (dx);
}

/**
 * Calculate distance in 2D in box
 * @param p0
 * @param p1
 * @param box_x
 * @param box_y
 * @return
 */
double get_distance_2d(particle *p0, particle *p1, double box_x, double box_y)
{
	double x = get_distance_1d(p0->pos[0], p1->pos[0], box_x);
	double y = get_distance_1d(p0->pos[1], p1->pos[1], box_y);
	return(sqrt(x*x+y*y));
}

/**
 * Calculate distance in 2D in box
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param box_x
 * @param box_y
 * @return
 */
double get_distance_2d(double x0, double y0, double x1, double y1, double box_x, double box_y)
{
	double x = get_distance_1d(x0, x1, box_x);
	double y = get_distance_1d(y0, y1, box_y);
	return(sqrt(x*x+y*y));
}

/**
 * Calculate distance in 2D to particle in box
 * @param to_particle
 * @param box_x
 * @param box_y
 * @return
 */
double particle::get_distance(particle *to_particle, double box_x, double box_y)
{
	double dx = get_distance_1d(this->pos[0], to_particle->pos[0], box_x);
	double dy = get_distance_1d(this->pos[1], to_particle->pos[1], box_y);
	return (sqrt(dx*dx+dy*dy));

}

/**
 * Calculate velocity
 * @return
 */
double particle::get_velocity(void)
{
	return (sqrt(this->vel[0]*this->vel[0]+this->vel[1]*this->vel[1]));
}

/**
 * Calculate time to colision with particle
 * @param to_particle
 * @param box_x
 * @param box_y
 * @return
 */
double particle::get_time_to_collision(particle *to_particle, double box_x, double box_y)
{

	double dradius = this->r + to_particle->r;
	double rij = this->get_distance(to_particle, box_x, box_y);
	double drx = get_distance_1d(to_particle->pos[0], this->pos[0], box_x);
	double dry = get_distance_1d(to_particle->pos[1], this->pos[1], box_y);
	double dvx = to_particle->vel[0] - this->vel[0];
	double dvy = to_particle->vel[1] - this->vel[1];
	double bij = drx * dvx + dry * dvy;
	double vij = sqrt(dvx * dvx + dvy * dvy);
	double tij = 0.0;
	dradius *= dradius;
	if (bij * bij - vij * vij * (rij * rij - dradius) < 0.0)
	{
		tij = 10e10;
	}
	else
	{
		tij = (-bij - sqrt(bij * bij - vij * vij * (rij * rij - dradius)))
				/ (vij * vij);
	}
	if (tij < 0.0)
	{
		tij = 10e10;
	}

	return (tij);
}

/**
 * Return info of particle
 * @return
 */
std::string particle::get_info(void)
{
	uint8_t precision = 20;
	std::stringstream stream;
	stream << fixed << setprecision(0) << this->nr << "\t" << fixed
			<< setprecision(precision) << this->t << "\t";
	for (uint8_t c0 = 0; c0 < 2; c0++)
	{
		stream << this->pos[c0] << "\t";
	}
	for (uint8_t c0 = 0; c0 < 2; c0++)
	{
		stream << this->vel[c0] << "\t";
	}
	std::string str = stream.str();

	return (str);
}

ClassSiec::ClassSiec(void)
{
	this->dt = 1.0;
	this->box_x = 100.0;
	this->box_y = 100.0;
	this->previous_collision_dt = 0.0;
	this->diffusivity = 0.0;
	this->temperature = 0.0;
	this->global_time = 0.0;
}

/**
 * Constructor
 * @todo dt is deprecated
 * @param dt -> deprecated
 * @param box_x
 * @param box_y
 */
ClassSiec::ClassSiec(double dt, double box_x, double box_y)
{
	this->dt = dt;
	this->box_x = box_x;
	this->box_y = box_y;
	this->previous_collision_dt = 0.0;
	this->diffusivity = 0.0;
	this->temperature = 0.0;
	this->global_time = 0.0;
}

ClassSiec::~ClassSiec(void)
{
	this->particles.clear();
}

/**
 * Set delta time
 * @todo function is deprecated
 * @param dt
 * @return
 */
int ClassSiec::set_dt(double dt)
{
	this->dt = dt;
	return (OK);
}

/**
 * Set positions to box
 * @param x
 * @param y
 */
void ClassSiec::convert_to_box(double *x, double *y)
{
	*x -= this->box_x * nearbyint(*x / this->box_x);
	*y -= this->box_y * nearbyint(*y / this->box_y);
}

/**
 *
 * @return numbers of particles
 */
uint64_t ClassSiec::get_particles_len(void)
{
	return (this->particles.size());

}

/**
 * Add particle to array
 * @todo maxVelocity is probably useless
 * @param x
 * @param y
 * @param r
 * @param vx
 * @param vy
 * @param maxVelocity
 * @return
 */
int ClassSiec::add_particle(double x, double y, double r, double vx, double vy,
		double maxVelocity)
{
	double tmpx = x;
	double tmpy = y;
	uint64_t nr = this->particles.size();
	this->particles.push_back(particle(tmpx, tmpy, r, vx, vy, maxVelocity, nr));
	return (OK);
}


/**
 * Create random lattice
 * @param r
 * @param density
 * @param precision
 * @return
 */
int ClassSiec::create_random(double r_min, double r_max, double density, double precision)
{
	volatile double x = 0.0;
	volatile double y = 0.0;
	vector<double> vect_density_check;// = new vector<double>;
	vect_density_check.clear();
	double r = 1.0;
	if (r_max < r_min)
	{
		double tmp_r_max = r_max;
		r_max = r_min;
		r_min = tmp_r_max;
	}
	double r_delta = r_max - r_min;
	this->particles.clear();
	while (find_is_in_range(this->get_density_real(), density, precision) == 0)
	{
		while ((this->get_particles_len() > 0)
				&& (this->get_density_real() >= (density + precision)))
		{
			this->particles.pop_back();
		}
		if(find_is_in_range(this->get_density_real(), density, precision))
		{
			return (OK);
		}
		x = drand48() * this->box_x;
		y = drand48() * this->box_y;
		r = (drand48() * r_delta) + r_min;
		while (check_is_allowed_position(x, y, r) == ERROR)
		{
			x = drand48() * this->box_x;
			y = drand48() * this->box_y;
			r = (drand48() * r_delta) + r_min;
		}
		this->add_particle(x, y, r, 0.0, 0.0);
		vect_density_check.push_back(this->get_particles_len());
		if (vect_density_check.size() > 10)
		{
			vect_density_check.erase(vect_density_check.begin());
			if (find_delta(vect_density_check) == 0)
			{
				vect_density_check.clear();
				return (OK);
			}
		}
		cout << "Particles: " << this->get_particles_len() << ",\t density: "
				<< this->get_density_real() << "\n";
	}
	vect_density_check.clear();
	return (OK);
}

int ClassSiec::check_is_allowed_position(double x, double y, double r)
{
	double n = this->get_particles_len();
	for (uint64_t c0 = 0; c0 < n; c0++)
	{

		if (get_distance_2d(x, y, this->particles.at(c0).pos[0],
				this->particles.at(c0).pos[1], box_x, box_y)
				< (r + this->particles.at(c0).r))
		{
			return (ERROR);
		}
	}
	return (OK);
}



/**
 * Set random velocity for all particles
 * @param multiplier
 * @return
 */
int ClassSiec::set_random_velocity(double multiplier)
{
	for (uint64_t c0 = 0; c0 < this->get_particles_len(); c0++)
	{
		double u1 = drand48();
		double u2 = drand48();
		double g1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
		double g2 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);
		this->particles.at(c0).vel[0] = (g1 / 0.04) * multiplier;
		this->particles.at(c0).vel[1] = (g2 / 0.04) * multiplier;
	}
	return (OK);
}

/**
 * Set random size of particles
 * @param min
 * @param max
 * @return
 */
int ClassSiec::set_random_size(double min, double max)
{
	if (min <= 0.0 || max <= 0.0)
	{
		return (ERROR);
	}
	if (min > max)
	{
		double tmp_min = min;
		min = max;
		max = tmp_min;
	}
	for (uint64_t c0 = 0; c0 < this->get_particles_len(); c0++)
	{
		this->particles.at(c0).r = (drand48() * (max - min)) + min;
	}
	return (OK);
}

/**
 * Sets the masses according to the radius of particle
 * @param ratio
 * @return
 */
int ClassSiec::set_mass_to_radius(double ratio)
{
	for (uint64_t c0 = 0; c0 < this->get_particles_len(); c0++)
	{
		this->particles.at(c0).m = this->particles.at(c0).r * ratio;
	}
	return (OK);
}

/**
 * Sets the masses according to the area of particle
 * @param ratio
 * @return
 */
int ClassSiec::set_mass_to_area(double ratio)
{
	ratio *= M_PI;
	for (uint64_t c0 = 0; c0 < this->get_particles_len(); c0++)
	{
		this->particles.at(c0).m = this->particles.at(c0).r * this->particles.at(c0).r * ratio;
	}
	return (OK);
}

/**
 * Sets the masses for all particles
 * @param mass
 * @return
 */
int ClassSiec::set_mass_all(double mass)
{
	for (uint64_t c0 = 0; c0 < this->get_particles_len(); c0++)
	{
		this->particles.at(c0).m = mass;
	}
	return (OK);
}

/**
 * Set temperature to Ekpoz_t
 * @param Ekpoz_t
 * @param precision
 * @return
 */
int ClassSiec::set_momentum_to_zero(double temperature, double precision)
{
	double n = this->get_particles_len();
	double Ek = 0.0;
	double Ekpoz = 0.0;


	double temp = this->get_temperature();
	while (find_is_in_range(temp, temperature, precision)==0)
	{
		Ek = this->get_kinetic_energy();
		Ekpoz = sqrt(temperature / Ek);
		if (temp > temperature)
		{

			for (uint64_t c0 = 0; c0 < n; c0++)
			{
				this->particles[c0].vel[0] *= Ekpoz;
				this->particles[c0].vel[1] *= Ekpoz;
			}
		}
		else
		{
			for (uint64_t c0 = 0; c0 < n; c0++)
			{
				this->particles[c0].vel[0] /= Ekpoz;
				this->particles[c0].vel[1] /= Ekpoz;
			}
		}

		temp = this->get_temperature();
	}

	return (OK);
}

/**
 * Saves the initial states to an individual array
 * @return
 */
int ClassSiec::set_particles_zero_time(void)
{
	double Dnorm = 0.0;
	double n = (double)this->get_particles_len();
	this->particles_zero_time.clear();
	this->particles_zero_time.reserve(n);
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		this->particles_zero_time.emplace_back(&this->particles.at(c0));
		Dnorm += this->particles.at(c0).vel[0] * this->particles.at(c0).vel[0]
				+ this->particles.at(c0).vel[1] * this->particles.at(c0).vel[1];
	}
	this->VAF_Dnorm = Dnorm / n;
	return (OK);
}

/**
 * Get address of particle with number to destination
 * @todo Probably useless
 * @param nr
 * @param here
 * @return
 */
int ClassSiec::get_particle(uint64_t nr, particle *here)
{
	if (nr < this->particles.size())
	{
		here = &this->particles[nr];
		return (OK);

	}
	else
	{
		return (ERROR);
	}
}

/**
 * Constructor for pair of particles
 * @param a
 * @param b
 * @param dt
 */
s_pair::s_pair(uint64_t a, uint64_t b, double dt)
{
	this->a = a;
	this->b = b;
	this->dt = dt;
}

/**
 * Return pair of next collision
 * @return
 */
s_pair ClassSiec::get_next_collision_particle_number(void)
{
	uint64_t n = this->get_particles_len();
	double mintime = 10e10;
	s_pair ret_pair(0, 0, mintime);
	for (uint64_t c0 = 0; c0 < (n - 1); c0++)
	{
		for (uint64_t c1 = (c0 + 1); c1 < n; c1++)
		{
			if (!(c1 == c0))
			{
				double tmp_mintime = this->particles[c0].get_time_to_collision(
						&this->particles[c1], this->box_x, this->box_y);
				if (tmp_mintime < mintime)
				{
					mintime = tmp_mintime;
					ret_pair = s_pair(c0, c1, mintime);
				}
			}
		}
	}

	return (ret_pair);

}

/**
 * Fills the tables of the next collisions
 * @param pairs
 * @return
 */
double ClassSiec::get_next_collision_particles(vector<s_pair> *pairs)
{
	uint64_t n = this->get_particles_len();
	pairs->clear();
	double mintime = 10e11;
	s_pair ret_pair(0,0, mintime);
	for (uint64_t c0 = 0; c0 < (n - 1); c0++)
	{
		for (uint64_t c1 = (c0 + 1); c1 < n; c1++)
		{
			if (!(c1 == c0))
			{
				double tmp_mintime = this->particles[c0].get_time_to_collision(&this->particles[c1], this->box_x, this->box_y);
				if (tmp_mintime<mintime)
				{
					mintime=tmp_mintime;
				}
				pairs->push_back(s_pair(c0, c1, tmp_mintime));
			}
		}
	}
	return (mintime);

}

/**
 * Repair position of particle to the box
 * @param particle
 * @param box_x
 * @param box_y
 */
void th_to_box(particle *particle, double box_x = 0.0, double box_y = 0.0)
{
	particle->pos[0] = box_x
			+ (particle->pos[0] - box_x * ceil(particle->pos[0] / box_x));
	particle->pos[1] = box_y
			+ (particle->pos[1] - box_y * ceil(particle->pos[1] / box_y));
}

/**
 * Repair positions of all particles to the box
 * @return
 */
int ClassSiec::fix_position(void)
{
	uint64_t n = this->get_particles_len();
	particle *ptr0 = &this->particles[0];
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		th_to_box(ptr0++, box_x, box_y);
	}

	return (OK);
}

/**
 *
 * @param filename
 * @return
 */
int ClassSiec::init(std::string filename)
{
	this->filename = filename;
	this->file.open(this->filename, fstream::out | fstream::trunc);
	this->set_particles_zero_time();
	this->file << this->get_box_info_title();
	this->file.flush();
	this->diffusivity_vector.push_back(0.0);
	this->Velocity_Autocorrelation_Function_vector.push_back(0.0);

	return (OK);
}

/**
 * Flush string to file
 * @param data
 * @return
 */
int ClassSiec::insert_to_file(std::string data)
{
	this->file << data;
	return (OK);
}

int ClassSiec::flush_file(void)
{
	this->file.flush();
	return (OK);
}

/**
 * Flush and close file
 * @return
 */
int ClassSiec::close_file(void)
{
	this->file.flush();
	this->file.close();
	return (OK);
}

/**
 * Step all particles
 * @return
 */
int ClassSiec::step_all(int debug)
{
	uint64_t n = this->get_particles_len();
	this->fix_position();
	particle *ptr0 = &this->particles[0];
	vector<s_pair> next_collisions;

	double tmp_distx=0.0;
	double tmp_disty=0.0;

	next_collisions.clear();
	this->dt = this->get_next_collision_particles(&next_collisions);

	double distx_del=0.0;
	double disty_del=0.0;
	double dist_del=0.0;

	ptr0 = &this->particles[0];
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		tmp_distx = ptr0->vel[0] * this->dt;
		tmp_disty = ptr0->vel[1] * this->dt;
		ptr0->pos[0] += tmp_distx;
		ptr0->pos[1] += tmp_disty;
		ptr0->t += this->dt;
		ptr0->color = al_map_rgb(255 - 255.0/exp(ptr0->get_velocity()), 0, 0);
		distx_del+=tmp_distx;
		disty_del+=tmp_disty;
		ptr0++;
	}
		this->distancex=distx_del/n;
		this->distancey=disty_del/n;
		this->distance=sqrt(distx_del*distx_del+disty_del*disty_del)/n;
	this->fix_position();


	uint64_t tmp_collision_n = next_collisions.size();

	for (uint64_t c0 = 0; c0 < tmp_collision_n; c0++)
	{

		if (next_collisions.at(c0).dt == this->dt)
		{
			zderzenie(&this->particles[next_collisions.at(c0).a],
					&this->particles[next_collisions.at(c0).b], box_x, box_y);
		}

	}
	this->diffusivity += 0.5
			* (this->Velocity_Autocorrelation_Function_vector.at(this->Velocity_Autocorrelation_Function_vector.size()-1)
					+ this->get_Velocity_Autocorrelation_Function()) * this->dt;

	this->diffusivity_vector.push_back(this->diffusivity);
	if(this->diffusivity_vector.size() > 10)
	{
		this->diffusivity_vector.erase(this->diffusivity_vector.begin());
	}
	this->Velocity_Autocorrelation_Function_vector.push_back(
			this->get_Velocity_Autocorrelation_Function());
	if (this->Velocity_Autocorrelation_Function_vector.size() > 10)
	{
		this->Velocity_Autocorrelation_Function_vector.erase(
				this->Velocity_Autocorrelation_Function_vector.begin());
	}

	double v_tmp_x = this->particles[next_collisions.at(0).a].pos[0];
	double v_tmp_y = this->particles[next_collisions.at(0).b].pos[1];
	particle point_of_interaction(v_tmp_x, v_tmp_y, 0.0, 0.0, 0.0, 0.0, -1);
	th_to_box(&point_of_interaction, box_x, box_y);
	this->get_radial_distribution_function(0.0, this->get_min_radius()*2.0*10.0, &point_of_interaction, 100.0);

	if(debug>0)
	{
		cout << fixed << setprecision(10) << this->get_box_info("\n") << '\n';
	}
	this->insert_to_file(this->get_box_info_raw("\t"));
	this->global_time += this->dt;
	return (OK);
}

/**
 * Make collision of particles
 * @param cz0
 * @param cz1
 * @param box_x
 * @param box_y
 * @return
 */
int zderzenie(particle *cz0, particle *cz1, double box_x, double box_y)
{
	double tmp[4];
	double Mp = cz0->m + cz1->m;

	double dx01 = get_distance_1d(cz0->pos[0], cz1->pos[0], box_x);
	double dy01 = get_distance_1d(cz0->pos[1], cz1->pos[1], box_y);
	double dx10 = -dx01;
	double dy10 = -dy01;
	double odl01 = cz0->get_distance(cz1, box_x, box_y);
	odl01 *= odl01;

	double dvx01 = cz0->vel[0] - cz1->vel[0];
	double dvy01 = cz0->vel[1] - cz1->vel[1];

	tmp[0] = 2.0 * cz1->m / Mp * (dvx01 * dx01 + dvy01 * dy01) * dx01 / odl01;
	tmp[1] = 2.0 * cz1->m / Mp * (dvx01 * dx01 + dvy01 * dy01) * dy01 / odl01;
	tmp[2] = 2.0 * cz0->m / Mp * (-dvx01 * dx10 - dvy01 * dy10) * dx10 / odl01;
	tmp[3] = 2.0 * cz0->m / Mp * (-dvx01 * dx10 - dvy01 * dy10) * dy10 / odl01;

	cz0->vel[0] -= tmp[0];
	cz0->vel[1] -= tmp[1];
	cz1->vel[0] -= tmp[2];
	cz1->vel[1] -= tmp[3];

	ALLEGRO_COLOR zielony = al_map_rgb(0, 255, 0);
	cz0->color = zielony;
	cz1->color = zielony;
	cz0->tlc = 0.0;
	cz1->tlc = 0.0;

	return (OK);
}

float ClassSiec::get_time(void)
{
	return(this->global_time);
}

/**
 * Get temperature
 * @return
 */
float ClassSiec::get_temperature(void)
{
	double n = this->get_particles_len();
	double temperature = 0.0;
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		double vx = this->particles[c0].vel[0];
		double vy = this->particles[c0].vel[1];
		temperature += this->particles[c0].m * (vx * vx + vy * vy);
	}
	return (temperature / (n * kBoltzmann * 2.0));
}

/**
 * Get density particles in box
 * @return
 */
float ClassSiec::get_density(void)
{
	return(this->get_particles_len() / (this->box_x * this->box_y));
}

/**
 * Get density(real) particles in box
 * @return
 */
float ClassSiec::get_density_real(void)
{
	double n = this->get_particles_len();
	double P1 = 0.0;
	double P2 = this->box_x * this->box_y;
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		P1 += this->particles[c0].r*this->particles[c0].r;
	}
	return (M_PI * P1 / P2);
}

/**
 * Get the packing ratio of the particles in the box
 * @return
 */
float ClassSiec::get_packing_ratio(void)
{
	double sigma = 0.0;
	double n = this->get_particles_len();
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		sigma += this->particles[c0].r;
	}
	sigma *= 2.0/n;

	return (M_PI_4 * sigma * sigma * n / (this->box_x * this->box_y));

}

/**
 * Get the kinetic energy of particles
 * @return
 */
double ClassSiec::get_kinetic_energy(void)
{
	double Ek = 0.0;
	double n = this->get_particles_len();
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		Ek += this->particles[c0].m * this->particles[c0].get_velocity();
	}
	return (0.5 * Ek);

}

/**
 * Get the number of particles in radius for center of particle
 * @param r
 * @param dr
 * @param for_particle
 * @return
 */
uint64_t ClassSiec::get_number_of_particles_in_radius(double r, double dr,
		particle *for_particle)
{
	uint64_t N = 0;
	double n = this->get_particles_len();
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		double tmp_distance = for_particle->get_distance(&this->particles[c0],
				this->box_x, this->box_y);
		if ((tmp_distance >= r) & (tmp_distance < (r + dr)))
		{
			N++;
		}

	}

	return (N);

}

/**
 * Get number of particles in radius of each particles
 * @param r
 * @param dr
 * @return
 */
uint64_t ClassSiec::get_number_of_particles_in_radius(double r, double dr)
{
	uint64_t N = 0;
	double n = this->get_particles_len();
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		for (uint64_t c1 = 0; c1 < n; c1++)
		{
			if (c0 != c1)
			{
				double tmp_distance = get_distance_2d(&this->particles[c0],
						&this->particles[c1], this->box_x, this->box_y);
				if ((tmp_distance >= r) & (tmp_distance < (r + dr)))
				{
					N++;
				}
			}
		}

	}

	return (N);

}

/**
 * Get Radial distribution Function for particle
 * @param r
 * @param dr
 * @param for_particle
 * @param prec -> divide dr into 'prec' parts
 * zrobic histogramy dla wszystkich kulek i liczyc g(r) od (r/d) lub (r/sigma)
 * @return
 */
float ClassSiec::get_radial_distribution_function(double r, double dr,
		particle *for_particle, uint64_t prec)
{
	double _scl = dr / double(prec);
	double _end = 0.0;
	double _down = (this->get_density() * 2.0 * M_PI);
	this->current_RDF.clear();
	this->current_RDF.reserve(prec);
	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		if (c0 != 0)
		{
			double _tmp = this->get_number_of_particles_in_radius(r + c0 * _scl,
					_scl, for_particle) / (_down * (r + c0 * _scl) * _scl);
			_end += _tmp;
			this->current_RDF.emplace_back(_tmp);
		}
	}
	return (_end);

}

/**
 * Get Radial distribution Function
 * @bug probably bad function
 * @param r
 * @param dr
 * @return
 */
float ClassSiec::get_radial_distribution_function(double r, double dr)
{
	return (this->get_number_of_particles_in_radius(r, dr)
			/ (this->get_density() * 2.0 * M_PI * r * dr));
}

/**
 * Get Radial distribution Function - theoretical
 * @todo Check this
 * @return
 */
float ClassSiec::get_radial_distribution_function_theoretical(void)
{
	double eta = this->get_packing_ratio();
	return ((1.0 - (eta / 2.0)) / ((1.0 - eta) * (1.0 - eta)));
}

/**
 * Get state space - Boublik
 * @return
 */
float ClassSiec::get_state_space_Boublik(void)
{
	double eta = this->get_packing_ratio();
	double eta2 = eta * eta;
	double up = (1.0 / (1.0 - eta))
			+ (eta * (1.0 + eta / 7.0 - eta2 / 14.0))
					/ (((1.0 - eta) * (1.0 - eta)));
	return (up / (this->get_density() * kBoltzmann * this->get_temperature()));
}

/**
 * Get state space - Handerson
 * @return
 */
float ClassSiec::get_state_space_Handerson(void)
{
	double eta = this->get_packing_ratio();
	double up = (1.0 + (eta * eta / 8.0)) / ((1.0 - eta) * (1.0 - eta));
	return (up / (this->get_density() * kBoltzmann * this->get_temperature()));
}

/**
 * Get state space - Solan
 * @return
 */
float ClassSiec::get_state_space_Solan(void)
{
	double eta = this->get_packing_ratio();
	double eta2 = eta * eta;
	double up = (1.0 + eta2 / 8.0 - eta2 * eta2 / 10.0)
			/ ((1.0 - eta) * (1.0 - eta));
	return (up / (this->get_density() * kBoltzmann * this->get_temperature()));
}

/**
 * Get Velocity Autocorrelation Function
 * iloczyn skalarny vx(0)*vx(t)
 * @return
 */
float ClassSiec::get_Velocity_Autocorrelation_Function(void)
{
	double D = 0.0;
	uint64_t n = this->get_particles_len();

	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		D += this->particles_zero_time.at(c0).vel[0]
				* this->particles.at(c0).vel[0]
				+ this->particles_zero_time.at(c0).vel[1]
						* this->particles.at(c0).vel[1];
	}
	D /= n;

	return (D / this->VAF_Dnorm);
}

/**
 * Get diffusivity
 * @return
 */
float ClassSiec::get_diffusivity(void)
{
	return (this->diffusivity / 2.0);
}

/**
 * Get diffusivity delta
 * @return
 */
double ClassSiec::get_diffusitivity_delta(void)
{
	return (find_delta(this->diffusivity_vector));
}

double ClassSiec::get_Velocity_Autocorrelation_Function_delta(void)
{
	return (find_delta(this->Velocity_Autocorrelation_Function_vector));
}

/**
 * Get diffusivity delta ratio
 * @return
 */
double ClassSiec::get_diffusitivity_delta_ratio(void)
{
	return (find_delta(this->diffusivity_vector)/this->get_diffusivity());
}

/**
 * Get Velocity Autocorrelation Function delta ratio
 * @return
 */
double ClassSiec::get_Velocity_Autocorrelation_Function_delta_ratio(void)
{
	return (find_delta(this->Velocity_Autocorrelation_Function_vector)/this->get_Velocity_Autocorrelation_Function());
}

double ClassSiec::get_box_x(void)
{
	return (this->box_x);
}
double ClassSiec::get_box_y(void)
{
	return (this->box_y);
}

double ClassSiec::get_min_radius(void)
{
	double r = this->particles[0].r;
	double n = this->get_particles_len();
	for (uint64_t c0 = 1; c0 < n; c0++)
	{
		if (r > this->particles[c0].r)
		{
			r = this->particles[c0].r;
		}
	}
	return (r);
}

double ClassSiec::get_max_radius(void)
{
	double r = this->particles[0].r;
	double n = this->get_particles_len();
	for (uint64_t c0 = 1; c0 < n; c0++)
	{
		if (r < this->particles[c0].r)
		{
			r = this->particles[c0].r;
		}
	}
	return (r);
}

/**
 * Save to file
 * @param filename
 * @param data
 * @return
 */
int save_to_file(std::string filename, std::string data)
{

	fstream myfile;
	myfile.open(filename, fstream::in | fstream::app);
	myfile << data;
	myfile.close();
	return (OK);
}

/**
 * Get box info -> info for save in logs
 * @return
 */
std::string ClassSiec::get_box_info(std::string sep)
{
	uint8_t precision = 10;
	std::stringstream stream;

	stream << fixed << setprecision(precision)
					<< "Time: " << this->global_time
			<< sep << "dt: " << this->dt
			<< sep << "Velocity Autocorrelation Function: " << this->get_Velocity_Autocorrelation_Function()
			<< sep << "Velocity Autocorrelation Function delta: " << this->get_Velocity_Autocorrelation_Function_delta()
			<< sep << "Diffusivity: " << this->get_diffusivity()// / this->global_time
			<< sep << "Diffusivity delta: " << this->get_diffusitivity_delta()
			<< "\n";

	std::string str = stream.str();

	return (str);
}

/**
 * Return title of infos
 * @param sep
 * @return
 */
std::string ClassSiec::get_box_info_title(std::string sep)
{
	uint8_t precision = 10;
	std::stringstream stream;

	stream << fixed << setprecision(precision)
					<< "Time"
			<< sep << "dt"// << this->dt
			<< sep << "Velocity Autocorrelation Function"//<< this->get_Velocity_Autocorrelation_Function()
			<< sep << "Velocity Autocorrelation Function delta"// << this->get_Velocity_Autocorrelation_Function_delta()
			<< sep << "Diffusivity"// << this->get_diffusivity() / this->global_time
			<< sep << "Diffusivity delta"// << this->get_diffusitivity_delta()
			<< "\n";

	std::string str = stream.str();

	return (str);
}

/**
 * Get raw data of info
 * @param sep
 * @return
 */
std::string ClassSiec::get_box_info_raw(std::string sep)
{
	uint8_t precision = 10;
	std::stringstream stream;

	stream << fixed << setprecision(precision)
				   << this->global_time
			<< sep << this->dt
			<< sep << this->get_Velocity_Autocorrelation_Function()
			<< sep << this->get_Velocity_Autocorrelation_Function_delta()
			<< sep << this->get_diffusivity()// / this->global_time
			<< sep << this->get_diffusitivity_delta()
			<< "\n";

	std::string str = stream.str();

	return (str);
}

/**
 * Get RDF
 * @param r
 * @param dr
 * @param prec
 * @param sep
 * @return
 */
std::string ClassSiec::get_RDF_r(double r, double dr, uint64_t prec,
		std::string sep)
{
	double _scl = dr / double(prec);
	double _end = 0.0;
	double _down = (this->get_density() * 2.0 * M_PI);
	double n = (double) this->get_particles_len();
	std::stringstream stream;
	double *tmp_tabl = new double[prec];

	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		tmp_tabl[c0] = 0.0;
	}

	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		for (uint64_t c1 = 0; c1 < prec; c1++)
		{
				double _tmp = this->get_number_of_particles_in_radius(
						r + c1 * _scl, _scl, &this->particles.at(c0))
						/ (_down * (r + c1 * _scl) * _scl);
				tmp_tabl[c1] +=  _tmp;
		}
	}

	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		stream << c0 << ";" << tmp_tabl[c0]/n << sep;
	}
	stream << '\n';

	return (stream.str());
}

/**
 * Get default RDF
 * @param prec
 * @param sep
 * @return
 */
std::string ClassSiec::get_RDF_r(uint64_t prec, std::string sep)
{
	return (this->get_RDF_r(0.0, min(this->box_x, this->box_y),
			prec, sep));
}

/**
 * Save default RDF to file
 * @param prec
 * @param sep
 * @return
 */
int ClassSiec::save_RDF(uint64_t prec, std::string sep)
{
	double n = (double) this->get_particles_len();
	std::stringstream stream;

	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		this->current_RDF[c0] = 0.0;
	}

	std::thread th[prec];
	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		th[c0] = std::thread(thread_RDF, this, c0, prec);
	}
	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		if(th[c0].joinable())
		{
			th[c0].join();
		}
	}

	stream.clear();
	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		stream << c0 << ";" << this->current_RDF[c0] / n << sep;
	}
	this->insert_to_file(stream.str());

	return (OK);
}

void ClassSiec::save_RDF_to_array(vector<double> *array, uint64_t prec)
{
	double n = (double) this->get_particles_len();

	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		this->current_RDF[c0] = 0.0;
	}

	std::thread th[prec];
	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		th[c0] = std::thread(thread_RDF, this, c0, prec);
	}
	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		if (th[c0].joinable())
		{
			th[c0].join();
		}
	}

	for (uint64_t c0 = 0; c0 < prec; c0++)
	{
		if (this->current_RDF[c0] != INFINITY)
		{
			array->at(c0) += (this->current_RDF[c0] / n);
		}
	}
}

/**
 * Thread for RDF
 * @param siec
 * @param c1
 * @param prec
 */
void thread_RDF(ClassSiec *siec, uint64_t c1, double prec)
{
	double r = 0.0;
	double dr = siec->get_min_radius() * 2.0 * 10.0;
	double _scl = dr / double(prec);
	double _down = (siec->get_density() * 2.0 * M_PI);
	double n = (double) siec->get_particles_len();
	for (uint64_t c0 = 0; c0 < n; c0++)
	{
		double _tmp = siec->get_number_of_particles_in_radius(r + c1 * _scl,
				_scl, &siec->particles.at(c0))
				/ (_down * (r + c1 * _scl) * _scl);
		siec->current_RDF[c1] += _tmp;
	}
}

/**
 * Get static parameters only title
 * @param sep
 * @return
 */
std::string ClassSiec::get_static_parameters_title(std::string sep)
{
	std::stringstream stream;
	double precision = 10;

	stream << '\n';
	stream << "Static parameters:";
	stream << '\n';
	stream << fixed << setprecision(precision)
			<< "Temperature"
			<< sep << "Density"
			<< sep << "Density real"
			<< sep << "Velocity Autocorrelation Function"
			<< sep << "Diffusitivity delta"
			<< sep << "Diffusitivity delta ratio"
			<< sep << "Diffusivity"
			<< sep << "Packing_ratio"
			<< sep << "State space Boublik"
			<< sep << "State space Handerson"
			<< sep << "State space Solan";

	stream << "\n\n";

	return (stream.str());
}

/**
 * Get static parameters full
 * @param sep
 * @return
 */
std::string ClassSiec::get_static_parameters_info(std::string sep)
{
	std::stringstream stream;
	double precision = 10;
	std::string sep_middle="\t";

	stream << '\n';
	stream << fixed << setprecision(precision)
			<< "Temperature: " << sep_middle << this->get_temperature()
			<< sep << "Density: "                            << sep_middle << this->get_density()
			<< sep << "Density real: "                       << sep_middle << this->get_density_real()
			<< sep << "Velocity Autocorrelation Function: "  << sep_middle << this->get_Velocity_Autocorrelation_Function()
			<< sep << "Diffusitivity delta: "                << sep_middle << this->get_diffusitivity_delta()
			<< sep << "Diffusitivity delta ratio: "          << sep_middle << this->get_diffusitivity_delta_ratio()
			<< sep << "Diffusivity: "                        << sep_middle << this->get_diffusivity()
			<< sep << "Packing_ratio: "                      << sep_middle << this->get_packing_ratio()
			<< sep << "Pressure from state space Boublik: "  << sep_middle << this->get_state_space_Boublik()
			<< sep << "Pressure from state space Handerson: "<< sep_middle << this->get_state_space_Handerson()
			<< sep << "Pressure from state space Solan: "    << sep_middle << this->get_state_space_Solan()
			<< sep << "Number of particles: "				 << sep_middle << int64_t(this->get_particles_len())
			<< sep << "RDF theor: " 						 << sep_middle << this->get_radial_distribution_function_theoretical()
			<< "\n\n";

#if DEBUG>0
	cout << stream.str();
#endif

	return (stream.str());
}

/**
 * Get static parameters raw data only
 * @param sep
 * @return
 */
std::string ClassSiec::get_static_parameters_raw(std::string sep)
{
	std::stringstream stream;
	double precision = 10;

	stream << '\n';
	stream << fixed << setprecision(precision)
			<< this->get_temperature()
			<< sep << this->get_density()
			<< sep << this->get_density_real()
			<< sep << this->get_Velocity_Autocorrelation_Function()
			<< sep << this->get_diffusitivity_delta()
			<< sep << this->get_diffusitivity_delta_ratio()
			<< sep << this->get_diffusivity()
			<< sep << this->get_packing_ratio()
			<< sep << this->get_state_space_Boublik()
			<< sep << this->get_state_space_Handerson()
			<< sep << this->get_state_space_Solan();

	stream << "\n\n";

	return (stream.str());
}
