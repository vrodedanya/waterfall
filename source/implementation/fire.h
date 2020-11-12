#ifndef FIRE_H
#define FIRE_H

#include "../particle.h"
#include "../manager.h"
#include "../dbhelper.h"
#include <vector>
#include <thread>
#include <SDL2/SDL.h>

class Fire : public Particle
{
private:
public:
	Fire();
	~Fire();
	double t;
	double x;
	double y;
	unsigned environment;

};
class FireManager : public Manager
{
private:
	unsigned int threads_count;
	SDL_Renderer* renderer;
	std::vector<Fire*> particles;
	int& exclude_x;
	int& exclude_y;

	int center_x;
	int center_y;
	int radius_x;
	int radius_y;
	int exclude_radius;
	
	unsigned& dwidth;
	unsigned& dheight;
public:
	explicit FireManager(SDL_Renderer* renderer, unsigned& window_width, unsigned& window_height, unsigned count, int& exc_x, int& exc_y, int cen_x, int cen_y, int rad_x, int rad_y, int exc_rad) : exclude_x(exc_x), exclude_y(exc_y), center_x(cen_x), center_y(cen_y), radius_x(rad_x), radius_y(rad_y), exclude_radius(exc_rad), dwidth(window_width), dheight(window_height)
	{
		this->renderer = renderer;
		for (unsigned i = 0 ; i < count ; i++)
		{
			Fire* buf = new Fire;
			particles.emplace_back(buf);
		}
		threads_count = std::thread::hardware_concurrency();
	}
	~FireManager()
	{
		for (unsigned i = 0 ; i < particles.size() ; i++)
		{
			delete particles[i];
		}
	}
	void spawn_part(int begin, int end);
	void draw();
	void move(int begin, int end);
	void check(int begin, int end);

	void zeroize_env(int begin, int end);
	void update();
};

#endif