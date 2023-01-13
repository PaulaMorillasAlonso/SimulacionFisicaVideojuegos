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
	double damping_, lifeTime_, scale_,mass_;
	Vector4 colour_ = { 0,0,0,1 };
	Vector3 std_dev_pos, std_dev_vel, mean_acc;
	double radius_;
public:
	GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel,Vector3 meanAcc,Vector3 std_dev_pos,Vector3 std_dev_vel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour, double scale, double mass);
	GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, Vector3 std_dev_pos, Vector3 std_dev_vel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour, double scale, double mass,double radius);
	std::list<Particle*>generateParticle();
	~GaussianParticleGenerator() {};
};

