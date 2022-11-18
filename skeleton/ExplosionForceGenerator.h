#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator :public ForceGenerator
{
public:

	ExplosionForceGenerator(double K, double R,double const_tiempo, Vector3&position);
	virtual void updateForce(Particle* particle, double t) override;
	~ExplosionForceGenerator() {};

protected:

	Vector3 pos_;
	double K_,R_,const_tiempo_;
	
};
