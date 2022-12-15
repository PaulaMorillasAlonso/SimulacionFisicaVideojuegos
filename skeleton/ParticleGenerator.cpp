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
    WindForceGenerator* wind = static_cast<WindForceGenerator*>(force);
    if (wind != nullptr) {
        windGen_ = wind;
        return -1;
    }
    WhirlwindForceGenerator* whirl = static_cast<WhirlwindForceGenerator*>(force);
    if (whirl != nullptr) {
        whirlWindGen_ = whirl;
        return -1;
    }
    ExplosionForceGenerator* exp = static_cast<ExplosionForceGenerator*>(force);
    if (exp != nullptr) {
        explosionGen_ = exp;
        return -1;
    }
    return 0;
}
std::vector<ForceGenerator*>ParticleGenerator::returnForce() {
    std::vector<ForceGenerator*>forceGen;
    if (gravGen_ != nullptr) {
        forceGen.push_back(gravGen_);
    }
    if (windGen_ != nullptr) {
        forceGen.push_back(windGen_);
    }
    if (whirlWindGen_ != nullptr) {
        forceGen.push_back(whirlWindGen_);
    }
    if (explosionGen_ != nullptr) {
        forceGen.push_back(explosionGen_);
    }
    return forceGen;
}