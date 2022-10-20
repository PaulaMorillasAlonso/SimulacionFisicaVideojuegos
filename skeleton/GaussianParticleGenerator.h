#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include <random>

class GaussianParticleGenerator: public ParticleGenerator
{
	std::normal_distribution<double> dist_pos{0,1};
	std::normal_distribution<double> dist_vel{0,1};
	std::default_random_engine gen_;
	double minPos_, maxPos_, minVel_, maxVel_;
	int numParticles;
public:
	GaussianParticleGenerator(double minPos, double maxPos, double minVel, double maxVel);
	std::list<Particle*>generateParticle();
};

