#pragma once
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping);
	Particle() {};
	~Particle();
	void integrate(double t);

private:
	Vector3 vel = {0,0,0};
	Vector3 acc = {0,0,0};
	physx::PxTransform pose;
	double damping, inverse_mass, gravity;
	RenderItem* rendeItem;

protected:
	Vector3 getVel() { return vel; }
	void setPos(Vector3 Pose) { pose.p = Pose; };
	void setMass(double Mass) { inverse_mass = 1 / Mass; };
	void setVelocity(Vector3 Vel) { vel = Vel; };
	void setAcceleration(Vector3 Acc) { acc = Acc; };
	void setDamping(double Damping) { damping = Damping; }
};

