#pragma once
#include "ParticleGenerator.h"
#include <list>
#include <string>

class ParticleSystem
{
private:
	std::list<Particle*>_paticles;
	std::list<ParticleGenerator*>_paticle_generators;
protected:
public:
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();
};

