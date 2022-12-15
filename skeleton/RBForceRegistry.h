#pragma once
#include <map>
#include "RBForceRegistry.h"
#include "ForceGenerator.h"


typedef std::pair< ForceGenerator*, PxRigidDynamic*> FRPairRB;

class RBForceRegistry :public std::multimap< ForceGenerator*, PxRigidDynamic*>
{
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForceRB(it->second, duration);
		}
	}
	void addRegistry(ForceGenerator* fg, PxRigidDynamic *p) {
		insert({ fg, p });

	}
	void deleteParticleRegistry(PxRigidDynamic* p) {
		for (auto it = begin(); it != end(); ) {
			if (it->second == p) {
				it = erase(it);
			}
			else it++;
		}
	}
	void deleteForce() {
		for (auto it = begin(); it != end(); ) {
			it = erase(it);
		}
	}
};