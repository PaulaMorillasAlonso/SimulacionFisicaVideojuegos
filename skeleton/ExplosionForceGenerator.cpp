#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(double K, double R, double const_tiempo, Vector3& position)
{
	forceType = EXPLOSION;
	pos_ = position;
	K_ = K;
	R_ = R;
	const_tiempo_ = const_tiempo;
}

void ExplosionForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass() < 1e-10))
		return;
	double r = pow((particle->getPos().x - pos_.x), 2) +
		pow((particle->getPos().y - pos_.y), 2) +
		pow((particle->getPos().z - pos_.z), 2);
	if (r < R_) {

		Vector3 force = (K_ / r) *
			Vector3(particle->getPos().x - pos_.x,
				particle->getPos().y - pos_.y,
				particle->getPos().z - pos_.z)
			* std::exp(-t / const_tiempo_);

		particle->addForce(force);
	}
	R_ += 343 * t;
}

void ExplosionForceGenerator::updateForceRB(PxRigidDynamic* particle, double t)
{
	if (fabs(particle->getInvMass() < 1e-10))
		return;
	double r = pow((particle->getGlobalPose().p.x - pos_.x), 2) +
		pow((particle->getGlobalPose().p.y - pos_.y), 2) +
		pow((particle->getGlobalPose().p.z - pos_.z), 2);
	if (r < R_) {

		Vector3 force = (K_ / r) *
			Vector3(particle->getGlobalPose().p.x - pos_.x,
				particle->getGlobalPose().p.y - pos_.y,
				particle->getGlobalPose().p.z - pos_.z)
			* std::exp(-t / const_tiempo_);

		particle->addForce(force);
	}
	R_ += 343 * t;
}

