#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(double minPos, double maxPos,double minVel,double maxVel)
{
    minPos_ = minPos;
    maxPos_ = maxPos;
    minVel_ = minVel;
    maxVel_ = maxVel;
    dist_pos = std::uniform_real_distribution<double>(minPos_, maxPos_);
    dist_vel = std::uniform_real_distribution<double>(minVel_, maxVel_);
    numParticles = 7;
}

std::list<Particle*> UniformParticleGenerator::generateParticle()
{
    std::list<Particle*> lista;
    for (int i = 0; i < numParticles; i++) {
        Particle* p = new Particle();
        auto newPosX = dist_pos(gen_);
        auto newPosY = dist_pos(gen_);
        auto newPosZ = dist_pos(gen_);
        p->setPos({(float) (p->getPos().x+newPosX), (float)(p->getPos().y+newPosY), (float)(p->getPos().z+newPosZ) });
        
        auto newVelX = dist_vel(gen_);
        auto newVelY = dist_vel(gen_);
        auto newVelZ = dist_vel(gen_);
        p->setVel({ (float)(p->getVel().x + newVelX), (float)(p->getVel().y + newVelY), (float)(p->getVel().z + newVelZ) });

        lista.push_back(p);
    }

    return lista;
}
