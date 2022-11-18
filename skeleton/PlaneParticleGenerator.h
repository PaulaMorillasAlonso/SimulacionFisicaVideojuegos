#pragma once
#include "ParticleGenerator.h"
#include "Particle.h"

class PlaneParticleGenerator :public ParticleGenerator
{
	double damping_, lifeTime_, scale_, mass_;
	Vector4 colour_ = { 0,0,0,1 };
	Vector3 pos_, vel_, acc_;
	std::list<Particle*> lista;

public:
	PlaneParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc,int numPart, double damping, double lifeTime,
		Vector4 colour, double scale, double mass);
	std::list<Particle*>generateParticle();
};

