#pragma once
#include "SpringForceGenerator.h"
using namespace std;
class ParticleBungee : public SpringForceGenerator
{
public:
     ParticleBungee(double k, double resting, Particle* other);
     ~ParticleBungee() { delete other_; };
     virtual void updateForce(Particle* particle, double t);

};

