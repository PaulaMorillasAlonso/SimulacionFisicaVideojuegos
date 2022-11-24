#pragma once
#include "./Particle.h"
#include <list>
#include <random>

class ForceGenerator
{
public: 
	virtual void updateForce(Particle* particle, double duration)=0;
	std::string _name;
	double t = -1e10; 
	enum forceTypes{NONE,GRAVITY,WIND, WHIRLWIND,EXPLOSION };
	forceTypes forceType=NONE;
	bool isActive = true;
	void deactivate() { isActive = false; }
	void activate() { isActive =true; }
protected:
	int type_;
};

