#pragma once
#include "GaussianParticleGenerator.h"
#include "WindForceGenerator.h"
#include "Particle.h"
class BolaNieve
{
	GaussianParticleGenerator* generator_;
	WindForceGenerator* force_;
	Particle* base_;
	Particle* esfera_;
	
public:
	BolaNieve(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, Vector3 std_dev_pos, Vector3 std_dev_vel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour, double scale, double mass,double radius);
	~BolaNieve();
	GaussianParticleGenerator* getBolaGen() { return generator_; };
	WindForceGenerator* getBolaForce() { return force_; };
};

