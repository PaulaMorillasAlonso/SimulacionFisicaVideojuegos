#pragma once
#include "Particle.h"
#include <list>
#include <memory>
#include "ParticleGenerator.h"
struct FireworkRule {

	int type_;
	Vector3 pos_;
	Vector3 vel_;
	Vector3 acc_;
	double damping_;
	double lifeTime_;
	Vector4 colour_;
	double size_;
	int payload_;
	double mass_;

	void set(Vector3 pos,Vector3 vel,Vector3 acc,double damping,double lifeTime,
		Vector4 colour,double size,int payload, double mass,int type ) {
		type_ = type;
		pos_=pos;
		vel_=vel;
		acc_=acc;
		damping_=damping;
		lifeTime_=lifeTime;
		colour_=colour;
		size_=size;
		payload_=payload;
		mass_ = mass;
	}

};
class Firework : public Particle
{
public:

	//Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, Vector4 colour,
	//	double size, int payload, std::shared_ptr<ParticleGenerator> gens);
	Firework(FireworkRule rules, ParticleGenerator* gen);
	~Firework() {};
	//virtual Particle* clone() const;
	virtual std::list<Particle*> explode()override;
	//virtual void integrate(double t) override;
	std::list<ParticleGenerator*> getGenerators() { return gens_; };
private:
	std::list<ParticleGenerator*> gens_;
	int payload_;
};

