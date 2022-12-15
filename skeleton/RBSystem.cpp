#include "RBSystem.h"
#include "RBParticle.h"

RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics)
{
	scene_ = scene;
	gPhysics_ = gPhysics;
	spawnCubes_ = 3000;
	iniTime_ = 0;
	maxUniformParticles_ = 10;
}

void RBSystem::update(double t)
{
	/*std::list<RBParticle*>::iterator it = rigidBodies_.begin();

	while (it != rigidBodies_.end()) {
		RBParticle* p = *it;
		if (p->isAlive()) {
			p->integrate(t);
			++it;
		}
		else
		{
			it = rigidBodies_.erase(it);
			forceReg_->deleteParticleRegistry(p);
			delete p;
		}
	}
	for (auto e : rbGenerator_)
	{
		auto list = e->generateRB();

		std::vector<ForceGenerator*> force = e->returnForce();

		for (auto i : list)
		{
			rigidBodies_.push_back(i);

			for (auto s : force) {

				if (s->forceType == RBForceGenerator::GRAVITY) {
					GravityForceGenerator* grav = static_cast<GravityForceGenerator*>(s);
					if (grav != nullptr) {
						forceReg_->addRegistry(grav, i);
					}
				}
				else if (s->forceType == RBForceGenerator::WIND) {
					WindForceGenerator* w = static_cast<WindForceGenerator*>(s);
					if (w != nullptr) {
						forceReg_->addRegistry(w, i);
					}
				}
				else if (s->forceType == RBForceGenerator::WHIRLWIND) {
					WhirlwindForceGenerator* w = static_cast<WhirlwindForceGenerator*>(s);
					if (w != nullptr) {
						forceReg_->addRegistry(w, i);
					}
				}
				else if (s->forceType == RBForceGenerator::EXPLOSION) {
					ExplosionForceGenerator* exp = static_cast<ExplosionForceGenerator*>(s);
					if (exp != nullptr) {
						forceReg_->addRegistry(exp, i);
					}
				}

			}
		}

	}
	forceReg_->updateForces(t);*/
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
	}
}
