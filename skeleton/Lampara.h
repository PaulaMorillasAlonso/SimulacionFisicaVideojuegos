#pragma once
#include "UniformParticleGenerator.h"
#include "Particle.h"
class Lampara
{
	UniformParticleGenerator* generator_;
	Particle* base_;
	Particle* capsula_;

public:
	Lampara(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, double minPos, double maxPos, double minVel, double maxVel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour, double scale, double mass);
	~Lampara();
	UniformParticleGenerator* getLampGen() { return generator_; };
};

