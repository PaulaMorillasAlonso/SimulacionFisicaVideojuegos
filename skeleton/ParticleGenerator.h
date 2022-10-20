#pragma once
#include "Particle.h"
#include <list>
#include <string>
class ParticleGenerator
{
protected:
	std::string _name;
	//Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;
	//Particle* _model;

public:
	//void setParticle(Particle *model);
	virtual std::vector<Particle*> generateParticle() = 0;

};

