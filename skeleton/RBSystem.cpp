#include "RBSystem.h"
#include "RBParticle.h"

RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics)
{
	scene_ = scene;
	gPhysics_ = gPhysics;
	spawnCubes_ = 3000;
	iniTime_ = 0;
	maxUniformParticles_ = 10;
	windGen_ = new WindForceGenerator(1, 0, Vector3(10, 100, -10), { -150,0,-250 }, 10);
}

void RBSystem::update(double t)
{
	std::list<RBParticle*>::iterator it = rigidBodies_.begin();

	while (it != rigidBodies_.end()) {
		RBParticle* p = *it;
		if (p->isAlive()) {
			p->integrate(t);
			++it;
		}
		else
		{
			it = rigidBodies_.erase(it);
			forceReg_->deleteParticleRegistry(castParticle(p));
			delete p;
		}
	}
	
	forceReg_->updateForces(t);
}

void RBSystem::addStaticRB(Vector3 pos, Vector4 color, Vector3 scale, double lifetime, int mass, Vector3 matValue)
{
	RBParticle* p = new RBParticle(pos, { 0,0,0 }, { 0,0,0 }, 1, lifetime, color,
		scale, false, scene_, gPhysics_, mass,matValue);
}

void RBSystem::addDynamicRB(Vector3 pos, Vector3 vel, Vector4 color, Vector3 scale, double lifetime, int mass, Vector3 matValue)
{
	RBParticle* p = new RBParticle(pos, vel, { 0,0,0 }, 1, lifetime, color,
		scale, true, scene_, gPhysics_, mass,matValue);
}
void RBSystem::addUniformGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, double minPos, double maxPos, double minVel, double maxVel, double gen_prob,
	int numPart, double damping, double lifeTime, Vector4 colour, Vector3 scale, 
	double mass, PxScene* scene, PxPhysics* gPhysics, bool isDynamic, Vector3 matValue)
{
	uniformGen_ = new UniformRBGenerator(meanPos, meanVel, meanAcc, minPos, maxPos, minVel, maxVel, gen_prob,
		numPart, damping, lifeTime, colour, scale, mass, scene, gPhysics, isDynamic,matValue);
	
}

void RBSystem::generatePerSeconds()
{
	std::list<RBParticle*> partList;
	if (glutGet(GLUT_ELAPSED_TIME) >= iniTime_ && rigidBodies_.size()<maxUniformParticles_) {
		
		partList=uniformGen_->generateRB();
		iniTime_ = glutGet(GLUT_ELAPSED_TIME) + spawnCubes_;
	}
	for (auto e:partList) {

		rigidBodies_.push_back(e);
		forceReg_->addRegistry(windGen_, castParticle(e));
	}
}
