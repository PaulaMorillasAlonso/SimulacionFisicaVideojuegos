#include "Firework.h"

//Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, double lifeTime, Vector4 colour, 
//	double size, int payload, std::shared_ptr<ParticleGenerator> gens):
//
//	Particle(Pos,Vel,Acc,damping,lifeTime,colour,size)
//{
//	payload_ = payload;
//	gens_.push_back(gens);
//}
Firework::Firework(FireworkRule rules,ParticleGenerator* gen):Particle(rules.pos_,rules.vel_,rules.acc_,rules.damping_,rules.lifeTime_,rules.colour_,rules.size_,rules.mass_,-1) {
	payload_ = rules.payload_;
	type_ = rules.type_;
	gens_.push_back(gen);
}

std::list<Particle*> Firework::explode()
{
	auto list=std::list<Particle*>();
		for (auto e : gens_)
		{
			auto res = e->generateParticle();
			for (auto e : res) {
				e->setPos(pose.p);
				list.push_back(e);
			}
		}

	return list;
}

