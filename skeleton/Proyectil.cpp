#include "Proyectil.h"
Proyectil::Proyectil(types tipo, Vector3 pos, Vector3 dir) :Particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, 1)
{
	tipo_ = tipo;
	setPos(pos);
	auto vel = getVel();
	switch (tipo) {
	case BULLET:
		vel = dir * 35;
		setVelocity(vel);
		setAcceleration({ 0,-1,0 }); 
		setDamping(0.99f);
		break;
	case CANNON:
		vel= dir * 40;
		setVelocity(vel);
		setAcceleration({ 0,-20,0 });
		setDamping(0.99f);
		break;
	case FIREBALL:
		vel = dir * 10;
		setVelocity(vel);
		setAcceleration({ 0,0.6,0 });
		setDamping(0.9f);
		break;
	case LASER:
		vel = dir * 100;
		setVelocity(vel);
		setAcceleration({ 0,0,0 });
		setDamping(0.99f);
		break;
	}
}
Proyectil::Proyectil(types tipo, Vector3 pos, Vector3 dir, Vector4 color) :Particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, 1, color)
{
	tipo_ = tipo;
	setPos(pos);
	auto vel = getVel();
	switch (tipo) {
	case BULLET:
		vel = dir * 35;
		setVelocity(vel);
		setAcceleration({ 0,-1,0 });
		setDamping(0.99f);
		break;
	case CANNON:
		vel = dir * 40;
		setVelocity(vel);
		setAcceleration({ 0,-20,0 });
		setDamping(0.99f);
		break;
	case FIREBALL:
		vel = dir * 10;
		setVelocity(vel);
		setAcceleration({ 0,0.6,0 });
		setDamping(0.9f);
		break;
	case LASER:
		vel = dir * 100;
		setVelocity(vel);
		setAcceleration({ 0,0,0 });
		setDamping(0.99f);
		break;
	}
}

Proyectil::~Proyectil()
{
}
