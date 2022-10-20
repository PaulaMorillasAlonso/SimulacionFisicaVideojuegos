#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(double minPos, double maxPos, double minVel, double maxVel)
{
    minPos_ = minPos;
    maxPos_ = maxPos;
    minVel_ = minVel;
    maxVel_ = maxVel;
    numParticles = 7;
}

std::vector<Particle*> GaussianParticleGenerator::generateParticle()
{
    std::vector<Particle*> lista;
	return lista ;
}
