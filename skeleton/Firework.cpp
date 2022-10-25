#include "Firework.h"

Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, Vector4 colour)
{
}

bool Firework::update(double t)
{
	return false;
}

Particle* Firework::clone() const
{
	return nullptr;
}

std::list<Particle*> Firework::explode()
{
	return std::list<Particle*>();
}
