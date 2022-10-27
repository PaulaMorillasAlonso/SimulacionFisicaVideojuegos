#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	/*fuente_ = new UniformParticleGenerator({ 7,50,7 }, { 0,0,0 }, {0,-10.0,0}, 2, 5, 1, 2, 1, 1, 0.99, 5000, { 0,0,1,1 },1.0);
	_particle_generators.push_back(fuente_);*/
	
	/*humo_ = new GaussianParticleGenerator({ 7,50,7 }, { 7,7,2 }, { 0,2,0 }, {4, 4, 0}, { 2,2,0 }, 1, 1, 0.99, 3000, { 0.8,0.8,0.8,1 });
	_particle_generators.push_back(humo_);*/
	createFireworkRules();
	generateFireworkSystem(0);
	generateFireworkSystem(1);
}

void ParticleSystem::update(double t)
{
	std::list<Particle*>::iterator it = _particles.begin();

	while (it != _particles.end()) {
		Particle* p = *it;
		if (p->isAlive()) {
			p->integrate(t);
			++it;
		}
		else {
			if (p->isFirework()) {
				auto part=p->explode();
				for (auto a : part) {
					_particles.push_back(a);
				}
				
			}
			it = _particles.erase(it);
			delete p;
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

ParticleGenerator* ParticleSystem::getParticleGenerator(std::string name)
{
	for (auto e : _particle_generators) {

		if (name == e->getGeneratorName()) return e;
	}
	return nullptr;
}

void ParticleSystem::createFireworkRules()
{
	firework_rules_ = std::vector<FireworkRule>(2);
	firework_rules_[0].set({ 7,50,7 }, { 2,2,0 }, { 0,4.0,0 }, 0.99, 3000, { 0,1,1,1 }, 1.0, 10, 0); //Fuego básico, sube y explota
	firework_rules_[1].set({ 10,40,10 }, { 2,2,0 }, { 0,4.0,0 }, 0.99, 3000, {1,0.08,0.6,1},1.0,10,1); //Fuego circular

}
void ParticleSystem::generateFireworkSystem(unsigned type)
{
	if (type >= firework_rules_.size()) {
		return;
	}

	std::shared_ptr<ParticleGenerator> g;
	switch (type) {
	case 0:
		g = std::shared_ptr<ParticleGenerator>(new GaussianParticleGenerator(firework_rules_[type].pos_, firework_rules_[type].vel_,
			{ 0,-2,0 }, { 20, 20, 0 }, { 10,10,0 }, 1, firework_rules_[type].payload_, firework_rules_[type].damping_, firework_rules_[type].lifeTime_,
			firework_rules_[type].colour_, firework_rules_[type].size_));
		break;
	case 1:
		 g=std::shared_ptr<ParticleGenerator>(new CircleParticleGenerator({4,4,0},1,15));
		break;
	}
	
	Firework* p = new Firework(firework_rules_[type],g);
	g->setParticle(p);
	_particles.push_back(p);
}
