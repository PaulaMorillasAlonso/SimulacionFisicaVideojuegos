#include "ParticleGenerator.h"

void ParticleGenerator::setParticle(Particle* model)
{
	delete model_;
	model_ = model;
}

Particle* ParticleGenerator::clone()
{

	return new Particle(model_->getPos(), model_->getVel(), model_->getAcc(), model_->getDamping(), model_->getLifetime(), model_->getColour(), model_->getScale());
}
