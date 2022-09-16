#pragma once
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc,double damping);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	Vector3 acc;
	double damping;
	physx::PxTransform pose;
	RenderItem* rendeItem;
};

