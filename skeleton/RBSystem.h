#pragma once
#include "core.hpp"
#include "UniformRBGenerator.h"
#include <list>
using namespace std;
using namespace physx;

class RBSystem
{
private:
	std::list<RBParticle*>rigidBodies_;
	PxScene* scene_;
	PxPhysics* gPhysics_;
	float iniTime_,spawnCubes_;
	UniformRBGenerator* uniformGen_;
	int maxUniformParticles_;
public:

	RBSystem(PxScene *scene, PxPhysics *gPhysics);
	~RBSystem() {};
	void update(double t) {};
	
	void addStaticRB(Vector3 pos, Vector4 color, Vector3 size, double lifetime, int mass);
	void addDynamicRB(Vector3 pos, Vector3 vel, Vector4 color, Vector3 scale, double lifetime, int mass);

	void addUniformGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, double minPos, double maxPos, double minVel, double maxVel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour, Vector3 scale, double mass, PxScene* scene, PxPhysics* gPhysics, bool isDynamic);
	void generatePerSeconds();
};

