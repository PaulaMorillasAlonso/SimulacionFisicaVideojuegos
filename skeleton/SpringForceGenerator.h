#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator :public ForceGenerator
{
public:
	SpringForceGenerator(double k, double restingLength, Particle* other) {
		k_ = k;
		resting_length = restingLength;
		other_ = other;
	
	};
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double k) { k_ = k; }
	inline double getK() { return k_; }
	virtual ~SpringForceGenerator() {}

protected:
	double k_; // Elastic Coeff.
	double resting_length;
	Particle* other_;
};

