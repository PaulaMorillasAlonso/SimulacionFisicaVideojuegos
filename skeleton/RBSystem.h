#pragma once
#include "core.hpp"
#include <list>
using namespace std;
using namespace physx;

class RBSystem
{
private:
	std::list<PxRigidDynamic*>dynamicRigidBodies_;
	std::list<PxRigidStatic*>staticRigidBodies_; //{·O·}
	PxScene* scene_;
	PxPhysics* gPhysics_;

public:

	RBSystem(PxScene *scene, PxPhysics *gPhysics);
	~RBSystem() {};
	void update(double t) {};
	
	void addStaticRB(Vector3 pos, Vector4 color, Vector3 size, double lifetime, int mass);
	void addDynamicRB(Vector3 pos, Vector3 vel, Vector4 color, Vector3 scale, double lifetime, int mass);
};

