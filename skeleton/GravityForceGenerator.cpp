#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInverseMass())<1e-10) {
		return;
	}
	p->addForce(gravity_ * p->getMass());
}
