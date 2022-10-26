#pragma once
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime,Vector4 colour,double scale, int type=-1);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, physx::PxShape* geomType, Vector4 colour);
	Particle() {};
	~Particle();
	virtual void integrate(double t);
	virtual Particle* clone() const;
	Vector3 getPos() { return pose.p; }
	void setColour(Vector4 color) { colour_ = color; }
	Vector3 getVel() { return vel; }
	void setPos(Vector3 Pose) { pose.p = Pose; };
	void setVel(Vector3 Vel) { vel = Vel; };
	void setMass(double Mass) { inverse_mass = 1 / Mass; };
	void setVelocity(Vector3 Vel) { vel = Vel; };
	void setAcceleration(Vector3 Acc) { acc = Acc; };
	void setDamping(double Damping) { damping = Damping; }
	double getLifetime() { return lifeTime_;}
	void resetLifetime(double t) { lifeTime_ = t; }
	bool isAlive() { return alive_; }
	bool isFirework() { return type_ >= 0; }
	//virtual Particle* clone() const;

protected:

	Vector3 vel = {0,0,0};
	Vector3 acc = {0,0,0};
	Vector4 colour_ = { 0,0,0,1 };
	physx::PxTransform pose;
	double damping, inverse_mass, gravity;
	double lifeTime_, iniTime_, scale_;
	bool alive_;
	int type_;
	RenderItem* renderItem;
	
};

