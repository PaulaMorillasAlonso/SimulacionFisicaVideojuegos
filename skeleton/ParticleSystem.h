#pragma once
#include "ParticleGenerator.h"
#include <list>
#include <string>
#include <vector>
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "CircleParticleGenerator.h"
#include "SphereParticleGenerator.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ForceGenerator.h"
#include "ParticleDragGenerator.h"

class ParticleSystem
{
private:
	std::list<Particle*>_particles;
	std::list<ParticleGenerator*>_particle_generators;
	UniformParticleGenerator* fuente_;
	GaussianParticleGenerator* humo_;
	std::vector<FireworkRule> firework_rules_;
	Vector4 randomColour();

	ParticleForceRegistry* forceReg_;
	GravityForceGenerator* gravGen_ = nullptr;
	WindForceGenerator* windGen_ = nullptr;
	WhirlwindForceGenerator* whirlwindGen_ = nullptr;

protected:

public:
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem(unsigned type);
	void createFireworkRules();
	ParticleSystem();
	void creaFuente();
	void creaFuenteGravedad(Vector3 g, Vector3 pos, Vector4 color, double mass);
	void creaViento();
	void creaTornado();
	~ParticleSystem();
	
};

