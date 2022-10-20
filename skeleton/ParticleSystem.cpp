#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	fuente_ = new UniformParticleGenerator(2,5, 1,2, 1, 10, 0.99, 1000, CreateShape(physx::PxSphereGeometry(1.0)), {0,0,1,1});
	_particle_generators.push_back(fuente_);
	
}
std::vector<Particle*> ParticleSystem::getParticleList()
{
	return _particles;
}
void ParticleSystem::update(double t)
{
	for (auto e : _particle_generators)
	{
		auto list = e->generateParticle();
		for (auto i : list)
		{
			_particles.push_back(i);
		}
	}
	
}

//ParticleGenerator* ParticleSystem::getParticleGenerator(std::string name)
//{
//
//	return nullptr;
//}

//void ParticleSystem::generateFireworkSystem()
//{
//}
