#pragma once
#include "Particle.h"
#include <list>
struct FireworkRule {

} rules;
class Firework : public Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, Vector4 colour);
	~Firework() {};
	bool update(double t);
	virtual Particle* clone() const;
	std::list<Particle*> explode();
private:
	//std::list<std::shared_ptr<Particle>> gens_;
};

