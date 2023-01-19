#include "RBSystem.h"
#include "RBParticle.h"

RBSystem::RBSystem(PxScene* scene, PxPhysics* gPhysics)
{
	scene_ = scene;
	gPhysics_ = gPhysics;
	spawnCubes_ = 3000;
	iniTime_ = 0;
	maxUniformParticles_ = 10;
	//windGen_ = new WindForceGenerator(1, 0, Vector3(-100, 1, 0), { -150,0,-250 }, 20);
	forceReg_ = new RBForceRegistry();
}

RBSystem::~RBSystem()
{
	delete uniformGen_;
	delete windGen_;
	delete windBloquesGen_;

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

void RBSystem::creaBloques(Vector3& pos)
{
	windBloquesGen_= new WindForceGenerator(1, 0, Vector3(40, 80, 30), {pos.x,pos.y,pos.z }, 20);
	windBloquesGen_->deactivate();

	addStaticRB({pos.x,pos.y,pos.z}, { 0,0.9,1,1 }, { 8,8,8 }, -1, 1, { 0.5,0.5,0.6 }); //estatico


	RBParticle* p = new RBParticle({ pos.x + 20,pos.y,pos.z - 10 }, { 0,0,0 }, { 0,0,0 }, //dinamico mayor size y masa
		0.99f, -1, { 1,0,1,1 }, {6,6,6 }, scene_, gPhysics_, 4, {0.5,0.5,0.5});
	rigidBodies_.push_back(p);
	forceReg_->addRegistry(windBloquesGen_, p->getDynamicInstance());

	RBParticle* p2 = new RBParticle({ pos.x+20 ,pos.y,pos.z+20}, { 0,0,0 }, { 0,0,0 }, //dinamico menor size y masa
		0.99f, -1, { 1,0.99,0,1 }, { 3,3,3 }, scene_, gPhysics_, 1, { 0.5,0.5,0.5 });
	rigidBodies_.push_back(p2);
	forceReg_->addRegistry(windBloquesGen_, p2->getDynamicInstance());


	RBParticle* p3 = new RBParticle({ pos.x ,pos.y+10,pos.z }, { 0,0,0 }, { 0,0,0 }, //pelota
		0.99f, -1, { 0.78,0,0.22,1 }, { 3,3,3 }, scene_, gPhysics_, 1, { 0.7,0.8,1 },CreateShape(physx::PxSphereGeometry(4)));
	rigidBodies_.push_back(p3);
	forceReg_->addRegistry(windBloquesGen_, p3->getDynamicInstance());


	RBParticle* p4 = new RBParticle({ pos.x-10 ,pos.y,pos.z+50 }, { 0,0,0 }, { 0,0,0 }, //pelota
		0.99f, -1, { 0.36,1,0,1 }, { 3,3,3 }, scene_, gPhysics_, 1, { 0.5,0.5,0.5 }, CreateShape(physx::PxSphereGeometry(6)));
	rigidBodies_.push_back(p4);
	forceReg_->addRegistry(windBloquesGen_, p4->getDynamicInstance());


}
