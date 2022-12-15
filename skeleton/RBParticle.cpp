#include "RBParticle.h"

RBParticle::RBParticle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, double lifeTime, Vector4 colour, Vector3 scale, 
	bool isDynamic, PxScene* scene, PxPhysics* gPhysics, int mass, Vector3 matValues)
{
	vel = Vel;
	acc = Acc;
	mass_ = mass;
	inverse_mass = 1 / mass_;
	damping = Damping;
	lifeTime_ = lifeTime;
	colour_ = colour;
	scale_ = scale;
	pos = Pos;
	alive_ = true;
	isDynamic_ = isDynamic;
	iniTime_ = glutGet(GLUT_ELAPSED_TIME);
	scene_ = scene;
	gPhysics_ = gPhysics;
	staticFriction_ = matValues.x;
	dynamicFriction_ = matValues.y;
	restitution_ = matValues.z;

	if (isDynamic_) {
		addDynamicRB(pos,vel,colour_,scale_,staticFriction_,dynamicFriction_,restitution_);
	}
	else {
		addStaticBody(pos,colour_,scale_, staticFriction_, dynamicFriction_, restitution_);
	}
}



void RBParticle::integrate(double t)
{
	//MRU
	if (inverse_mass <= 0.0f) return;

	//EULER
	//vel += acc * t;
	//vel *= powf(damping, t);

	Vector3 newAcc = acc;
	newAcc += totForce * inverse_mass;

	vel = vel * pow(damping, t) + newAcc * t;
	pos = Vector3(pos.x + vel.x * t, pos.y + vel.y * t, pos.z + vel.z * t);
	clearForce();

	double actualTime = glutGet(GLUT_ELAPSED_TIME);
	if (lifeTime_ != -1) {
		if (actualTime - iniTime_ >= lifeTime_ || pos.y <= -1000 || pos.y >= 1000) {

			alive_ = false;
		}
	}
}

void RBParticle::addStaticBody(Vector3 pos, Vector4 color, Vector3 size, float staticFriction,float dynamicFriction, float restitution)
{
	PxRigidStatic* rs = gPhysics_->createRigidStatic(PxTransform(pos));
	mat_=  gPhysics_->createMaterial(staticFriction,dynamicFriction,restitution); //static friction, dynamic friction, restitution
	PxShape* shape = CreateShape(PxBoxGeometry(size.x, size.y, size.z),mat_);
	rs->attachShape(*shape);
	auto item = new RenderItem(shape, rs, color);
	scene_->addActor(*rs);
	
}

PxRigidDynamic* RBParticle::addDynamicRB(Vector3 pos, Vector3 vel, Vector4 color, Vector3 size,
	float staticFriction, float dynamicFriction, float restitution)
{
	rd = gPhysics_->createRigidDynamic(PxTransform(pos));
	rd->setLinearVelocity(vel);
	rd->setAngularVelocity({0,0,0});
	mat_ = gPhysics_->createMaterial(staticFriction, dynamicFriction, restitution); //static friction, dynamic friction, restitution
	PxShape* shape = CreateShape(PxBoxGeometry(size.x, size.y, size.z), mat_);
	rd->attachShape(*shape);
	rd->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });
	auto item = new RenderItem(shape, rd, color);
	scene_->addActor(*rd);
	
	return rd;
}
