#pragma once
#include "ParticleGenerator.h"
#include <list>
#include <string>
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "CircleParticleGenerator.h"
#include "SphereParticleGenerator.h"
#include "Firework.h"

class ParticleSystem
{
private:
	std::list<Particle*>_particles;
	std::list<ParticleGenerator*>_particle_generators;
	UniformParticleGenerator* fuente_;
	GaussianParticleGenerator* humo_;
	std::vector<FireworkRule> firework_rules_;
	Vector4 randomColour();
protected:
public:
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem(unsigned type);
	void createFireworkRules();
	ParticleSystem();
	~ParticleSystem() {};
	
};

