#pragma once
#include "ParticleGenerator.h"
#include <list>
#include <string>
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"

class ParticleSystem
{
private:
	std::list<Particle*>_particles;
	std::list<ParticleGenerator*>_particle_generators;
	UniformParticleGenerator* fuente_;
	GaussianParticleGenerator* humo_;
protected:
public:
	void update(double t);
	//ParticleGenerator* getParticleGenerator(std::string name);
	//void generateFireworkSystem();
	ParticleSystem();
	~ParticleSystem();
	std::list<Particle*>getParticleList();
};

