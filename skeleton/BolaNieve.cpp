#include "BolaNieve.h"

BolaNieve::BolaNieve(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, Vector3 std_dev_pos, Vector3 std_dev_vel, double gen_prob,
	int numPart, double damping, double lifeTime, Vector4 colour, double scale, double mass,double radius)
{
	generator_ = new GaussianParticleGenerator({meanPos.x,meanPos.y,meanPos.z}, meanVel, meanAcc, std_dev_pos, std_dev_vel, gen_prob,
		numPart,  damping,  lifeTime, colour, scale, mass,radius-1);

	auto baseObj = CreateShape(physx::PxBoxGeometry(1.5, 0.8, 1.5));
	base_ = new Particle({ meanPos.x,meanPos.y - 3,meanPos.z }, { 0,0,0 }, { 0,0,0 }, 0, -1, baseObj, { 0.5, 0.2, 0.0, 1 }, 1);

	
	auto capsObj = CreateShape(physx::PxSphereGeometry(radius));
	esfera_ = new Particle({ meanPos.x,meanPos.y,meanPos.z }, { 0,0,0 }, { 0,0,0 }, 0, -1, capsObj, { 0.69, 0.84, 0.98, 0.6 }, 1);

	force_ = new WindForceGenerator(-1, 0, {-1.5,-1,1}, { meanPos.x,meanPos.y,meanPos.z }, 1);

}

BolaNieve::~BolaNieve()
{
	delete generator_;
	delete base_;
	delete esfera_;
	delete force_;
}
