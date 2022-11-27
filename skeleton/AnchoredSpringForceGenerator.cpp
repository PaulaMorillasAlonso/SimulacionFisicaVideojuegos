#include "AnchoredSpringForceGenerator.h"
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos) :
	SpringForceGenerator(k, resting, nullptr) {

	auto cube = CreateShape(physx::PxBoxGeometry(4, 2, 4));
	other_= new Particle(anchor_pos, { 0,0,0 }, { 0,0,0 }, 1, -1, cube, { 0,1,0,1 }, 1);
}
AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {

	delete other_;
}