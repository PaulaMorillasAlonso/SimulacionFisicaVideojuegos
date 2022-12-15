#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator: public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g){ 
		forceType = GRAVITY;
		setGravity(g);
	};
	virtual void updateForce(Particle* particle, double t);
	virtual void updateForceRB(PxRigidDynamic* particle, double t);
	inline void setGravity(Vector3 g) { gravity_ = g; }
protected:
	Vector3 gravity_;
};

