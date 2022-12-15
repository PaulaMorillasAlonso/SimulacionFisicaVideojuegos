#pragma once
#include "WindForceGenerator.h"

class WhirlwindForceGenerator :public WindForceGenerator
{
public:
	WhirlwindForceGenerator(const float k1, const float k2, float K, Vector3 windVelocity, Vector3 origin);
	virtual void updateForce(Particle* particle, double t) override;
	virtual void updateForceRB(PxRigidDynamic* particle, double t) override;

	~WhirlwindForceGenerator() {};
private:
	Vector3 origin_;
	float varY_,K_;
};

