#pragma once
#include "Particle.h"
#include <list>
#include <string>
#include <vector>
#include "ForceGenerator.h"
#include "GravityForceGenerator.h"

class ParticleGenerator
{
	GravityForceGenerator* gravGen_=nullptr;
protected:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;
	Particle* model_ = nullptr;

public:
	void setParticle(Particle *model);
	virtual std::list<Particle*> generateParticle() = 0;
	std::string getGeneratorName() { return _name; }
	virtual Particle* clone();
	int addForceGenerator(ForceGenerator* force);
	std::vector<ForceGenerator*>returnForce();
};

