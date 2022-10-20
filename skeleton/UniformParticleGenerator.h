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
	RenderItem* renderItem_;
	physx::PxTransform pose;
	Vector4 colour_ = { 0,0,0,1 };
	physx::PxShape* geomType_;

public:
	UniformParticleGenerator(double minPos, double maxPos, double minVel, double maxVel,double gen_prob, 
		int numPart,double damping, double lifeTime, physx::PxShape* geomType, Vector4 colour);
	std::vector<Particle*>generateParticle();
};

