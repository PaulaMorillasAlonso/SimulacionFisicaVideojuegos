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
int ParticleGenerator::addForceGenerator(GravityForceGenerator* force) {
    GravityForceGenerator* grav = force;
    if (grav != nullptr) {
        gravGen_ = grav;
        return -1;
    }
    return 0;
}
std::vector<GravityForceGenerator*>ParticleGenerator::returnForce() {
    std::vector<GravityForceGenerator*>forceGen;
    if (gravGen_ != nullptr) {
        forceGen.push_back(gravGen_);
    }
    return forceGen;
}