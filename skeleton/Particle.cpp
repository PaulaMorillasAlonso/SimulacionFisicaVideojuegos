#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc , double Damping)
{
	vel = Vel;
	acc = Acc;
	damping = Damping;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	rendeItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.5,0,0.5,1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(rendeItem);
}

void Particle::integrate(double t)
{
	//MRU
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
	vel += acc * t;
	vel *= pow(damping, t);

}
