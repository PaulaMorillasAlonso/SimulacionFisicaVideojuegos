#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	fuente_ = new UniformParticleGenerator({7,50,7}, {0,0,0}, 2, 5, 1, 2, 1, 1, 0.99, 5000, { 0,0,1,1 });
	_particle_generators.push_back(fuente_);
	
}
std::vector<Particle*> ParticleSystem::getParticleList()
{
	return _particles;
}
void ParticleSystem::update(double t)
{
	
	for (int i = 0; i < _particles.size(); i++)
	{
		if (_particles[i]->isAlive()) {
			_particles[i]->integrate(t);
		}
		else {
			delete _particles[i];
			_particles.erase(_particles.begin() + i);
			--i;
		}
	}

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
