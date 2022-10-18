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
        p->setPos({ p->getPos().x+newPosX, p->getPos().y+newPosY, p->getPos().z+newPosZ });
      
        //p->setVelocity();
    }



    return lista;
}
