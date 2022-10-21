#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include <random>

class GaussianParticleGenerator: public ParticleGenerator
{
	std::normal_distribution<double> dist_pos;
	std::normal_distribution<double> dist_vel;
	std::uniform_real_distribution<double> gen_prob_dist;
	std::default_random_engine gen_;
	double minPos_, maxPos_, minVel_, maxVel_, damping_, lifeTime_;
	Vector4 colour_ = { 0,0,0,1 };

public:
	GaussianParticleGenerator(double minPos, double maxPos, double minVel, double maxVel,double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour);
	std::vector<Particle*>generateParticle();
};

