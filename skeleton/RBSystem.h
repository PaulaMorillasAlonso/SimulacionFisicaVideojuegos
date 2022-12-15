#pragma once
#include "core.hpp"
#include "UniformRBGenerator.h"
#include "RBForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "ExplosionForceGenerator.h"
#include <list>
using namespace std;
using namespace physx;


class RBSystem
{
private:
	std::list<RBParticle*>rigidBodies_;
	std::list<UniformRBGenerator*>rbGenerator_;
	PxScene* scene_;
	PxPhysics* gPhysics_;
	float iniTime_,spawnCubes_;
	UniformRBGenerator* uniformGen_;
	int maxUniformParticles_;
	//RBForceRegistry* forceReg_;
public:

	RBSystem(PxScene *scene, PxPhysics *gPhysics);
	~RBSystem() {};
	void update(double t);
	
	void addStaticRB(Vector3 pos, Vector4 color, Vector3 size, double lifetime, int mass, Vector3 matValue);
	void addDynamicRB(Vector3 pos, Vector3 vel, Vector4 color, Vector3 scale, double lifetime, int mass, Vector3 matValue);

	void addUniformGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, double minPos, double maxPos, double minVel, double maxVel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour, Vector3 scale, double mass, 
		PxScene* scene, PxPhysics* gPhysics, bool isDynamic,Vector3 matValue);
	void generatePerSeconds();
};

