#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInverseMass())<1e-10) {
		return;
	}
	p->addForce(gravity_ * p->getMass());
}

void GravityForceGenerator::updateForceRB(PxRigidDynamic* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10) {
		return;
	}
	particle->addForce(gravity_ * particle->getMass());
}
