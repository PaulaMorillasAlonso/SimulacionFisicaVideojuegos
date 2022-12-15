//#pragma once
//#include <map>
//#include "RBForceRegistry.h"
//#include "RBForceGenerator.h"
//
//
//typedef std::pair< RBForceGenerator*, RBParticle*> FRPair;
//
//class RBForceRegistry :public std::multimap< RBForceGenerator*, RBParticle*>
//{
//public:
//	void updateForces(double duration) {
//		for (auto it = begin(); it != end(); it++) {
//			it->first->updateForce(it->second, duration);
//		}
//	}
//	void addRegistry(RBForceGenerator* fg, RBParticle* p) {
//		insert({ fg, p });
//
//	}
//	void deleteParticleRegistry(RBParticle* p) {
//		for (auto it = begin(); it != end(); ) {
//			if (it->second == p) {
//				it = erase(it);
//			}
//			else it++;
//		}
//	}
//	void deleteForce() {
//		for (auto it = begin(); it != end(); ) {
//			it = erase(it);
//		}
//	}
//};