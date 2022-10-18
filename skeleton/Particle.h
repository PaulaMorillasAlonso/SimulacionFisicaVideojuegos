#pragma once
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping,Vector4 colour);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, physx::PxShape* geomType, Vector4 colour);
	Particle() {};
	~Particle();
	void integrate(double t);

private:
	Vector3 vel = {0,0,0};
	Vector3 acc = {0,0,0};
	Vector4 colour_ = { 0,0,0,1 };
	physx::PxTransform pose;
	double damping, inverse_mass, gravity;
	RenderItem* rendeItem;
public:
	Vector3 getPos() { return pose.p; }
	void setColour(Vector4 color) { colour_ = color; }
	Vector3 getVel() { return vel; }
	void setPos(Vector3 Pose) { pose.p = Pose; };
	void setVel(Vector3 Vel) { vel = Vel; };
	void setMass(double Mass) { inverse_mass = 1 / Mass; };
	void setVelocity(Vector3 Vel) { vel = Vel; };
	void setAcceleration(Vector3 Acc) { acc = Acc; };
	void setDamping(double Damping) { damping = Damping; }
};

