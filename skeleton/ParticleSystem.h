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
#include "ExplosionForceGenerator.h"
#include "PlaneParticleGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "ParticleBungee.h"
#include "BuoyancyForceGenerator.h"
#include "Lampara.h"
#include "BolaNieve.h"
#include "Pecera.h"

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

	ExplosionForceGenerator* bolaExpGen_ = nullptr;
	WhirlwindForceGenerator* whirlwindGen_ = nullptr;
	ExplosionForceGenerator* explosionGen_ = nullptr;
	SpringForceGenerator* springGen_ = nullptr;
	ParticleDragGenerator* partDragGen_ = nullptr;
	BuoyancyForceGenerator* buoyancyGen_ = nullptr;
	double iniTime_;
	bool agitaBola_;

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
	void creaExplosion();
	void muelleFijo();
	void muelleDoble();
	void gomaElastica();
	void flotaTest();
	void creaSlinky();
	void activateSpringWind() { windGen_->activate(); };
	void deactivateSpringWind() { windGen_->deactivate(); };
	void activaViento();

	void addK();
	void subK();

	~ParticleSystem();

	//Final	
	void creaLampara(Vector3& pos);
	void creaBolaNieve(Vector3& pos);
	void agitaBolaNieve();
	void creaPeces(Vector3& pos);
};

