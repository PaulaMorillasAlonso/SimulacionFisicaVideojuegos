#include "Lampara.h"

Lampara::Lampara(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, double minPos, double maxPos, double minVel, double maxVel, double gen_prob, int numPart, double damping, double lifeTime, Vector4 colour, double scale, double mass)
{
	generator_ = new UniformParticleGenerator({meanPos.x-1,meanPos.y+2,meanPos.z-1}, meanVel, meanAcc, minPos, maxPos, minVel, maxVel,
				gen_prob, numPart, damping, lifeTime, colour, scale, mass);

	auto baseObj = CreateShape(physx::PxBoxGeometry(1.5, 0.8, 1.5));
	base_ = new Particle({meanPos.x,meanPos.y-3,meanPos.z}, { 0,0,0 }, { 0,0,0 }, 0, -1, baseObj, { 0.5, 0.2, 0.0, 1 }, 1);

	auto capsObj = CreateShape(physx::PxBoxGeometry(0.6, 2, 0.6));
	capsula_= new Particle({ meanPos.x,meanPos.y,meanPos.z }, { 0,0,0 }, { 0,0,0 }, 0, -1, capsObj, { 1, 0.8, 0.6, 1 }, 1);

}

Lampara::~Lampara()
{
	delete generator_;
	delete base_;
	delete capsula_;
}
