#pragma once
#include "RenderUtils.hpp"
#include <list>
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, Vector4 colour, double scale, int mass = 10, int type = -1);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, Vector4 colour, double scale, bool radio,double radius=-1,int mass=10,int type = -1);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, physx::PxShape* geomType, Vector4 colour, double scale, int mass = 10, int type = -1);
	Particle() {};
	~Particle();

	//get
	Vector3 getPos() { return pose.p; }
	Vector3 getVel() { return vel; }
	Vector3 getAcc() { return acc; }
	double getScale() { return scale_; }
	double getDamping() { return damping; }
	double getLifetime() { return lifeTime_; }
	Vector4 getColour() { return colour_;}
	double getInverseMass() { return inverse_mass; }
	double getMass() { return mass_; }

	//set
	void setColour(Vector4 color) { colour_ = color; }
	void setVel(Vector3 Vel) { vel = Vel; };
	void setPos(Vector3 Pose) { pose.p = Pose; };
	void setMass(double Mass) { mass_ = Mass; inverse_mass = 1 / Mass; };
	void setVelocity(Vector3 Vel) { vel = Vel; };
	void setAcceleration(Vector3 Acc) { acc = Acc; };
	void setDamping(double Damping) { damping = Damping; }
	void resetLifetime(double t) { lifeTime_ = t; }
	void setAlive(bool viva) { alive_ = viva; }

	//check
	bool isAlive() { return alive_; }
	bool isFirework() { return type_ >= 0; }

	virtual void integrate(double t);
	virtual std::list<Particle*> explode();

	//Fuerzas
	void addForce(Vector3 f) { 
		totForce += f; 
	}
	void clearForce() { totForce = Vector3(0,0,0); }

protected:

	Vector3 vel = { 0,0,0 };
	Vector3 iniPos = { 0,0,0 };
	Vector3 totForce = {0,0,0};
	Vector3 acc = {0,0,0};
	Vector4 colour_ = { 0,0,0,1 };
	physx::PxTransform pose;
	double damping, mass_,inverse_mass, gravity;
	double lifeTime_, iniTime_, scale_;
	bool alive_,tieneRadio_=false;
	int type_;
	double radius_;
	RenderItem* renderItem;

	
};

