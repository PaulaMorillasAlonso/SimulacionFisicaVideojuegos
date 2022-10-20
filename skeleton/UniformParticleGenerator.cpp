#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(double minPos, double maxPos,
    double minVel,double maxVel,double gen_prob, int numPart, double damping, double lifeTime, Vector4 colour)
{
    minPos_ = minPos;
    maxPos_ = maxPos;
    minVel_ = minVel;
    maxVel_ = maxVel;
    dist_pos = std::uniform_real_distribution<double>(minPos_, maxPos_);
    dist_vel = std::uniform_real_distribution<double>(minVel_, maxVel_);
    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
    _name = "UniformParticleGenerator";
    _generation_probability = gen_prob;
    _num_particles = numPart;
    damping_ = damping;
    lifeTime_ = lifeTime;
    colour_ = colour;


}
//UniformParticleGenerator::UniformParticleGenerator(double minPos, double maxPos,
//    double minVel, double maxVel, double gen_prob, int numPart, double damping, double lifeTime,
//    physx::PxShape* geomType, Vector4 colour)
//{
//    minPos_ = minPos;
//    maxPos_ = maxPos;
//    minVel_ = minVel;
//    maxVel_ = maxVel;
//    dist_pos = std::uniform_real_distribution<double>(minPos_, maxPos_);
//    dist_vel = std::uniform_real_distribution<double>(minVel_, maxVel_);
//    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
//    _name = "UniformParticleGenerator";
//    _generation_probability = gen_prob;
//    _num_particles = numPart;
//    damping_ = damping;
//    lifeTime_ = lifeTime;
//    colour_ = colour;
//    geomType_ = geomType;
//
//    pose = physx::PxTransform(minPos, minPos, minPos);
//    renderItem_ = new RenderItem(geomType_, &pose, colour_);
//
//}

std::vector<Particle*>UniformParticleGenerator::generateParticle()
{
    std::vector<Particle*> lista;

    for (int i = 0; i < _num_particles; i++) {

        int genProbRnd = gen_prob_dist(gen_);

        if (genProbRnd < _generation_probability) {


        Particle* p = new Particle({ 7,50,7 }, {0,0,0}, { 0,-10.0,0 }, damping_, lifeTime_, colour_);
        double newPosX = dist_pos(gen_);
        double newPosY = dist_pos(gen_);
        double newPosZ = dist_pos(gen_);
        p->setPos({(float) (p->getPos().x + newPosX),(float)(p->getPos().y + newPosY),(float) (p->getPos().z + newPosZ) });

        double newVelX = dist_vel(gen_);
        double newVelY = dist_vel(gen_);
        double newVelZ = dist_vel(gen_);
        p->setVel({ (float)(p->getVel().x + newVelX),(float)(p->getVel().y + newVelY),(float)(p->getVel().z + newVelZ) });

        
            lista.push_back(p);
        }
       
    }

    return lista;
}
