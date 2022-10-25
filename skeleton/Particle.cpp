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
	iniTime_ = glutGet(GLUT_ELAPSED_TIME);
}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, double lifeTime, Vector4 colour, double scale)
{
	vel = Vel;
	acc = Acc;
	damping = Damping;
	lifeTime_ = lifeTime;
	colour_ = colour;
	scale_ = scale;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(scale_)), &pose, colour_);
	alive_ = true;
	iniTime_ = glutGet(GLUT_ELAPSED_TIME);
}
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, double lifeTime, physx::PxShape* geomType, Vector4 colour)
{
	vel = Vel;
	acc = Acc;
	damping = Damping;
	lifeTime_ = lifeTime;
	colour_ = colour;
	pose = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(geomType, &pose, colour_);
	alive_ = true;
	iniTime_ = glutGet(GLUT_ELAPSED_TIME);

}

Particle::~Particle()
{
	
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	//MRU
	//if (inverse_mass <= 0.0f) return;

	//EULER
	pose = physx::PxTransform(pose.p.x + vel.x * t, pose.p.y + vel.y * t, pose.p.z + vel.z * t);
	vel += acc * t;
	vel *= powf(damping, t);

	double actualTime = glutGet(GLUT_ELAPSED_TIME);
	if ( actualTime-iniTime_>=lifeTime_|| pose.p.y <= 0 || pose.p.y>=100) {

		alive_ = false;
	}
}

Particle* Particle::clone() const
{
	return nullptr;
}
