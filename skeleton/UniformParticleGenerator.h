#pragma once

#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include <random>

class UniformParticleGenerator: public ParticleGenerator
{
private:
	std::uniform_real_distribution<double> dist_pos;
	std::uniform_real_distribution<double> dist_vel;
	std::default_random_engine gen_;
	double minPos_,maxPos_,minVel_,maxVel_;
	int numParticles;
public:
	UniformParticleGenerator(double minPos, double maxPos, double minVel, double maxVel);
	std::list<Particle*>generateParticle();
};

