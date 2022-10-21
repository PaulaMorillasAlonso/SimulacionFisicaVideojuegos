#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 dev_pos, 
    Vector3 dev_vel, double gen_prob, int numPart, double damping, double lifeTime, Vector4 colour)
{
    _mean_pos = meanPos;
    _mean_vel = meanVel;
    std_dev_pos = dev_pos;
    std_dev_vel = dev_vel;
    dist_pos = std::normal_distribution<double>(0, 1);
    dist_vel = std::normal_distribution<double>(0, 1);
    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
    _name = "GaussianParticleGenerator";
    _generation_probability = gen_prob;
    _num_particles = numPart;
    damping_ = damping;
    lifeTime_ = lifeTime;
    colour_ = colour;
}

std::list<Particle*> GaussianParticleGenerator::generateParticle()
{
    std::list<Particle*> lista;
    for (int i = 0; i < _num_particles; i++) {

        int genProbRnd = gen_prob_dist(gen_);

        if (genProbRnd < _generation_probability) {


            Particle* p = new Particle({ _mean_pos.x,_mean_pos.y,_mean_pos.z }, { _mean_pos.x,_mean_pos.y,_mean_vel.z }, { 0,2.0,0 }, damping_, lifeTime_, colour_);
            double newPosX = dist_pos(gen_)*std_dev_pos.x;
            double newPosY = dist_pos(gen_)*std_dev_pos.y;
            double newPosZ = dist_pos(gen_)*std_dev_pos.z;
            p->setPos({ (float)(_mean_pos.x + newPosX),(float)(_mean_pos.y + newPosY),(float)(_mean_pos.z + newPosZ) });

            double newVelX = dist_vel(gen_)*std_dev_vel.x;
            double newVelY = dist_vel(gen_)*std_dev_vel.y;
            double newVelZ = dist_vel(gen_)*std_dev_vel.z;
            p->setVel({ (float)(_mean_vel.x + newVelX),(float)(_mean_vel.y + newVelY),(float)(_mean_vel.z + newVelZ) });


            lista.push_back(p);
        }
    }
	return lista;
}
