#pragma once
#include "Particle.h"
class Proyectil:public Particle
{
public:
	enum types { BULLET, CANNON, FIREBALL, LASER };
	Proyectil(types tipo, Vector3 pos, Vector3 dir);
	~Proyectil();

private:
	types tipo_;

};

