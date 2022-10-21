#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(double minPos, double maxPos, double minVel, double maxVel, double gen_prob,
    int numPart, double damping, double lifeTime, Vector4 colour)
{
    minPos_ = minPos;
    maxPos_ = maxPos;
    minVel_ = minVel;
    maxVel_ = maxVel;
    dist_pos = std::normal_distribution<double>(minPos_, maxPos_);
    dist_vel = std::normal_distribution<double>(minVel_, maxVel_);
    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
    _name = "GaussianParticleGenerator";
    _generation_probability = gen_prob;
    _num_particles = numPart;
    damping_ = damping;
    lifeTime_ = lifeTime;
    colour_ = colour;
}

std::vector<Particle*> GaussianParticleGenerator::generateParticle()
{
    std::vector<Particle*> lista;
	return lista ;
}
