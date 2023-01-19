#include "WindForceGenerator.h"
WindForceGenerator::WindForceGenerator(const float k1, const float k2, Vector3 windVel,
	Vector3 pos, int radius):ParticleDragGenerator(k1,k2)
{
	setDrag(k1, k2);
	windVel_ = windVel;
	forceType = WIND;
	pos_ = pos;
	r_ = radius;
	isActive = true;
	//new Particle(pos, { 0,0,0 }, { 0,0,0 }, 1.0, 30000, { 1, .0, 0.0, 0.1 },r_,1);
}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass()) < 1e-10)
		return;
	if (isActive) {
		//if (checkPosition(particle)) {
		Vector3 particlePos = particle->getPos();
		if ((particlePos.x <= pos_.x + r_ && particlePos.x >= pos_.x - r_) &&
			(particlePos.y <= pos_.y + r_ && particlePos.y >= pos_.y - r_) &&
			(particlePos.z <= pos_.z + r_ && particlePos.z >= pos_.z - r_)) {
			Vector3 v = particle->getVel() - windVel_;

			float drag_coef = v.normalize();
			Vector3 dragF;
			drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
			dragF = -v * drag_coef;

			particle->addForce(dragF);

			//}
		}
	}
	
}

void WindForceGenerator::updateForceRB(PxRigidDynamic* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10)
		return;
	if (isActive) {
	
		Vector3 v = particle->getLinearVelocity() - windVel_;

		float drag_coef = v.normalize();
		Vector3 dragF;
		drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
		dragF = -v * drag_coef;

		particle->addForce(dragF);
	}
}


