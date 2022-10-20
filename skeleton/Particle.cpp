#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc , double Damping, double lifeTime)
{
	vel = Vel;
	acc = Acc;
	damping = Damping;
	lifeTime_ = lifeTime;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.5,0,0.5,1 });
	alive_ = true;
}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, double lifeTime, Vector4 colour)
{
	vel = Vel;
	acc = Acc;
	damping = Damping;
	lifeTime_ = lifeTime;
	colour_ = colour;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, colour_);
	alive_ = true;

}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, double lifeTime, physx::PxShape* geomType, Vector4 colour)
{
	vel = Vel;
	acc = Acc;
	damping = Damping;
	lifeTime_ = glutGet(GLUT_ELAPSED_TIME) + lifeTime;
	colour_ = colour;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(geomType, &pose, colour_);
	alive_ = true;

}

Particle::~Particle()
{
	//if(rendeItem!=NULL)
	//DeregisterRenderItem(rendeItem);
}

void Particle::integrate(double t)
{
	//MRU
	//if (inverse_mass <= 0.0f) return;

	if (glutGet(GLUT_ELAPSED_TIME) >= lifeTime_ || pose.p.y <= -100) {

		alive_ = false;
	}
	//EULER
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
	vel += acc * t;
	vel *= powf(damping, t);

}
