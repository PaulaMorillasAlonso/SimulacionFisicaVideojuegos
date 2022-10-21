#pragma once
#include "Particle.h"
#include <list>
#include <string>
class ParticleGenerator
{
protected:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;

public:
	//void setParticle(Particle *model);
	virtual std::list<Particle*> generateParticle() = 0;
	std::string getGeneratorName() { return _name; }
};

