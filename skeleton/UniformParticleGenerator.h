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
	std::uniform_real_distribution<double> gen_prob_dist;
	std::default_random_engine gen_;
	double minPos_,maxPos_,minVel_,maxVel_, damping_,lifeTime_;
	Vector3 mean_acc;
	Vector4 colour_ = { 0,0,0,1 };

public:
	UniformParticleGenerator(Vector3 meanPos, Vector3 meanVel,Vector3 meanAcc,double minPos, double maxPos, double minVel, double maxVel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour);
	std::list<Particle*>generateParticle();
};

