#include "Pecera.h"

Pecera::Pecera(Vector3 pos1, double mass,double k1, float restLenght, double radius)
{
	pez1_ = new Particle({ pos1.x,pos1.y,pos1.z }, { 0,0,0 }, { 0,0,0 }, 0.99, -1, { 0.29,0.43,0.99,1 }, 1, 4, -1);
	pez2_ = new Particle({ pos1.x+3,pos1.y,pos1.z }, { 0,0,0 }, { 0,0,0 }, 0.99, -1, { 1,0.5,0.29,1 }, 1, 1, -1);

	force1_ = new SpringForceGenerator(k1, restLenght, pez2_);
	force2_ = new SpringForceGenerator(k1, restLenght, pez1_);

	auto capsObj = CreateShape(physx::PxSphereGeometry(radius));
	auto esfera_ = new Particle({ pos1.x+2,pos1.y,pos1.z }, { 0,0,0 }, { 0,0,0 }, 0, -1, capsObj, { 0.69, 0.84, 0.98, 0.6 }, 1);
}

Pecera::~Pecera()
{
	delete pez1_;
	delete pez2_;
	delete force1_;
	delete force2_;
}
