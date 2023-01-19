#pragma once
#include <list>
#include "RenderUtils.hpp"

using namespace std;
using namespace physx;
class RBParticle
{
public:

	RBParticle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, double lifeTime, Vector4 colour, Vector3 scale,
		 PxScene* scene, PxPhysics* gPhysics, int mass, Vector3 matValues,	PxRigidDynamic* rigid=nullptr);

	RBParticle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, double lifeTime, Vector4 colour, Vector3 scale,
		PxScene* scene, PxPhysics* gPhysics, int mass, Vector3 matValues, physx::PxShape* geomType,PxRigidDynamic* rigid = nullptr);
	
	~RBParticle();

	//get
	Vector3 getPos() { return pos; }
	Vector3 getVel() { return vel; }
	Vector3 getAcc() { return acc; }
	Vector3 getScale() { return scale_; }
	double getDamping() { return damping; }
	double getLifetime() { return lifeTime_; }
	Vector4 getColour() { return colour_; }
	double getInverseMass() { return inverse_mass; }
	double getMass() { return mass_; }
	float getBounce() { return restitution_; }
	float getStaticFriction() { return dynamicFriction_; }
	float getDynamicFriction() { return staticFriction_; }


	//set
	void setColour(Vector4 color) { colour_ = color; }
	void setVel(Vector3 Vel) { vel = Vel; };
	void setPos(Vector3 Pose) { pos = Pose; };
	void setMass(double Mass) { mass_ = Mass; inverse_mass = 1 / Mass; };
	void setVelocity(Vector3 Vel) { vel = Vel; };
	void setAcceleration(Vector3 Acc) { acc = Acc; };
	void setDamping(double Damping) { damping = Damping; }
	void resetLifetime(double t) { lifeTime_ = t; }

	void setBounce(float b) {
		restitution_ = b; 
		mat_->setRestitution(restitution_);
	};
	void setDynamicFriction(float df) {
		dynamicFriction_ = df;
		mat_->setDynamicFriction(dynamicFriction_);
	}
	void setStaticFriction(float sf) {
		staticFriction_ = sf;
		mat_->setStaticFriction(staticFriction_);
	}
	void setInertiaTensor(Vector3 size) {
		rd->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });
	}

	//check
	bool isAlive() { return alive_; }

	virtual void integrate(double t);
	

	//Fuerzas
	void addForce(Vector3 f) {
		totForce += f;
	}
	void clearForce() { totForce = Vector3(0, 0, 0); }

	//creacion
	
	void addDynamicRB(Vector3 pos, Vector3 vel, Vector4 color, Vector3 size,
		float staticFriction, float dynamicFriction, float restitution, PxRigidDynamic *rigid);

	void addDynamicRB(Vector3 pos, Vector3 vel, Vector4 color, Vector3 size,
		float staticFriction, float dynamicFriction, float restitution, PxRigidDynamic* rigid, physx::PxShape* geomType);

	PxRigidDynamic* getDynamicInstance() { return rd; }

	

protected:

	Vector3 vel = { 0,0,0 };
	Vector3 totForce = { 0,0,0 };
	Vector3 acc = { 0,0,0 };
	Vector4 colour_ = { 0,0,0,1 };
	Vector3 pos;
	double damping, mass_, inverse_mass, gravity_;
	double lifeTime_, iniTime_;
	Vector3 scale_ = {10,1,10};
	bool alive_;
	PxScene* scene_;
	PxPhysics* gPhysics_;
	float staticFriction_,  dynamicFriction_,restitution_;
	PxMaterial* mat_;
	PxRigidDynamic* rd;
};

