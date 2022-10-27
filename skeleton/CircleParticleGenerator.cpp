#include "CircleParticleGenerator.h"
CircleParticleGenerator::CircleParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, Vector3 dev_pos,
    Vector3 dev_vel, double gen_prob, int numPart, double damping, double lifeTime, Vector4 colour, double scale)
{
    _mean_pos = meanPos;
    _mean_vel = meanVel;
    mean_acc = meanAcc;
    std_dev_pos = dev_pos;
    std_dev_vel = dev_vel;
    dist_pos = std::normal_distribution<double>(0, 1);
    dist_vel = std::normal_distribution<double>(0, 1);
    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
    _name = "CircleParticleGenerator";
    _generation_probability = gen_prob;
    _num_particles = numPart;
    damping_ = damping;
    lifeTime_ = lifeTime;
    colour_ = colour;
    scale_ = scale;
    radius_ = 10;
}

std::list<Particle*> CircleParticleGenerator::generateParticle()
{
    std::list<Particle*> lista;

    float angle = 0;
    for (int i = 0; i < _num_particles; i++) {

        int genProbRnd = gen_prob_dist(gen_);

        if (genProbRnd < _generation_probability) {

            Particle* p = new Particle({ _mean_pos.x,_mean_pos.y,_mean_pos.z }, { _mean_vel.x,_mean_vel.y,_mean_vel.z }, mean_acc, damping_, lifeTime_, colour_, scale_);

            angle = 360 / _num_particles * i;

            Vector3 pos(cos(angle * (std::_Pi / 180)) * radius_, std::sin(angle * (std::_Pi/ 180)) * radius_, 0);
            Vector3 vel = Vector3(cos(angle * (std::_Pi / 180)), sin(angle * (std::_Pi / 180)), 0);

            p->setVel({ vel.x * _mean_vel.x,vel.y * _mean_vel.y,vel.z * _mean_vel.z });
            p->setPos(pos);

            lista.push_back(p);
        }   
    }
    return lista;
}