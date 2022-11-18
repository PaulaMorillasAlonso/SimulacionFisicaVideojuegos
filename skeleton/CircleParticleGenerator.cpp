#include "CircleParticleGenerator.h"
CircleParticleGenerator::CircleParticleGenerator(Vector3 pos,Vector3 meanVel,double gen_prob,double radius,double numPart)
{
    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
    _mean_vel = meanVel;
    _name = "CircleParticleGenerator";
    radius_ = radius;
    _generation_probability = gen_prob;
    _num_particles = numPart;
    setParticle(new Particle(pos, meanVel, { 0,0,0 }, 0.99, 5000, {1,0,0,1},1,1));
}

std::list<Particle*> CircleParticleGenerator::generateParticle()
{
    std::list<Particle*> lista;

    float angle = 0;
    for (int i = 0; i < _num_particles; i++) {

        int genProbRnd = gen_prob_dist(gen_);

        if (genProbRnd < _generation_probability) {

            Particle* p;
            
            p = clone();
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