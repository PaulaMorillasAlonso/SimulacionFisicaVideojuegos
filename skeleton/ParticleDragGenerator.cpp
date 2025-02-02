#include "ParticleDragGenerator.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10) {
		return;
	}

	Vector3 v = particle->getVel();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	particle->addForce(dragF);
}

void ParticleDragGenerator::updateForceRB(PxRigidDynamic* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10) {
		return;
	}

	Vector3 v = particle->getLinearVelocity();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	particle->addForce(dragF);
}
