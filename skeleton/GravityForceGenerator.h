#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator: public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g) :gravity_(g),myType(ForceGenerator::GRAVITY) {};
	virtual void updateForce(Particle* particle, double t);
	inline void setGravity(Vector3 g) { gravity_ = g; }
protected:
	Vector3 gravity_;
	forceTypes myType;
};

