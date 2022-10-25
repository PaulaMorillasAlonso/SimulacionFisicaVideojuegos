#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 meanPos,Vector3 meanVel,Vector3 meanAcc,double minPos, double maxPos,
    double minVel,double maxVel,double gen_prob, int numPart, double damping, double lifeTime, Vector4 colour)
{
    _mean_pos = meanPos;
    _mean_vel = meanVel;
    mean_acc = meanAcc;
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

std::list<Particle*>UniformParticleGenerator::generateParticle()
{
    std::list<Particle*> lista;

    for (int i = 0; i < _num_particles; i++) {

        int genProbRnd = gen_prob_dist(gen_);

        if (genProbRnd < _generation_probability) {


        Particle* p = new Particle({ _mean_pos.x,_mean_pos.y,_mean_pos.z }, {_mean_pos.x,_mean_pos.y,_mean_vel.z}, mean_acc, damping_, lifeTime_, colour_);
        double newPosX = dist_pos(gen_);
        double newPosY = dist_pos(gen_);
        double newPosZ = dist_pos(gen_);
        p->setPos({(float) (_mean_pos.x + newPosX),(float)(_mean_pos.y + newPosY),(float) (_mean_pos.z + newPosZ) });

        double newVelX = dist_vel(gen_);
        double newVelY = dist_vel(gen_);
        double newVelZ = dist_vel(gen_);
        p->setVel({ (float)(_mean_vel.x + newVelX),(float)(_mean_vel.y + newVelY),(float)(_mean_vel.z + newVelZ) });

        
            lista.push_back(p);
        }
       
    }

    return lista;
}
