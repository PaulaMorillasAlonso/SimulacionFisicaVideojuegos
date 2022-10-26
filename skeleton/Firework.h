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
	/*
	float minAge_;
	float maxAge_;
	Vector3 minVelocity_;
	Vector3 maxVelocity_;
	float damping_;*/
	/*, float minAge, float maxAge, Vector3 minVelocity, Vector3 maxVelocity, float damping*/
	/*	minAge_ = minAge;
			maxAge_ = maxAge;
			minVelocity_ = minVelocity;
			maxVelocity_ = maxVelocity;
			damping_ = damping;*/

	void set(Vector3 pos,Vector3 vel,Vector3 acc,double damping,double lifeTime,
		Vector4 colour,double size,int payload, int type ) {
		type_ = type;
		pos_=pos;
		vel_=vel;
		acc_=acc;
		damping_=damping;
		lifeTime_=lifeTime;
		colour_=colour;
		size_=size;
		payload_=payload;
	}

};
class Firework : public Particle
{
public:

	//Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, Vector4 colour,
	//	double size, int payload, std::shared_ptr<ParticleGenerator> gens);
	Firework(FireworkRule rules, std::shared_ptr<ParticleGenerator> gen);
	~Firework() {};
	//virtual Particle* clone() const;
	std::list<Particle*> explode();
	//virtual void integrate(double t) override;
private:
	std::list<std::shared_ptr<ParticleGenerator>> gens_;
	int payload_;
	int totalExplosions_;
};

