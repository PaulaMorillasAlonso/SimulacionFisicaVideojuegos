#pragma once
#include "Particle.h"
#include "SpringForceGenerator.h"
class Pecera
{
	Particle* pez1_;
	Particle* pez2_;
	SpringForceGenerator* force1_;
	SpringForceGenerator* force2_;

public:
	Pecera(Vector3 pos1, double mass, double k1, float restLenght, double radius);
	~Pecera();
	Particle* getPez1() { return pez1_; }
	Particle* getPez2() { return pez2_; }
	SpringForceGenerator* getForce1() { return force1_; }
	SpringForceGenerator* getForce2() { return force2_; }


};

