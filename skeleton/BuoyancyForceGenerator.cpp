#include "BuoyancyForceGenerator.h"
BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, Vector3 &pos):height(h),volume(V),liquid_density(d)
{
	_liquid_particle = new Particle(pos, { 0,0,0 }, { 0,0,0 }, 1, -1, {0,0,1,0.9}, 8 , 4);
}
void BuoyancyForceGenerator::updateForce(Particle* p, double t) {

	float h = p->getPos().y;
	float h0 = _liquid_particle->getPos().y;
	Vector3 f(0, 0, 0);
	float immersed = 0.0;

	if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5){
		//Totally immersed
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}
	
	f.y = liquid_density * volume * immersed * 9.8;
	p->addForce(f);
	
}