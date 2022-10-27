#pragma once
#include "ParticleGenerator.h"
#include <list>
#include "Particle.h"
#include <random>
class SphereParticleGenerator :public ParticleGenerator
{
	std::uniform_real_distribution<double> gen_prob_dist;
	std::default_random_engine gen_;
	double radius_;
public:
	SphereParticleGenerator(Vector3 meanVel, double gen_prob, double radius, double numPart = 10);
	SphereParticleGenerator() {};
	std::list<Particle*>generateParticle();
};

