#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	forceReg_ = new ParticleForceRegistry();
	//creaFuente();
	
	/*humo_ = new GaussianParticleGenerator({ 7,50,7 }, { 5,5,2 }, { 0,2,0 }, {4, 4, 0}, { 2,2,0 }, 1, 1, 0.99, 3000, { 0.8,0.8,0.8,1 },0.8);
	_particle_generators.push_back(humo_);*/
	createFireworkRules();
}

void ParticleSystem::creaFuente()
{
	gravGen_= new GravityForceGenerator({ 0,-10.0,0 });
	fuente_ = new UniformParticleGenerator({ 7,50,7 }, { 0,0,0 }, { 0,1.0,0 }, 2, 5, 1, 2, 1, 1, 0.99, 5000, { 0,0,1,1 }, 1.0,1);
	fuente_->addForceGenerator(gravGen_);
	_particle_generators.push_back(fuente_);
}

ParticleSystem::~ParticleSystem()
{
	for (auto gens : _particle_generators) {
		delete gens;
	}
	for (auto p :_particles) {
		delete p;
	}

	forceReg_->deleteForce();
	delete forceReg_;
}

Vector4 ParticleSystem::randomColour()
{
	std::random_device rd;
	std::default_random_engine gen_(rd());
	std::uniform_real_distribution<> distr(0, 1); // define the range
	Vector4 col;

	col.x = distr(gen_);
	col.y = distr(gen_);
	col.z = distr(gen_);
	col.w = 1.0;
	return col;
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
			forceReg_->deleteParticleRegistry(p);
			delete p;
		}
	}
	
	for (auto e : _particle_generators)
	{
		auto list = e->generateParticle();
		std::vector<GravityForceGenerator*> force = e->returnForce();
		for (auto i : list)
		{
			_particles.push_back(i);

			for (auto s : force) {
				GravityForceGenerator* grav = s;
				if (grav != nullptr) {
					forceReg_->addRegistry(grav, i);
				}
			}
		}

	}
	forceReg_->updateForces(t);
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
	firework_rules_ = std::vector<FireworkRule>(3);

	firework_rules_[0].set({ 7,50,7 }, { 10,10,1 }, { 0,8.0,0 }, 0.99, 1000, randomColour(), 0.4, 40,1, 0); //Fuego básico, sube y explota
	firework_rules_[1].set({ 10,40,10 }, { 10,10,0 }, { 0,8.0,0 }, 0.99, 2000, {0.1,0.9,0.9,1}, 0.4, 50,1, 1); //Fuego circular
	firework_rules_[2].set({ 15,60,15 }, { 10,10,0 }, { 0,8.0,0 }, 0.99, 1000, {0.9,0.1,0.47,1}, 0.4, 60,1, 2); //Fuego esfera

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
			{ 0,-2,0 }, { 40, 40, 0 }, { 20,10,0 }, 1, firework_rules_[type].payload_, firework_rules_[type].damping_, firework_rules_[type].lifeTime_,
			randomColour(), firework_rules_[type].size_,firework_rules_[type].mass_));
		break;
	case 1:
		 g=std::shared_ptr<ParticleGenerator>(new CircleParticleGenerator({4,4,0},1,15,firework_rules_[type].payload_));
		break;
	case 2:
		g = std::shared_ptr<ParticleGenerator>(new SphereParticleGenerator({ 20,20,0 }, 1, 15, firework_rules_[type].payload_));
		break;

	}
	
	Firework* p = new Firework(firework_rules_[type],g);
	g->setParticle(p);
	_particles.push_back(p);
}


