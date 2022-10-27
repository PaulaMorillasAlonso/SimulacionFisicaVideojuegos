#include "SphereParticleGenerator.h"
SphereParticleGenerator::SphereParticleGenerator(Vector3 meanVel, double gen_prob, double radius, double numPart)
{
    gen_prob_dist = std::uniform_real_distribution<double>(0, 1);
    _mean_vel = meanVel;
    _name = "SphereParticleGenerator";
    radius_ = radius;
    _generation_probability = gen_prob;
    _num_particles = numPart;

}

std::list<Particle*> SphereParticleGenerator::generateParticle()
{
    std::list<Particle*> lista;
    std::random_device rd{};
    std::default_random_engine gen_(rd());

    std::uniform_real_distribution<> rand(0,1);

    for (int i = 0; i < _num_particles; i++) {

        int genProbRnd = gen_prob_dist(gen_);

        double alpha = 0, beta = 0;
        if (genProbRnd < _generation_probability) {

            Particle* p;

            p = clone();

            alpha = 2 *std::_Pi * rand(gen_);
            beta = acos(2 * rand(gen_) - 1.0);

            Vector3 vel({ (float ) (std::cos(alpha) * std::sin(beta)),
                            (float) (std::sin(alpha) * std::sin(beta)),
                            (float) (std::cos(beta))});
           
            p->setVel(vel);
            p->setPos(_mean_pos);

            lista.push_back(p);
        }
    }
    return lista;
}