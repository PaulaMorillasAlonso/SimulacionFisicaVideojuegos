#include "ParticleGenerator.h"

void ParticleGenerator::setParticle(Particle* model)
{
	delete model_;
	model_ = model;
}

Particle* ParticleGenerator::clone()
{

	return new Particle(model_->getPos(), model_->getVel(), model_->getAcc(), model_->getDamping(), model_->getLifetime(), model_->getColour(), model_->getScale(),1);
}
int ParticleGenerator::addForceGenerator(ForceGenerator* force) {
    GravityForceGenerator * gravity = static_cast<GravityForceGenerator*>(force);
    if (gravity != nullptr) {
        gravGen_ = gravity;
        return -1;
    }
    return 0;
}
std::vector<ForceGenerator*>ParticleGenerator::returnForce() {
    std::vector<ForceGenerator*>forceGen;
    if (gravGen_ != nullptr) {
        forceGen.push_back(gravGen_);
    }
    return forceGen;
}