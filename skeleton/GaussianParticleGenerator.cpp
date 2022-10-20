#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(double minPos, double maxPos, double minVel, double maxVel)
{
    minPos_ = minPos;
    maxPos_ = maxPos;
    minVel_ = minVel;
    maxVel_ = maxVel;
    numParticles = 7;
}

std::list<Particle*> GaussianParticleGenerator::generateParticle()
{
    std::list<Particle*> lista;
	return lista ;
}
