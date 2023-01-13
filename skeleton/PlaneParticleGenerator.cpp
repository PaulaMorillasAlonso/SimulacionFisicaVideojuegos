#include "PlaneParticleGenerator.h"
PlaneParticleGenerator::PlaneParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, int numPart,
    double damping, double lifeTime, Vector4 colour, double scale, double mass):pos_(meanPos),vel_(meanVel),acc_(meanAcc),damping_(damping),lifeTime_(lifeTime),colour_(colour),scale_(scale),mass_(mass)
{
    _name = "PlaneParticleGenerator";
    _num_particles = numPart;
    lista = std::list<Particle*>();
    for (float i = -_num_particles; i < _num_particles; i += 3) {
        for (float j = -_num_particles; j < _num_particles; j += 3) {

            Particle* p = new Particle(pos_, vel_, acc_, damping_, lifeTime_, colour_, scale_, mass_,-1);
            p->setPos({ p->getPos().x + i,p->getPos().y+j,p->getPos().z });
            lista.push_back(p);
        }
    }
}
std::list<Particle*>PlaneParticleGenerator::generateParticle()
{
    return lista;
}