#include "RBSystem.h"
#include "RBParticle.h"

RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics)
{
	scene_ = scene;
	gPhysics_ = gPhysics;
	spawnCubes_ = 3000;
	iniTime_ = 0;
	maxUniformParticles_ = 10;
	windGen_ = new WindForceGenerator(-1, 0, Vector3(100, 1, -100), { -150,0,-250 }, 100);
	forceReg_ = new RBForceRegistry();
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
			forceReg_->deleteParticleRegistry(p->getDynamicInstance());
			delete p;
		}
	}
	
	forceReg_->updateForces(t);
}

void RBSystem::addStaticRB(Vector3 pos, Vector4 color, Vector3 scale, double lifetime, int mass, Vector3 matValue)
{
	PxRigidStatic* rs = gPhysics_->createRigidStatic(PxTransform(pos));
	PxMaterial* mat = gPhysics_->createMaterial(matValue.x, matValue.y, matValue.z); //static friction, dynamic friction, restitution
	PxShape* shape = CreateShape(PxBoxGeometry(scale.x, scale.y, scale.z), mat);
	rs->attachShape(*shape);
	auto item = new RenderItem(shape, rs, color);
	scene_->addActor(*rs);

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

	std::list<PxRigidDynamic*> dynList;
	if (glutGet(GLUT_ELAPSED_TIME) >= iniTime_ && rigidBodies_.size()<maxUniformParticles_) {
		
		dynList=uniformGen_->generateRB();
		iniTime_ = glutGet(GLUT_ELAPSED_TIME) + spawnCubes_;
	}
	
	for (auto i : dynList) 
	{
		dynamicBodies_.push_back(i);
		forceReg_->addRegistry(windGen_, i);
	}
}
