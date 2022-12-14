#include "RBSystem.h"
#include "RBParticle.h"

RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics) 
{
	scene_ = scene;
	gPhysics_ = gPhysics;

}

void RBSystem::addStaticRB(Vector3 pos, Vector4 color, Vector3 scale,double lifetime,int mass)
{
	RBParticle* p = new RBParticle(pos, { 0,0,0 }, {0,0,0}, 1,lifetime ,color,
		scale, false, scene_, gPhysics_,mass);
}

void RBSystem::addDynamicRB(Vector3 pos,Vector3 vel, Vector4 color, Vector3 scale, double lifetime, int mass)
{
	RBParticle* p = new RBParticle(pos, vel, { 0,0,0 }, 1, lifetime, color,
		scale, true, scene_, gPhysics_, mass);
}
