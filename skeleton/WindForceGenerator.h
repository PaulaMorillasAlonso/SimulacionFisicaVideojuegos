#pragma once
#include "ParticleDragGenerator.h"

class WindForceGenerator : public ParticleDragGenerator
{
public:
	
	WindForceGenerator(const float k1, const float k2, Vector3 windVelocity, Vector3 pos, int radius=0);
	virtual void updateForce(Particle* particle, double t) override;
	~WindForceGenerator() {};

protected:

	Vector3 windVel_;
	Vector3 pos_;
	//double r_;

};

