#pragma once
#include "ParticleGenerator.h"
#include <list>
#include <string>
#include "UniformParticleGenerator.h"

class ParticleSystem
{
private:
	std::vector<Particle*>_particles;
	std::vector<ParticleGenerator*>_particle_generators;
	UniformParticleGenerator* fuente_;
protected:
public:
	void update(double t);
	//ParticleGenerator* getParticleGenerator(std::string name);
	//void generateFireworkSystem();
	ParticleSystem();
	~ParticleSystem();
	std::vector<Particle*>getParticleList();
};

