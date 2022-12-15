#pragma once
#include <list>
#include <random>
#include "core.hpp"
#include "RBParticle.h"
using namespace physx;
using namespace std;

class UniformRBGenerator
{
private:
	std::uniform_real_distribution<double> dist_pos;
	std::uniform_real_distribution<double> dist_vel;
	std::uniform_real_distribution<double> gen_prob_dist;
	std::default_random_engine gen_;
	double minPos_, maxPos_, minVel_, maxVel_, damping_, lifeTime_, mass_;
	Vector3 mean_pos_,mean_vel_,mean_acc,scale_;
	Vector4 colour_ = { 0,0,0,1 };
	float generation_probability_;
	int num_particles_;
	PxScene* scene_;
	PxPhysics* gPhysics_;
	bool isDynamic_;
public:
	UniformRBGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 meanAcc, double minPos, double maxPos, double minVel, double maxVel, double gen_prob,
		int numPart, double damping, double lifeTime, Vector4 colour, Vector3 scale, double mass,PxScene* scene, PxPhysics* gPhysics,bool isDynamic);
	std::list<RBParticle*>generateRB();
};

